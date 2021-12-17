#include "header.h"

static int	read_instruct(FILE *fd)
{

}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test.txt", "r");
	read_instruct(fd);

	fclose(fd);
}