#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define RED			"\033[031m"
#define GREEN		"\033[032m"
#define YELLOW		"\033[033m"
#define END			"\033[0m"
#define SIZE_LEN	9
#define PATH_NAND	"./nands"

int				compare_nand(char *nand1, char *nand2, unsigned int size_nand)
{
	int		i = 0;
	FILE	*n1 = NULL;
	FILE	*n2 = NULL;

	if ((n1 = fopen("./nands/nand1.bin", "r")) == NULL || (n2 = fopen("./nands/nand2.bin", "r")) == NULL )
	{
		printf(RED"Unable to open nand1.bin or nand2.bin\n"END);
		return (EXIT_FAILURE);
	}
	while (i < size_nand)
	{
		if (fgetc(n1) != fgetc(n2))
		{
			printf(RED"Nand are not the same !\n"END);
			fclose(n1);
			fclose(n2);
			return (EXIT_FAILURE);
		}
		++i;
	}
	printf(GREEN"Nand are the same !\n"END);
	fclose(n1);
	fclose(n2);
	return (EXIT_SUCCESS);
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
	compare_nand(argv[1], argv[2], size_nand1);
	return (EXIT_SUCCESS);
}
