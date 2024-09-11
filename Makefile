NAME = miniRT
NAME_BONUS = miniRT_bonus
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
		mlx_init.c \
		render.c \
		mlx_events.c \
		3Dvect.c \
		3Dvect2.c \
		color_vect.c \
		form_intersect.c \
		fps_counter.c \
		intersect.c \
		light.c \
		utils2.c \
		vec3D_utils.c \
		vec3D_utils2.c \
		cylinder_utils.c

FILES_BONUS = $(wildcard bonus/source/*.c)
SOURCES = $(addprefix sources/,$(FILES))
SOURCES_BONUS = $(FILES_BONUS)
OUT = bins/

BINS = $(addprefix $(OUT),$(SOURCES:.c=.o))
BINS_BONUS = $(addprefix $(OUT),$(SOURCES_BONUS:.c=.o))

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

$(NAME_BONUS): $(BINS_BONUS) 
	make -C libs/mlx
	$(CC) $^ $(FLAGS) -o $@ $(LIBS)

$(OUT)%.o:	%.c $$(@D)/.f
	$(CC) $(CFLAGS) -c $< -o $@

%/.f:
	mkdir -p $(dir $@)

bonus: $(LIBS_DIRS) $(NAME_BONUS)

clean: $(LIBS_DIRS)
	make -C libs/mlx clean
	rm -rf $(OUT)

fclean: $(LIBS_DIRS) clean
	rm -f $(NAME) $(NAME_BONUS)

re:	fclean all

.PHONY:	$(LIBS_DIRS)

# https://www.cmcrossroads.com/article/making-directories-gnu-make
