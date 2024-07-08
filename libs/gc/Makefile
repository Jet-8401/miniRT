NAME =		garbage-collector-lib.a
FILES =		gc.c \
			gc-alloc.c \
			gc-free.c \
			gc-utils.c

#SOURCES =	$(addprefix srcs/,$(FILES))
OUT =		bins/

BINS =		$(addprefix $(OUT),$(FILES:.c=.o))

CFLAGS =	-Wall -Werror -Wextra -Wpedantic -g -O3

.SECONDEXPANSION:

all:	$(NAME)

$(NAME): $(BINS)
	ar -rc $@ $?

$(OUT)%.o:	%.c $$(@D)/.f
	$(CC) $(CFLAGS) -c $< -o $@

%/.f:
	mkdir -p $(dir $@)

clean:
	rm -f $(BINS)

fclean: clean
	rm -rf $(OUT)
	rm -f $(NAME)

re:	fclean all

# https://www.cmcrossroads.com/article/making-directories-gnu-make
