NAME := miniRT

HEADERS_DIRECTORY := include
HEADERS := $(HEADERS_DIRECTORY)/minirt.h
HEADERS += $(HEADERS_DIRECTORY)/data.h
HEADERS += $(HEADERS_DIRECTORY)/functions.h
HEADERS += $(HEADERS_DIRECTORY)/settings.h

SOURCES_DIRECTORY := src
OBJECTS_DIRECTORY := build

SOURCES := $(addprefix $(SOURCES_DIRECTORY)/,\
		main.c \
		$(addprefix parsing/, identifiers.c identifiers2.c parser.c factories.c factories2.c factories3.c factories4.c \
			factories_utils.c factories_utils2.c factories_utils3.c checker.c init.c rt_file.c counter.c) \
		$(addprefix exit/, prints.c error.c free.c free2.c) \
		$(addprefix render/, render.c calculate_pixel.c shoot_ray.c shading.c) \
		$(addprefix mlx_hooks/, mlx.c events.c mouse.c) \
		$(addprefix intersection_tests/, cylinder.c intersection_test_shadow.c intersection_test_visibility.c plane.c \
			sphere.c) \
		$(addprefix math/, math.c math_utils.c dot_in_place_33.c dot_in_place_44.c rodrigues.c) \
)

OBJECTS := $(patsubst $(SOURCES_DIRECTORY)/%.c,$(OBJECTS_DIRECTORY)/%.o, $(SOURCES))

LIBFT_DIRECTORY := lib/libft
LIBFT := $(LIBFT_DIRECTORY)/libft.a

MLX_DIRECTORY := lib/minilibx-linux
LIBMLX := $(MLX_DIRECTORY)/libmlx.a

LIB_FLAGS := -L$(LIBFT_DIRECTORY)
LIB_FLAGS += -L$(MLX_DIRECTORY)    
LIB_FLAGS += -lft
LIB_FLAGS += -lmlx_Linux
LIB_FLAGS += -lXext
LIB_FLAGS += -lX11
LIB_FLAGS += -lm

CC := cc

CFLAGS := -Wall -Wextra -Werror
CFLAGS += -g
CFLAGS += -Wuninitialized
CFLAGS += -mavx
CFLAGS += -Ofast
CFLAGS += -mavx
CFLAGS += -march=native
CFLAGS += -ffunction-sections
CFLAGS += -flto
CFLAGS += -finline-functions
CFLAGS += -I$(HEADERS_DIRECTORY) -I$(LIBFT_DIRECTORY) -I$(MLX_DIRECTORY)

all: $(OBJECTS_DIRECTORY) $(LIBMLX) $(LIBFT) $(NAME)

YELLOW=\033[0;33m
GREEN=\033[0;32m
NC=\033[0m

$(LIBMLX):
	@if [ ! -d "$(MLX_DIRECTORY)" ]; then \
			mkdir -p $(MLX_DIRECTORY); \
			echo "$(YELLOW)Cloning MiniLibX repository...$(NC)"; \
			git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIRECTORY); \
	fi
	@echo "$(YELLOW)Compiling MiniLibX...$(NC)"
	@make -s -C $(MLX_DIRECTORY) >/dev/null 2>&1;
	@echo "$(GREEN)MiniLibX compiled$(NC)"

$(NAME): $(OBJECTS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIB_FLAGS) -o $(NAME) -Wl,--gc-sections

$(OBJECTS_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.c $(HEADERS) | $(OBJECTS_DIRECTORY)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(NC)"
	@make -C $(LIBFT_DIRECTORY) >/dev/null 2>&1;
	@echo "$(GREEN)Libft compiled$(NC)"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@rm -rf $(MLX_DIRECTORY) clean >/dev/null 2>&1
	@make -s -C $(LIBFT_DIRECTORY) fclean >/dev/null 2>&1

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
