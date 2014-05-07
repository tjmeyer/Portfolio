#include <cstdlib>
#include <NTL/ZZ.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

NTL_CLIENT

bool checkForLargePrime(ZZ num);
bool checkPrime(ZZ num);
ZZ getNextPrimeNumber(ZZ num);

int main(int argv, char* argc[])
{
   if (argv < 2 || argv > 2)
   {
      cout << "ERROR: REQUIRES 1 ARGUEMENTS\n";
      return 0;
   }
   ZZ number = to_ZZ(argc[1]);
   ZZ next = getNextPrimeNumber(number);
   cout << "Next prime number after " << number << " is " << next << endl;
   return 0;
}
   

bool checkPrime(ZZ num)
{
   ZZ k = to_ZZ(2);

   if (num > 100)
   {
      return checkForLargePrime(num);
   }
   while (k < num)
   {
      ZZ mod = num % k;
      if (mod == 0)
      {
         return false;
      }
      
      k++;
   }
   return true;
}
            
ZZ getNextPrimeNumber(ZZ num)
{
   num++;
   bool is = true;

   while (is)
   {
      if (checkPrime(num))
         is = false;
      else
         num++;
   }
   return num;
}


bool checkForLargePrime(ZZ num)
{
   if (num > 100)
   {
      ZZ sss = SqrRoot(num) + 1;
      ZZ pn = to_ZZ(2);

      while (pn < sss)
      {
         if (num % pn == 0)
         {
            return false;
         }
         pn = getNextPrimeNumber(pn);
      }
      return true;
   }
   else
   {
      return false;
   }
}
