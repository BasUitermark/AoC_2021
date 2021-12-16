#include "header.h"

static void	print_board(int **board)
{
	size_t	x = 0;
	size_t	y = 0;

	while (x < BOARD_SIZE)
	{
		while (y < BOARD_SIZE)
		{
			printf("%d ", board[x][y]);
			y++;
		}
		printf("\n");
		y = 0;
		x++;
	}
}

static void	print_input(int **input)
{
	size_t	x = 0;
	size_t	y = 0;

	while (x < INPUT_ROWS)
	{
		while (y < 4)
		{
			printf("%d ", input[x][y]);
			y++;
		}
		printf("\n");
		y = 0;
		x++;
	}
}

static int	**make_board(void)
{
	size_t	x = 0;
	size_t	y = 0;
	int		**board;

	board = (int **)ft_calloc(BOARD_SIZE, sizeof(int *));
	while (x < BOARD_SIZE)
	{
		board[x] = (int *)ft_calloc(BOARD_SIZE, sizeof(int));
		x++;
	}
	return (board);
}

static int	**read_input(FILE *fd)
{
	size_t	x = 0;
	size_t	y = 0;
	size_t	i = 0;
	char	temp[20];
	int		**input;

	input = (int **)ft_calloc(INPUT_ROWS, sizeof(int *));
	while (x < INPUT_ROWS)
	{
		fgets(temp, 20, fd);
		input[x] = (int *)ft_calloc(4, sizeof(int));
		while (y < 4)
		{
			input[x][y] = ft_atoi(&temp[i]);//1
			y++;
			while (ft_isdigit(temp[i]))
				i++;
			i++;
			input[x][y] = ft_atoi(&temp[i]);//2
			y++;
			while (ft_isdigit(temp[i]))
				i++;
			while (!ft_isdigit(temp[i]))
				i++;
			input[x][y] = ft_atoi(&temp[i]);//3
			y++;
			while (ft_isdigit(temp[i]))
				i++;
			i++;
			input[x][y] = ft_atoi(&temp[i]);//4
			y++;
		}
		i = 0;
		y = 0;
		x++;
	}
	return (input);
}

static void	*fill_row(int *row)
{
	size_t	y = 0;

	while (y < 4)
	{
		row[y] = -1;
		y++;
	}
}

static void	filter_input(int **input)
{
	size_t	x = 0;
	size_t	y = 0;
	while (x < INPUT_ROWS)
	{
		while (y < 4)
		{
			if (!(input[x][0] == input[x][2] || input[x][1] == input[x][3]))
				fill_row(input[x]);
			y++;
		}
		y = 0;
		x++;
	}
}

static void	fill_y(int **board, int *input)
{
	size_t	start = 0;
	size_t	end = 0;

	if (input[1] < input[3])
	{
		start = input[1];
		end = input[3];
	}
	else
	{
		start = input[3];
		end = input[1];
	}
	while (start <= end)
	{
		board[start][input[0]] += 1;
		start++;
	}
}

static void	fill_x(int **board, int *input)
{
	size_t	start = 0;
	size_t	end = 0;

	if (input[0] < input[2])
	{
		start = input[0];
		end = input[2];
	}
	else
	{
		start = input[2];
		end = input[0];
	}
	while (start <= end)
	{
		board[input[1]][start] += 1;
		start++;
	}
}

static void fill_downleft(int start_x, int start_y, int end_x, int end_y, int **board)
{
	while (start_x >= end_x && start_y <= end_y)
	{
		board[start_y][start_x] += 1;
		start_x--;
		start_y++;
	}
}

static void fill_downright(int start_x, int start_y, int end_x, int end_y, int **board)
{
	while (start_x <= end_x && start_y <= end_y)
	{
		board[start_y][start_x] += 1;
		start_x++;
		start_y++;
	}
}

static void	fill_diagonal(int **board, int *input)
{
	if (input[0] < input[2] && input[1] > input[3])
		fill_downleft(input[2], input[3], input[0], input[1], board);
	//going up right x- y+
	//use down left with input 2,3 to 0,1
	else if (input[0] > input[2] && input[1] > input[3])
		fill_downright(input[2], input[3], input[0], input[1], board);
	//going up left x- y-
	//use down right with input 2,3 to 0,1
	else if (input[0] > input[2] && input[1] < input[3])
		fill_downleft(input[0], input[1], input[2], input[3], board);
	//going down left x+ y-
	//use down left with input 0,1 to 2,3
	else if (input[0] < input[2] && input[1] < input[3])
		fill_downright(input[0], input[1], input[2], input[3], board);
	//going down right x+ y+
	//use down right with input 0,1 to 2,3
}

static void	insert_input(int **board, int **input)
{

	size_t	x = 0;
	size_t	start = 0;
	size_t	end = 0;

	while (x < INPUT_ROWS)
	{
		if (input[x][0] == input[x][2])//y-axis
			fill_y(board, input[x]);
		else if (input[x][1] == input[x][3])//x-axis
			fill_x(board, input[x]);
		else
			fill_diagonal(board, input[x]);
		x++;
	}
}

static void	count_board(int **board)
{
	size_t	x = 0;
	size_t	y = 0;
	size_t	num = 0;

	while (x < BOARD_SIZE)
	{
		while (y < BOARD_SIZE)
		{
			if (board[x][y] > 1)
				num++;
			y++;
		}
		y = 0;
		x++;
	}
	printf("%d\n", num);
}

int	read_instruct(FILE *fd)
{
	int	**board;
	int	**input;

	board = make_board();
	input = read_input(fd);
	// filter_input(input);
	insert_input(board, input);
	count_board(board);
	// print_board(board);
	// print_input(input);
	return (0);
}

int	main(void)
{
	FILE	*fd;

	fd = fopen("input.txt", "r");
	read_instruct(fd);
	fclose(fd);
}