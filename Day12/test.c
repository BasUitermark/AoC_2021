// #include <stdio.h>
// #include <fcntl.h>
// #include "header.h"
#include <unistd.h>

void	ft_print_alphabet(void)
{
	char	c;
	c = 'a';
	while (c <= 'z')
	{
		write(1, &c, 1);
		c++;
	}
}

void	ft_print_alphabet1(void)
{
	write(1, "abcdefghijklmnopqrstuvwxyz", 27);
}

int main()
{
	ft_print_alphabet();
	printf("\n");
	ft_print_alphabet1();
}
