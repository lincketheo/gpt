
all: main

example: main
	./main shakespeare.txt out.txt w 10

example-gdb: main
	gdb --args ./main shakespeare.txt out.txt w 10

example-vg: main
	valgrind -- ./main shakespeare.txt out.txt w 10

main:
	gcc -o $@ main.c base.c -g

clean:
	rm -f main
