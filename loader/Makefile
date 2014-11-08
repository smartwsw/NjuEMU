CC = gcc
CFLAGS = -m32 -O2 -Wall -Werror -fno-builtin -I./include
# "myloader/include" to search for header files.
ASFLAGS = -m32

CSRC = $(shell find src/ -name "*.c")  # TODO: Find all .c files under the "myloader/src" directory.

OBJS = $(CFILES:.c=.o)  # TODO: Convert the suffix of all string in $(CSRC) into ".o".

loader: $(OBJS) src/start.o  # TODO: Add prerequisites for creating the loader.
	ld -o loader -e start -Ttext 0x100000 -m elf_i386 src/start.o $(OBJS)

clean:
	-rm -f loader src/start.o $(OBJS) 2> /dev/null  # TODO: Add command to remove all compile results.
