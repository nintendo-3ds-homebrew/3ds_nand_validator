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

#define RED			"\033[031m"
#define GREEN		"\033[032m"
#define YELLOW		"\033[033m"
#define END			"\033[0m"
#define SIZE_LEN	9

//=========================check_size_nand.c===================================
unsigned int		get_size_nand(char *nand_filename);
int					check_nand_valid(unsigned int *nand);
void				check_size_nand(unsigned int *size_nand1, unsigned int *size_nand2, char **argv);
//===========================compare_nand.c====================================
int					compare_nand(unsigned int size_nand);
//=============================================================================
#endif
