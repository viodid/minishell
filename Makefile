# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 17:09:42 by kde-la-c          #+#    #+#              #
#    Updated: 2024/03/22 17:09:44 by kde-la-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
LIBNAME			= libft.a

SRCDIR			= src/
INCDIR			= include/
LIBDIR			= libft/
OBJDIR			= obj/
BINDIR			= bin/

INCLUDE			= $(INCDIR)minishell.h
SRC				= $(SRCDIR)main.c				\
				$(SRCDIR)core/minishell.c		\
				$(SRCDIR)core/ft_getenv.c		\
				$(SRCDIR)parser/parser.c		\
				$(SRCDIR)executor/executor.c	\
				$(SRCDIR)signals/signals.c		\
				$(SRCDIR)builtins/echo.c		\
				$(SRCDIR)builtins/pwd.c			\
				$(SRCDIR)builtins/cd.c			\

OBJS			= $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRC))

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
CFLAGS			+= -fsanitize=address -g3
# CFLAGS			+= -fsanitize=leak -g3
LIBREADLINE		= -lreadline
LDFLAGS			= $(LIBREADLINE)

RM				= rm
RFLAGS			= -rf

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBNAME)
				$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
				@echo "\033[0;32m--- Minishell compiled successfully! ---\033[0m"

$(LIBNAME):
				$(MAKE) -C $(LIBDIR)
				cp $(LIBDIR)$(LIBNAME) .
				$(MAKE) -C $(LIBDIR) fclean

$(OBJDIR)%.o:	$(SRCDIR)%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c -o $@ $<

clean:
				$(RM) $(RFLAGS) $(OBJS)
				@echo "\033[0;32m--- Objects cleaned successfully! ---\033[0m"

fclean:			clean
				$(RM) $(RFLAGS) $(NAME) $(LIBNAME)
				@echo "\033[0;32m--- Archive cleaned successfully! ---\033[0m"

re:				fclean all

diff:
				$(info The status of the repository, and the volume of per-file changes:)
				git status
				git --no-pager diff --stat

.SILENT:		diff
.PHONY:			all clean fclean re diff