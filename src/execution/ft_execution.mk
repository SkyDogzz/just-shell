# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_execution.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 12:11:46 by yandry            #+#    #+#              #
#    Updated: 2025/06/12 15:49:40 by tstephan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_EXEC_MODULE_NAME	:= ft_execution


FT_BUILTINS_SRC		:= cd.c \
					   echo.c \
					   env.c \
					   exit.c \
					   export.c \
					   pwd.c \
					   unset.c \
					   ft_is_builtin.c \
					   ft_execute_builtin.c

FT_UTILS_SRC		:= execution_utils.c

FT_CORE_SRC			:= ft_execution_context.c \
					   ft_cmd_exists.c

FT_EXEC_SRC			:= ft_exec.c ft_exec_simple.c ft_exec_logical.c \
					   $(addprefix core/, $(FT_CORE_SRC)) \
					   $(addprefix builtins/, $(FT_BUILTINS_SRC)) \
					   $(addprefix utils/, $(FT_UTILS_SRC))

FT_EXEC_OBJ			:= $(FT_EXEC_SRC:.c=.o)

FT_EXEC_SRCS		:= $(addprefix $(SRC_PATH)execution/, $(FT_EXEC_SRC))
FT_EXEC_OBJS		:= $(addprefix $(OBJ_PATH)execution/, $(FT_EXEC_SRC:.c=.o))
FT_EXEC_DEPS		:= $(FT_EXEC_OBJS:.o=.d)

FT_EXEC_OBJ_DIR		:= $(sort $(dir $(FT_EXEC_OBJS)))

.PHONY: clean_ft_execution create_ft_exec_dirs ft_exec_announce

-include $(FT_EXEC_DEPS)

ft_exec_announce:
	@if [ ! -f .ft_execution_announced ]; then \
		echo "$(Color_Off)[Announcer] Building $(Cyan)$(FT_EXEC_MODULE_NAME) $(Color_Off)module"; \
		touch .ft_execution_announced; \
	fi

create_ft_exec_dirs:
	@mkdir -p $(FT_EXEC_OBJ_DIR)

$(OBJ_PATH)execution/%.o: $(SRC_PATH)execution/%.c ft_exec_announce create_ft_exec_dirs
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || (echo "$(Color_Off)[Announcer] $(Yellow)$(FT_EXEC_MODULE_NAME)$(Purple)'s compilation $(Red)failed$(Color_Off) :[" && exit 1)


clean_ft_execution:
	@rm -rf $(FT_EXEC_OBJS) $(FT_EXEC_DEPS)
	@rm -f .ft_execution_announced
	@echo "$(Color_Off)[Announcer] Removed $(Cyan)$(FT_EXEC_MODULE_NAME) $(Color_Off)module's object files"

