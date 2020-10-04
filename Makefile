NAME = test
INC = /usr/lib
SRC = main.c step1.c sphere.c plane.c triangle.c
OBJ = $(SRC:.c=.o)

all	:$(NAME)

$(NAME)	:$(OBJ)
	gcc -o $(NAME) $(OBJ) -L./minilibx/ -lmlx -L$(INC) -lXext -lX11 -lm

%.o:%.c mlx.h 
	gcc -c $(SRC) -o $@  
