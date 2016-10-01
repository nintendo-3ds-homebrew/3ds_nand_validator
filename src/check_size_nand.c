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
			printf(YELLOW"Size_nand1 = %d\n"END, *nand);
			printf(GREEN"Size nand OK\n"END);
			return (EXIT_SUCCESS);
		}
		++i;
	}
	return (EXIT_FAILURE);
}
