# Program name
NAME = cub3D

# Colors
GREEN = \033[32m
RED = \033[31m
MAGENTA = \033[35m
YELLOW = \033[33m
CYAN = \033[36m
RESET = \033[0m

# Compile Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
MLX_FLAGS = -lXext -lX11 -lm -lz

# Libft
LIBFT = includes/libft/libft.a
LIBFT_DIR = includes/libft

# MLX
MLX_DIR = includes/minilibx-linux/
MLX = $(MLX_DIR)libmlx.a

# Source files
SRC_DIR = src/
SRC =	src/color.c \
		src/cub3d.c \
		src/exit.c \
		src/flood.c \
		src/handle_key.c \
		src/import.c \
		src/init.c \
		src/map.c \
		src/move.c \
		src/parsing.c \
		src/player.c \
		src/raycasting.c \
		src/raycasting2.c \
		src/raycasting3.c \
		src/render.c \
		src/textures.c \
		src/utils.c

# Object files
OBJS_DIR = build/
OBJS = $(SRC:src/%.c=$(OBJS_DIR)%.o)

# Include directories
INCLUDES =	-I ./includes \
			-I ./includes/libft/

# Targets
all: $(NAME)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(CYAN)Linking $@...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@ $(LDFLAGS)
	@echo "$(GREEN)$@ is ready!$(RESET)"

$(LIBFT):
	@echo "$(MAGENTA)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(MAGENTA)Libft built successfully!$(RESET)"

$(MLX):
	@echo "$(MAGENTA)Making MinilibX...$(RESET)"
	@make -C $(MLX_DIR)
	@echo "$(MAGENTA)MinilibX built successfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning up object files...$(RESET)"
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "$(RED)Object files removed.$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME) libft, and MinilibX...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)$(NAME) and libft removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
