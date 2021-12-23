#include "header.h"

static void	print_array(int ***board)
{
	size_t	num = 0;
	size_t	x = 0;
	size_t	y = 0;

	while (num < 3)
	{
		while (x < 5)
		{
			while (y < 5)
			{
				printf("%d ", board[num][x][y]);
				y++;
			}
			printf("\n");
			y = 0;
			x++;
		}
		printf("\n");
		x = 0;
		num++;
	}
}

static int	*input_handler(FILE *fd)
{
	char		input_read[73];//292
	static int	input[27];//100
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

static int	check_board(int ***board)
{
	size_t	x_axis = 0;
	size_t	y_axis = 0;
	size_t	num = 0;
	size_t	x = 0;
	size_t	y = 0;

	//== Check y axis ==//
	while (num < 3)
	{
		while (x < 5)
		{
			while (y < 5)
			{
				if (board[num][x][y] == -1)
					y_axis++;
				if (y_axis == 5)
					return (num);
				y++;
			}
			y_axis = 0;
			y = 0;
			x++;
		}
		x = 0;
		num++;
	}
	num = 0;
	x = 0;
	y = 0;
	//== Check x axis ==//
	while (num < 3)
	{
		while (y < 5)
		{
			while (x < 5)
			{
				if (board[num][x][y] == -1)
					x_axis++;
				if (x_axis == 5)
					return (num);
				x++;
			}
			x_axis = 0;
			x = 0;
			y++;
		}
		y = 0;
		num++;
	}
	return (0);
}

static void	calc_number(int **board, int input)
{
	size_t	x = 0;
	size_t	y = 0;
	size_t	sum = 0;

	while (x < 5)
	{
		while (y < 5)
		{
			if (board[x][y] > 0)
				sum += board[x][y];
			y++;
		}
		y = 0;
		x++;
	}
	printf("%d\n", sum * input);
}

static void	board_fill(int *input, int ***board)
{
	size_t	i = 0;
	size_t	num = 0;
	size_t	x = 0;
	size_t	y = 0;

	while (i < 27)
	{
		while (num < 3)
		{
			while (x < 5)
			{
				while (y < 5)
				{
					if (input[i] == board[num][x][y])
						board[num][x][y] = -1;
					if (check_board(board) != 0)
					{
						calc_number(board[check_board(board)], input[i]);
						return ;
					}
					y++;
				}
				y = 0;
				x++;
			}
			x = 0;
			num++;
		}
		num = 0;
		i++;
	}
	// print_array(board);
}

int	read_instruct(FILE *fd)
{
	int		***board;
	int		*input;

	input = input_handler(fd);
	board = board_handler(fd);
	board_fill(input, board);
	free (board);
	return (0);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("test.txt", "r");
	read_instruct(fd);
	fclose(fd);
}
