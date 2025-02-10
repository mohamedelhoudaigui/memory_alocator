SRCS = memory_alloc.c \
	   mem_interface.c \
	   utils.c

OBJS_DIR = Objects

OBJS = $(patsubst %.cpp, $(OBJS_DIR)/%.o, $(SRCS))

HEADERS = memory_alloc.h

CC = cc

CFLAGS = -Wall -Wextra -Werror -std=11 -g -fsanitize=address

NAME = m_alloc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all



