# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 14:48:17 by yandry            #+#    #+#              #
#    Updated: 2025/04/15 18:15:40 by yandry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Purple=$(shell tput setaf 5)
Red=$(shell tput setaf 1)
Cyan=$(shell tput setaf 6)
Blue=$(shell tput setaf 4)
Yellow=$(shell tput setaf 3)
Green=$(shell tput setaf 2)
Color_Off=$(shell tput sgr0)

NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
LIBFT_PATH := libft/
INCLUDES = -I ./includes -I $(LIBFT_PATH)
LDFLAGS := -lreadline

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

UTILS_SRC		:= ft_set.c \
				   ft_strndup.c \
				   ft_strreplace.c \
				   ft_get_max.c \
				   ft_strjoin_free.c \
				   ft_strcmp.c \
				   string_to_token.c \
				   is_logical.c

SIGNAL_SRC		:= signal.c

LEXING_SRC		:= lex.c \
				   lst_helper.c \
				   space.c \
				   clear.c \
				   expand.c \
				   split.c \
				   lst_helper2.c \
				   is.c

PARSING_SRC		:= parse.c \
				   free_leaf.c \
				   create_leaf.c

HEREDOC_SRC		:= read.c \
				   handle.c

QUOTE_SRC		:= read.c

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
				   fill_tree.c

SUBSHELL_SRC 	:= subshell.c \
				   read.c

PROMPT_SRC		:= shell.c \
				   prompt_builder.c \
				   prompt_builder_utils.c

EXEC_SRC		:= ft_exec.c \
				   ft_execute_simple_cmd.c \
				   ft_execft.c \
				   execution_utils.c \
				   ft_execute_pipeline.c

IO_SRC			:= ft_gethostname.c \
				   ft_tuyau.c

FT_READLINE_SRC := ft_readline.c \
				   handle_chars.c \
				   init.c \
				   terminal.c

SRC := main.c \
	   $(addprefix utils/, $(UTILS_SRC)) \
	   $(addprefix signal/, $(SIGNAL_SRC)) \
	   $(addprefix lexing/, $(LEXING_SRC)) \
	   $(addprefix parsing/, $(PARSING_SRC)) \
	   $(addprefix heredoc/, $(HEREDOC_SRC)) \
	   $(addprefix quote/, $(QUOTE_SRC)) \
	   $(addprefix btree/, $(BTREE_SRC)) \
	   $(addprefix subshell/, $(SUBSHELL_SRC)) \
	   $(addprefix prompt/, $(PROMPT_SRC)) \
	   $(addprefix execution/, $(EXEC_SRC)) \
	   $(addprefix io/, $(IO_SRC))

ifdef CUSTOM_RL
SRC += $(addprefix io/ft_readline/, $(FT_READLINE_SRC))
endif

SRCS := $(addprefix $(SRC_PATH), $(SRC))
OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_PATH), $(OBJ))

OBJ_DIRS := $(sort $(dir $(OBJS)))

LIBFT := $(LIBFT_PATH)libft.a

.PHONY: all clean fclean re norm nm lint

all: $(NAME)

-include $(OBJS:.o=.d)

$(OBJ_DIRS):
	@$(foreach dir,$(OBJ_DIRS),mkdir -p $(dir);)
	@echo "$(Blue)Created $(Purple)objects $(Blue)directory$(Color_Off)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_DIRS)
	@echo -n "$(Cyan)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo -n "$(Color_Off)"

$(LIBFT):
	@echo "$(Color_Off)[Announcer] $(Purple)Oh so they wanted to use their libft huh? Guess we're compiling that too now$(Color_Off)"
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@echo -n "$(Green)"
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)
ifeq ($(DEBUG), 1)
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) has been compiled in $(Red)DEBUG$(Purple) mode!$(Color_Off)"
else
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) has been compiled :D! Happy hacking!$(Color_Off)"
endif

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

