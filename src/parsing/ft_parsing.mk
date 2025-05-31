
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_parsing.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 19:40:00 by yandry            #+#    #+#              #
#    Updated: 2025/05/16 19:40:00 by yandry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_PARSING_MODULE_NAME	:= ft_parsing

FT_PARSING_SUBDIR		:= parsing/

FT_LEXING_SRC			:= lex.c \
						   lst_helper.c \
						   space.c \
						   clear.c \
						   expand.c \
						   split.c \
						   lst_helper2.c \
						   is.c \
						   pid.c

FT_CORE_SRC				:= parse.c \
						   free_leaf.c \
						   create_leaf.c

FT_HEREDOC_SRC 			:= read.c \
						   handle.c

FT_QUOTE_SRC			:= read.c

FT_WILDCARD_SRC			:= wildcard.c

FT_PARSING_SRC 			:= $(addprefix core/, $(FT_CORE_SRC)) \
						   $(addprefix heredoc/, $(FT_HEREDOC_SRC)) \
						   $(addprefix lex/, $(FT_LEXING_SRC)) \
						   $(addprefix quote/, $(FT_QUOTE_SRC)) \
						   $(addprefix wildcard/, $(FT_WILDCARD_SRC))

FT_PARSING_OBJ			:= $(FT_PARSING_SRC:.c=.o)
FT_PARSING_SRCS			:= $(addprefix $(SRC_PATH)$(FT_PARSING_SUBDIR), $(FT_PARSING_SRC))
FT_PARSING_OBJS			:= $(addprefix $(OBJ_PATH)$(FT_PARSING_SUBDIR), $(FT_PARSING_OBJ))
FT_PARSING_DEPS			:= $(FT_PARSING_OBJS:.o=.d)

FT_PARSING_OBJ_DIR		:= $(sort $(dir $(FT_PARSING_OBJS)))

.PHONY: clean_ft_parsing

-include $(FT_PARSING_DEPS)

$(FT_PARSING_OBJ_DIR):
	@if [ ! -f .ft_parsing_announced ]; then \
		echo "$(Color_Off)[Announcer] Building $(Cyan)$(FT_PARSING_MODULE_NAME) $(Color_Off)module"; \
		touch .ft_parsing_announced; \
	fi
	@$(foreach dir, $(FT_PARSING_OBJ_DIR), mkdir -p $(dir);)

$(OBJ_PATH)parsing/%.o: $(SRC_PATH)parsing/%.c | $(FT_PARSING_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || (echo "$(Color_Off)[Announcer] $(Yellow)$(FT_PARSING_MODULE_NAME)$(Purple)'s compilation $(Red)failed$(Color_Off) :[" && exit 1)


clean_ft_parsing:
	@rm -rf $(FT_PARSING_OBJS) $(FT_PARSING_DEPS)
	@rm -f .ft_parsing_announced
	@echo "$(Color_Off)[Announcer] Removed $(Cyan)$(FT_PARSING_MODULE_NAME) $(Color_Off)module's object files"

