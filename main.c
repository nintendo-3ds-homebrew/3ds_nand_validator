#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>

#define RED		"\033[031m"
#define GREEN	"\033[032m"
#define YELLOW	"\033[033m"
#define END		"\033[0m"

int				check_nand_valid(unsigned int *nand)
{
	int				i = 0;
	unsigned int	size[] = {988807168, 1979711488, 1000341504, 1300234240,		/*2DS nand*/
							988807168, 1000341504,									/*Old 3ds_nand*/
							1979711488, 1300234240, 1954545664,};					/*N3ds nand*/

	while  (i < 9)
	{
		if (*nand == size[i])
		{
			printf(YELLOW"Size_nand1 = %d\n"END, *nand);
			printf(GREEN"Size nand OK\n"END);
			return (EXIT_SUCCESS);
		}
		++i;
	}
	return (EXIT_FAILURE);
}

unsigned int	check_size_nand(char *nand, struct stat *sb)
{
	unsigned int	size_nand;

	stat(nand, sb);
	size_nand = sb->st_size;
	return (size_nand);
}

int	main(int argc, char **argv)
{
	unsigned int	size_nand1;
	unsigned int	size_nand2;
	struct stat		sb;

	if (argc != 3)
	{
		printf("Usage : ./a.out nand1.bin nand2.bin\n");
		return (EXIT_FAILURE);
	}
	size_nand1 = check_size_nand(argv[1], &sb);
	size_nand2 = check_size_nand(argv[2], &sb);
	printf("%d\n", size_nand1);
	printf("%d\n", size_nand2);
	if (check_nand_valid(&size_nand1) == EXIT_FAILURE)
	{
		printf(RED"Size nand1 KO\n"END);
		return (EXIT_FAILURE);
	}
	if (check_nand_valid(&size_nand2) == EXIT_FAILURE)
	{
		printf(RED"Size nand2 KO\n"END);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
