#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include "../../libft/include/libft.h"

typedef struct s_array
{
	int	x;
	int	y;
}	t_array;


//== Test ==//

#define LINES 18
#define SIZE 6
#define FOLDS 2
#define FOLD_SIZE 3
#define STR_SIZE 15

#define X 11
#define Y 15

#endif