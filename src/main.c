#include "../include/nand_checker.h"

// verifier si le fichier existe √
// verfier la taille du fichier √
// verifier si le fichier a une extension en .bin ou .img √
// verifier qu'il ny pas plus ou moins de 3 arguments √
// verfier la presence de NCSD a l'octet 256 √

void	create_folder(void)
{
	/*struct stat	st;*/

	/*if (stat("./nands", &st) == -1)*/
	if (access("./nands", F_OK) == -1)
		mkdir("./nands", 0700);
}

void	check_if_nand_exist()
{
	if (access("./nands/nand1.bin", F_OK) == -1 || access("./nands/nand2.bin", F_OK) == -1)
	{
		printf("Put nand1.bin and nand2.bin in nands folder\n");
		exit (EXIT_FAILURE);
	}
}

int	main(void)
{
	unsigned int	size_nand1;
	unsigned int	size_nand2;

	create_folder();
	check_if_nand_exist();
	/*while (check_if_nand_exist() == EXIT_FAILURE)*/
	/*{*/
		/*printf("Press enter to check nands\n");*/
		/*scanf("OK\n");*/
	/*}*/
	size_nand1 = get_size_nand("./nands/nand1.bin");
	size_nand2 = get_size_nand("./nands/nand2.bin");
	check_size_nand(&size_nand1, &size_nand2, "./nands/nand1.bin", "./nands/nand2.bin");
	compare_nand("./nands/nand1.bin", "./nands/nand2.bin");
	printf(GREEN"./nands/nand1.bin and ./nands/nand1.bin [Ok] !\n");
	return (EXIT_SUCCESS);
}
