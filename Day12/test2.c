// C program to print all permutations with duplicates allowed
#include <stdio.h>
#include <string.h>

/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

/* Function to print permutations of string
This function takes three parameters:
1. String
2. Starting index of the string
3. Ending index of the string. */
int permute(char *a, int l, int r)
{
	int i;
	int	count = 0;
	//do check here to see if the order is allowed
	if (l == r && a[0] == 's' && a[5] == 'e')
	{
		printf("%s\n", a);
		count++;
	}
	else
	{
		for (i = l; i <= r; i++)
		i = l;
		while (i <= r)
		{
			swap((a+l), (a+i));
			count += permute(a, l+1, r);
			swap((a+l), (a+i)); //backtrack
		}
	}
	return (count);
}

/* Driver program to test above functions */
int main()
{
	int	count = 0;
	char str[] = "sAbcde";
	int n = strlen(str);
	count = permute(str, 0, n-1);
	printf("Count: %d\n", count);
	return 0;
}
