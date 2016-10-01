NAME = 3ds_nand_checker

SRCS = src/*.c

OBJS = ./*.o

INCLUDE = ./include/nand_checker.h

FLAGS = -Wall -Wextra -Werror

all:
	@gcc -c $(FLAGS) $(SRCS)
	@gcc $(OBJS) -o $(NAME)
	@printf "$(NAME) created.\n"

clean:
	@printf "clean ...\n"
	@rm -fr *.o $(NAME)
