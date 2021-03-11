NAME = minishell

SRC = main.c control.c parse.c ft_error.c ft_signal.c ft_splittoargv.c \
	ft_processargv.c ft_processargv_utils.c ft_processvars.c utils_export.c \
	ft_exit.c ft_echo.c ft_env.c ft_cd.c ft_pwd.c ft_unset.c ft_export.c \
	ft_redirect.c pipes.c ft_runcmd.c ft_pathvutils.c ft_sigprint.c

SRCDIR = ./srcs/
SRC := $(addprefix $(SRCDIR), $(SRC))
OBJ = $(SRC:.c=.o)
INCLUDEDIR = ./includes/
HEADERS = $(INCLUDEDIR)shell.h
LIBFTDIR = ./libft/
LIBFT = $(LIBFTDIR)libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDEDIR) -I$(LIBFTDIR)
LIBFLAGS = -L$(LIBFTDIR) -lft
EXECFLAGS = $(CFLAGS) $(LIBFLAGS)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(EXECFLAGS)

%.o: %.c $(HEADERS) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "> Building libft"
	@make -C $(LIBFTDIR)
	@echo "> Done\n"

clean:
	@make clean -C $(LIBFTDIR)
	@/bin/rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@/bin/rm -f $(NAME)

re: fclean all
