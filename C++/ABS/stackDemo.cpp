/***********************************************************************
 * Program:
 *    Assignment 03
 *    Brother Ercanbrack, CS235
 * Author:
 *    Trevor Meyer
 ************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>

using namespace std;

// BEGIN STACK CLASS

/************************************************************
*
*  NAME: Brother Ercanbrack
*  PROGRAM: stack.h
*  PURPOSE: Class definition for a stack object
*
************************************************************/
class Stack
{
   private:
     int myTop;                  // index of top of stack
     int maxSize;                // maximum size of stack  
     char *stackItems;            // pointer for dynamic array
   public:
     Stack(int size = 100);      // default constructor (stack size 100)
     Stack(const Stack &aStack); // copy constructor 
     char top(void);           // returns the value of top item in the stack
     void push(char item);     // store item on the stack
     void pop(void);             // remove/delete top item off stack
     bool empty(void);           // is stack empty
     bool full(void);            // is stack full
     ~Stack();                   // destructor
     Stack& operator = (const Stack &rtSide); // overloaded assignment operator
};

/*************************************************************************
 *STACK CLASS CONSTRUCTOR
 *              Creates an empty stack object with a provided size.
 *INPUT:        stack size (character)
 *OUTPUT:       new stack object
 ************************************************************************/
Stack::Stack(int size)
      : myTop(0), maxSize(size)
{
   stackItems = new char[size];
}

/*************************************************************************
 *STACK CLASS DECONSTRUCTOR
 *              Deletes the pointer from the class when it goes out of
 *              scope or is explicitly called.
 ************************************************************************/
Stack::~Stack()
{
   delete [] stackItems;
}

/*************************************************************************
 *STACK CLASS COPY CONSTRUCTOR
 *              A constructor that allows for the stack class to be
 *              copied when needed. Very similar to the assignment
 *              operator.
 *INPUT:        stack object
 *OUTPUT:       copied stack object
 ************************************************************************/
Stack::Stack(const Stack& aStack)
: myTop(aStack.myTop), maxSize(aStack.maxSize), stackItems(new char[maxSize])
{
   for (int i = 0; i < myTop; i++)
      stackItems[i] = aStack.stackItems[i];
}

/*************************************************************************
 *STACK CLASS OPERATOR =
 *              Allows for two stack objects to be assigned from on to
 *              another.
 *INPUT:        stack object to be assigned
 *OUTPUT:       New stack object
 ************************************************************************/
Stack& Stack::operator =(const Stack &rtSide)
{
   if (this == &rtSide)
      return *this;

   delete [] stackItems;
   stackItems = new char[rtSide.maxSize];
   myTop = rtSide.myTop;
   maxSize = rtSide.maxSize;

   for (int i = 0; i < myTop; i++)
      stackItems[i] = rtSide.stackItems[i];

   return *this;
}

/*************************************************************************
 *STACK TOP
 *              Returns the item that resides on the top of the stack.
 *OUTPUT:       top of the stack
 ************************************************************************/
char Stack::top(void)
{
   if (empty())
      return '\0';
   else
      return stackItems[myTop - 1];
}

/*************************************************************************
 *STACK POP
 *              Indexes the top of the stack by -1. This function does not
 *              delete the data at the top of the stack, but shifts the
 *              pointer down the stack one place. Does not allow for
 *              stack underflow.
 ************************************************************************/
void Stack::pop(void)
{
   if (empty())
   {
      cout << "ERROR: Stack Underflow\n";
      exit(1);
   }
   else
      myTop--;
}

/*************************************************************************
 *STACK PUSH
 *              Pushes a new item to the top of the stack if the stack is
 *              not full. Does not permit stack overflow.
 *INPUT:        integer item
 ************************************************************************/
void Stack::push(char item)
{
   if (!full())
   {
      stackItems[myTop] = item;
      myTop++;
   }
   else
   {
      cout << "ERROR: Stack Overflow\n";
      exit(1);
   }
}

/*************************************************************************
 *STACK EMPTY
 *              Returns true if the top of the stack is equal to 0.
 *              Therefore informing the user if the stack is empty or not.
 *OUTPUT:       TRUE when stack object is empty
 ************************************************************************/
bool Stack::empty(void)
{
   return (myTop == 0);
}

/*************************************************************************
 *STACK FULL
 *              Returns true if the top of the stack is the same value
 *              as the max size of the stack. Therefore informing the user
 *              if the stack is full or not.
 *OUTPUT:       TRUE when stack object is full
 ************************************************************************/
bool Stack::full(void)
{
   return (myTop == maxSize);
}

// END OF STACK CLASS

// BEGINNING OF EXPRESSION CLASS

/************************************************************************
 *CLASS EXPRESSION
 *              Stores an expression and allows the user the manipulate
 *              the notation of the input expression.
 ***********************************************************************/
class Expression
{
private:
   string equationInFix;
   string equationPostFix;

   int pres(char ch);
   bool isOperator(char ch);
   
public:
   Expression() : equationInFix("A+B*C"){}
   Expression(string newEquation) : equationInFix(newEquation){}
   void convertPostFix();
   void displayPostFix() { cout << equationPostFix << endl; }
   void displayInFix()   { cout << equationInFix   << endl; }
   void displayAssembly();
};

/************************************************************************
 *CLASS EXPRESSION DISPLAY ASSEMBLY
 *              Displays the post fix notation of an expression in the
 *              expression class in assembly code.
 ***********************************************************************/
void Expression::displayAssembly()
{
   char o1;     // first evaluated operand
   char o2;     // second evaluated operand
   string op;   // operation in assembly ex. "ML" etc.
   char temp = '1';
   Stack stack(equationPostFix.length());

   int i = 0;   // looping index
   
   while (equationPostFix[i])
   {
      char ch = equationPostFix[i];
      if (isOperator(ch))
      {
         o2 = stack.top();
         stack.pop();
         o1 = stack.top();
         stack.pop();

         if (ch == '+')
            op = "AD  ";
         else if (ch == '-')
            op = "SB  ";
         else if (ch == '*')
            op = "ML  ";
         else if (ch == '/')
            op = "DV  ";
         
         if (isdigit(o1))
            cout << "LD  " << "TEMP" << o1 << endl;
         else
            cout << "LD  " << o1 << endl;

         cout << op;

         if (isdigit(o2))
            cout << "TEMP" << o2 << endl;
         else
            cout << o2 << endl;

         cout << "ST  TEMP" << temp << endl;
         stack.push(temp);

         temp++;
      }
      else
         stack.push(ch);
      
      i++;
   }
}

/************************************************************************
 *CLASS EXPRESSION: CONVERT TO POST FIX NOTATION
 *              Converts the stored infix equation into a postfix notation.
 *              Writes new notation to a new variable to preserve the
 *              original infix notation.
 ***********************************************************************/
void Expression::convertPostFix()
{
   int length = equationInFix.length();
   Stack stack(length);
   string postFix = "";
   int i = 0;           // for all looping
   int j = 0;

   while (equationInFix[i])
   {
      char ch = equationInFix[i];
      if (isalpha(ch))
         postFix.push_back(ch);
      else if (isOperator(ch))
      {
         while (isOperator(stack.top()) &&
                pres(ch) <= pres(stack.top()))
         {
            postFix.push_back(stack.top());
            stack.pop();
         }
         stack.push(ch);
      }
      else if (ch == '(')
         stack.push(ch);
      else if (ch == ')')
      {
         while (stack.top() != '(')
         {
            if (stack.empty())
            {
               cout << "ERROR: MISMATCHING PARENTHESES\n";
               exit(1);
            }
            postFix.push_back(stack.top());
            stack.pop();
         }
         stack.pop(); // remove left parentheses
      }
      i++;
   }
   while (!stack.empty())
   {
      postFix.push_back(stack.top());
      stack.pop();
   }
   equationPostFix = postFix;
}

/************************************************************************
 *CLASS EXPRESSION: PRESEDENCE
 *              Determines the presedence of an opertion according to
 *              the rules of algebra.
 *INPUT:        operation character
 *OUTPUT:       presedence value (integer)
 ***********************************************************************/
int Expression::pres(char ch)
{
   if (ch == '^')
      return 3;
   else if (ch == '*' || ch == '/')
      return 2;
   else if (ch == '+' || ch == '-')
      return 1;
   else
   {
      cout << "ERROR: PRESEDENCE EXCEPTION OCCURED\n";
      exit(1);
   }
}

/************************************************************************
 *CLASS EXPRESSION: IS OPERATOR
 *              Determines if a character is an operator or not.
 *INPUT:        character
 *OUTPUT:       TRUE (if the character is an operator)
 ***********************************************************************/
bool Expression::isOperator(char ch)
{
   if (ch == '+' || ch == '-' || ch == '/' ||
       ch == '*' || ch == '^')
      return true;
   else
      return false;
}
// END OF EXPRESSION CLASS DEFINITION

/************************************************************************
 *MAIN
 *              Receives a file location and acts as a driver to the
 *              above defined classes.
 ***********************************************************************/
int main(int argc, char* argv[])
{
   // check for correct number of arguements
   if (argc < 2)
   {
      cout << "\tERROR: FILE LOCATION REQUIRED\n";
      return 0;
   }
   else if (argc > 2)
   {
      cout << "\tERROR: TOO MANY ARGUEMENTS\n";
      return 0;
   }

   ifstream fin;
   fin.open(argv[argc - 1]);
   if (fin.fail())
   {
      cout << "\nFILE READ ERROR\n"
           << "Please check file location and try again.\n"
           << "Exiting Program..... \n\n";
      return 0;
   }

   string temp;
   
   while (!fin.eof())
   {
      getline(fin, temp);
      if (temp.length() > 1)
      {
         Expression cool(temp);
         cool.convertPostFix();
         cool.displayAssembly();
         cout << endl;
      }
   }
   
   fin.close();
   
   return 0;
}
