#ifndef HEADER_H
# define HEADER_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include "../../libft/include/libft.h"

//== Global Variables ==//

int		paths = 0;
t_dlist	*marked_caves;
int		marks;
int		count = 0;
char	*cave;


//== Test 1 ==//
// # define LINES 7
// # define SIZE 8

//== Test 2 ==//
// # define LINES 10
// # define SIZE 9

//== Test 3 ==//
// # define LINES 18
// # define SIZE 9

//== Input ==//
# define LINES 21
# define SIZE 9

#define RED		"\x1b[31m"
#define GREEN	"\x1b[32m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"
#define MAGENTA	"\x1b[35m"
#define CYAN	"\x1b[36m"
#define RESET	"\x1b[0m"

#endif