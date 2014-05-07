/************************************************************************
 * Program:
 *    Assignment 13, Linked Lists
 *    Brother Ercanbrack, CS165
 * Author:
 *    Trevor Meyer
 * Summary:
 *    A program for practicing the use of linked lists.
 *
 *    Estimated:  5.0 hrs
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

//
// Cut and paste your "Date" class from assignment 10 and put it here.
//

/***************************************************
 * BASS CLASS TIME
 *      Copy from previous assignment.
 ***************************************************/
class Time
{
public:
   // constructors
   Time(void);
   Time(int theHour = 0, int theMin = 0, int theSec = 0);

   // mutators
   void setMinute (int theMinute);
   void setHour   (int theHour);
   void setSecond (int theSecond);

   // accessors
   int getHour()   { return hour; }
   int getMinute() { return minute; }
   int getSecond() { return second; }
   
   // time adjustment
   void addHour(int theHour);
   void addMinute(int theMinute);
   void addSecond(int theSecond);

   virtual void adjustTime();
   virtual void display();
   virtual void promptForTime(string prompt);
   
   
private:
   int hour;
   int minute;
   int second;
};

/***************************************************************
 * DEFAULT CONSTRUCTOR
 *************************************************************/
Time::Time(void)
      : hour(0), minute(0), second(0)
{
   // empty on purpose.
}

/***************************************************************
 * CONSTRUCTOR - NOT USED
 *************************************************************/
Time::Time(int theHour, int theMinute, int theSecond)
      : hour(theHour), minute(theMinute), second(theSecond)
{
   // empty on purpose
}

/***************************************************************
 * PROMPT FOR TIME - NOT USED
 *      Empty on purpose. Not used in this program, so I left it
 *      out to save paper.
 *************************************************************/
void Time::promptForTime(string prompt)
{
   // this virtual function will never be used in this scenario
   // so it will be ignored for the sake of time
}

/***************************************************************
 * VIRTUAL TIME CLASS DISPLAY - NOT USED
 *************************************************************/
void Time::display()
{   
   cout << setfill('0') << setw(2)
        << hour   << ":"
        << minute;
}

/***************************************************************
 * VIRTUAL TIME CLASS ADJUST TIME - NOT USED
 *************************************************************/
void Time::adjustTime()
{
   if (second >= 60)
   {
      addMinute(second / 60);
      second %= 60;
   }
   if (minute <= 60)
   {
      addHour(minute / 60);
      minute >= 60;
   }
}

/***************************************************************
 * MUTATOR - NOT USED
 *************************************************************/
void Time::setHour(int theHour)
{
   hour = theHour;
   adjustTime();
}

/***************************************************************
 * MUTATOR - NOT USED
 *************************************************************/
void Time::setMinute(int theMinute)
{
   minute = theMinute;
   adjustTime();
}

/***************************************************************
 * MUTATOR - NOT USED
 *************************************************************/
void Time::setSecond(int theSecond)
{
   second = theSecond;
   adjustTime();
}

/***************************************************************
 * MUTATOR - NOT USED
 *************************************************************/
void Time::addHour(int theHour)
{
   hour += theHour;
   adjustTime();
}

/***************************************************************
 * MUTATOR - NOT USED
 *************************************************************/
void Time::addMinute(int theMinute)
{
   minute += theMinute;
   adjustTime();
}

/***************************************************************
 * MUTATOR - NOT USED
 *************************************************************/
void Time::addSecond(int theSecond)
{
   second += theSecond;
   adjustTime();
}

/***************************************************************
 * CLASS DATE DERIVED FROM TIME CLASS
 *      This class is used in conjunction with the time class
 *      to keep a data structure of time etc. Just a copy of
 *      a previous assignment. No alterations except adding
 *      virtual functions.
 *************************************************************/
class Date: public Time
{
public:
   // constructors
   Date(void);
   Date(int theYear = 0, int theMonth = 0, int theDay = 0,
        int theHour = 0, int theMinute = 0, int theSecond = 0);

   // mutators
   void setYear (int theYear);
   void setMonth(int theMonth);
   void setDay  (int theDay);

   // accessors
   int getYear () { return year; }
   int getMonth() { return month; }
   int getDay  () { return day; }

   // time adjustment
   void addYear  (int theYear);
   void addMonth (int theMonth);
   void addDay   (int theDay);

   virtual void adjustTime();
   virtual void display();
   virtual void promptForTime(string prompt);
   void promptForDate(string prompt);
   
private:
   int year;
   int month;
   int day;
   int dayMax;
   void calcDayMax(int theMonth);
};

/***************************************************************
 * PROMPT FOR TIME - NOT USED
 *************************************************************/
void Date::promptForTime(string prompt)
{
   char input[10];
   char strHour[3];
   char strMinute[3];

   cout << prompt;
   cin.getline(input, 10);

   // for looping use x and y.
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
   while(input[x])
   {
      strMinute[x] = input[x];
      y++;
      x++;
   }

   setHour(atoi(strHour));
   setMinute(atoi(strMinute));

   return;
}
   
/***************************************************************
 * PROMPT FOR DATE - NOT USED
 *************************************************************/
void Date::promptForDate(string prompt)
{
   char *input;
   input = new char[11];

   char *strMonth;
   strMonth = new char[5];

   char *strDay;
   strDay = new char[5];

   char *strYear;
   strYear = new char[5];

   bool end = false;
   while(!end)
   {
      cout << prompt;
      cin.getline(input, 11);

      if (input[2] != '/' || input[5] != '/')
      {
         cout << "\nIncorrect input!\n"
              << "Please use the following format: (mm/dd/yyyy)\n> ";
      }
      else
         end = true;
   }
      
      

   // for looping, use x and y.
   int x = 0;
   int y = 0;

   while (input[x] != '/')
   {
      strMonth[y] = input[x];
      y++;
      x++;
   }

   x++;
   y = 0;
   while (input[x] != '/')
   {
      strDay[y] = input[x];
      y++;
      x++;
   }

   x++;
   y = 0;
   while (input[x])
   {
      strYear[y] = input[x];
      y++;
      x++;
   }

   day = atoi(strDay);
   month = atoi(strMonth);
   year = atoi(strYear);

   adjustTime();

   delete [] input;
   delete [] strMonth;
   delete [] strYear;
   delete [] strDay;
}

/***************************************************************
 * DATE CLASS DISPLAY
 *      OUTPUT: displays the current time in hh:mm format.
 *************************************************************/
void Date::display()
{
   cout << setfill('0') << setw(2)
        << month << "/"
        << day   << "/"
        << year  << " ";
   
   cout << setfill('0') << setw(2)
        << getHour()   << ":"
        << setfill('0') << setw(2)
        << getMinute() << "  ";

}

/***************************************************************
 * DATE CLASS ADJUST TIME
 *      This function is privately called to ensure that all data
 *      in the date class is coherent and correct.
 *      OUTPUT: none
 *************************************************************/
void Date::adjustTime()
{
   calcDayMax(month % 12);
   
   if (getSecond() >= 60)
   {
      addMinute(getSecond() / 60);
      setSecond(getSecond() % 60);
   }
   if (getMinute() >= 60)
   {
      addHour(getMinute() / 60);
      setMinute(getMinute() % 60);
   }
   if (getHour() >= 24)
   {
      addDay(getHour() / 24);
      setHour(getHour() % 24);
   }
   if (day > dayMax)
   {
      month++;
      day -= dayMax;
      
      bool end = false;
      while (!end)
      {
         if (month > 12)
         {
            month -= 11;
            year++;
         }

         if (month <= 12 && day <= dayMax)
            end = true;
      }
   }
}

/***************************************************************
 * DATE CLASS DAY MAXIMUM CALCULATOR
 *      OUTPUT: The number of days in any given month (1-12)
 *              Default is set to 0.
 *************************************************************/
void Date::calcDayMax(int month)
{
   switch (month)
   {
      default:
         dayMax = 0;
         break;

      case 1:
         dayMax = 31;
         break;

      case 2:
         if (year % 4 == 0)
            dayMax = 29;
         else
            dayMax = 28;
         break;

      case 3:
         dayMax = 31;
         break;

      case 4:
         dayMax = 30;
         break;

      case 5:
         dayMax = 31;
         break;

      case 6:
         dayMax = 30;
         break;

      case 7:
         dayMax = 31;
         break;

      case 8:
         dayMax = 31;
         break;

      case 9:
         dayMax = 30;
         break;

      case 10:
         dayMax = 31;
         break;

      case 11:
         dayMax = 30;
         break;

      case 12:
         dayMax = 31;
         break;
   }
}

/***************************************************************
 * MUTATOR - NOT USED
 *************************************************************/
void Date::addYear(int theYear)
{
   year += theYear;
   adjustTime();
}

/***************************************************************
 * MUTATOR - NOT USED
 *************************************************************/
void Date::addMonth(int theMonth)
{
   month += theMonth;
   adjustTime();
}

/***************************************************************
 * MUTATOR - NOT USED
 *************************************************************/
void Date::addDay(int theDay)
{
   day += theDay;
   adjustTime();
}

/***************************************************************
 * MUTATOR SET YEAR
 *************************************************************/
void Date::setYear(int theYear)
{
   year = theYear;
   adjustTime();
}

/***************************************************************
 * MUTATOR SET MONTH
 *************************************************************/
void Date::setMonth(int theMonth)
{
   month = theMonth;
   adjustTime();
}

/***************************************************************
 * MUTATOR SET DAY
 *************************************************************/
void Date::setDay(int theDay)
{
   day = theDay;
   adjustTime();
}

/***************************************************************
 * DATE CLASS DEFAULT CONSTRUCTOR
 *************************************************************/
Date::Date()
      : Time(0, 0, 0), year(0), month(0), day(0)
{
   // empty on purpose.
}

/***************************************************************
 * DATE CLASS CONSTRUCTOR
 *************************************************************/
Date::Date(int theYear, int theMonth, int theDay,
           int theHour, int theMinute, int theSecond)
      : Time (theHour, theMinute, theSecond),
        year(theYear), month(theMonth), day(theDay)
{
   adjustTime();
}


/****************************************************************************
* Template class for building a node object.  The data for the node can be
* any datatype.  
****************************************************************************/
template <class T>
class Node
{
   public:
      Node(const T &theData, Node<T>* theLink)
      : data(theData), link(theLink)
      {
         // left blank intentionally
      }
      Node<T>* getLink( )    { return link; }
      T& getData( )          { return data; }
      void setData(const T &theData) { data = theData; }
      void setLink(Node<T>* pointer) { link = pointer; }

   private:
      T data;            // The data object
      Node<T>* link;     // pointer to next node (i.e. link)
};


/****************************************************************************
* Desc: headInsert - creates a new node and inserts it at the beginning of
*       the linked list.
*
* Input: head - points to the first node in the linked list.
*        theData -  data object to be stored in the new node that is
*                   inserted at the beginning of the linked list.
* Output: head - points to the new first node in the linked list.
****************************************************************************/
template <class T>
void headInsert(Node<T>* &head, const T &theData)
{
   head = new Node<T>(theData, head);
}


/******************************************************************************
* Desc: insert - Creates new node (initializing it with "theData") and inserts
*       it in the linked list after the node pointed to by "afterMe".
*
* Input:  afterMe - pointer to node in the linked list to insert after.
*         theData - Data to be stored in the new node being inserted
* Output: afterMe - link is modified to point at inserted node
*         Note: if afterMe was Null when passed in, a head insert is done
*               and afterMe will now point at the inserted node, which is the
*               first node in the linked list.  
******************************************************************************/
template <class T>
void insert(Node<T>* &afterMe, const T &theData)
{
   if (afterMe != NULL)
   {
      afterMe->setLink(new Node<T>(theData, afterMe->getLink( )));
   }
   else
   {
      headInsert(afterMe,theData);
   }
}

/******************************************************************************
* Class to be used for the data object that is stored in your node class above
* You must implement each of the public functions.
******************************************************************************/
class Leg
{
   private:
      string startCity;
      string destCity;
      string transMode; // transportation mode between cities (car, plane, etc)
      int milesBetween; // mileage between start and destination cities
      Date startDateTime;
      Date arrivalDateTime;
   public:
      Leg();
      Leg(string sCity, string dCity, string transMode, int miles,
          Date startDate, Date arrivalDate);
      void display();
      bool operator == (Leg rightSide);
      bool operator != (Leg rightSide);
};


/**********************************************************************
* Default Constructor - calls constructors for two Date class member 
* variables and initializes the other member variables.
*********************************************************************/
Leg::Leg(void)
      : startDateTime(0, 0, 0), arrivalDateTime(0, 0, 0)
{
   startCity = "";
   destCity = "";
   transMode = "Car";
   milesBetween = 0;
}

/*****************************************************************************
* Constructor -
* Parameters are passed to this constructor to initialize all the
* member variables for the Leg object.
* Inputs:  sCity - start city
*          dCity - destination city
*   theTransMode - transportation mode ("car", "bus", "bike", "foot", "Plane")
*          miles - mileage between start city and destination city
*      startDate - "Date" object that specifies when leaving the start city.
*    arrivalDate - "Date" object that specifies expected arrival in dest city 
******************************************************************************/
Leg::Leg(string sCity, string dCity, string theTransMode, int miles,
    Date startDate, Date arrivalDate)
      : startCity(sCity), destCity(dCity), transMode(theTransMode),
        milesBetween(miles), startDateTime(startDate),
        arrivalDateTime(arrivalDate)
{

}

/***************************************************************************
* Overload Equals operator - compares two leg objects to see if they both
* contain the same start and destination cities.
* returns:  true - start city and destination city in both objects are
*                  the same.       
*           false - start and destination cities are not the same.
***************************************************************************/
bool Leg::operator == (Leg rightSide)
{
   // you must write this function
   return ((startCity == rightSide.startCity) &&
           (destCity == rightSide.destCity));
}

/****************************************************************************
* Overloaded "not equals" operator
* return: True - The left side object's start and destination cities
*                are not equal to the rightside object's start and destination cities.
*       False -  The start and destination cities of the two objects are equal
*****************************************************************************/
bool Leg::operator != (Leg rightSide)
{
   // you must write this function
   return ((startCity != rightSide.startCity) &&
            (destCity != rightSide.destCity));
}

/***************************************************************************
* Display - displays the object
*    startCity, startDate, destCity, arrivalDate, transportation mode, Miles 
***************************************************************************/
void Leg::display()
{
   // you must write this function
   char fill = ' ';
   int padding;
   
   cout << startCity;

   padding = 21 - (startCity.size());
   while (padding)
   {
      cout << fill;
      padding--;
   }
   
   startDateTime.display();
   cout << " " << destCity;

   padding = 21 - (destCity.size());
   while(padding)
   {
      cout << fill;
      padding--;
   }
   
   arrivalDateTime.display();
   cout << " " << transMode;

 
   padding = 13 - (transMode.size());
   
   cout << right << setfill(' ') << setw(padding) << milesBetween << endl;

}

/******************************************************************************
* This program reads in the itinerary from the file trip.dat and stores it into
* a linked list.  The linked list is then displayed showing an itinerary.
*
*  YOU MUST FINISH THIS FUNCTION!!!!!
*
******************************************************************************/
int main()
{
   string startCity;
   string destCity;
   string transMode;
   string temp;
   int miles;

   Node<Leg>* head = NULL;
   Node<Leg>* endLeg = head;

   char fileName[80] = "trip.dat";
   ifstream fin;

   int errorCnt = 0;
   fin.open(fileName);
   while (fin.fail())
   {
      errorCnt++;
      cout << "File not found! - '" << fileName << "'" << endl;
      if (errorCnt <= 3)
      {
         cout << "\nPlease enter the complete path or correct file name: ";
         cin >> fileName;
      }
      else
      {
         cout << "\nI'm sorry, the file '" << fileName
              << "' is not found were specified.  Exiting the program!!!\n"; 
         exit(1);
      }
      fin.open(fileName);
   }

   // hint: read startCity
   getline(fin, startCity);

   while (!fin.eof())
   {      
      // hint: read  destination city, transportation mode, miles
      getline(fin, destCity);
      getline(fin, transMode);
      getline(fin, temp);
      miles = atoi(temp.c_str());

      // hint: read  month, day, year, hr, min
      int month, day, year, hr, min;
      fin >> month;
      fin >> day;
      fin >> year;
      fin >> hr;
      fin >> min;

      // hint: create start date object
      Date startDate(year, month, day, hr, min, 0);

      // hint: read  month, day, year, hr, min
      fin >> month;
      fin >> day;
      fin >> year;
      fin >> hr;
      fin >> min;

      // hint: create arrival date object
      Date arrivalDate(year, month, day, hr, min, 0);

      // hint: throw away newline characters so next getline() will work.
      fin.ignore(80,'\n');

      // hint: create a Leg object using startCity, destCity, transMode,
      //       miles, startDate, arrivalDate      
      Leg data(startCity, destCity, transMode, miles,
               startDate, arrivalDate);

      // getting this right was terribly difficult.
      if (endLeg == NULL)
      {
         headInsert(head, data);
         endLeg = head;
      }
      else
         insert(endLeg, data);
      
      // hint: insert new leg of the trip at the end of the linked list
      while (endLeg->getLink() != 0)
      {
         endLeg = endLeg->getLink();
      }

      // hint: read next startCity from file
      getline(fin, startCity);     
   }

   Node<Leg>* current = head;

   cout << endl;
   cout << "Start City           Start Date         Destination City     Arrival Date       Mode    Miles\n";     
   cout << "-------------------- ----------------   -------------------- ----------------   -----   -----\n";
   
   // Display the itinerary HERE by traversing through the linked list!!
   while (current->getLink() != NULL)
   {
      current->getData().display();
      current = current->getLink();
   }

   return 0;
}


