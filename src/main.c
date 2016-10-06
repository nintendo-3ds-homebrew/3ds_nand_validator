#include "../include/nand_checker.h"

void    press_enter()
{
    printf("\nPress enter to exit\n");
    getchar();
}

void	create_folders(void)
{
	if (access("./nands", F_OK) == -1)
		CreateDirectory("./nands", NULL);
	if (access("./log", F_OK) == -1)
		CreateDirectory("./log", NULL);
}

void	check_if_nand_exist(FILE **log)
{
	if (access("./nands/nand1.bin", F_OK) == -1 || access("./nands/nand2.bin", F_OK) == -1)
	{
	    color(RED, BLACK);
		printf("Put nand1.bin and nand2.bin in nands folder\n");
		color(WHITE, BLACK);
		write_log_time(log);
		fprintf(*log, "Put nand1.bin and nand2.bin in nands folder\n");
		fclose(*log);
		press_enter();
		exit (EXIT_FAILURE);
	}
}

void color(int text,int background)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, background * 16 + text);
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
	compare_nand(&log, "./nands/nand1.bin", "./nands/nand2.bin", &size_nand1);
	color(GREEN, BLACK);
	printf("Dumps are good !\n");
	color(WHITE, BLACK);
    press_enter();
	write_log_time(&log);
	fprintf(log, "Dumps are good !\n");
	fclose(log);
	return (EXIT_SUCCESS);
}
