LIBFILE=thbrk.c
LIBOBJ=thbrk.o
INCLUDEPATH=-I../../include
CFLAGS=-O2 -Wall

all: cttex dict2state app

cttex: cttex.c map.o 
	gcc ${CFLAGS} ${INCLUDEPATH} -o cttex cttex.c map.o

map.o: map.c
	gcc  ${CFLAGS} ${INCLUDEPATH} -c map.c

${LIBOBJ}: thbrk.c 
	gcc ${CFLAGS} ${INCLUDEPATH} -c ${LIBFILE} 

dict2state: dict2state.c
	gcc  ${CFLAGS} ${INCLUDEPATH} -o dict2state dict2state.c

map.c: tdict.txt dict2state
	./dict2state

app: test_thbrk.c ${LIBOBJ}
	gcc ${CFLAGS} ${INCLUDEPATH} -o test_thbrk ${LIBOBJ} test_thbrk.c map.o

clean: 
	rm -f cttex test_thbrk map.c map.h *~ *.o dict2state

