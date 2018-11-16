TARGETS=libinstrument_functions.so controller

all:${TARGETS}


libinstrument_functions.so:libinstrument_functions.o
	${CC} -shared libinstrument_functions.o -o libinstrument_functions.so -O2 -lrt

libinstrument_functions.o:libinstrument_functions.h libinstrument_functions.c
	${CC} libinstrument_functions.c -O2 -fPIC -c -o libinstrument_functions.o

controller:controller.c libinstrument_functions.h
	${CC} controller.c -O2 -o controller -L. -linstrument_functions

clean:
	rm ${TARGETS} *.o
