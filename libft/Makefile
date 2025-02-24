# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandry <yandry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 21:12:49 by yandry            #+#    #+#              #
#    Updated: 2025/02/01 14:29:12 by yandry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Purple=$(shell tput setaf 5)
Red=$(shell tput setaf 1)
Cyan=$(shell tput setaf 6)
Blue=$(shell tput setaf 4)
Yellow=$(shell tput setaf 3)
Green=$(shell tput setaf 2)
Color_Off=$(shell tput sgr0)

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

ifdef DEBUG
CFLAGS += -g3
endif
ifdef FSAN
CFLAGS += -fsanitize=address
endif

SRC_PATH = src/
OBJ_PATH = obj/

FT_FILE=ft_get_next_line.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c

FT_LIST=ft_lstadd_back.c \
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
		ft_lsttoarray.c

FT_MEMORY=ft_bzero.c \
		  ft_calloc.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c

FT_PRINTF=ft_printf.c \
		  ft_printf_utils.c

FT_STRING=ft_atoi.c \
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

# prepend the respective path to the files of each variable
# so FT_FILE will be ft_file/<source>.c and so on
SRC = $(addprefix ft_file/, $(FT_FILE)) \
	  $(addprefix ft_list/, $(FT_LIST)) \
	  $(addprefix ft_memory/, $(FT_MEMORY)) \
	  $(addprefix ft_printf/, $(FT_PRINTF)) \
	  $(addprefix ft_string/, $(FT_STRING))

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
INCLUDES = -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo -n "$(Cyan)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 
	@echo -n "$(Color_Off)"

$(OBJ_PATH):
	@echo -n "$(Blue)"
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)ft_file
	mkdir -p $(OBJ_PATH)ft_list
	mkdir -p $(OBJ_PATH)ft_memory
	mkdir -p $(OBJ_PATH)ft_printf
	mkdir -p $(OBJ_PATH)ft_string
	@echo "$(Color_Off)[Announcer] $(Purple)Created object files directory$(Color_Off)"

$(NAME): $(OBJ_PATH) $(OBJS)
	@echo -n "$(Green)"
	ar -rsc ${NAME} ${OBJS}
ifeq ($(DEBUG), 1)
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) has been compiled in $(Red)DEBUG$(Purple) mode!$(Color_Off)"
else
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) has been compiled :D! Happy sufferi- I mean coding... hahaha... yeah...$(Color_Off)"
endif

clean:
	@echo -n "$(Blue)"
	rm -rf $(OBJ_PATH)
	@echo "$(Color_Off)[Announcer] $(Purple)Removed object files of $(NAME)$(Color_Off)"

fclean: clean
	@echo -n "$(Blue)"
	rm -f $(NAME)
	@echo "$(Color_Off)[Announcer] $(Purple)$(NAME) is GONE!!$(Color_Off)"

norm:
	@norminette | grep -v "OK" && exit 1 || echo "$(Color_Off)[Announcer]$(Purple) All files follow the $(Green)Norm$(Purple)!!! (that was painful though)$(Color_Off)"

re: fclean all

.PHONY: all clean fclean re
