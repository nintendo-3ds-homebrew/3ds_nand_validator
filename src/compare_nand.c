#include "../include/nand_checker.h"

static int	check_NCSD(char *buff1)
{
	if (buff1[256] == 'N' && buff1[257] == 'C' && buff1[258] == 'S' && buff1[259] == 'D')
		printf(GREEN"NCSD found !\n"END);
	else
	{
		printf(RED"NCSD not found !\nDumps are bad !\n"END);
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	compare_nand(char *nand1, char *nand2)
{
	int				fd1;
	int				fd2;
	int				ret1 = 0;
	int				ret2 = 0;
	char			*buff1 = (char *)malloc(sizeof(char) * BUFF_SIZE);
	char			*buff2 = (char *)malloc(sizeof(char) * BUFF_SIZE);
	char			i = 0;

	if ((fd1 = open(nand1, O_RDONLY)) == -1)
	{
		printf("Unable to open %s : %s\n", nand1, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if ((fd2 = open(nand1, O_RDONLY)) == -1)
	{
		printf("Unable to open %s : %s\n", nand2, strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf(CYAN"Reading nand ...\n"END);
	while ((ret1 = read(fd1, buff1, BUFF_SIZE)) > 0 && (ret2 = read(fd2, buff2, BUFF_SIZE)) > 0)
	{
		if (strcmp(buff1, buff2) != 0)
		{
			printf(RED"Nand are not same\n"END);
			close(ret1);
			close(ret2);
			free(buff1);
			free(buff2);
			exit(EXIT_FAILURE);
		}
		if (i == 0)
		{
			check_NCSD(buff1);
			i = 1;
		}
	}
	printf(GREEN"Nand are the same\n"END);
	close(ret1);
	close(ret2);
	free(buff1);
	free(buff2);
	return (EXIT_FAILURE);
}
