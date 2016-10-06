#include "../include/nand_validator.h"

static int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		*ss1;
	unsigned char		*ss2;
	size_t				i;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ss1[i] != ss2[i])
			return (i);
		i++;
	}
	return (-1);
}

static int	check_NCSD(FILE **log, char *buff1)
{
	if (buff1[256] == 'N' && buff1[257] == 'C' && buff1[258] == 'S' && buff1[259] == 'D')
	{
		write_log_time(log);
		fprintf(*log, "NCSD found !\n");
	}
	else
	{
	    color(RED, BLACK);
		printf("Dumps are bad !\n");
		color(WHITE, BLACK);
		write_log_time(log);
		fprintf(*log, "NCSD not found !\n");
		write_log_time(log);
		fprintf(*log, "Dumps are bad !\n");
		fclose(*log);
		press_enter();
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	compare_nand(FILE **log, char *nand1, char *nand2, unsigned int *size_nand)
{
	int				fd1;
	int				fd2;
	int				ret1 = 0;
	int				ret2 = 0;
	char			*buff1 = (char *)malloc(sizeof(char) * BUFF_SIZE);
	char			*buff2 = (char *)malloc(sizeof(char) * BUFF_SIZE);
	int				i = 0;
	int				progress = (*size_nand / BUFF_SIZE) / 10;
	int				ret_cmp = 0;
	int				iter = 0;

	if ((fd1 = open(nand1, O_RDONLY | O_BINARY)) == -1)
	{
		printf("Unable to open %s : %s\n", nand1, strerror(errno));
		write_log_time(log);
		fprintf(*log, "Unable to open %s : %s\n", nand1, strerror(errno));
		fclose(*log);
		exit(EXIT_FAILURE);
	}
	if ((fd2 = open(nand2, O_RDONLY | O_BINARY)) == -1)
	{
		printf("Unable to open %s : %s\n", nand2, strerror(errno));
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
        if (i == progress * iter)
		{
		    printf("%d%% ", iter * 10);
			++iter;
		}
		if ((ret_cmp = ft_memcmp(buff1, buff2, BUFF_SIZE)) != -1)
		{
		    printf("\n");
		    color(RED, BLACK);
		    printf("Difference at byte %d\n", (i * BUFF_SIZE) + ret_cmp);
		    write_log_time(log);
		    fprintf(*log, "Difference at byte %d\n", (i * BUFF_SIZE) + ret_cmp);
			printf("Nands are not same\n");
			color(WHITE, BLACK);
			write_log_time(log);
			fprintf(*log, "Nands are not same\n");
			close(ret1);
			close(ret2);
			fclose(*log);
			free(buff1);
			free(buff2);
			press_enter();
			exit(EXIT_FAILURE);
		}
		if (i == 0)
			check_NCSD(log, buff1);
		i++;
	}
	printf("\n");
	write_log_time(log);
	fprintf(*log, "Nand are the same\n");
	//close(ret1);
	//close(ret2);
	free(buff1);
	free(buff2);
	return (EXIT_FAILURE);
}
