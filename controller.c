/*
 * libinstrument-functions
 * Copyright © 2018 yiifburj
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libinstrument_functions.h"
#include <errno.h>
#include <getopt.h>

/* TODO:
 * support thread time upgrade network */

int main(int argc, char *argv[])
{
	int turn_on = -1;

#define input_error() do{fprintf(stderr, "input error\n");exit(1);}while(0)
	while(1){
		static struct option long_options[]=
		{
			{"on", required_argument, 0, 1},
			{"off", required_argument, 0, 0},
		};

		int c = getopt_long(argc, argv,"", long_options, NULL);
		if(c == -1)
			break;
		switch (c) {
			case 1:
				if(turn_on != -1)
					input_error();
				turn_on = 1;
				break;
			case 0:
				if(turn_on != -1)
					input_error();
				turn_on = 0;
				break;
			default:
					input_error();
		}
	}

	int idx;
	if((idx=get_process_idx(argv[optind])) < 0)
	{
		fprintf(stderr, "not controller\n");
		exit(1);
	}

	int shm_size;
	char *controller_map = get_map_addr_size(PROT_READ|PROT_WRITE, &shm_size);

	int old = controller_map[idx];
	if(turn_on == 1){
		switch(old)
		{
			case TO_OFF:
				fprintf(stderr, "in closing\n");
				exit(1);
			case ON:
				break;
			case OFF:
				if(!__sync_bool_compare_and_swap(controller_map+idx,OFF, ON))
				{
					fprintf(stderr, "conflict, try again\n");
					exit(1);
				}
			default:
				fprintf(stderr, "memory is corrupted!\n");
				exit(1);
		}
	}
	else if(turn_on == 0)
	{
		switch(old)
		{
			case TO_OFF:
				fprintf(stderr, "in closing\n");
				exit(1);
			case OFF:
				break;
			case ON:
				if(!__sync_bool_compare_and_swap(controller_map+idx,ON, OFF))
				{
					fprintf(stderr, "conflict, try again\n");
					exit(1);
				}
			default:
				fprintf(stderr, "memory is corrupted!\n");
				exit(1);
		}
	}


	munmap(controller_map, shm_size);
	return 0;
}

