using System;

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Zadajte prvé číslo: ");
        int a = Convert.ToInt32(Console.ReadLine());

        Console.Write("Zadajte druhé číslo: ");
        int b = Convert.ToInt32(Console.ReadLine());

        int sum = a + b;

        Console.WriteLine("Súčet čísel {0} a {1} je {2}", a, b, sum);

        Console.ReadKey();
    }
}
