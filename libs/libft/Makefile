# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 14:19:42 by ruidos-s          #+#    #+#              #
#    Updated: 2025/02/21 12:29:19 by ruidos-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	ft_atol.c  ft_atoi.c  ft_isalnum.c  ft_isalpha.c  ft_isascii.c  ft_isdigit.c  ft_isprint.c\
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c\
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
		ft_memchr.c ft_memcmp.c ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c\
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isspace.c\
		ft_printf.c print_format.c printf_putchar.c printf_putstr.c printf_putnbr.c printf_putptr.c\
		get_next_line.c get_next_line_utils.c ft_strndup.c ft_strcpy.c ft_realloc.c\
		ft_strtok.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c 

OBJS_DIR = obj
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS = $(BONUS:%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "📂 Created obj directory"

$(NAME): $(OBJS_DIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "✅ Libft compiled successfully!"

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS_DIR) $(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "✨ Bonus part compiled!"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "🧹 Cleaned object files"

fclean: clean
	@rm -f $(NAME) ./test*
	@echo "🗑️ Fully cleaned project"

re: fclean all

test: $(SRCS) main.c
	@$(CC) $(CFLAGS) $(SRCS) $(BONUS) main.c -o teste_main
	@echo "🛠️ Test binary created"

git:
	@git add .
	@git commit -m "guardar coisas no github"
	@git push
	@git status

.PHONY: all clean fclean re test git