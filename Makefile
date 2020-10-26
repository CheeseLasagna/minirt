NAME = test
INC = /usr/lib
SRC = main.c \
	window.c \
	step1.c \
	triangle.c \
	triangle2.c \
	sphere.c \
	sphere2.c \
	plane.c \
	plane2.c \
	square.c \
	square2.c \
	square3.c \
	cylinder.c \
	cylinder2.c \
	cylinder3.c \
	additional.c \
	additional2.c \
	shadow.c \
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

all	:$(NAME)

$(NAME)	:$(OBJ)
	(cd libft; make all)
	gcc -o $(NAME) $(OBJ) -L./libft -lft -L./minilibx/ -lmlx -L$(INC) -lXext -lX11 -lm

%.o:%.c mlx.h 
	gcc -c $(SRC) -o $@  

clean:
	rm test $(OBJ)

fclean: clean
	rm shot.bmp
	(cd libft; make fclean)
