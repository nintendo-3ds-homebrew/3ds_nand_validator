#ifndef nand_validator_H
#define nand_validator_H

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
#include <time.h>
#include <windows.h>

#define BLACK           0
#define DARK_BLUE       1
#define GREEN           2
#define BLUE_GREY       3
#define BROWN           4
#define PURPLE          5
#define KHAKI           6
#define LIGHT_GREY      7
#define GREY            8
#define BLUE            9
#define FLASHY_GREEN    10
#define CYAN            11
#define RED             12
#define FLASHY_PINK     13
#define FLASHY_YELLOW   14
#define WHITE           15

#define SIZE_LEN	9
#define BUFF_SIZE	1048576 /*1 Mo*/

//=========================check_size_nand.c===================================
unsigned int		get_size_nand(FILE **log, char *nand_filename);
int					check_nand_valid(FILE **log, unsigned int *nand, int *nand_type);
void				check_size_nand(FILE **log, unsigned int *size_nand1, unsigned int *size_nand2, char *nand1, char *nand2);
//===========================compare_nand.c====================================
int					compare_nand(FILE **log, char *nand1, char *nand2, unsigned int *size_nand);
//===========================log.c====================================
void				create_log_file(FILE **log);
void				write_log_time(FILE **log);
//===========================main.c====================================
void				check_if_nand_exist(FILE **log);
void				create_folders(void);
void                press_enter();
void                color(int text,int background);
//=============================================================================
#endif
