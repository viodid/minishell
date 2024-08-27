# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 17:09:42 by kde-la-c          #+#    #+#              #
#    Updated: 2024/08/27 21:48:46 by kde-la-c         ###   ########.fr        #
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
SRC				= $(SRCDIR)main.c						\
				$(SRCDIR)core/minishell.c				\
				$(SRCDIR)core/get_env.c					\
				$(SRCDIR)core/set_env.c					\
				$(SRCDIR)core/get_env_array.c			\
				$(SRCDIR)parser/parser.c				\
				$(SRCDIR)executor/executor.c			\
				$(SRCDIR)executor/executor_builtin.c	\
				$(SRCDIR)executor/redirections.c		\
				$(SRCDIR)signals/signals.c				\
				$(SRCDIR)builtins/echo.c				\
				$(SRCDIR)builtins/cd.c					\
				$(SRCDIR)builtins/pwd.c					\
				$(SRCDIR)builtins/export.c				\
				$(SRCDIR)builtins/unset.c				\
				$(SRCDIR)builtins/env.c					\
				$(SRCDIR)builtins/exit.c				\
				$(SRCDIR)utils/free_struct.c			\
				$(SRCDIR)utils/printers.c				\

OBJS			= $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRC))

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
LIBFLAG			=
LIBREADLINE		= -lreadline
LDFLAGS			= $(LIBREADLINE)

RM				= rm
RFLAGS			= -rf

all:			$(NAME)

asan:			fclean
# asan:			cleanbin
asan:			CFLAGS += -fsanitize=address -g3
asan:			LIBFLAG = asan
asan:			LIBNAME = libft_asan.a
asan:			all

lsan:			fclean
# lsan:			cleanbin
lsan:			CFLAGS += -fsanitize=leak -g3
lsan:			LIBFLAG = lsan
lsan:			LIBNAME = libft_lsan.a
lsan:			all

$(NAME):		$(OBJS) $(LIBNAME)
				echo $(LIBNAME)
				$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBNAME) $(LDFLAGS)
				@echo "\033[0;32m--- Minishell compiled successfully! ---\033[0m"

$(LIBNAME):
				$(MAKE) $(LIBFLAG) -C $(LIBDIR)
				cp $(LIBDIR)$(LIBNAME) .
				$(MAKE) -C $(LIBDIR) clean

$(OBJDIR)%.o:	$(SRCDIR)%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c -o $@ $<

clean:
				$(RM) $(RFLAGS) $(OBJS)
				@echo "\033[0;32m--- Objects cleaned successfully! ---\033[0m"

cleanbin:		clean
				$(RM) $(RFLAGS) $(NAME)
				@echo "\033[0;32m--- $(NAME) cleaned successfully! ---\033[0m"

fclean:			cleanbin
				$(RM) $(RFLAGS) $(NAME) $(LIBNAME)
				@echo "\033[0;32m--- Libft cleaned successfully! ---\033[0m"

re:				fclean all

diff:
				$(info The status of the repository, and the volume of per-file changes:)
				git status
				git --no-pager diff --stat

.SILENT:		diff
.PHONY:			all clean fclean re diff