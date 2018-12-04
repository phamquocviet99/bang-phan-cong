using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimpleExample
{
    public delegate int BinaryOp(int x, int y);

    public class SimpleMath
    {
        public static int add(int x, int y)
        {
            return x + y;

        }
        public static int Subtract(int x, int y)
        {
            return x - y;
        }
        public static int SquareNumber(int a, int b)
        {
            return a * b;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("*****Simple Delegate Example ****\n");
            //Create a BinaryOp object that
            //"point to" SimpleMath();
            //BinaryOp b=mew BinaryOp(s.Add);
            BinaryOp b = new BinaryOp(SimpleMath.add);
            //invoke add() method indirectly using //delegate object
            Console.WriteLine("10+10 is{0}", b(10, 10));
            BinaryOp b1 = new BinaryOp(SimpleMath.SquareNumber);
            b = new BinaryOp(SimpleMath.Subtract);
            Console.ReadLine();
        }

    }
}
