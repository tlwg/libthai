all: dictsort
	./dictsort

dictsort: dictsort.c tdict.nonsorted
	gcc -O2 -o dictsort dictsort.c

tdict.nonsorted: tdict.org tdict.local
	cat tdict.org tdict.local > tdict.nonsorted

clean: 
	rm -f dictsort dict2state map.c map.h *~ *.o \
	tdict.nonsorted tdict.txt

