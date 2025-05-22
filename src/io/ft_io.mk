# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_io.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 19:00:48 by yandry            #+#    #+#              #
#    Updated: 2025/05/16 14:01:57 by yandry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_IO_MODULE_NAME	:= ft_io

FT_READLINE_SRC		:= ft_readline.c \
					   handle_chars.c \
					   init.c \
					   terminal.c

FT_IO_SRC			:= ft_tuyau.c \
					   infile.c \
					   outfile.c \
					   file_operations.c

ifdef CUSTOM_RL
FT_IO_SRC			+= $(addprefix ft_readline/, $(FT_READLINE_SRC))
endif

FT_IO_OBJ			:= $(FT_IO_SRC:.c=.o)
FT_IO_SRCS			:= $(addprefix $(SRC_PATH)io/, $(FT_IO_SRC))
FT_IO_OBJS			:= $(addprefix $(OBJ_PATH)io/, $(FT_IO_SRC:.c=.o))
FT_IO_DEPS			:= $(FT_IO_OBJS:.o=.d)

FT_IO_OBJ_DIR		:= $(sort $(dir $(FT_IO_OBJS)))

.PHONY: clean_ft_io create_ft_io_dirs ft_io_announce

-include $(FT_IO_DEPS)

ft_io_announce:
	@if [ ! -f .ft_io_announced ]; then \
		echo "$(Color_Off)[Announcer] Building $(Cyan)$(FT_IO_MODULE_NAME) $(Color_Off)module"; \
		touch .ft_io_announced; \
	fi

create_ft_io_dirs:
	@mkdir -p $(FT_IO_OBJ_DIR)

$(OBJ_PATH)io/%.o: $(SRC_PATH)io/%.c ft_io_announce create_ft_io_dirs
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || (echo "$(Color_Off)[Announcer] $(Yellow)$(FT_IO_MODULE_NAME)$(Color_Off)'s compilation $(Red)failed$(Color_Off) :[" && exit 1)


clean_ft_io:
	@rm -rf $(FT_IO_OBJS) $(FT_IO_DEPS)
	@rm -f .ft_io_announced
	@echo "$(Color_Off)[Announcer] Removed $(Cyan)$(FT_IO_MODULE_NAME) $(Color_Off)module's object files"

