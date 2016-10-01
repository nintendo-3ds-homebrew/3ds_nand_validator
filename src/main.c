#include "../include/nand_checker.h"

void	create_folder(void)
{
	struct stat	st;

	if (stat("./nands", &st) == -1)
		mkdir("./nands", 0700);
}

int	main(int argc, char **argv)
{
	unsigned int	size_nand1;
	unsigned int	size_nand2;

	if (argc != 3)
	{
		printf("Usage : ./a.out nand1.bin nand2.bin\n");
		return (EXIT_FAILURE);
	}
	create_folder();
	size_nand1 = get_size_nand(argv[1]);
	size_nand2 = get_size_nand(argv[2]);
	if (check_nand_valid(&size_nand1) == EXIT_FAILURE)
	{
		printf(RED"Size nand1 are bad\n"END);
		return (EXIT_FAILURE);
	}
	if (check_nand_valid(&size_nand2) == EXIT_FAILURE)
	{
		printf(RED"Size nand2 are bad\n"END);
		return (EXIT_FAILURE);
	}
	compare_nand(size_nand1);
	return (EXIT_SUCCESS);
}
