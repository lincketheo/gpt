TARGETS=$(wildcard apps/*.c)
SRCS=$(wildcard src/*.c)
CFLAGS=-Iinclude -Wall -Wextra -Werror -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -std=c99

all: embedding_init

embedding_init: $(SRCS)
	gcc -o $@ apps/embedding_init.c $(SRCS) -g -Iinclude $(CFLAGS)

clean:
	rm -f embedding_init
