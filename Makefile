# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 14:48:17 by yandry            #+#    #+#              #
#    Updated: 2025/04/25 19:45:28 by tstephan         ###   ########.fr        #
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
				   ft_strjoin_free.c \
				   ft_strcmp.c \
				   ft_string_to_token.c \
				   ft_is_pipe.c \
				   ft_is_logical.c \
				   ft_is_operator.c \
				   ft_random_filename.c \
				   ft_getmax.c

ENV_SRC			:= ft_init_env.c \
				   ft_clear_env.c \
				   ft_new_env.c \
				   ft_get_env.c \
				   ft_update_env.c \
				   ft_delete_env.c \
				   ft_env_utils.c

SIGNAL_SRC		:= ft_signal.c

LEXING_SRC		:= ft_lex.c \
				   ft_space.c \
				   ft_clear.c \
				   ft_expand.c \
				   ft_split.c \
				   ft_pid.c \
				   ft_fill_tree.c

PARSING_SRC		:= ft_parse.c \
				   ft_free_leaf.c \
				   ft_create_leaf.c \
				   ft_parse_redir.c \
				   ft_read_quote.c \
				   ft_read_heredoc.c \
				   ft_read_subshell.c \
				   ft_subshell.c \
				   ft_handle_heredoc.c

BTREE_SRC 		:= ft_btree_clear.c \
				   ft_btree_height.c \
				   ft_btree_inorder.c \
				   ft_btree_insert.c \
				   ft_btree_new.c \
				   ft_btree_postorder.c \
				   ft_btree_preorder.c \
				   ft_btree_size.c \
				   ft_print.c \
				   ft_btree_insert_in.c

PROMPT_SRC		:= ft_shell.c \
				   ft_prompt_builder.c \
				   ft_prompt_user_utils.c \
				   ft_prompt_host_utils.c \
				   ft_prompt_path_utils.c \
				   ft_prompt_exit_utils.c

EXEC_SRC		:= ft_exec.c \
				   ft_execute_simple_cmd.c \
				   ft_execft.c \
				   ft_pipeline_utils.c \
				   ft_execution_utils.c \
				   ft_execute_pipeline.c \
				   ft_execute_logical.c

IO_SRC			:= ft_tuyau.c \
				   ft_infile.c \
				   ft_outfile.c

BUILTINS_SRC	:= ft_is_builtin.c \
				   ft_execute_builtin.c \
				   ft_echo.c \
				   ft_cd.c \
				   ft_pwd.c \
				   ft_export.c \
				   ft_unset.c \
				   ft_env.c \
				   ft_exit.c

FT_READLINE_SRC := ft_readline.c \
				   ft_handle_chars.c \
				   ft_init.c \
				   ft_terminal.c
				   
LST_HELPER_SRC	:= ft_lst_helper.c \
				   ft_lst_helper2.c

SRC := main.c \
	   $(addprefix utils/, $(UTILS_SRC)) \
	   $(addprefix env/, $(ENV_SRC)) \
	   $(addprefix signal/, $(SIGNAL_SRC)) \
	   $(addprefix lexing/, $(LEXING_SRC)) \
	   $(addprefix parsing/, $(PARSING_SRC)) \
	   $(addprefix heredoc/, $(HEREDOC_SRC)) \
	   $(addprefix quote/, $(QUOTE_SRC)) \
	   $(addprefix btree/, $(BTREE_SRC)) \
	   $(addprefix subshell/, $(SUBSHELL_SRC)) \
	   $(addprefix prompt/, $(PROMPT_SRC)) \
	   $(addprefix execution/, $(EXEC_SRC)) \
	   $(addprefix io/, $(IO_SRC)) \
	   $(addprefix builtins/, $(BUILTINS_SRC)) \
	   $(addprefix lst_helper/, $(LST_HELPER_SRC))

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
	--suppress=missingIncludeSystem --suppress=missingInclude \
	--suppress=constVariablePointer --suppress=unusedFunction src 1> /dev/null

