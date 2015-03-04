/***********************************************************************
* Program:
*    Assignment 04, Queue Library
*    Brother Ercanbrack, CS 235
* Author:
*    Trevor Meyer
***********************************************************************/
using namespace std;
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <math.h>
#include <time.h>


// BEGINNING OF AIRPLANE CLASS
/**********************************************************************
 * CLASS AIRPLANE
 *              Contains all the data required of an airplane in my
 *              imaginary air-traffic control center.
 **********************************************************************/
class Airplane
{
private:
   int  waitTime;
   int  status;  // 1 is in flight, 0 is landed, 2 is refused
   int  goalStatus;
   bool inQueue;
   int  recordNum;

public:
   Airplane();
   Airplane(int stat, int goal, int num);
   void setStatus(int stat)   { status = stat; }
   void setQueue(bool inORout) { inQueue = inORout; }
   int  getStatus(void)        { return status; }
   int  getGoalStatus(void)    { return goalStatus; }
   bool getQueue(void)         { return inQueue; }
   int  getRecordNum(void)     { return recordNum; }
   int  getTime(void)          { return waitTime; }
   void addWaitTime(void);

};

/**********************************************************************
 * DEFAULT CONSTRUCTOR
 **********************************************************************/
Airplane::Airplane()
:  waitTime(0), status(0), goalStatus(1), inQueue(false),
   recordNum(NULL)
{

}

/**********************************************************************
 * AIRPLANE CONSTRUCTOR
 **********************************************************************/
Airplane::Airplane(int stat, int goal, int num)
: waitTime(0), status(stat), goalStatus(goal),
   inQueue(false), recordNum(num)
{
   // empty on purpose
}

/**********************************************************************
 * AIRPLANE ADD WAIT TIME
 *              If the airplane is in a queue, this function adds time
 *              as long as the airplane continues to wait.
 **********************************************************************/
void Airplane::addWaitTime(void)
{
   if (inQueue)
      waitTime++;
}
// END OF AIRPLANE CLASS


// BEGINNING OF QUEUE CLASS
/**********************************************************************
 * CLASS QUEUE
 *              Modified from original version to accept Airplane
 *              data types.
 **********************************************************************/
class Queue
{
 private:
  int front;                  // --- index of front of queue
  int back;                   // --- index of back of queue
  int maxSize;                // --- max storage capacity of array
  int numItems;               // --- number of items currently in queue
  Airplane* queueItems;            // --- array containing queue items
  
 public:
  Queue(int = 100);           // --- constructor
  Queue(const Queue &aQueue); //  copy constructor
  ~Queue(void);               // --- destructor
  void insert(Airplane item);      // --- insert item into back of queue
  Airplane remove(void);           // --- remove item from front of queue
  int empty(void);            // --- returns 1 if queue is empty, 0 otherwise
  int full(void);             // --- returns 1 if queue is full, 0 otherwise
  Queue& operator = (const Queue &rtSide); // overloaded assignment operator
};

/**********************************************************************
 * default constructor
 **********************************************************************/
Queue::Queue(int size)    
{
   maxSize = size > 0 ? size : 100;    // if s is negative, set queue size to 100
   numItems = 0;
   back = front = maxSize - 1;
   queueItems = new Airplane[maxSize];
}

/**********************************************************************
 * destructor
 **********************************************************************/
Queue::~Queue(void)
{
   delete [] queueItems;
}

/***********************************************************************
 * Queue Copy Constructor
 ***********************************************************************/
Queue::Queue(const Queue &aQueue)
{
   maxSize = aQueue.maxSize;
   numItems = aQueue.numItems;
   front = aQueue.front;
   back = aQueue.back;
   queueItems = new Airplane[maxSize];
   for (int i = 0; i < maxSize; i++)
   {
      queueItems[i] = aQueue.queueItems[i];
   }
}

/***********************************************************************
 * Overloaded assignment operator.
 ***********************************************************************/
Queue& Queue::operator =(const Queue &rtSide)
{
   if (this != &rtSide)
   {
   
      if( maxSize != rtSide.maxSize)
      {
         delete [] queueItems;
         queueItems = new Airplane[rtSide.maxSize];
      }
   
      for (int i = 0; i < rtSide.maxSize; i++)
      {
         queueItems[i] = rtSide.queueItems[i];
      }
      maxSize = rtSide.maxSize;   //max size of queue
      numItems = rtSide.numItems; //number of items in queue
      back = rtSide.back;
      front = rtSide.front;
   }
   return *this;
}

/**********************************************************************
 * returns true if queue is empty
 **********************************************************************/
int Queue::empty(void)
{
   return (numItems == 0);
}

/**********************************************************************
 * returns true if queue is full
 **********************************************************************/
int Queue::full(void)
{
   return (numItems == maxSize);
}

/**********************************************************************
 * inserts item into back of queue, then increments number of items
 * in queue
 **********************************************************************/
void Queue::insert(Airplane item)
{
   // --- check for overflow
   if (full())
   {
      cout << "Queue overflow" << endl;
      exit(1);
   }
   queueItems[back] = item;
   back = (back + 1) % maxSize;
   numItems++;
}

/**********************************************************************
 * removes item from front of queue, then decrements number of items
 * in queue
 **********************************************************************/
Airplane Queue::remove(void)
{
   Airplane temp;
   
   if (empty())
   {
      cout << "queue underflow" << endl;
      exit(1);
   }
   temp = queueItems[front];
   front = (front + 1) % maxSize;
   numItems--;
   return (temp);
   
}
// END OF QUEUE CLASS




// BEGINNING OF RUNWAY CLASS
/**********************************************************************
 * CLASS RUNWAY
 *              Everything a runway might need to know all the ins and
 *              outs of the planes that are serviced by it.
 **********************************************************************/
class Runway
{
private:
   int time;
   int idleTime;
   double arrivalsPerCycle;
   double departuresPerCycle;
   int numRecords;      // records increment counter
   int recordsMax;      // max size of records for simulation
   int numPlane;        // counts the number of planes serviced
      
public:
   Airplane* records; // no reason for this to be private since Airplanes are restricted
   Queue arrivalQueue;
   Queue departureQueue;
   Runway();
   Runway(double arrivals, double depatures,
          int departSize, int arriveSize, int newTime);
   ~Runway();
   double getArrivals(void)   { return arrivalsPerCycle; }
   double getDepartures(void) { return departuresPerCycle; }
   void addIdleTime(void)     { idleTime++; }
   int getNumPlane(void)      { return numPlane; }
   int getNumRecords(void)    { return numRecords; }
   int getIdleTime(void)      { return idleTime; }
   int calcRefused(void);
   void addNumRecords(void);
   int calcNumDepartOrArrive(bool depart);
   double calcPercentWait(void);
   double calcAverageWait(bool depart);
   int calcNumWaiting(bool depart);
   void addPlane(Airplane newPlane, int recordNum);
      
};

/**********************************************************************
 * RUNWAY ADD PLANE
 *              Adds a plane to the runway records and registers it
 *              a unique ID.
 **********************************************************************/
void Runway::addPlane(Airplane newPlane, int recordNum)
{
   records[recordNum] = newPlane;
   numPlane++;
   addNumRecords();
}

/**********************************************************************
 * RUNWAY CALCULATE NUMBER OF DEPARTURES OR ARRIVALS
 *              Calculates the total number of departures or arrivals
 *              that have been successfully complete at the time it is
 *              called.
 * INPUT:       boolean
 * OUTPUT:      if input is true, returns total number of departures
 *              if input is false, returns total number of arrivals
 **********************************************************************/
int Runway::calcNumDepartOrArrive(bool depart)
{
   int num = 0;
   int i;
   if (depart)
   {
      for (i = 0; i < numRecords; i++)
      {
         if (records[i].getGoalStatus() == records[i].getStatus() &&
             records[i].getStatus() == 1)
            num++;
      }
   }
   else
   {
      for (i = 0; i < numRecords; i++)
      {
         if (records[i].getGoalStatus() == records[i].getStatus() &&
             records[i].getStatus() == 0)
            num++;
      }
   }
   return num;
}

/**********************************************************************
 * RUNWAY ADD NUMBER TO RECORDS
 *              Adds a number to the records and checks to make sure
 *              the allocated memory for the records does not overflow.
 **********************************************************************/
void Runway::addNumRecords(void)
{
   if (numRecords == recordsMax)
      cout << "ERROR: RECORDS OVERFLOW\n";
   else
      numRecords++;
}

/**********************************************************************
 * RUNWAY CALCULATE WAIT TIME PERCENTAGE
 *              Determines the percent of time that the runway remains
 *              idle and returns that value.
 * OUTPUT:      idle time percentage
 **********************************************************************/
double Runway::calcPercentWait(void)
{
   return ((double)idleTime / (double)time) * 100.0;
}

/**********************************************************************
 * RUNWAY CALCULATE REFUSED SERVICES
 *              Determines total number of airplanes have been refused
 *              services at the time the function is called.
 * OUTPUT:      number of refused airplanes (integer)
 **********************************************************************/
int Runway::calcRefused(void)
{
   int refused = 0;
   for (int i = 0; i < numRecords; i++)
   {
      if (records[i].getStatus() == 2)
         refused++;
   }
   return refused;
}

/**********************************************************************
 * RUNWAY CALCULATE THE NUMBER OF CURRENTLY WAITING AIRPLANES
 *              Determines the number of airplanes that are waiting
 *              to take off or land at the time the function is called.
 * INPUT:       boolean
 * OUTPUT:      if true: number of airplanes currently waiting to depart
 *              if false: number of airplanes currently waiting to land
 **********************************************************************/
int Runway::calcNumWaiting(bool departing)
{
   int numWaiting = 0;
   int i;
   if (departing)
   {
      for (i = 0; i < numRecords; i++)
      {
         if (records[i].getGoalStatus() != records[i].getStatus() &&
             records[i].getStatus() == 0) // arriving flights
            numWaiting++;
      }
   }
   else
   {
      for (i = 0; i < numRecords; i++)
      {
         if (records[i].getGoalStatus() != records[i].getStatus() &&
             records[i].getStatus() == 1) // departing flights
            numWaiting++;         
      }
   }
   return numWaiting;
}

/**********************************************************************
 * RUNWAY CALCULATE AVERAGE WAIT TIME
 *              Calculates the average wait time airplanes are
 *              experiencing on the runway when the function is called.
 * INPUT:       boolean
 * OUTPUT:      if true: average wait time for departing airplanes
 *              if false: average wait time for arriving airplanes
 **********************************************************************/
double Runway::calcAverageWait(bool departing)
{
   double total = 0.0;
   int num = 0;
   int i;

   if (departing)
   {
      for (i = 0; i < numRecords; i++)
         if (records[i].getGoalStatus() == records[i].getStatus() &&
             records[i].getStatus() == 1)  // have departed
         {
            total += records[i].getTime(); // wait time to take off
            num++;
         }
   }
   else
   {
      for (i = 0; i < numRecords; i++)
         if (records[i].getGoalStatus() == records[i].getStatus() &&
             records[i].getStatus() == 0)  // have arrived
         {
            total += records[i].getTime(); // wait time to land
            num++;
         }
   }
   return (total / (double)num);
}

/**********************************************************************
 * RUNWAY DESTRUCTOR
 **********************************************************************/
Runway::~Runway()
{
   delete [] records;
}

/**********************************************************************
 * RUNWAY DEFAULT CONSTRUCTOR
 **********************************************************************/
Runway::Runway()
:  arrivalsPerCycle(.50), departuresPerCycle(.50), idleTime(0),
   arrivalQueue(5), departureQueue(5), numPlane(0), time(100),
   numRecords(0), recordsMax(200)
{
   records = new Airplane[recordsMax];
}

/**********************************************************************
 * RUNWAY CONSTRUCTOR
 **********************************************************************/
Runway::Runway(double arrivals, double departures,
               int arrivalSize, int departSize, int newTime)
:  arrivalsPerCycle(arrivals), departuresPerCycle(departures),
   departureQueue(arrivalSize), arrivalQueue(departSize), numPlane(0), time(newTime),
   numRecords(0), idleTime(0)
{
   recordsMax = ((arrivals + departures) * 2) * newTime;
   records = new Airplane[recordsMax];
}
// END RUNWAY CLASS

// START RANDOM CLASS
/**********************************************************************
 * CLASS RANDOM
 *              Allows for random numbers to be called for simulation.
 **********************************************************************/
class Random
{
 public:
  Random();

  /* --- Get next Poisson random --- */
  int poissonRandom(double expected);

};

Random::Random()
{
   // srand((int)time(NULL));   // variable seed for real simulation
   srand(2500);                 // fixed seed for debug and grading
}

int Random::poissonRandom(double expected)
{
  int n = 0;
  double limit;
  double x;
  
  limit = exp(-expected);
  x = rand() / ((double)RAND_MAX + 1);
  while (x > limit)
    {
      n++;
      x *= rand() / ((double)RAND_MAX + 1);
    }
  return n;
}
// END RANDOM CLASS

/**********************************************************************
 * MAIN
 *              Main driver function. Contains the air-traffic control
 *              algorithm for this assignment that effectively makes
 *              use of the queue, runway, airplane, and random classes.
 **********************************************************************/
int main()
{
   int time;
   double arrivals;
   double departures;
   bool loop = true;
   while (loop)
   {
      cout << "Units of time the simulation will run: ";
      cin  >> time;
      if (cin.fail())
      {
         loop = true;
         cin.clear();
         cin.ignore();
         cout << "Please enter an integer.\n";
      }
      else
         loop = false;
   }
   loop = true;
   while (loop)
   {
      cout << "Expected number of arrivals per time unit: ";
      cin  >> arrivals;
      if (cin.fail())
      {
         loop = true;
         cin.clear();
         cin.ignore();
         cout << "Please enter a double.\n";
      }
      else
         loop = false;
   }
   loop = true;
   while (loop)
   {
      cout << "Expected number of take offs per time unit: ";
      cin  >> departures;
      if (cin.fail())
      {
         loop = true;
         cin.clear();
         cin.ignore();
         cout << "Please enter a double.\n";
      }
      else
         loop = false;
   }
   cout << endl;

   Runway runway(arrivals, departures, 5, 5, time);
   Random random; // class to generate random numbers
   int numberOfArrivals;
   int numberOfDepartures;
   int i = 0; // for looping purposes
   int r = 0; // records incrementor

   // start simulation loop
   for (int currentTime = 0; currentTime < time; currentTime++)
   {
      numberOfArrivals = random.poissonRandom(runway.getArrivals());
      for (i = 0; i < numberOfArrivals; i++)
      {
         Airplane temp1(1, 0, r);
         runway.addPlane(temp1, r);
         // creates registration record for new plane
         
         if (runway.arrivalQueue.full())
            runway.records[runway.getNumRecords()].setStatus(2);
            // refused status

         else
         {
            runway.arrivalQueue.insert(temp1);
            runway.records[r].setQueue(1);
         }
         r++;
      }

      numberOfDepartures = random.poissonRandom(runway.getDepartures());
      for (i = 0; i < numberOfDepartures; i++)
      {
         Airplane temp0(0, 1, r);
         runway.addPlane(temp0, r); // creates registration record for new plane
         if (runway.departureQueue.full())
            runway.records[r].setStatus(2); //refused status

         else
         {
            runway.departureQueue.insert(temp0);
            runway.records[r].setQueue(true);
         }
         r++;
      }
      if (!runway.arrivalQueue.empty())
      {
         Airplane tempRemoved0;
         tempRemoved0 = runway.arrivalQueue.remove();
         runway.records[tempRemoved0.getRecordNum()].setStatus(0);
         runway.records[tempRemoved0.getRecordNum()].setQueue(false);
      }
      else if (!runway.departureQueue.empty())
      {
         Airplane tempRemoved1;
         tempRemoved1 = runway.departureQueue.remove();
         runway.records[tempRemoved1.getRecordNum()].setStatus(1);
         runway.records[tempRemoved1.getRecordNum()].setQueue(false);
      }
      else
         runway.addIdleTime();

      for (i = 0; i < r; i++)
         runway.records[i].addWaitTime(); 
   }
   
   bool departing = true;

   cout << "Total number of planes processed: "
        << runway.getNumRecords()
        << endl
        << "Number of planes landed: "
        << runway.calcNumDepartOrArrive(!departing)
        << endl
        << "Number of planes taken off: "
        << runway.calcNumDepartOrArrive(departing)
        << endl
        << "Number left ready to land: "
        << runway.calcNumWaiting(!departing)
        << endl
        << "Number left ready to take off: "
        << runway.calcNumWaiting(departing)
        << endl
        << "Number of planes refused use: "
        << runway.calcRefused()
        << endl
        << fixed << setprecision(2)
        << "Percentage of time runway idle: "
        << runway.calcPercentWait() << "%"
        << endl
        << "Average wait time to land: "
        << runway.calcAverageWait(!departing)
        << endl
        << "Average wait time to take off: "
        << runway.calcAverageWait(departing)
        << endl;

   return 0;
}
