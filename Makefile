SRCS = memory_alloc.c \
	   mem_interface.c \
	   utils.c \
	   tests.c

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

HEADERS = memory_alloc.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -std=c11 -g -fsanitize=address

NAME = m_alloc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(NAME)

re: clean all



