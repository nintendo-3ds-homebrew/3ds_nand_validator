#include "../include/nand_checker.h"

unsigned int	get_size_nand(char *nand_filename)
{
	struct	stat	nand_stat;

	if (lstat(nand_filename, &nand_stat) < 0)
	{
		if (stat(nand_filename, &nand_stat) < 0)
		{
			fprintf(stderr, "error stat: %s: %s\n",  strerror(errno), nand_filename);
			exit(EXIT_FAILURE);
		}
	}
	return(nand_stat.st_size);
}

int				check_nand_valid(unsigned int *nand)
{
	int				i = 0;
	unsigned int	size[] = {	988807168, 1979711488, 1000341504, 1300234240,	/*2DS nand*/
								988807168, 1000341504,							/*Old 3ds_nand*/
								1979711488, 1300234240, 1954545664				/*N3ds nand*/
	};

	while  (i < SIZE_LEN)
	{
		if (*nand == size[i])
		{
			printf(YELLOW"Size nand = %d octets\n"END, *nand);
			return (EXIT_SUCCESS);
		}
		++i;
	}
	return (EXIT_FAILURE);
}

void	check_size_nand(unsigned int *size_nand1, unsigned int *size_nand2, char **argv)
{
	printf(WHITE"===================================\n"END);
	printf(CYAN"Checking size %s ...\n"END, argv[1]);
	/*check if nand1 and nand2 have same size*/
	if (*size_nand1 != *size_nand2)
	{
		printf(RED"Size %s and %s are not same\n"END, argv[1], argv[2]);
		exit(EXIT_FAILURE);
	}
	/*check if nand1 have a good size*/
	if (check_nand_valid(size_nand1) == EXIT_FAILURE)
	{
		printf(RED"Size %s are bad\n"END, argv[1]);
		exit (EXIT_FAILURE);
	}
	printf(GREEN"Size of %s [Ok]\n"END, argv[1]);

	printf(WHITE"===================================\n"END);

	printf(CYAN"Checking size %s ...\n"END, argv[2]);
	/*check if nand2 have a good size*/
	if (check_nand_valid(size_nand2) == EXIT_FAILURE)
	{
		printf(RED"Size %s are bad\n"END, argv[2]);
		exit (EXIT_FAILURE);
	}
	printf(GREEN"Size of %s [Ok]\n"END, argv[2]);

	printf(WHITE"===================================\n"END);
}
