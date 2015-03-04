/***********************************************************************
 * Program:
 *    Exploration 3, RSA
 *    Rick Neff, CS237
 *
 * Author:
 *    Trevor Meyer
 *
 * Summary:
 *    RSA Encryption/Decryption Driver
 *    Compile with:
 *      g++ -c rsaZZmain.cpp
 ***********************************************************************/
#include <cstdlib>
#include <NTL/ZZ.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

NTL_CLIENT


// THE FOLLOWING FUNCTIONS WERE NOT INCLUDED IN THE ORIGINAL CPP FILE, BUT ARE
// VERY USEFUL FOR CREATE A TRUELY "RANDOM" ENCRYPTION ALGORITHM.
ZZ getNextPrimeNumber(ZZ &num);
bool checkForLargePrime(ZZ &num);
bool checkPrime(ZZ &num);

/******************************************************************************
 * CHECK PRIMALITY ON LARGE INTEGERS (APPROXIMATE)
 * INPUT:       large integer
 * OUTPUT:      true, if probably a prime
 ******************************************************************************/
bool checkForLargePrime(ZZ &num)
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
         getNextPrimeNumber(pn);
      }
      return true;
   }
   else
   {
      return false;
   }
}

/******************************************************************************
 * CHECK PRIMALITY (APPROXIMATE)
 * INPUT:       large integer
 * OUTPUT:      true, if probably a prime
 ******************************************************************************/
bool checkPrime(ZZ &num)
{
   ZZ k = to_ZZ(2);
   if (num > 1000)
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

/******************************************************************************
 * GET NEXT PRIME NUMBER
 * INPUT:       large integer
 * OUTPUT:      next prime number larger than the input
 *      This function is very slow, but fairly accurate. O(n^2)
 ******************************************************************************/
ZZ getNextPrimeNumber(ZZ &num)
{
   num++;
   bool isPrime = true;

   while (isPrime)
   {
      if (checkPrime(num))
         isPrime = false;
      else
         num++;
   }
   return num;
}

/******************************************************************************
 * RELATIVELY PRIME - EUCLIDIAN ALGORITHM       
 * INPUT:       two large integers
 * OUTPUT:      1, if relatively prime.
 ******************************************************************************/
ZZ relPrime(ZZ a, ZZ b)
{
   while (a != 0)
   {
      if (b > a)
      {
         ZZ temp = a;
         a = b;
         b = temp;
      }
      
      ZZ newA = a / b;
      ZZ newB = a % b;
      
      a = newB;
   }
   return b;
}
// END OF ADDED FUNCTIONS

/******************************************************************************
 * Find b^n % m.
 ******************************************************************************/
ZZ modExp(ZZ b, ZZ n, ZZ m)
{
   int bin; // bin for binary
   ZZ x = to_ZZ(1);
   while (n != 0)
   {
      // binary conversion on the fly
      bin = n % 2;
      n /= 2;

      if (bin == 1)
         x = (x * b) % m;

      b = (b * b) % m;
   }
   return x;
}

/******************************************************************************
 * Find i such that a * i is congruent to 1 (mod m).
 ******************************************************************************/
ZZ findInverse(ZZ a, ZZ m)
{
   // use the extended euclidean algorithm to find s such that
   // d = gcd(a, m) = a*s + m*t

   ZZ s;
   ZZ t;
   ZZ d;

   XGCD(d, s, t, a, m);

   /*
   ZZ q;  //q for quotient

   ZZ mOriginal = m;
   ZZ x = to_ZZ(0);
   ZZ y = to_ZZ(1);
   ZZ lastx = to_ZZ(1);
   ZZ lasty = to_ZZ(0);
   
   ZZ temp;
   while (m != 0)
   {
      q = a / m;
      temp = a % m;
      a = m;
      m = temp;

      temp = x;
      x = lastx - q * x;
      lastx = temp;

      temp = y;
      y = lasty - q * y;
      lasty = temp;
   }
   */
   if (s < 0)
      s += m;

   return s;
}

/******************************************************************************
 * Convert from a text message representing a base 27 number to a ZZ number.
 ******************************************************************************/
ZZ fromBase27(string message)
{
   ZZ num = to_ZZ(0);
   ZZ ZZ_27 = to_ZZ(27);
   int pow = 0;
   for (int i = message.length() - 1; i >= 0; i--)
   {
      if (message[i] != ' ')
      {
         num += (message[i] - 64) * power(ZZ_27, pow);
      }
      pow++;
   }
   return num;
}

/******************************************************************************
 * Convert from a ZZ number to a base 27 number represented by a text message.
 ******************************************************************************/
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

/******************************************************************************
 * Find a suitable e for a ZZ number that is the "totient" of two primes.
 ******************************************************************************/
ZZ findE(ZZ t)
{
   ZZ e = to_ZZ(1);
   
   bool coprime = false;
   ZZ gcd;
   while (!coprime)
   {
      e++;
      gcd = relPrime(t, e);
      if (gcd == 1)
      {
         coprime = true;
      }
   }
   return e;
}


/******************************************************************************
 * Find suitable primes p and q for encrypting a ZZ number that is the message.
 ******************************************************************************/
void findPandQ(ZZ m, ZZ& p, ZZ& q)
{
   ZZ bound = SqrRoot(m); // minimize needed p and q size with boundaries
   long length = NumBits(bound);

   // bool isPrime = false;
   p = 0;
   q = 0;
   while (p == q) // unlikely, but p and q cannot be the same!
   {
      GenPrime(p, length, 80);
      GenPrime(q, length, 80);
   }                     
   return;
}
