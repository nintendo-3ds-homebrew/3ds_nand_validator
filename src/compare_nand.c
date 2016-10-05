#include "../include/nand_checker.h"

static int	check_NCSD(FILE **log, char *buff1)
{
	if (buff1[256] == 'N' && buff1[257] == 'C' && buff1[258] == 'S' && buff1[259] == 'D')
	{
		write_log_time(log);
		fprintf(*log, "NCSD found !\n");
	}
	else
	{
		printf(RED"Dumps are bad !\n"END);
		write_log_time(log);
		fprintf(*log, "NCSD not found !\n");
		write_log_time(log);
		fprintf(*log, "Dumps are bad !\n");
		fclose(*log);
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	compare_nand(FILE **log, char *nand1, char *nand2)
{
	int				fd1;
	int				fd2;
	int				ret1 = 0;
	int				ret2 = 0;
	char			*buff1 = (char *)malloc(sizeof(char) * BUFF_SIZE);
	char			*buff2 = (char *)malloc(sizeof(char) * BUFF_SIZE);
	int				i = 0;

	if ((fd1 = open(nand1, O_RDONLY)) == -1)
	{
		printf(RED"Unable to open %s : %s\n"END, nand1, strerror(errno));
		write_log_time(log);
		fprintf(*log, "Unable to open %s : %s\n", nand1, strerror(errno));
		fclose(*log);
		exit(EXIT_FAILURE);
	}
	if ((fd2 = open(nand2, O_RDONLY)) == -1)
	{
		printf(RED"Unable to open %s : %s\n"END, nand2, strerror(errno));
		write_log_time(log);
		fprintf(*log, "Unable to open %s : %s\n", nand2, strerror(errno));
		fclose(*log);
		exit(EXIT_FAILURE);
	}
	printf("Reading nand ...\n");
	write_log_time(log);
	fprintf(*log, "Reading nand ...\n");
	while ((ret1 = read(fd1, buff1, BUFF_SIZE)) > 0 && (ret2 = read(fd2, buff2, BUFF_SIZE)) > 0)
	{
		if (memcmp(buff1, buff2, BUFF_SIZE) != 0)
		{
			printf(RED"Nands are not same\n"END);
			write_log_time(log);
			fprintf(*log, "Nands are not same\n");
			close(ret1);
			close(ret2);
			fclose(*log);
			free(buff1);
			free(buff2);
			exit(EXIT_FAILURE);
		}
		if (i == 0)
			check_NCSD(log, buff1);
		i++;
	}
	write_log_time(log);
	fprintf(*log, "Nand are the same\n");
	close(ret1);
	close(ret2);
	free(buff1);
	free(buff2);
	return (EXIT_FAILURE);
}
