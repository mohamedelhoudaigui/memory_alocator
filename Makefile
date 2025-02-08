SRCS = *.c

HEADERS = *.h

CC = cc

CFLAGS = -Wall -Wextra -g -fsanitize=address

NAME = m_alloc

all:
	$(CC) $(CFLAGS) $(SRCS) $(HEADERS) -o $(NAME)

