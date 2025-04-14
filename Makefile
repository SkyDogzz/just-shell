# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 14:48:17 by yandry            #+#    #+#              #
#    Updated: 2025/04/14 17:10:44 by yandry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Purple=$(shell tput setaf 5)
Red=$(shell tput setaf 1)
Cyan=$(shell tput setaf 6)
Blue=$(shell tput setaf 4)
Yellow=$(shell tput setaf 3)
Green=$(shell tput setaf 2)
Color_Off=$(shell tput sgr0)

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

ifdef DEBUG
CFLAGS += -g3
CFLAGS += -D DEBUG=TRUE
endif
ifdef FSAN
CFLAGS += -fsanitize=address
endif
ifdef CUSTOM_RL
CFLAGS += -D USE_CUSTOM_RL
endif

SRC_PATH = src/
OBJ_PATH = obj/
LIBFT_PATH = libft/

UTILS_SRC = utils/ft_set.c utils/ft_strndup.c utils/ft_strreplace.c \
			utils/ft_get_max.c utils/ft_strjoin_free.c utils/ft_strcmp.c
SIGNAL_SRC = signal/signal.c
LEXING_SRC = lexing/lex.c lexing/lst_helper.c lexing/space.c \
			  lexing/clear.c lexing/expand.c lexing/split.c \
			  lexing/lst_helper2.c lexing/is.c
PARSING_SRC = parsing/parse.c parsing/free_leaf.c \
			  parsing/create_leaf.c
HEREDOC_SRC = heredoc/read.c heredoc/handle.c
QUOTE_SRC = quote/read.c
BTREE_SRC = btree/ft_btree_clear.c btree/ft_btree_height.c \
			btree/ft_btree_inorder.c btree/ft_btree_insert.c \
			btree/ft_btree_new.c btree/ft_btree_postorder.c \
			btree/ft_btree_preorder.c btree/ft_btree_size.c btree/print.c \
			btree/ft_btree_insert_in.c
SUBSHELL_SRC = subshell/subshell.c subshell/read.c
PROMPT_SRC = prompt/shell.c
EXEC_SRC = execution/ft_exec.c execution/ft_execute_simple_cmd.c execution/ft_execft.c execution/execution_utils.c execution/ft_execute_pipeline.c
IO_SRC = io/ft_gethostname.c io/ft_tuyau.c
FT_READLINE_SRC = ft_readline/ft_readline.c ft_readline/handle_chars.c ft_readline/init.c ft_readline/terminal.c

SRC = main.c $(UTILS_SRC) $(SIGNAL_SRC) $(LEXING_SRC) $(PARSING_SRC) \
	  $(HEREDOC_SRC) $(QUOTE_SRC) $(BTREE_SRC) $(SUBSHELL_SRC) $(PROMPT_SRC) $(EXEC_SRC) $(IO_SRC) $(addprefix io/, $(FT_READLINE_SRC))

OBJ = $(SRC:.c=.o)
SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES = -I ./includes -I $(LIBFT_PATH)
LIBFT = $(LIBFT_PATH)libft.a

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c includes/minishell.h
	@echo -n "$(Cyan)"
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo -n "$(Color_Off)"

$(OBJ_PATH):
	@echo -n "$(Blue)"
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/utils
	mkdir -p $(OBJ_PATH)/signal
	mkdir -p $(OBJ_PATH)/lexing
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/heredoc
	mkdir -p $(OBJ_PATH)/quote
	mkdir -p $(OBJ_PATH)/btree
	mkdir -p $(OBJ_PATH)/subshell
	mkdir -p $(OBJ_PATH)/prompt
	mkdir -p $(OBJ_PATH)/execution
	mkdir -p $(OBJ_PATH)/io
	mkdir -p $(OBJ_PATH)/io/ft_readline

$(NAME): $(LIBFT) $(OBJS)
	@echo -n "$(Green)"
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)
ifeq ($(DEBUG), 1)
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) has been compiled in $(Red)DEBUG$(Purple) mode!$(Color_Off)"
else
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) has been compiled :D! Happy hacking!$(Color_Off)"
endif

$(LIBFT):
	@echo "$(Color_Off)[Announcer] $(Purple)Oh so they wanted to use their libft huh? Guess we're compiling that too now$(Color_Off)"
	$(MAKE) -C $(LIBFT_PATH)

clean:
	@echo "$(Color_Off)[Announcer] $(Purple)Let's clean up libft first :D$(Color_Off)"
	$(MAKE) clean -C $(LIBFT_PATH)
	@echo -n "$(Blue)"
	rm -rf $(OBJ_PATH)
	@echo "$(Color_Off)[Announcer] $(Purple)Removed object files of $(NAME)$(Color_Off)"

fclean: clean
	@echo "$(Color_Off)[Announcer] $(Purple)Now let's clean up libft completely :D$(Color_Off)"
	$(MAKE) fclean -C $(LIBFT_PATH)
	@echo -n "$(Blue)"
	rm -f $(NAME)
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) is GONE!!$(Color_Off)"
		
re: fclean all

norm:
	@norminette src/ includes/ libft/ | grep -v "OK" && exit 1 || echo "$(Color_Off)[Announcer]$(Purple) All files follow the $(Green)Norm$(Purple)!!! (that was painful though)$(Color_Off)"

nm: re
	nm $(NAME) | grep GLIBC

lint:
	@cppcheck --enable=all --check-level=exhaustive --suppress=variableScope \
	--suppress=missingIncludeSystem src 1> /dev/null

.PHONY: all clean fclean re norm
