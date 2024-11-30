all: compiler

compiler: compiler.c
	$(CC) -o $@ $^
