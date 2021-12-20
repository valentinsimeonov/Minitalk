NAME_S = server
NAME_C = client
NAME_SB = server_bonus
NAME_CB = client_bonus

SRCS_S = server.c
SRCS_C = client.c
SRCS_SB = server_bonus.c
SRCS_CB = client_bonus.c

OBJS_S = $(SRCS_S:.c=.o)
OBJS_C = $(SRCS_C:.c=.o)
OBJS_SB = $(SRCS_SB:.c=.o)
OBJS_CB = $(SRCS_CB:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: $(NAME_S) $(NAME_C)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME_S): $(OBJS_S) 
	$(CC) $(CFLAGS) -o $@ $(OBJS_S)

$(NAME_C): $(OBJS_C)
	$(CC) $(CFLAGS) -o $@ $(OBJS_C)

bonus: $(NAME_SB) $(NAME_CB)

$(NAME_SB): $(OBJS_SB)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SB)

$(NAME_CB): $(OBJS_CB)
	$(CC) $(CFLAGS) -o $@ $(OBJS_CB)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME_S) $(NAME_SB) $(NAME_C) $(NAME_CB)

re: fclean all

.PHONY: all bonus clean fclean re
