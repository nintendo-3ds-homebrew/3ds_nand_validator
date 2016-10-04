#include "../include/nand_checker.h"

void	create_folders(void)
{
	if (access("./nands", F_OK) == -1)
		mkdir("./nands", 0700);
	if (access("./log", F_OK) == -1)
		mkdir("./log", 0700);
}

void	check_if_nand_exist(FILE **log)
{
	if (access("./nands/nand1.bin", F_OK) == -1 || access("./nands/nand2.bin", F_OK) == -1)
	{
		printf(RED"Put nand1.bin and nand2.bin in nands folder\n"END);
		write_log_time(log);
		fprintf(*log, "Put nand1.bin and nand2.bin in nands folder\n");
		fclose(*log);
		exit (EXIT_FAILURE);
	}
}

int	main()
{
	unsigned int	size_nand1;
	unsigned int	size_nand2;
	FILE			*log = NULL;

	create_folders();
	create_log_file(&log);
	check_if_nand_exist(&log);
	size_nand1 = get_size_nand(&log, "./nands/nand1.bin");
	size_nand2 = get_size_nand(&log, "./nands/nand2.bin");
	check_size_nand(&log, &size_nand1, &size_nand2, "./nands/nand1.bin", "./nands/nand2.bin");
	compare_nand(&log, "./nands/nand1.bin", "./nands/nand2.bin");
	printf(GREEN"Dumps are good !\n"END);
	write_log_time(&log);
	fprintf(log, "Dumps are good !\n");
	fclose(log);
	return (EXIT_SUCCESS);
}
