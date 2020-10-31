MAKE_VARS_LOC = ../
include $(MAKE_VARS_LOC)make.vars

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -I. -c

OBJ = $(SRC_FT:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

%.o: %.c libft.h
	@echo "..."
	@gcc $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
