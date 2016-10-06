NAME = 3ds_nand_validator

SRCS = src/*.c

OBJS = ./*.o

INCLUDE = ./include/nand_validator.h

FLAGS = -O3 #-Wall -Wextra -Werror

all:
	@gcc -c $(FLAGS) $(SRCS)
	@gcc $(OBJS) -o $(NAME)
	@printf "$(NAME) created.\n"

clean:
	@printf "clean ...\n"
	@rm -fr *.o $(NAME)
