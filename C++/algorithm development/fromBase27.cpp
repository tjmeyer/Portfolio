#include <cstdlib>
#include <NTL/ZZ.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

NTL_CLIENT

/******************************************************************************
 * Convert from a text message representing a base 27 number to a ZZ number.
 ******************************************************************************/
ZZ fromBase27(string message)
{
   ZZ num = to_ZZ(0);
   int power = 0;
   for (int i = message.length() - 1; i >= 0; i--)
   {
      if (message[i] != ' ')
      {
         num += (message[i] - 64) * pow(27, power);
      }
      power++;
   }
   return num;
}

int main(int argv, char* argc[])
{
   if (argv < 2)
   {
      cout << "ERROR: " << argc[0] << " requires at least 1 arguement\n";
      return 0;
   }

   string message;

   for (int i = 1; i < argv; i++)
   {
      message.append(argc[i]);
      if (argc[i + 1])
      {
         message.append(" ");
      }
   }
   ZZ num = fromBase27(message);
   cout << num << endl;
   return 0;
}


ZZ num;
   int power = 0;
   for (int i = message.length() - 1; i >= 0; i--)
   {
      if (message[i] != ' ')
         num += (message[i] - 64) * pow(27, power);
      power++;
   }
   return num;
