using System.Runtime.Serialization;
using System;
using System.IO;

namespace CS_Puzzle01
{
	class puzzle01
	{
		// static int	[]SumCount(string []array, int i)
		// {
		// 	int	[]store = {0, 0};

		// 	store[0] = int.Parse(array[i]) + int.Parse(array[i + 1]) + int.Parse(array[i + 2]);
		// 	store[1] = int.Parse(array[i - 1]) + int.Parse(array[i]) + int.Parse(array[i + 1]);
		// 	return (store);
		// }
		static int	ReadArray(string []array)
		{
			int	i = 1;
			int	count = 0;
			int	[]store = new int[2];
		
			while (i < array.Length)
			{
				store[0] = int.Parse(array[i]) + int.Parse(array[i + 1]) + int.Parse(array[i + 2]);
				store[1] = int.Parse(array[i - 1]) + int.Parse(array[i]) + int.Parse(array[i + 1]);
				// store = SumCount(array, i);
				if (store[0] > store[1])
					count++;
				i++;
			}
			return (count);
		}
		static void	Main()
		{
			string	[]array;
		
			array = File.ReadAllLines(@"input.txt");
			Console.WriteLine(ReadArray(array));
		}
	}
}
