/***********************************************************************
* Program:
*    Assignment 01, 
*    Brother Ercanbrack, CS235
* Author:
*    Trevor Meyer
************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

/*********************************************************************
 * CLASS DATA
 * CONTAINS:  array pointer
 *            capacity of array
 *            name of data set
 *******************************************************************/
class Data
{
public:
   //overload operators
   Data operator = (const Data& list2);
   const Data operator - (const Data& list2) const;
   const Data operator + (const Data& list2) const;
   const Data operator && (const Data& list2) const;
   const Data operator || (const Data& list2) const { return *this + list2; }
   bool operator == (const Data& list2) const;

   Data();
   Data (int* pointer, int theCap, string theName);
   ~Data() { delete [] array; }
   Data (const Data& copy);

   void removeDuplicates();
   void sortArray();
   void displayArray();
   void add(int number);
   int getSize() { return capacity; }
   bool searchArray(int number);

   string name;
   
private:
   int* array;
   int capacity;
};

/******************************************************************
 * BINARY DATA OPERATOR &&
 * DESCRIPTION: Takes two sets of data and ouputs only the values
 *              that exists in both sets. The order of the operands
 *              does not matter.
 * INPUT:       two data objects
 * OUPUT:       one data object
 *****************************************************************/
const Data Data::operator && (const Data& list2) const
{
   stringstream ss;
   string newName;
   int cap = capacity;
   int size = 0;
   int x = 0;
   int y = 0;

   ss << "Intersection of " << name << " and " << list2.name;
   getline(ss, newName);

   ss.clear();
   
   while (x < cap)
   {
      y = 0;
      while (y < list2.capacity)
      {
         if (array[x] == list2.array[y])
         {
            ss << array[x] << " ";
            size++;
         }
         y++;
      }
      x++;
   }

   int* temp = new int[size];
   
   for (x = 0; x < size; x++)
      ss >> temp[x];
   
   return Data(temp, size, newName);
}

/******************************************************************
 * BINARY DATA OPERATOR +
 * DESCRIPTION: Recieves two data objects and outputs a new object
 *              that is a combination of the two.
 * INPUT:       Data objects
 * OUTPUT:      Data object
 *****************************************************************/
const Data Data::operator + (const Data& list2) const
{
   int *temp;
   int cap = capacity + list2.capacity;
   stringstream ss;
   string newName;
   int x;

   ss << "Union of " << name << " and " << list2.name;
   getline(ss, newName);

   ss.clear();
   
   for (x = 0; x < capacity; x++)
      ss << array[x] << " ";
   for (x = 0; x < list2.capacity; x++)
      ss << list2.array[x] << " ";

   temp = new int[cap];
   
   for (x = 0; x < cap; x++)
      ss >> temp[x];

   return Data(temp, cap, newName);
}

/******************************************************************
 * BINARY DATA OPERATOR ==
 * DESCRIPTION: Compares the two data objects and returns a boolean
 *              value to determine equality. Only tests for location
 *              equality, not data equality.
 * INPUT:       Data objects
 * OUTPUT:      Bollean value
 *****************************************************************/
bool Data::operator == (const Data& list2) const
{
   bool value;
   if (&array == &list2.array && capacity == list2.capacity)
      value = true;
   else
      value = false;

   return value;
}

/******************************************************************
 * BINARY DATA OPERATOR -
 * DESCRIPTION: Removes values from the first operand that also
 *              exist in the second operand and creates a new
 *              data object from the resulting values.
 * INPUT:       Data Objects
 * OUTPUT:      Data Object
 ******************************************************************/
const Data Data::operator - (const Data& list2) const
{
   int* temp;
   int cap = capacity;
   stringstream ss;
   string newName;
   int t = 0;

   ss << "Difference of " << name << " and " << list2.name;
   getline(ss, newName);

   temp = new int[cap];

   for (int t = 0; t < cap; t++)
      temp[t] = array[t];
   
   int x = 0;
   int y = 0;

   while (x < cap)
   {
      y = 0;
      while (y < list2.capacity)
      {
         if (temp[x] == list2.array[y])
         {
            --cap;         
            // left-shift array
            for (t = x; t < cap; t++)
               temp[t] = temp[t + 1];
         }
         y++;
      }
      x++;
   }

   return Data(temp, cap, newName);
}

/******************************************************************
 * BINARY DATA OPERATOR =
 * DESCRIPTION: Allows the user to set one data object equal to
 *              another.
 * INPUT:       Data object
 * OUTPUT:      Data object
 ******************************************************************/
Data Data::operator = (const Data& list2)
{
   if (this == &list2)
      return *this;
   
   else
   {
      if (list2.capacity > capacity)
      {
         delete [] array;
         array = new int[list2.capacity];
         capacity = list2.capacity;
      }
      
      for (int i = 0; i < list2.capacity; i++)
         array[i] = list2.array[i];
      
      capacity = list2.capacity;
      return *this;
   }
}

/******************************************************************
 * DATA DISPLAY MEMBER FUNCTION
 * DESCRIPTION: May be called at any time to display a formatted
 *              table of the contents of the object's array.
 *              Each line is 10 across.
 ******************************************************************/
void Data::displayArray()
{
   if (name == "A" || name == "B")
      cout << "Set " << name << ":\n";
   else
      cout << name << ":\n";
   for (int x = 0; x < capacity; x++)
   {
      cout << setw(4) << array[x];
      if (((x + 1) % 10) == 0 && x + 1 != capacity)
         cout << endl;
   }
   cout << endl << endl;
   return;
}

/******************************************************************
 * DATA SEARCH ARRAY MEMBER FUNCTION
 * DESCRIPTION: This function can be called at anytime to search
 *              the data object's array for any integer. Returns
 *              true if found.
 * INPUT:       Integer
 * OUTPUT:      Boolean value
 ******************************************************************/
bool Data::searchArray(int number)
{
   for (int x = 0; x < capacity; x++)
      if (array[x] == number)
         return true;
   
   return false;
}

/******************************************************************
 * DATA ADD MEMBER FUNCTION
 * DESCRIPTION: Allows the user to add a value to the end of the
 *              data object array.
 * INPUT:       Integer
 * OUPUT:       None
 ******************************************************************/
void Data::add(int number)
{
   // increment capacity
   ++capacity;
   // create new array with modified capacity
   int* temp = new int[capacity];
   temp[0] = number;
   for (int x = 0; x < capacity - 1; x++)
      temp[x + 1] = array[x];

   delete [] array;
   array = temp;
   return;
}

/******************************************************************
 * DATA REMOVE DUPLICATES MEMBER FUNCTION
 * DESCRIPTION: Removes any duplicates from the data objects array
 *              and properly re-adjusts for correct data allocation.
 ******************************************************************/
void Data::removeDuplicates()
{
   int* temp;
   int x = 0;
   int y = 0;

   while (x < capacity)
   {
      y = x + 1;
      while (y < capacity)
      {
         if (array[x] == array[y])
         {            
            --capacity;
            
            // left-shift array
            for (int o = y; o < capacity; o++)
               array[o] = array[o + 1];
                        
            temp = new int[capacity];
            for(int m = 0; m < capacity; m++)
               temp[m] = array[m];

            array = temp;
            y--;
         }
         y++;
      }
       x++;
   }
}

/******************************************************************
 * DATA SORT ARRAY MEMBER FUNCTION
 * DESCRIPTION: Sorts the data in a data class object in accending order.
 ******************************************************************/
void Data::sortArray()
{
   int temp;
   int x = 0;
   while (x < capacity)
   {
      if (array[x] > array[x + 1]
          && x + 1 < capacity)
      {
         temp = array[x];
         array[x] = array[x + 1];
         array[x + 1] = temp;
         x = 0;
      }
      else
         x++;
   }
}

/******************************************************************
 * DATA CLASS DEFAULT CONSTRUCTOR
 ******************************************************************/
Data::Data() :
      array(NULL), capacity(0), name("Blank")
{
}

/******************************************************************
 * DATA CLASS CONSTRUCTOR
 * INPUT:       integer pointer
 *              capacity of array (integer)
 *              name of the data set (string)
 * OUTPUT:      Data object
 ******************************************************************/
Data::Data(int* pointer, int theCap, string theName) :
      array(pointer), capacity(theCap), name(theName)
{
   removeDuplicates();
}

/******************************************************************
 * DATA CLASS COPY CONSTRUCTOR
 *      Needed for correct integer pointer copying if needed.
 ******************************************************************/
Data::Data(const Data& list2) :
      array(list2.array), capacity(list2.capacity), name(list2.name)
{
   this->removeDuplicates();
}

/******************************************************************
 * MAIN
 * DESCRIPTION: Walks through the required functions and reads in
 *              a formatted file from command line. Driver function
 *              that fulfills the requirements for the assignment.
 *              Also takes care of all  necessary error handling.
 ******************************************************************/
int main(int argc, char* argv[])
{
   //check for correct arguments
   if (argc < 2)
   {
      cout << "Correct usage:\n"
           << "\t[program Name] [file]" << endl;
      return 0;
   }
   else
   {
      ifstream fin;
      fin.open(argv[argc - 1]);
      if (fin.fail())
      {
         cout << "\nFile Error. Please check file location and try again.\n"
              << "exiting program....\n\n";
         return 0;
      }
      
      
      int* temp;
      int cap;
      int x;      // for looping
      
      //read in and sort Set A
      fin >> cap;
      temp = new int[cap];
      for (x = 0; x < cap; x++)
         fin >> temp[x];

      Data setA(temp, cap, "A");
      setA.sortArray();
      setA.displayArray();

      //read in and sort Set B
      fin >> cap;
      temp = new int[cap];
      for (x = 0; x < cap; x++)
         fin >> temp[x];

      fin.close();
      
      Data setB(temp, cap, "B");
      setB.sortArray();
      setB.displayArray();
            
      //create and sort intersection of A and B
      Data intersectAB = setA && setB;
      intersectAB.sortArray();
      intersectAB.displayArray();

      //Union of A and B Data
      Data unionAB = setA || setB;
      unionAB.sortArray();
      unionAB.displayArray();

      //Difference of A and B Data
      Data differenceAB = setA - setB;
      differenceAB.sortArray();
      differenceAB.displayArray();

      //Difference of B and A Data
      Data differenceBA = setB - setA;
      differenceBA.sortArray();
      differenceBA.displayArray();
   }
   return 0;
}
