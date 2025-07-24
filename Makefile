# Source files
SRCS = memory_alloc.c \
       mem_interface.c \
       utils.c 

# Object files
OBJS = $(patsubst %.c, %.o, $(SRCS))

# Headers
HEADERS = memory_alloc.h

# Compiler
CC = cc

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Name of the static library
LIB_ARCH_NAME = libft_alloc_$(HOSTTYPE).so
LIB_NAME = libft_alloc.so

# Default target
all: $(LIB_ARCH_NAME)

# Rule to create the static library
$(LIB_ARCH_NAME): $(OBJS)
	$(CC) -shared -o $(LIB_ARCH_NAME) $(OBJS)
	ln -sf $(LIB_ARCH_NAME) $(LIB_NAME)

# Rule to compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS)
	rm -f test

fclean: clean
	rm -f $(LIB_NAME) $(LIB_ARCH_NAME)

main:
	$(CC) -o test -L. -lft_alloc -g main.c


# Rebuild the library
re: clean all main
