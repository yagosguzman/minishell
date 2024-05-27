# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 13:04:34 by gpinilla          #+#    #+#              #
#    Updated: 2024/04/23 18:45:57 by gpinilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Suprimir la salida de los comandos make
MAKEFLAGS += --silent

################################################################################
### COLORS
################################################################################

DEL_LINE =		\033[2K
NC		=		\033[0m
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

#=================COMMANDS=================#
NAME			= Minishell
LIBFT			= Libft/libft.a
READLINE		= readline/libreadline.a readline/libhistory.a
LIB_READLINE	= -Lreadline
CC				= gcc
CCFLAGS			= -g -Wall -Wextra -Werror
RM				= rm -rf
SRC				= src/
BUILTINS		= src/builtins/
COMFLAGS		= -I./Libft/inc -I./readline

LIB_A			:= $(LIBFT) $(READLINE)
LINKFLAGS		:= -lreadline -lhistory -ltermcap -lft
LIB_ADD_DIR		:=	-LLibft -Lreadline
#==================FILES===================#

INCLUDE 		= include/minishell.h
FILES_SRC		= env_creation.c error_handler.c executor.c expander.c frees.c get_cmds.c\
					inits.c main.c read.c redirs.c signals.c utils_checks.c utils_env.c utils_env_2.c\
					utils_executor.c utils_executor_2.c utils_executor_checks.c utils_expander.c utils_expander_2.c\
					utils_quote.c utils_read.c utils_read_2.c utils_redir.c pipes.c set_heredoc.c\

FILES_BUILTINS	= ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c\
					utils_builtins.c\

SRC_FILES		= $(addprefix $(SRC), $(FILES_SRC))
BUILTINS_FILES	= $(addprefix $(BUILTINS), $(FILES_BUILTINS))
DIR_OBJ			= temp/
OBJ_SRC			= $(patsubst $(SRC)%.c,$(DIR_OBJ)%.o,$(SRC_FILES))
OBJ_BUILTINS	= $(patsubst $(BUILTINS)%.c,$(DIR_OBJ)%.o,$(BUILTINS_FILES))
OBJ				= $(OBJ_SRC) $(OBJ_BUILTINS)
#==================RULES===================#

all: temp libft_make rdline $(DIR_OBJ) $(NAME) 
	@echo "$(GREEN)Minishell is up to date ✓$(DEF_COLOR)\n"

temp:
	@mkdir -p $(DIR_OBJ)

rdline :
	@echo "${YELLOW}Compiling Readline...${NC}"
	@cd ./readline/ &> /dev/null && ./configure &> /dev/null
	@make -C ./readline/ &> /dev/null
	@echo "${GREEN}Readline Compiled${NC}"
	
libft_make:
	@$(MAKE) -C Libft
	@echo "$(GREEN)\nCreated $(LIBFT) ✓$(DEF_COLOR)\n"

$(DIR_OBJ)%.o: $(SRC)%.c $(INCLUDE) $(LIB_A) Makefile
	@mkdir -p $(DIR_OBJ)
	@$(CC) $(CCFLAGS) -DREADLINE_LIBRARY=1 $(COMFLAGS) -c $< -o $@
	@echo "${BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(CYAN)$< $(DEF_COLOR)"

$(DIR_OBJ)%.o: $(BUILTINS)%.c $(INCLUDE) $(LIB_A) Makefile
	@$(CC) $(CCFLAGS) -DREADLINE_LIBRARY=1 $(COMFLAGS) -c $< -o $@
	@echo "${BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(CYAN)$< $(DEF_COLOR)"

$(NAME): $(OBJ)
	@${CC} $(CCFLAGS) ${OBJ} $(LIB_ADD_DIR) $(LINKFLAGS) $(LIB_A) -o ${NAME}
	@echo "$(GREEN)\nCreated ${NAME} ✓$(DEF_COLOR)\n"


clean:
	@$(RM) $(DIR_OBJ)
	@$(MAKE) -C Libft clean
	@echo "DELETING OBJ"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C Libft fclean
	@echo "${RED}DELETING MINISHELL${NC}"
	@$(MAKE) -C readline clean --no-print-directory

re: fclean all

norm:
	@norminette $(FILES_BUILTINS) $(FILES_SRC) $(INCLUDE)

.PHONY: make all clean fclean re 
