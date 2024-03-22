# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kde-la-c <kde-la-c@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 17:09:42 by kde-la-c          #+#    #+#              #
#    Updated: 2024/03/22 17:09:44 by kde-la-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BINARY		= minishell
LIB			= libft.a
CODEDIRS	= src
INCDIR		= ./include/
LIBDIR		= libft/
BIN_DIR		= ./bin/

CC			= gcc
OPT			= -g3
CFLAGS		= -Wall -Wextra -Werror -I$(INCDIR) $(OPT)

CFILES		= $(shell find $(CODEDIRS) -name '*.c')
OBJECTS		= $(CFILES:.c=.o)

all:		$(BINARY)

$(BINARY):	$(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $(LIB) -o $@ $^

$(LIB):		$(LIBDIR)
	$(MAKE) -C $(LIBDIR)
	cp $(LIBDIR)$(LIB) .
	$(MAKE) -C $(LIBDIR) fclean

clean:
	rm -f $(OBJECTS)

fclean:		clean
	rm -f $(BINARY)

re:			fclean all

diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git --no-pager diff --stat

.PHONY:		all clean fclean re diff