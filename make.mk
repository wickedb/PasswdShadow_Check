make: support1.o support2.o source_prog.o
	gcc -o make support1.o support2.o source_prog.o

support1.o: support1.c source_prog.h
	gcc -c support1.c
support2.o: support2.c source_prog.h
	gcc -c support2.c

source_prog.o: source_prog.c source_prog.h
	gcc -c source_prog.c
