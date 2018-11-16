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

#ifndef INSTRUMENT_FUNCTIONS_PUBLIC_H
#define INSTRUMENT_FUNCTIONS_PUBLIC_H



enum controller_state
{
	OFF,
	ON,
	TO_OFF,
};


int get_process_idx(const char *name);
char * get_map_addr(int prot);


#endif
