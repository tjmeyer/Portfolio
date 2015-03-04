#include <cstdlib>
#include <NTL/ZZ.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

NTL_CLIENT

string toBase27(ZZ n)
{
   string message;
   int base27;
   stringstream out;
   string temp;
   while (n > 0)
   {
      base27 = n % 27;
      n /= 27;
      if (base27 == 0)
      {
         message.insert(0, " ");
      }
      else
      {
         char letter = base27 + 64;
         out << letter;
         temp = out.str();
         message.insert(0, temp);
         out.str("");
      }
   }
   return message;
}

int main(int argv, char* argc[])
{
   ZZ message = to_ZZ(argc[1]);
   string newMessage = toBase27(message);
   cout << newMessage << endl;
   return 0;
}

string message;
   int base27;
   stringstream out;
   string temp;
   while (n > 0)
   {
      message.insert(0, " ");
      base27 = n % 27;
      n /= 27;
      if (base27 == 0)
      {
         message.insert(0, " ");
      }
      else
      {
         out << base27;
         temp = out.str();
         message.insert(0, temp);
         out.str("");
      }
   }
   return message;
}
