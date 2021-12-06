#include "header.h"
#include <inttypes.h>

/*
/== INSTRUCTIONS P1 ==/
Considering only the first bit of each number, 
there are five 0 bits and seven 1 bits.
Since the most common bit is 1, the first bit of the gamma rate is 1.
The most common second bit of the numbers in the diagnostic report is 0,
so the second bit of the gamma rate is 0.
The most common value of the third, fourth,
and fifth bits are 1, 1, and 0, respectively,
and so the final three bits of the gamma rate are 110.
So, the gamma rate is the binary number 10110, or 22 in decimal.
The epsilon rate is calculated in a similar way;
rather than use the most common bit,
the least common bit from each position is used.
So, the epsilon rate is 01001, or 9 in decimal.
Multiplying the gamma rate (22) by the epsilon rate (9)
produces the power consumption, 198.
Use the binary numbers in your diagnostic report
to calculate the gamma rate and epsilon rate, then multiply them together. 
What is the power consumption of the submarine?
(Be sure to represent your answer in decimal, not binary.)

/== OBSERVATIONS ==/
Epsilon is the reverse binary of gamma.
*/

int	*count_num(char **array, int i, int j, int *count_num)
{
	int	num1;
	int	num2;

	num1 = 0;
	num2 = 0;
	i = 0;
	while (array[i])
	{
		if (array[i][j] == '0')
			num1++;
		else
			num2++;
		i++;
	}
	if (num1 > num2)
	{
		count_num[0] = 0;
		count_num[1] = num1;
		return (count_num);
	}
	else
	{
		count_num[0] = 1;
		count_num[1] = num2;
		return (count_num);
	}
}

// int	count_num(char **array, int i, int j)
// {
// 	int	num1;
// 	int	num2;

// 	num1 = 0;
// 	num2 = 0;
// 	i = 0;
// 	while (array[i])
// 	{
// 		if (array[i][j] == '0')
// 			num1++;
// 		else
// 			num2++;
// 		i++;
// 	}
// 	if (num1 > num2)
// 		return (0);
// 	else
// 		return (1);
// }

int	read_instruct(int fd)
{
	char	**array;
	char	**tempArray;
	int		count[2];
	char	temp[10000];
	int		i;
	int		j;
 
	i = 0;
	j = 0;
	read(fd, temp, 10000);
	array = ft_split(temp, '\n');
	tempArray = (char **)malloc(13 * 6 * sizeof(char));
	while (array[i][j])
	{
		count_num(array, i, j, count);
		tempArray = (char **)realloc(tempArray, count[1] * 13 * sizeof(char));
		while (array[i])
		{
			if (array[i][j] == '0' && count[0] == 0)
				tempArray[i] = array[i];
			else if (array[i][j] == '1' && count[0] == 1)
				tempArray[i] = array[i];
				i++;
		}
		i = 0;
		array = (char **)realloc(array, count[1] * 13 * sizeof(char));
		array = tempArray;
		j++;
	}
	// printf("num: %d\ncount: %d\n", count[0], count[1]);
	printf("%s\n", array[0]);

	return (0);
}

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	read_instruct(fd);
	// printf("Product:	%d\n", read_instruct(fd));
	close(fd);
}
