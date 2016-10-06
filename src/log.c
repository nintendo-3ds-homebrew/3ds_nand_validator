#include "../include/nand_validator.h"

void	create_log_file(FILE **log)
{
	if ((*log = fopen("./log/info.log", "w")) == NULL)
	{
		printf(RED"info.log failure\n"END);
		exit(EXIT_FAILURE);
	}
	fprintf(*log, "############### 3DS_nand_validator ############\n");
	fprintf(*log, "#                                             #\n");
	fprintf(*log, "#          Developped by SegFault42           #\n");
	fprintf(*log, "#       https://github.com/SegFault42/        #\n");
	fprintf(*log, "#                                             #\n");
	fprintf(*log, "###############################################\n\n");
}

void	write_log_time(FILE **log)
{
	time_t			ltime; /* calendar time */

	ltime = time(NULL); /* get current cal time */
	fprintf(*log, "<%.24s> : ",asctime(localtime(&ltime)));
}

