/***********************************************************************
 * Program:
 *    Assignment 02, Stack Class
 *    Brother Ercanbrack, CS235
 * Author:
 *    Trevor Meyer
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "stack.h"

using namespace std;

/*************************************************************************
 *STACK CLASS CONSTRUCTOR
 *              Creates an empty stack object with a provided size.
 *INPUT:        stack size (integer)
 *OUTPUT:       new stack object
 ************************************************************************/
Stack::Stack(int size)
      : myTop(0), maxSize(size)
{
   stackItems = new int[size];
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
: myTop(aStack.myTop), maxSize(aStack.maxSize), stackItems(new int[maxSize])
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
   stackItems = new int[rtSide.maxSize];
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
int Stack::top(void)
{
   if (empty())
      cout << "ERROR: Stack is empty\n";
   else
      return stackItems[myTop - 1];
}

/*************************************************************************
 *STACK PUSH
 *              Pushes a new item to the top of the stack if the stack is
 *              not full. Does not permit stack overflow.
 *INPUT:        integer item
 ************************************************************************/
void Stack::push(int item)
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
