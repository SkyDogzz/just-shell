# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 21:12:49 by yandry            #+#    #+#              #
#    Updated: 2025/04/27 12:11:48 by yandry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Purple=$(shell tput setaf 5)
Red=$(shell tput setaf 1)
Cyan=$(shell tput setaf 6)
Blue=$(shell tput setaf 4)
Yellow=$(shell tput setaf 3)
Green=$(shell tput setaf 2)
Color_Off=$(shell tput sgr0)

NAME := libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
INCLUDES := -I ./includes

ifdef DEBUG
CFLAGS += -g3
endif
ifdef FSAN
CFLAGS += -fsanitize=address
endif

SRC_PATH := src/
OBJ_PATH := obj/

FT_FILE := ft_get_next_line.c \
		   ft_putchar_fd.c \
		   ft_putendl_fd.c \
		   ft_putnbr_fd.c \
		   ft_putstr_fd.c

FT_LIST := ft_lstadd_back.c \
		   ft_lstadd_front.c \
		   ft_lstclear.c \
		   ft_lstcpyline.c \
		   ft_lstdelone.c \
		   ft_lstfoundchr.c \
		   ft_lstiter.c \
		   ft_lstlast.c \
		   ft_lstlentochr.c \
		   ft_lstmap.c \
		   ft_lstnew.c \
		   ft_lstsize.c \
		   ft_lsttoarray.c \
		   ft_lstcpy_if.c

FT_MEMORY := ft_bzero.c \
			 ft_calloc.c \
			 ft_memchr.c \
			 ft_memcmp.c \
			 ft_memcpy.c \
			 ft_memmove.c \
			 ft_memset.c

FT_PRINTF := ft_printf.c \
			 ft_snprintf.c \
			 ft_dprintf.c \
			 internal/ft_vsnprintf.c \
			 internal/format_processor.c \
			 internal/number_processor.c

FT_STRING := ft_atoi.c \
			 ft_isalnum.c \
			 ft_isalpha.c \
			 ft_isascii.c \
			 ft_isdigit.c \
			 ft_isprint.c \
			 ft_itoa.c \
			 ft_split.c \
			 ft_strchr.c \
			 ft_strdup.c \
			 ft_striteri.c \
			 ft_strjoin.c \
			 ft_strlcat.c \
			 ft_strlcpy.c \
			 ft_strlen.c \
			 ft_strmapi.c \
			 ft_strncmp.c \
			 ft_strnstr.c \
			 ft_strrchr.c \
			 ft_strtrim.c \
			 ft_substr.c \
			 ft_tolower.c \
			 ft_toupper.c \
			 ft_strappend.c

FT_UTILS := ft_free_array.c

SRC := $(addprefix ft_file/, $(FT_FILE)) \
	   $(addprefix ft_list/, $(FT_LIST)) \
	   $(addprefix ft_memory/, $(FT_MEMORY)) \
	   $(addprefix ft_printf/, $(FT_PRINTF)) \
	   $(addprefix ft_string/, $(FT_STRING)) \
	   $(addprefix ft_utils/, $(FT_UTILS))

SRCS := $(addprefix $(SRC_PATH), $(SRC))
OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_PATH), $(OBJ))

OBJ_DIRS := $(sort $(dir $(OBJS)))

.PHONY: all clean fclean re norm help .build_msg create_dirs

all: $(NAME)

-include $(OBJS:.o=.d)

.build_msg:
	@if [ ! -f .libft_building_announced ]; then \
		echo "$(Color_Off)[Announcer] Building $(Purple)$(NAME)$(Color_Off)"; \
		touch .libft_building_announced; \
	fi

create_dirs:
	@mkdir -p $(OBJ_DIRS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || (echo "$(Color_Off)[Announcer] $(Yellow)$(NAME)'s compilation $(Red)failed$(Color_Off) :[" && exit 1)

$(NAME): .build_msg create_dirs $(OBJS)
	@ar -rsc $@ $(OBJS)
ifeq ($(DEBUG), 1)
	@if [ ! -f .libft_compiled_announced ]; then \
		echo "$(Color_Off)[Announcer] $(Purple)$(NAME)$(Color_Off) has been compiled in $(Red)DEBUG$(Color_Off) mode!"; \
		touch .libft_compiled_announced; \
	fi
else
	@if [ ! -f .libft_compiled_announced ]; then \
		echo "$(Color_Off)[Announcer] $(Purple)$(NAME)$(Color_Off) has been compiled :D! Happy sufferi- I mean coding... hahaha... yeah..."; \
		touch .libft_compiled_announced; \
	fi
endif

clean:
	@rm -rf $(OBJ_PATH)
	@rm -f .libft_building_announced .libft_compiled_announced
	@echo "$(Color_Off)[Announcer] Removed object and dependency files for $(Purple)$(NAME)$(Color_Off)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(Color_Off)[Announcer] Removed $(Purple)$(NAME)$(Color_Off)"

norm:
	@norminette | grep -v "OK" && exit 1 || echo "$(Color_Off)[Announcer] $(Green)All files follow the Norm$(Color_Off)!!! (that was painful though)"

re: fclean all

help:
	@echo "$(Yellow)Available targets:$(Color_Off)"
	@echo "  $(Green)all$(Color_Off)     : Build the $(NAME) library"
	@echo "  $(Green)clean$(Color_Off)   : Remove object and dependency files"
	@echo "  $(Green)fclean$(Color_Off)  : Remove object, dependency files and the library"
	@echo "  $(Green)re$(Color_Off)      : Rebuild the library"
	@echo "  $(Green)norm$(Color_Off)    : Runs the norminette on the code. Let the battle begin"
	@echo "  $(Green)help$(Color_Off)    : Display this help message"
	@echo ""
	@echo "$(Yellow)Build options:$(Color_Off)"
	@echo "  $(Green)DEBUG=1$(Color_Off) : Enable debug symbols"
	@echo "  $(Green)FSAN=1$(Color_Off)  : Enable Address Sanitizer"
