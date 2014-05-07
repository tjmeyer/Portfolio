/***********************************************************************
* Program:
*    Assignment 05, Recursive Binary Search
*    Brother Ercanbrack, CS165
* Author:
*    Trevor Meyer
* Summary: 
*    Recursive binary search demonstration program. Had a good time making
*    this. It was interesting to sync the co-operation between first names
*    and last.
************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

/*******************************************************************
 * RECURSIVE BINARY SEARCH
 *
 *    This is where all the searching happens by last name only.
 *
 *      INPUT:   LAST NAME LIST
 *               LIST STARTING POSITION
 *               LIST ENDING POSITION
 *               SEARCH CRITERIA
 *      OUTPUT:  NONE
 *      RETURN:  SEARCH LOCATION
 *               INVERSE OF END POSITION (if item not found)
 ******************************************************************/
int binarySearch(string list[], int start, int end, string search)
{

   if (start <= end)
   {
      int mid = (start + end) / 2;  // determines mid-point

      if (search == list[mid])
         return mid;    // when found

      else if (search < list[mid])
         // call function for lower half
         return binarySearch (list, start, mid - 1, search);

      else
         // now for upper half
         return binarySearch (list, mid + 1, end, search);

   }
   return - (start);
}

/****************************************************************
 * SWAP
 *
 *      This is where select items are switched in position to
 *      re-organize the list.
 *
 *      INPUT:   LAST NAME LIST
 *               FIRST NAME LIST
 *               POSITION A (start)
 *               POSITION B (end)
 *      OUTPUT:  CHANGE IN POSITION
 *      RETURN:  NONE
 ***************************************************************/
void swap(string list[], string first[], int start, int end)
{

   string temp = list[start];
   list[start] = list[end];
   list[end] = temp;

   temp = first[start];
   first[start] = first[end];
   first[end] = temp;
   
   return;
}

/***************************************************************
 * FIND MINIMUM
 *
 *      This function determines which value is smallest between
 *      two locations at a time. If the value is found to be
 *      smaller than its compared value, it is passed on.
 *
 *      INPUT:   LAST NAME LIST
 *               FIRST NAME LIST
 *               COMPARISON POSITION START
 *               COMPARISON POSITION END
 *      OUTPUT:  NONE
 *      RETURN:  POSITION OF MINIMUM VALUE
 **************************************************************/
int findMin(string list[], string first[], int start, int end)
{
   int minimum = start;
   for (int i = start; i <= end; i++)
      if ((list[i] + first[i]) < (list[minimum] + first[minimum]))
         minimum = i;
   return minimum;
}

/***************************************************************
 * SORT
 *
 *      Determines when to stop switching list values. Calls
 *      the swap function, find minimum function, and the sort
 *      function accordingly. When the start position is equivalent
 *      to the end position, this function exits.
 *
 *      INPUT:   LAST NAME LIST
 *               FIRST NAME LIST
 *               START POSITION
 *               END POSITION
 *      OUTPUT:  NONE
 *      RETURN:  NONE
 **************************************************************/
void sort(string list[], string first[], int start, int end)
{

   if (start == end)
      return;
   else
   {
      swap(list, first, start, findMin(list, first, start, end));
      sort(list, first, start + 1, end);
   }
}

/****************************************************************
 *MAIN
 *      Opens the target file and does the corresponding error
 *      handling for all input values and function. Main also
 *      holds all primary variables.
 *
 *      See following comments for the implementation of 
 *      individual components of  the main function.
 **************************************************************/
main()
{   
   //import list
   ifstream fin("/home/ercanbracks/cs165-examples/assign05/studentList.txt");

   // error checking
   if (fin.fail())
   {
      cout << "File was not found.\n"
           << "Please make sure the following directory is available:\n"
           << "/home/ercanbracks/cs165-examples/assign05/studentList.txt\n\n"
           << "Exiting program\n";
      
      return 0;
   }

   int size;
   fin >> size; // read in initial value (size)
  
   string *last;
   string *first;
   last  = new string[size + 2]; // +1 for blank line, +1 for number
   first = new string[size + 2];
   
   for (int i = 0; fin >> last[i] >> first[i]; i++);
   
   fin.close();
   
   //sort list
   int start = 0;
   sort(last, first, start, size);


   // welcome screen start
   cout << "---------------------------------------------------------------\n"
        << "Binary Search Program - Search using last name (case sensitive)\n"
        << "---------------------------------------------------------------\n";
   
   //search loop begins
   string search = "";
   bool quit = false;
   while (!quit)
   {
      cout << endl << "Search for: ";

      cin  >> search;

      // error checking
      while (cin.fail())
      {
         cin.clear();
         cin.ignore(100, '\n');
         cout << "Error: Invalid Input\n";

         cout << endl << "Search for: ";
         cin  >> search;
      }

      if (search == "quit" ||
          search == "Quit")
         quit = true;  // <--- end program loop
      else
      {
         int result = binarySearch(last, start, size, search);
         if (result < 0)
            cout << endl << search << " is not found!\n";
         else
         {
            //count characters for spacing
            int count = 0;     // total count
            int countLoop = 0; // loop count
            for ( ; last[result][countLoop]; count++)
               countLoop++;

            countLoop = 0;     // re-initialize for next loop
            for ( ; first[result][countLoop]; count++)
               countLoop++;
            
            count += 2;  // for ", " insertion
                      
            cout << endl
                 << last[result] << ", " << first[result]
                 << setw(45 - count) << "Record Number: "
                 << result << endl;
         }
      }
      // end search loop here   
   }
   delete [] last;
   delete [] first;
   
   return 0;

}
