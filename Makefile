
all: phase.c
	gcc -g -Wall -o phase phase.c

clean:
	$(RM) phase