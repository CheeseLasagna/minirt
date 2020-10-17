NAME = test
SRC = args_read.c main.c stuff.c get/get_next_line.c get/get_next_line_utils.c parse.c parse_pl_sp.c parse_res.c parse_sq_cy.c parse_tr_l.c parse_cam_amb.c cdcs.c convert.c listadd.c listadd2.c free.c free2.c
OBJ = $(SRC:.c=.o)

all: 
	gcc -o $(NAME) $(SRC) -D BUFFER_SIZE=10

