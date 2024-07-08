NAME = miniRT
FILES =  
SOURCES = $(addprefix sources/,$(FILES))
OUT = bins/

BINS = $(addprefix $(OUT),$(SOURCES:.c=.o))

LIBS_DIRS = libs/libft \
			libs/gc
LIBS = libs/libft/libft.a \
	   libs/gc/garbage-collector-lib.a

CFLAGS = -Wall -Werror -Wextra -Wpedantic -g

.SECONDEXPANSION:

all:	$(LIBS_DIRS) $(NAME)

$(LIBS_DIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

$(NAME): $(BINS)
	$(CC) $^ -o $@ -lreadline $(LIBS)

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
