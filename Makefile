NAME = miniRT
FILES = minirt.c \
		error.c \
		list_utils.c \
		utils.c \
		parsing.c \
		props_init.c \
		forms_init.c \
		element_init.c \
		element_init2.c \
		ft_atof.c \
		parsing_checker.c \
		add_list.c
SOURCES = $(addprefix sources/,$(FILES))
OUT = bins/

BINS = $(addprefix $(OUT),$(SOURCES:.c=.o))

LIBS_DIRS = libs/libft-gc \
			libs/mlx
LIBS = libs/libft-gc/libft-gc.a \
	   libs/mlx/libmlx.a

CFLAGS = -Wall -Wextra -Werror -Wpedantic -g -O3 -Iheaders
LFLAGS = -Llibs/mlx -lmlx -L/usr/lib -lXext -lX11 -lm -I/usr/include

.SECONDEXPANSION:

all:	$(LIBS_DIRS) $(NAME)

$(LIBS_DIRS):
	- $(MAKE) -C $@ $(MAKECMDGOALS)

$(NAME): $(BINS)
	$(CC) $(LFLAGS) $^ -o $@ $(LIBS)

$(OUT)%.o:	%.c $$(@D)/.f
	$(CC) $(CFLAGS) -c $< -o $@

%/.f:
	mkdir -p $(dir $@)

clean: $(LIBS_DIRS)
	rm -rf $(OUT)

fclean: $(LIBS_DIRS) clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	$(LIBS_DIRS)

# https://www.cmcrossroads.com/article/making-directories-gnu-make
