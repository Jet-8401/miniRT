NAME = miniRT
FILES = minirt.c \
		error.c \
		list_utils.c \
		utils.c \
		parsing_checker.c \
		parsing.c \
		ft_atof.c \
		element_init.c \
		element_init2.c \
		props_init.c \
		forms_init.c \
		add_list.c \
		mlx_init.c 
SOURCES = $(addprefix sources/,$(FILES))
OUT = bins/

BINS = $(addprefix $(OUT),$(SOURCES:.c=.o))

LIBS_DIRS = libs/libft-gc
LIBS = libs/mlx/libmlx.a libs/libft-gc/libft-gc.a

CFLAGS = -g -O3 -Wall -Werror -Wextra -Wpedantic
FLAGS = -Llibs/mlx -L/usr/lib -lmlx -lXext -lX11 -lm -I/usr/include

.SECONDEXPANSION:

all:	$(LIBS_DIRS) $(NAME)

$(LIBS_DIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

$(NAME): $(BINS)
	make -C libs/mlx
	$(CC) $^ $(FLAGS) -o $@ $(LIBS)

$(OUT)%.o:	%.c $$(@D)/.f
	$(CC) $(CFLAGS) -c $< -o $@

%/.f:
	mkdir -p $(dir $@)

clean: $(LIBS_DIRS)
	make -C libs/mlx clean
	rm -rf $(OUT)

fclean: $(LIBS_DIRS) clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	$(LIBS_DIRS)

# https://www.cmcrossroads.com/article/making-directories-gnu-make
