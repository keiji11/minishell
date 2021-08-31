# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llucente <llucente@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 15:59:57 by llucente          #+#    #+#              #
#    Updated: 2021/08/31 15:32:30 by llucente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the final executable
NAME = minishell

# Project's directories
SOURCEDIR := ./src
HEADERSDIR := ./headers
OBJECTSDIR := ./objects
EXEC_FOLDER = execution
LEX_FOLDER = lexer
PARS_FOLDER = parse
EXPA_FOLDER = expansion
READ_FOLDER = readline
# LIBFT_HEADER = $(SOURCEDIR)/libft/libft.h
LIBFT_FOLDER = $(SOURCEDIR)/libft


# Name of variables
LIBFT_LIB = libft.a
LIBS = -lncurses
FLAGS = -Wall -Wextra -Werror -g
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m


# Execution files variable
EXEC_FILES =  ft_cd.c \
ft_check_path.c \
ft_echo_pwd_env.c \
ft_exe.c \
ft_exit.c \
ft_export.c \
ft_init_env.c \
ft_linked_lists.c \
ft_linked_lists_rest.c \
ft_pipes.c \
ft_redirection.c \
ft_unset.c \
ft_utils.c

# Lexer files variable

LEX_FILES = lexer_get_tkns_op.c \
lexer_get_tkns_word.c \
lexer_get_tkns.c \
lexer.c

# Parse files variable

PARS_FILES = check_syntax.c \
check_tkn_continue.c \
check_tkns.c \
check_word.c \
create_ast.c \
create_nodes.c \
destroy_nodes.c \
parser.c

# Readline files variable
READ_FILES = chars_list_rest.c \
chars_list.c \
get_input.c \
history.c \
line_nodes.c \
readline.c \
terminal_config.c 

# Expansion files variable
EXPA_FILES = expnd_args.c \
expnd_command.c \
expnd_double_quotes_word.c \
expnd_no_quotes_word.c \
expnd_redirection.c \
expnd_special_params_in_quotes.c \
expnd_special_params.c \
expnd_word.c \
expansion.c \
utils_continue.c \
utils.c

# Main file variable

MAIN_FILE = last_arg.c \
main.c \
minishell.c 

# Define objects for all sources
OBJ_EXEC = $(addprefix $(OBJECTSDIR)/$(EXEC_FOLDER)/, $(EXEC_FILES:.c=.o))
OBJ_LEX = $(addprefix $(OBJECTSDIR)/$(LEX_FOLDER)/, $(LEX_FILES:.c=.o))
OBJ_EXPA = $(addprefix $(OBJECTSDIR)/$(EXPA_FOLDER)/, $(EXPA_FILES:.c=.o))
OBJ_PARS = $(addprefix $(OBJECTSDIR)/$(PARS_FOLDER)/, $(PARS_FILES:.c=.o))
OBJ_READ = $(addprefix $(OBJECTSDIR)/$(READ_FOLDER)/, $(READ_FILES:.c=.o))
OBJ_MAIN = $(addprefix $(OBJECTSDIR)/, $(MAIN_FILE:.c=.o))
OBJS := $(OBJ_EXEC) $(OBJ_LEX) $(OBJ_EXPA) $(OBJ_PARS) $(OBJ_READ) $(OBJ_MAIN)
LIBFT_FILE := $(LIBFT_FOLDER)/$(LIBFT_LIB)

# Name the compiler
CC = gcc

# OS specific part
RM = rm -rf 
RMDIR = rm -rf 
MKDIR = mkdir -p
MAKE = make -C
ECHO = /bin/echo
ERRIGNORE = 2>/dev/null


.PHONY: all fclean 

all: $(NAME)
	
libft:
	@echo "$(BLUE)█████████████████████████ Making LIBFT █████████████████████████$(RESET)"
	@$(MAKE) $(LIBFT_FOLDER)
	@echo "$(BLUE)███████████████████████ Making minishell ███████████████████████$(RESET)"

$(NAME): libft $(OBJS)
	@$(CC) -I $(HEADERSDIR) -I $(LIBFT_FOLDER) $(OBJS) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(LIBS) -o $@
	@echo "$(BLUE)███████████████████████ Compiling is DONE ██████████████████████$(RESET)"

$(OBJECTSDIR)/%.o : $(SOURCEDIR)/%.c $(HEADERSDIR)/*.h
	@$(MKDIR) $(dir $@)
	@echo "$(BLUE)█ $(YELLOW)Compiling$(RESET) $<:\r\t\t\t\t\t\t\t$(GREEN){DONE}$(BLUE) █$(RESET)"
	@$(CC) $(FLAGS) -I $(HEADERSDIR) -I $(LIBFT_FOLDER) -o $@ -c $<

# Remove all objects, dependencies and executable files generated during the build

clean:
	@echo "$(RED)deleting$(RESET): " $(OBJECTSDIR)
	@$(RMDIR) $(OBJECTSDIR) $(ERRIGNORE)
	@echo "$(RED)deleting$(RESET): " "libft objects"
	@$(MAKE) $(LIBFT_FOLDER) clean

fclean: clean
	@echo "$(RED)deleting$(RESET): " $(LIBFT_FOLDER)/$(LIBFT_LIB)
	@$(RM) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(ERRIGNORE)
	@echo "$(RED)deleting$(RESET): " $(NAME)
	@$(RM) $(NAME) $(ERRIGNORE)

re: fclean $(NAME)
