MAKE_VARS_LOC = ./
include $(MAKE_VARS_LOC)make.vars

GCC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = RT

INC_DIR = include/
SRC_DIR = src/
OBJ_DIR = obj/
FT_DIR = libft/
SDL_DIR = sdl/

INC_RT = -I $(INC_DIR)
INC_FT = -I $(FT_DIR)
INC_SDL = -I $(SDL_DIR)include

LIB_SDL = -L ./sdl/lib -lSDL2 #-lOpenCL
LIB_MATH = -L /usr/lib -lm
LIB_FT = -L ./libft -lft

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
FRAMEWORKS = -framework OpenGL -framework AppKit -framework OpenCL

SRC = main.c pic.c construct_scene.c cl.c effect.c parser.c \
parser_functions1.c parser_functions2.c parser_functions3.c \
controls.c external_functions.c effect2.c effect3.c controls_inner.c \
controls_keybords.c
OBJ = $(SRC:.c=.o)
INC = rtv1.h

SRCS = ${addprefix $(SRC_DIR), $(SRC)}
OBJS = ${addprefix $(OBJ_DIR), $(OBJ)}

all: $(NAME)

$(NAME): $(OBJS) sdl/lib/libSDL2.a $(INC_DIR)$(INC) ${addprefix $(FT_DIR), $(SRC_FT)} ${addprefix $(FT_DIR), $(INCLUDE_FT)}
	@echo "Compiling libft"
	@ make -C libft/
	@echo "libft compiled\n"
	@echo "Compiling $(NAME) .exe file\n"
	@$(GCC) $(FLAGS) $(OBJS) $(INC_RT)$(INC) $(LIB_FT) $(LIB_SDL) $(LIB_MATH) $(FRAMEWORKS) -o $@
	@echo "Project compilation finished!"

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC_DIR)$(INC)
	@echo "Compiling a .o file for the main project"
	@ ${GCC} -c $(FLAGS) $(INC_RT) $(INC_FT) $(INC_SDL) $< -o $@
	
clean:
	@echo "Cleaning"
	@echo "..."
	@rm -f $(OBJS)
	@echo "..."
	@echo "..."
	@make clean -C ./libft
	@echo "Cleaned"

fclean: clean
	@echo "Cleaning everything"
	@echo "..."
	@make fclean -C ./libft
	@echo "..."
	@make uninstall -C ./sdl
	@echo "..."
	@make clean -C ./sdl
	@echo "..."
	@rm -f $(NAME)
	@echo "Everything clean"

sdl/lib/libSDL2.a:
	cd sdl && ./configure --prefix=$(ROOT_DIR)/sdl/ && cd ..
	make -C ./sdl
	make install -C ./sdl

re:	fclean all