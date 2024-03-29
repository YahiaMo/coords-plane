program: coordsptr.o dynamiclist.o grid.o coords.o
	gcc coordsptr.o dynamiclist.o grid.o coords.o -o program

coordsptr.o: coordsptr.c
	gcc coordsptr.c -c -Wall -Wextra -Wvla

dynamiclist.o: dynamiclist.c dynamiclist.h
	gcc dynamiclist.c -c -Wall -Wextra -Wvla

grid.o: grid.c grid.h
	gcc grid.c -c -Wall -Wextra -Wvla

coords.o: coords.c coords.h
	gcc coords.c -c -Wall -Wextra -Wvla

clean:
	rm *.o