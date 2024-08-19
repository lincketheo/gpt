
all: embedding_init

embedding_init:
	gcc -o $@ apps/embedding_init.c src/*.c -g -I include

clean:
	rm -f embedding_init
