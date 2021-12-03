#include "header.h"
#include <inttypes.h>

/*
/== INSTRUCTIONS ==/
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
void	get_epsilon(char *gamma, char *epsilon)
{
	int	i;

	i = 0;
	while (gamma[i])
	{
		if (gamma[i] == '0')
			epsilon[i] = '1';
		if (gamma[i] == '1')
			epsilon[i] = '0';
		i++;
	}
	epsilon[12] = '\0';
}

char	count_num(char **array, int i, int j)
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
		return ('0');
	else
		return ('1');
}

int	read_instruct(int fd)
{
	char	**array;
	char	temp[10000];
	char	gamma[13];
	char	epsilon[13];
	int		i;
	int		j;

	i = 0;
	j = 0;
	read(fd, temp, 10000);
	array = ft_split(temp, '\n');
	while (array[i][j])
	{
		gamma[j] = count_num(array, i, j);
		j++;
	}
	gamma[12] = '\0';
	get_epsilon(gamma, epsilon);
	printf("gamma:		%s\n", gamma);
	printf("epsilon:	%s\n", epsilon);
	printf("gamma int:	%ld\n", strtol(gamma, NULL, 2));
	printf("epsilon int:	%ld\n", strtol(epsilon, NULL, 2));
	return (strtol(gamma, NULL, 2) * strtol(epsilon, NULL, 2));
}

int	main(void)
{
	int	fd;

	fd = open("input.txt", O_RDONLY);
	// read_instruct(fd);
	printf("Product:	%d\n", read_instruct(fd));
	close(fd);
}
