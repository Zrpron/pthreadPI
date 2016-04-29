clean:
	rm *.c~ *.c# Makefile~ pthreadPI
all:
	gcc -o pthreadPI pthreadPI.c -lm -pthread
run:
	./pthreadPI
