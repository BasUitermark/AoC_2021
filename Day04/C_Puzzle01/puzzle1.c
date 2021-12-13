/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   puzzle1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 16:24:10 by buiterma      #+#    #+#                 */
/*   Updated: 2021/12/13 20:17:04 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*

ROW 1: 0, 1, 2, 3, 4
ROW 2: 5, 6, 7, 8, 9
ROW 3: 10, 11, 12, 13, 14
ROW 4: 15, 16, 17, 18, 29
ROW 5: 20, 21, 22, 23, 24

COL 1: 0, 5, 10, 15, 20
COL 2: 1, 6, 11, 16, 21
COL 3: 2, 7, 12, 17, 22
COL 4: 3, 8, 13, 18, 23
COL 5: 4, 9, 14, 19, 24

1. Make array with input numbers
2. Make list of boards
3. Input number in boards
4. Check boards for completion
*/
static int	*input_handler(FILE *fd)
{
	char		input_read[73];
	static int	input[27];
	size_t		y = 0;
	size_t		i = 0;

	fgets(input_read, 72, fd);
	while (y < 27)
	{
		input[y] = ft_atoi(&input_read[i]);
		i += 2;
		if (input_read[i] == ',')
			i++;
		y++;
	}
	return (input);
}

static int	***board_handler(FILE *fd)
{
	char	board_read[77];
	int		***board;
	size_t	i = 0;
	size_t	num = 0;
	size_t	x = 0;
	size_t	y = 0;

	board = (int ***)ft_calloc(3, sizeof(int **));
	while (num < 3)
	{
		fread(board_read, 1, 76, fd);
		board[num] = (int **)ft_calloc(5, sizeof(int *));
		while (x < 5)
		{
			board[num][x] = (int *)ft_calloc(5, sizeof(int));
			while (y < 5)
			{
				board[num][x][y] = ft_atoi(&board_read[i]);
				i += 3;
				y++;
			}
			y = 0;
			x++;
		}
		x = 0;
		i = 0;
		num++;
	}
	return (board);
}

int	read_instruct(FILE *fd)
{
	int		***board;
	int		*input;
	input = input_handler(fd);
	board = board_handler(fd);

	//== Debug ==//
	printf("Input:	%d\n", input[0]);
	printf("Board:	%d\n", board[0][0][2]);
	return (0);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test.txt", "r");
	read_instruct(fd);
	fclose(fd);
}
