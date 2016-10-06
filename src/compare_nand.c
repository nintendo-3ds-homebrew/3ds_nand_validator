#include "../include/nand_checker.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	putstr(char const *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		++i;
	}
}

static void	putnbr(int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		putnbr(nb / 10);
		putnbr(nb % 10);
	}
	else
		ft_putchar('0' + nb);
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

int	compare_nand(FILE **log, char *nand1, char *nand2, unsigned int *size_nand)
{
	int				fd1;
	int				fd2;
	int				ret1 = 0;
	int				ret2 = 0;
	char			*buff1 = (char *)malloc(sizeof(char) * BUFF_SIZE);
	char			*buff2 = (char *)malloc(sizeof(char) * BUFF_SIZE);
	int				i = 0;
	int				nb_percent = 11;
	int				percent = 1;
	int				progress = *size_nand / BUFF_SIZE;

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
		if (i == progress / nb_percent)
		{
			putnbr((percent - 1) * 10);
			putstr("% ");
			nb_percent--;
			percent++;
		}
		if (memcmp(buff1, buff2, BUFF_SIZE) != 0)
		{
			printf("\n");
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
	putnbr(100);
	putstr("%\n");
	write_log_time(log);
	fprintf(*log, "Nand are the same\n");
	close(ret1);
	close(ret2);
	free(buff1);
	free(buff2);
	return (EXIT_FAILURE);
}
