# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_execution.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 12:11:46 by yandry            #+#    #+#              #
#    Updated: 2025/04/26 14:59:19 by yandry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MODULE_NAME			:= ft_execution


FT_BUILTINS_SRC		:= cd.c \
					   echo.c \
					   env.c \
					   exit.c \
					   export.c \
					   pwd.c \
					   unset.c \
					   ft_is_builtin.c \
					   ft_execute_builtin.c

FT_UTILS_SRC		:= pipeline_utils.c \
					   execution_utils.c

FT_CORE_SRC			:= ft_execute_simple.c \
					   ft_execute_pipeline.c \
					   ft_execute_logical.c \
					   ft_execft.c

FT_EXEC_SRC			:= ft_exec.c \
					   $(addprefix core/, $(FT_CORE_SRC)) \
					   $(addprefix builtins/, $(FT_BUILTINS_SRC)) \
					   $(addprefix utils/, $(FT_UTILS_SRC))

FT_EXEC_OBJ			:= $(FT_EXEC_SRC:.c=.o)

FT_EXEC_SRCS		:= $(addprefix $(SRC_PATH)execution/, $(FT_EXEC_SRC))
FT_EXEC_OBJS		:= $(addprefix $(OBJ_PATH)execution/, $(FT_EXEC_SRC:.c=.o))
FT_EXEC_DEPS		:= $(FT_EXEC_OBJS:.o=.d)

FT_EXEC_OBJ_DIR		:= $(sort $(dir $(FT_EXEC_OBJS)))

-include $(FT_EXEC_DEPS)

$(FT_EXEC_OBJ_DIR):
	@$(foreach dir, $(FT_EXEC_OBJ_DIR), mkdir -p $(dir);)
	@echo "$(Color_Off)[Announcer] $(Purple)Created $(Cyan)$(MODULE_NAME) $(Purple)module's objects directory!$(Color_Off)"

$(OBJ_PATH)execution/%.o: $(SRC_PATH)execution/%.c | $(FT_EXEC_OBJ_DIR)
	@echo -n "$(Cyan)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo -n "$(Color_Off)"


clean_ft_execution:
	@rm -rf $(FT_EXEC_OBJS) $(FT_EXEC_DEPS)
	@echo "$(Color_Off)[Announcer] $(Purple)Removed $(Cyan)$(MODULE_NAME) $(Purple)module's object files$(Color_Off)"

.PHONY: clean_ft_execution
