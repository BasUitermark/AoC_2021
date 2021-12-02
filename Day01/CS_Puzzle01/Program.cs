using System.Runtime.Serialization;
using System;
using System.IO;

namespace CS_Puzzle01
{
	class Program
	{
		static int	ReadArray(string []array)
		{
			int	i = 1;
			int	count = 0;
		
			while (i < array.Length)
			{
				if (int.Parse(array[i]) > int.Parse(array[i - 1]))
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
