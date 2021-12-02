using System.Runtime.Serialization;
using System;
using System.IO;

namespace CS_Puzzle02
{
	class puzzle02
	{
		static void SumCount(string []array, int i, int []store)
		{
			store[0] = int.Parse(array[i]) + int.Parse(array[i + 1]) + int.Parse(array[i + 2]);
			store[1] = int.Parse(array[i - 1]) + int.Parse(array[i]) + int.Parse(array[i + 1]);
		}
		static int	ReadArray(string []array)
		{
			int	i = 1;
			int	count = 0;
			int	[]store = new int[2];
		
			while (i + 2 < array.Length)
			{
				SumCount(array, i, store);
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
			Console.WriteLine("Answer is: " + ReadArray(array));
		}
	}
}
