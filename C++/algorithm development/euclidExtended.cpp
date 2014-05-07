#include <iostream>
#include <cstdlib>

using namespace std;

int extendedEuclid(int a, int b)
{
   int q;  //q for quotient

   int bOriginal = b;
   int x = 0;
   int y = 1;
   int lastx = 1;
   int lasty = 0;

   int temp;
   while (b != 0)
   {
      q = a / b;
      temp = a % b;
      a = b;
      b = temp;

      temp = x;
      x = lastx - q * x;
      lastx = temp;

      temp = y;
      y = lasty - q * y;
      lasty = temp;
   }
   if (lastx < 0)
      lastx += bOriginal;

   return lastx;
}

int main(int argv, char* argc[])
{
   if (argv < 2 || argv > 4)
   {
      cout << "ERROR: REQUIRES 2 ARGUEMENTS: gcd(a, b)\n";
      return 0;
   }
   int a = atoi(argc[1]);
   int b = atoi(argc[2]);

   int x = extendedEuclid(a, b);
   cout << "x = " << x << endl;
   return 0;
}
