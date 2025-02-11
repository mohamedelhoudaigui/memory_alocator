# Source files
SRCS = memory_alloc.c \
       mem_interface.c \
       utils.c \
       tests.c

# Object files
OBJS = $(patsubst %.c, %.o, $(SRCS))

# Headers
HEADERS = memory_alloc.h

# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c11 -g -O3 -fsanitize=address -D_GNU_SOURCE

# Name of the static library
LIB_NAME = libm_alloc.a

# Default target
all: $(LIB_NAME)

# Rule to create the static library
$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

# Rule to compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(LIB_NAME)

# Rebuild the library
re: clean all
