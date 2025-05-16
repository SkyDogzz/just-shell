# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 14:48:17 by yandry            #+#    #+#              #
#    Updated: 2025/05/16 20:21:08 by yandry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Purple=$(shell tput setaf 5)
Red=$(shell tput setaf 1)
Cyan=$(shell tput setaf 6)
Blue=$(shell tput setaf 4)
Yellow=$(shell tput setaf 3)
Green=$(shell tput setaf 2)
Color_Off=$(shell tput sgr0)

MAKEFLAGS += --no-print-directory -j $(shell nproc)

NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
LIBFT_PATH := libft/
INCLUDES = -I ./includes -I $(LIBFT_PATH)
LDFLAGS := -lreadline

.PHONY: all vibe_check

vibe_check:
	@$(MAKE) --question $(NAME) 2>/dev/null && echo "$(Color_Off)[Announcer] $(Purple)Everything is up to date, nothing to do here. Zzz...$(Color_Off)" || $(MAKE) $(NAME)

all: vibe_check $(NAME)

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

SRC_PATH := src/
OBJ_PATH := obj/

include src/execution/ft_execution.mk
include src/io/ft_io.mk
include src/parsing/ft_parsing.mk
include src/env/ft_env.mk

UTILS_SRC		:= ft_set.c \
				   ft_strndup.c \
				   ft_strreplace.c \
				   ft_get_max.c \
				   ft_strjoin_free.c \
				   ft_strcmp.c \
				   string_to_token.c \
				   is_logical.c \
				   is_operator.c \
				   random_fd.c \
				   cleanup.c \
				   ft_isoutfile.c \
				   fd.c \
				   logger.c

SIGNAL_SRC		:= signal.c

BTREE_SRC 		:= ft_btree_clear.c \
				   ft_btree_height.c \
				   ft_btree_inorder.c \
				   ft_btree_insert.c \
				   ft_btree_new.c \
				   ft_btree_postorder.c \
				   ft_btree_preorder.c \
				   ft_btree_size.c \
				   print.c \
				   ft_btree_insert_in.c\
				   fill_tree.c \
				   parse_redir.c \
				   parse_input.c \
				   parse_outfile.c

SUBSHELL_SRC 	:= subshell.c \
				   read.c

PROMPT_SRC		:= shell.c \
				   prompt_builder.c \
				   prompt_user_utils.c \
				   prompt_host_utils.c \
				   prompt_path_utils.c \
				   prompt_exit_utils.c

HISTORY_SRC		:= history.c


SRC := main.c \
	   $(addprefix utils/, $(UTILS_SRC)) \
	   $(addprefix signal/, $(SIGNAL_SRC)) \
	   $(addprefix btree/, $(BTREE_SRC)) \
	   $(addprefix subshell/, $(SUBSHELL_SRC)) \
	   $(addprefix prompt/, $(PROMPT_SRC)) \
	   $(addprefix history/, $(HISTORY_SRC)) \

SRCS := $(addprefix $(SRC_PATH), $(SRC))
OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_PATH), $(OBJ)) $(FT_EXEC_OBJS) $(FT_IO_OBJS) $(FT_PARSING_OBJS) $(FT_ENV_OBJS)

OBJ_DIRS := $(sort $(dir $(OBJS)))

LIBFT := $(LIBFT_PATH)libft.a

.PHONY: clean fclean re norm nm lint

-include $(OBJS:.o=.d)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || (echo "$(Color_Off)[Announcer] $(Yellow)$(NAME)$(Color_Off)'s compilation $(Red)failed$(Color_Off) :[" && exit 1)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(Color_Off)[Announcer] Linking $(Purple)$(NAME)$(Color_Off)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)
ifeq ($(DEBUG), 1)
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) $(Color_Off)has been compiled in $(Red)DEBUG$(Color_Off) mode!"
else
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) $(Color_Off)has been compiled :D! Happy hacking!"
endif

clean: clean_ft_execution clean_ft_io clean_ft_parsing clean_ft_env
	@$(MAKE) clean -C $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)
	@echo "$(Color_Off)[Announcer] Removed object and dependency files for $(Purple)$(NAME)$(Color_Off)"

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "$(Color_Off)[Announcer] Removed $(Purple)$(NAME)$(Color_Off)"
		
re: fclean all

norm:
	@norminette src/ includes/ libft/ | grep -v "OK" && exit 1 || echo "$(Color_Off)[Announcer] $(Green)All files follow the Norm$(Color_Off)!!! (that was painful though)"

nm: re
	nm $(NAME) | grep GLIBC

lint:
	@cppcheck --enable=all --check-level=exhaustive --suppress=variableScope \
	--suppress=missingIncludeSystem --suppress=missingInclude \
	--suppress=constVariablePointer --suppress=unusedFunction src 1> /dev/null

