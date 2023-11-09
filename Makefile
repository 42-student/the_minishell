# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smargine <smargine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 01:38:53 by smargine          #+#    #+#              #
#    Updated: 2023/10/25 08:40:49 by smargine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Colors for printing
GREEN = \033[0;32m
NC = \033[0m # No Color

# NAME
NAME		= minishell

# SOURCES
SRCS := main.c lexer_split.c tokenizer.c syntax_check.c

# DIRECTORIES AND PATHS
INCLDIR		:= incl/
INCS		:= -I ./incl/ -I/usr/include
SRCDIR		:= src/
OBJDIR		:= obj/
LIBFTDIR	:= libft/
HEADER		:= incl/minishell.h

# LIBRARIES
LIBFT		:= $(LIBFTDIR)libft.a

# COMPILER & COMMANDS
CC			:= cc
RM			:= rm -f

# HEADERS
HEADERS		:= $(addprefix $(INCLDIR)/, minishell.h libft.h get_next_line.h ft_printf.h)

# FLAGS
CFLAGS		:= -Wall -Wextra -Werror -g
LIBFLAG		:= -L$(LIBFTDIR)
LIBFTLIB	:= -lft
RLFLAG		:= -lreadline


# OBJECTS
OBJ			:= $(SRCS:.c=.o)
OBJS		:= $(addprefix $(OBJDIR), $(OBJ))

# COMPILATION RULES
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# RULES
all: $(NAME) $(LIBFT)

# Compile libft.a
$(LIBFT): $(LIBFTDIR)*.c
	@$(MAKE) -C $(LIBFTDIR) all --no-print-directory

$(NAME): $(HEADERS) $(LIBFT) $(OBJDIR) $(OBJS) 
		@$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $(NAME) $(LIBFLAG) $(LIBFTLIB) $(RLFLAG)
		@echo "$(GREEN)$(NAME) is ready!$(NC)"

$(OBJDIR):
		mkdir $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
		$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Create links of headers in incl folder
$(HEADERS):
		ln $(LIBFTDIR)libft.h $(INCLDIR)libft.h
		ln $(LIBFTDIR)ft_printf.h $(INCLDIR)ft_printf.h
		ln $(LIBFTDIR)get_next_line.h $(INCLDIR)get_next_line.h

clean:
		$(RM) $(OBJS)
		$(RM) -r $(OBJDIR)
		$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
		$(RM) $(NAME)
		$(MAKE) -C $(LIBFTDIR) fclean
		$(RM) $(INCLDIR)libft.h
		$(RM) $(INCLDIR)ft_printf.h
		$(RM) $(INCLDIR)get_next_line.h

re:		fclean all

.PHONY:	all clean fclean re
