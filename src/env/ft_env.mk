# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_env.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 19:17:51 by yandry            #+#    #+#              #
#    Updated: 2025/05/16 19:30:17 by yandry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_ENV_MODULE_NAME	:= ft_env

FT_CORE_SRC			:= ft_init_env.c \
					   ft_clear_env.c \
					   ft_new_env.c \
					   ft_get_env.c \
					   ft_update_env.c \
					   ft_delete_env.c \
					   env_utils.c

FT_ENV_SRC			:= $(addprefix core/, $(FT_CORE_SRC))

FT_ENV_OBJ			:= $(FT_ENV_SRC:.c=.o)

FT_ENV_SRCS			:= $(addprefix $(SRC_PATH)env/, $(FT_ENV_SRC))
FT_ENV_OBJS			:= $(addprefix $(OBJ_PATH)env/, $(FT_ENV_OBJ))
FT_ENV_DEPS			:= $(FT_ENV_OBJS:.o=.d)

FT_ENV_OBJ_DIR		:= $(sort $(dir $(FT_ENV_OBJS)))

.PHONY: clean_ft_env create_ft_env_dirs ft_env_announce

-include $(FT_ENV_DEPS)

ft_env_announce:
	@if [ ! -f .ft_env_announced ]; then \
		echo "$(Color_Off)[Announcer] Building $(Cyan)$(FT_ENV_MODULE_NAME) $(Color_Off)module"; \
		touch .ft_env_announced; \
	fi

create_ft_env_dirs:
	@mkdir -p $(FT_ENV_OBJ_DIR)

$(OBJ_PATH)env/%.o: $(SRC_PATH)env/%.c ft_env_announce create_ft_env_dirs
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || (echo "$(Color_Off)[Announcer] $(Yellow)$(FT_ENV_MODULE_NAME)$(Purple)'s compilation $(Red)failed$(Color_Off) :[" && exit 1)


clean_ft_env:
	@rm -rf $(FT_ENV_OBJS) $(FT_ENV_DEPS)
	@rm -f .ft_env_announced
	@echo "$(Color_Off)[Announcer] Removed $(Cyan)$(FT_ENV_MODULE_NAME) $(Color_Off)module's object files"
