/**************************************************************************
* Program:
*    Assignment 08, Time class
*    Brother Ercanbrack, CS165
* Author:
*    Trevor Meyer
* Summary:
*    A program demonstrating the use of operator overloading for use with
*    Objects and classes.
****************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>

using namespace std;

#ifndef TIME_H
#define TIME_H

/*****************************************************************************
 * Class Name: Time
 * Summary: This class contains methods for the the creation,
 *          manipulation, input, and output of time objects
 *****************************************************************************/
class Time
{
   public:

      Time(int theHour, int theMin, int theSec);
      Time(int theHour, int theMin);
      Time(void);
      void setMinute(int theMinute);
      void setHour(int theHour);
      void setSecond(int theSecond);
      void addSeconds(int seconds2Add);
      void addMinutes(int minutes2Add);
      // add hours and returns # of days of overflow
      int  addHours(int hours2Add);
      // display as military time - default no seconds (hh:mm)
      void displayMilitaryTime(bool displaySeconds = false);
      // display the prompt and read data into the time object
      void promptForTime(string prompt, bool readSeconds = false);
      // add two time objects & return the resulting time object
      Time operator + (Time time2);                           

      // logical operators
      bool operator < (Time time2);
      bool operator > (Time time2);
      bool operator == (Time time2);
      bool operator <= (Time time2);
      bool operator >= (Time time2);

      // displays the time object in the format "hh:mm"
      friend ostream& operator << (ostream &out, const Time &time1);
      // reads into the time object.  Expects format "hh:mm"
      friend istream& operator >> (istream &in, Time &time1);

   private:
      int hour;
      int minute;
      int second;
};
#endif

/************************************************************************
 *  int getInt(string prompt, string errMsg)
 *
 *  Desc: Error safe - read integer routine
 *        On error, this function will re-prompt for the integer
 *        until there is no input error.
 *
 *  Inputs:  prompt - string used to prompt for the integer
 *           errMsg - error message you wish displayed if you get an error.
 *  Outputs: none
 *  return:  integer - read from the console
 **************************************************************************/
int getInt(string prompt, string errMsg = "\nValue must be an integer!\n")
{
   bool valid = false;
   int value;
   
   while (!valid)
   {
      cout << prompt;
      cin  >> value;

      if (cin.fail())
      {
         cin.clear();
         cin.ignore(100, '\n');
         cout << errMsg;
      }
      else
      {
         valid = true;
      }
   }
   return value;
}

/***********************************************************************
* Function comments for main go here!
*
* Note: Don't modify main() - Your class functions must work with main()
***********************************************************************/
int main (void)
{
   const bool DISPLAY_SECONDS = true;
   const bool READ_SECONDS = true;

   int hourInput;
   int minInput;
   int secInput;

   Time time1;
   cout << "\nTime1 = " << time1;
   Time time2(8,10);
   cout << "\nTime2 = " << time2; 
   time2.promptForTime("\nChange Time2 (hh:mm): ");

   Time time3(12,30,15);
   time3.promptForTime("Enter Time3 (hh:mm:ss): ",READ_SECONDS);

   Time time4;
   cout << "Enter Time4 (hh:mm): ";
   cin >> time4;

   cout << "\nTime1 = ";
   time1.displayMilitaryTime(DISPLAY_SECONDS);
   cout << "\nTime2 = ";
   time2.displayMilitaryTime(DISPLAY_SECONDS);
   cout << "\nTime3 = ";
   time3.displayMilitaryTime(DISPLAY_SECONDS);
   cout << "\nTime4 = ";
   time4.displayMilitaryTime();

   Time time5(8,0);
   cout << "\nTime5 = ";
   cout << time5;
   cout << endl << endl;
   
   cout << "Adding Time1 to Time2" << endl;
   time5 = time1 + time2;
   cout << time1 << " + " << time2 << " = " << time5 << endl;

   cout << "Adding Time3 to Time4" << endl;
   time5 = time3 + time4;
   cout << time3 << " + " << time4 << " = " << time5 << endl;

   cout << "\nTime5 = ";
   time5.displayMilitaryTime(DISPLAY_SECONDS);

   cout << "\nNow let's add to Time5\n";
   
   secInput = getInt("\nNumber of seconds to add: ","Invalid Seconds value!");
   time5.addSeconds(secInput);
   cout << "Adding " << secInput << " seconds to Time5 = ";
   time5.displayMilitaryTime(DISPLAY_SECONDS);

   minInput = getInt("\nNumber of minutes to add: ","Invalid Minutes value!");
   time5.addMinutes(minInput);
   cout << "Adding " << minInput << " minutes to Time5 = ";
   time5.displayMilitaryTime(DISPLAY_SECONDS);

   hourInput = getInt("\nNumber of hours to add: ","Invalid hours value!");
   int day = time5.addHours(hourInput);
   cout << "Adding " << hourInput << " hours to Time5 = ";
   time5.displayMilitaryTime(DISPLAY_SECONDS);
   cout << "\nDays carried over: " << day << endl;
   cout << endl;
  
   if (time1 < time2)
   {
      cout << time1 << " is less than " << time2 << endl;
   }

   if (time1 > time2)
   {
      cout << time1 << " is greater than " << time2 << endl;
   }
   
   if (time2 == time3)
   {
      cout << time2 << " is equal " << time3 << endl;
   }
   
   if (time3 <= time4)
   {
      cout << time3 << " is less or equal to " << time4 << endl;
   }
   
   if (time4 >= time5)
   {
      cout << time4 << " is greater or equal to " << time5 << endl;
   }

   Time time6(7,40,35);
   Time time7(9,20,40);
   if (time6 < time7)
   {
      time6.displayMilitaryTime(DISPLAY_SECONDS);
      cout << " is less than ";
      time7.displayMilitaryTime(DISPLAY_SECONDS);
      cout << endl;
   }
   else
   {
      time6.displayMilitaryTime(DISPLAY_SECONDS);
      cout << " is greater or equal to ";
      time7.displayMilitaryTime(DISPLAY_SECONDS);
      cout << endl;
   }

   time6 = Time(8,30,15);
   time7 = Time(8,20,15);
   if (time6 <= time7)
   {
      time6.displayMilitaryTime(DISPLAY_SECONDS);
      cout << " is less than or equal ";
      time7.displayMilitaryTime(DISPLAY_SECONDS);
      cout << endl;
   }
   else
   {
      time6.displayMilitaryTime(DISPLAY_SECONDS);
      cout << " is greater than ";
      time7.displayMilitaryTime(DISPLAY_SECONDS);
      cout << endl;
   }

   return 0;
}

/**********************************************************************
 * Constructor definition
 *********************************************************************/
Time::Time(int theHour, int theMin, int theSec)
      : hour(theHour), minute(theMin), second(theSec)
{
   
}

/**********************************************************************
 * Constructor definition
 *********************************************************************/
Time::Time(int theHour, int theMin)
      : hour(theHour), minute(theMin), second(0)
{
   
}

/**********************************************************************
 * Constructor definition
 *********************************************************************/
Time::Time(void)
      : hour(0), minute(0), second(0)
{

}

/**********************************************************************
 * Basic Setter Function: Set Hour
 **********************************************************************/
void Time::setHour(int theHour)
{
   hour = theHour % 24;
}

/**********************************************************************
 * Basic Setter Function: Set Minute
 **********************************************************************/
void Time::setMinute(int theMinute)
{
   minute = theMinute;
   
   if (minute >= 60)
   {
      addHours(minute / 60);
      minute = minute % 60;
   }
}

/**********************************************************************
 * Basic Setter Function: Set Seconds
 **********************************************************************/
void Time::setSecond(int theSecond)
{
   second = theSecond;

   if (second >= 60)
   {
      addMinutes(second / 60);
      second = second % 60;
   }
}

/**********************************************************************
 * Mutator Function: Add Seconds
 **********************************************************************/
void Time::addSeconds(int seconds2Add)
{
   second += seconds2Add;

   if (second >= 60)
   {
      addMinutes(second / 60);
      second = second % 60;
   }
}

/**********************************************************************
 * Mutator Function: Add Minutes
 **********************************************************************/
void Time::addMinutes(int minutes2Add)
{
   minute += minutes2Add;

   if (minute >= 60)
   {
      addHours(minute / 60);
      minute = minute % 60;
   }   
}

/**********************************************************************
 * Mutator Function: Add Hours
 *
 * RETURN: Days overflow
 **********************************************************************/
int Time::addHours(int hours2Add)
{
   hour += hours2Add;

   int dayOverflow;
   if (hour >= 24)
   {
      dayOverflow = hour / 24;
      hour = hour % 24;
   }

   return dayOverflow;
}

/**********************************************************************
 * Accessor Function: Display the time in military time format
 **********************************************************************/
void Time::displayMilitaryTime(bool displaySeconds)
{
   
   cout << setfill('0') << setw(2) << hour << ":";


   if (displaySeconds == true)
      cout << setfill('0') << setw(2) << minute << ":"
           << setfill('0') << setw(2) << second;
   else
      cout << setfill('0') << setw(2) << minute;
}

/**********************************************************************
 * Accessor Function: Display the time in military time format
 **********************************************************************/
void Time::promptForTime(string prompt, bool readSeconds)
{
   char input[10];
   char strHour[3];
   char strMinute[3];
   
   cout << prompt;
   cin.getline(input, 10);

   int x = 0;
   int y = 0;
   while (input[x] != ':')
   {
      strHour[y] = input[x];
      y++;
      x++;
   }

   x++;
   y = 0;
   if (readSeconds == true)
   {
      char strSecond[3];
      while (input[x] != ':')
      {
         strMinute[y] = input[x];
         y++;
         x++;
      }

      x++;
      y = 0;

      while (input[x])
      {
         strSecond[y] = input[x];
         y++;
         x++;
      }
      
      second = atoi(strSecond);
   }
   else
   {
      while (input[x])
      {
         strMinute[y] = input[x];
         y++;
         x++;
      }
   }

   hour = atoi(strHour);
   minute = atoi(strMinute);

}

/**********************************************************************
 * Operation overloader: +
 *********************************************************************/
Time Time::operator + (const Time time2)
{
   int allSeconds;
   int allMinutes;
   int allHours;

   allSeconds = second + time2.second;
   if (allSeconds >= 60)
   {      
      allMinutes++;
      allSeconds %= 60;
   }

   allMinutes = minute + time2.minute;
   if (allMinutes >= 60)
   {
      allHours++;
      allMinutes %= 60;
   }

   allHours = hour + time2.hour;

   return Time (allHours, allMinutes, allSeconds);
}

/**********************************************************************
 * Operation overloader: <
 *********************************************************************/
bool Time::operator < (const Time time2)
{
   if (hour < time2.hour)
      return true;
   else if (minute < time2.minute)
      return true;
   else if (second < time2.second)
      return true;
   else
      return false;
}

/**********************************************************************
 * Operation overloader: >
 *********************************************************************/
bool Time::operator > (const Time time2)
{
   if (hour > time2.hour)
      return true;
   else if (minute > time2.minute)
      return true;
   else if (second > time2.second)
      return true;
   else
      return false;
}

/**********************************************************************
 * Operation overloader: ==
 *********************************************************************/
bool Time::operator == (const Time time2)
{
   return ((hour == time2.hour) &&
           (minute == time2.minute) &&
           (second == time2.second));
}

/**********************************************************************
 * Operation overloader: <=
 *********************************************************************/
bool Time::operator <= (const Time time2)
{
   if (hour <= time2.hour)
   {
      if (hour == time2.hour)
      {
         if (minute <= time2.minute)
         {
            if (minute == time2.minute)
            {
               if (second <= time2.second)
               {
                  return true;
               }
               else
                  return false;                  
            }
            else if (minute < time2.hour)
               return true;
         }
         else
            return false;
      }
      else if (hour < time2.hour)
         return true;
   }
   else
      return false;
}

/**********************************************************************
 * Operation overloader: >=
 *********************************************************************/
bool Time::operator >= (const Time time2)
{
   if (hour >= time2.hour)
   {
      if (hour == time2.hour)
      {
         if (minute >= time2.minute)
         {
            if (minute == time2.minute)
            {
               if (second >= time2.second)
               {
                  return true;
               }
               else
                  return false;                  
            }
            else if (minute > time2.hour)
               return true;
         }
         else
            return false;
      }
      else if (hour > time2.hour)
         return true;
   }
   else
      return false;
}

/**********************************************************************
 * Operation overloader, friend function: <<
 *********************************************************************/
ostream& operator << (ostream& out, const Time &time1)
{
   out << setfill('0') << setw(2) << time1.hour << ':'
       << setfill('0') << setw(2) << time1.minute;

   return out;
}

/**********************************************************************
 * Operation overloader, friend function: >>
 *********************************************************************/
istream& operator >> (istream& in, Time &time1)
{
   char input[6];
   char strHour[3];
   char strMinute[3];
   
   in.getline(input, 10);

   int x = 0;
   int y = 0;
   while (input[x] != ':')
   {
      strHour[y] = input[x];
      y++;
      x++;
   }

   x++;
   y = 0;
   
   while (input[x])
   {
      strMinute[y] = input[x];
      y++;
      x++;
   }

   time1.hour = atoi(strHour);
   time1.minute = atoi(strMinute);

   return in;
}
