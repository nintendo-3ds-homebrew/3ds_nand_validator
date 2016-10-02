#include "../include/nand_checker.h"

// verifier si le fichier existe √
// verfier la taille du fichier √
// verifier si le fichier a une extension en .bin ou .img √
// verifier qu'il ny pas plus ou moins de 3 arguments √
// verfier la presence de NCSD a l'octet 256

void	create_folder(void)
{
	struct stat	st;

	if (stat("./nands", &st) == -1)
		mkdir("./nands", 0700);
}

void	error_parsing(int *argc, char **argv)
{
	if (*argc != 3)
	{
		printf("Usage : ./3ds_nand_checker nand1.bin nand2.bin\n        ./3ds_nand_checker nand1.img nand2.img\n");
		exit (EXIT_FAILURE);
	}
	if (strcmp(argv[1], "nands/nand1.bin") != 0 || strcmp(argv[2], "nands/nand2.bin") != 0)
	{
		if (strcmp(argv[1], "nands/nand1.img") == 0 || strcmp(argv[2], "nands/nand2.img") == 0)
			return ;
		printf("Usage : ./3ds_nand_checker nand1.bin nand2.bin\n        ./3ds_nand_checker nand1.img nand2.img\n");
		exit (EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	unsigned int	size_nand1;
	unsigned int	size_nand2;

	error_parsing(&argc, argv);
	create_folder();
	size_nand1 = get_size_nand(argv[1]);
	size_nand2 = get_size_nand(argv[2]);
	check_size_nand(&size_nand1, &size_nand2, argv);
	compare_nand(size_nand1);
	return (EXIT_SUCCESS);
}
