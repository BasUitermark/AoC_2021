#include "header.h"

static void	print_array(int ***board)
{
	size_t	num = 0;
	size_t	x = 0;
	size_t	y = 0;

	while (num < MAX_BOARD)
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
	char		input_read[INPUT_READ];
	static int	input[MAX_INPUT];
	size_t		y = 0;
	size_t		i = 0;

	fgets(input_read, INPUT_READ - 1, fd);
	while (y < MAX_INPUT)
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

	board = (int ***)ft_calloc(MAX_BOARD, sizeof(int **));
	while (num < MAX_BOARD)
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
	while (num < MAX_BOARD)
	{
		while (x < 5)
		{
			while (y < 5)
			{
				if (board[num][x][y] == -1 )
					y_axis++;
				if (y_axis == 5)
				{
					// printf("BINGO Y\n");
					return (num);
				}
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
	while (num < MAX_BOARD)
	{
		while (y < 5)
		{
			while (x < 5)
			{
				if (board[num][x][y] == -1)
					x_axis++;
				if (x_axis == 5)
				{
					// printf("BINGO X\n");
					return (num);
				}
				x++;
			}
			x_axis = 0;
			x = 0;
			y++;
		}
		y = 0;
		num++;
	}
	return (-1);
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
			if (board[x][y] >= 0)
				sum += board[x][y];
			y++;
		}
		y = 0;
		x++;
	}
	printf("%d\n", sum * input);
}

static void	refill_board(int **board)
{
	size_t	x = 0;
	size_t	y = 0;

	while (x < 5)
	{
		while (y < 5)
		{
			board[x][y] = -2;
			y++;
		}
		y = 0;
		x++;
	}
}

static void	board_fill(int *input, int ***board)
{
	size_t	i = 0;
	size_t	num = 0;
	size_t	x = 0;
	size_t	y = 0;
	size_t	bingo = 0;
	size_t	board_num = 0;

	while (i < MAX_INPUT)
	{
		while (num < MAX_BOARD)
		{
			while (x < 5)
			{
				while (y < 5)
				{
					if (input[i] == board[num][x][y])
						board[num][x][y] = -1;
					board_num = check_board(board);
					if (check_board(board) >= 0)
					{
						if (bingo == MAX_BOARD - 1)
						{
							printf("BINGO!\n");
							calc_number(board[board_num], input[i]);
							return ;
						}
						else
						{
							refill_board(board[board_num]);
							y = 5;
							x = 5;
							bingo++;
						}
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
		// printf("%d\n", i);
	}
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

	fd = fopen("input.txt", "r");
	read_instruct(fd);
	fclose(fd);
}
