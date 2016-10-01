#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>

int	main(int argc, char **argv)
{
	long long	size_nand;
	struct stat sb;
	int	size[] = {988807168, 1979711488, 1000341504, 1300234240,	/*2DS nand*/
				988807168, 1000341504,								/* Old 3ds_nand*/
				1979711488, 1300234240, 1954545664,					/*N3ds nand*/};

	if (argc != 2)
		exit(EXIT_FAILURE);
	size_nand = stat(argv[1], &sb);
	if (sb.st_size == size[7])
		printf("NAND Samsung, ");
	printf("size_nand = %lld\n", sb.st_size);
	return (EXIT_SUCCESS);
}
