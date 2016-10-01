#include "../include/nand_checker.h"

int				compare_nand(unsigned int size_nand)
{
	unsigned int	i = 0;
	FILE			*n1 = NULL;
	FILE			*n2 = NULL;

	if ((n1 = fopen("./nands/nand1.bin", "r")) == NULL || (n2 = fopen("./nands/nand2.bin", "r")) == NULL )
	{
		printf(RED"Unable to open nand1.bin or nand2.bin\n"END);
		return (EXIT_FAILURE);
	}
	while (i < size_nand)
	{
		if (fgetc(n1) != fgetc(n2))
		{
			printf(RED"Nands are not same !\n"END);
			fclose(n1);
			fclose(n2);
			return (EXIT_FAILURE);
		}
		/*if (i == 272)*/
			/*printf("lol\n");*/
		++i;
	}
	printf(GREEN"Nand are the same !\n"END);
	fclose(n1);
	fclose(n2);
	return (EXIT_SUCCESS);
}
