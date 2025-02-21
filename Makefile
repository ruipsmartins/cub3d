NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I include

SRCS_DIR = src
SRCS_FILES = main.c #render.c parser.c input.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_DIR = obj
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

LIBFT = ./libs/libft/libft.a
MLX = ./libs/mlx_linux/libmlx.a -lXext -lX11 -lm -lz

all: $(NAME)

$(LIBFT):
	@echo "🔨 Compiling Libft..."
	@make -C ./libs/libft
	@echo "✅ Libft compiled successfully!"

$(MLX):
	@echo "🔨 Compiling MinilibX..."
	@make -C ./libs/mlx_linux
	@echo "✅ MinilibX compiled successfully!"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "📂 Created obj directory"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "🚀 Cub3D compiled successfully!"

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C ./libs/libft
	@make clean -C ./libs/mlx_linux
	@echo "🧹 Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libs/libft
	@echo "🗑️ Fully cleaned project"

re: fclean all

git:
	git add .
	git commit -m "enviar para o github"
	git push
	git status

valgrind:
	valgrind --show-leak-kinds=all --leak-check=full ./cub3D

.PHONY: all clean fclean re git valgrind