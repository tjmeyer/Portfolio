#include <cstdlib>
#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

int gcd(int &a, int &b)
{
   if (b > a)
   {
      int temp = a;
      a = b;
      b = temp;
   }
   int newA = a / b;
   int newB = a % b;

   cout << a << " = " << b << " * " << newA << " + " << newB << endl;
   
   a = newB;
    
   if (a == 0)
      return b;
   else
      gcd(a, b);
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

   int wow = gcd(a, b);
   cout << "gcd(" << argc[1] << ", " << argc[2] << ") = " << wow << endl;
   return 0;
}
