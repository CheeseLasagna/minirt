NAME = miniRT 
INC = /usr/lib
SRC = src/main.c \
	src/window.c \
	src/save_bmp.c\
	src/step1.c \
	src/triangle.c \
	src/triangle2.c \
	src/sphere.c \
	src/sphere2.c \
	src/plane.c \
	src/plane2.c \
	src/square.c \
	src/square2.c \
	src/square3.c \
	src/cylinder.c \
	src/cylinder2.c \
	src/cylinder3.c \
	src/additional.c \
	src/additional2.c \
	src/shadow.c \
	parser/args_read.c \
	parser/cdcs.c \
	parser/convert.c \
	parser/free.c \
	parser/free2.c \
	parser/listadd.c \
	parser/listadd2.c \
	parser/parse_cam_amb.c \
	parser/parse_pl_sp.c \
	parser/parse_res.c \
	parser/parse_sq_cy.c \
	parser/parse_tr_l.c \
	parser/parse.c \
	parser/get/get_next_line.c \
	parser/get/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all	:$(NAME)

$(NAME)	:$(OBJ)
	(cd minilibx; make)
	(cd libft; make all)
	gcc $(FLAGS) -o $(NAME) $(OBJ) -L./libft -lft -L./minilibx/ -lmlx -L$(INC) -lXext -lX11 -lm

%.o:%.c mlx.h 
	gcc $(FLAGS) -c $(SRC) -o $@  

clean:
	rm miniRT $(OBJ)

fclean: clean
	(cd minilibx; make clean)
	(cd libft; make fclean)
	rm shot.bmp

re: fclean all
