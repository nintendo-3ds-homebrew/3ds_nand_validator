#ifndef NAND_CHECKER_H
#define NAND_CHECKER_H

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RED			"\033[031m"
#define GREEN		"\033[032m"
#define YELLOW		"\033[033m"
#define BLUE		"\033[034m"
#define PURPLE		"\033[035m"
#define CYAN		"\033[036m"
#define WHITE		"\033[037m"
#define END			"\033[0m"
#define SIZE_LEN	9
#define BUFF_SIZE	1048576 /*1 Mo*/

//=========================check_size_nand.c===================================
unsigned int		get_size_nand(char *nand_filename);
int					check_nand_valid(unsigned int *nand);
void				check_size_nand(unsigned int *size_nand1, unsigned int *size_nand2, char **argv);
//===========================compare_nand.c====================================
int					compare_nand(char *nand1, char *nand2);
//=============================================================================
#endif
