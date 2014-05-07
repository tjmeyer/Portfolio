/***********************************************************************
* Program:
*    Assignment 05, Stocks Program 
*    Brother Ercanbrack, CS235
* Author:
*    Trevor Meyer
* Description:
*    Totally awesome. Inputing a file that is not in the correct format
*    will yield undefined results. This is designed to demonstrate
*    the application of the abstract data type deque... and to awesome
*    because Trevor loves ABS's! :)  enjoy! Trevor also likes to program
*    creatively, otherwise programming would be copying and pasting from
*    cplusplus.com, and that's just no fun. My software doesn't have bugs,
*    it just develops random features.
************************************************************************/

#include <iostream>
#include <deque>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath> // lazy, wanted abs() function

using namespace std;

/***********************************************************************
 * CLASS SHARE
 *      Description:    Contains a quantity of stock and the price at
 *                      which they were orginially purchased. Also
 *                      includes access and mutator functions. Not all
 *                      are used in this program.
 **********************************************************************/
class Share
{
private:
   int quantity;
   double price;

public:
   Share();
   Share(int Quantity, double Price);
   int getQuantity() { return quantity; }
   double getPrice() { return price; }
   void setQuantity(int newQuantity) { quantity = newQuantity; }
   void setPrice(double newPrice) { price = newPrice; }
   void display();
};

/***********************************************************************
 * CLASS SHARE - DISPLAY
 *      Description:    Displays the two private variables of any share
 *                      object. 
 **********************************************************************/
void Share::display()
{
   cout << quantity << " shares bought for $"
        << fixed << setprecision(2) << price << endl;
}

/***********************************************************************
 * CLASS SHARE DEFAULT CONSTRUCTOR
 **********************************************************************/
Share::Share()
      : quantity(0), price(0.00)
{
   // empty on purpose
}

/***********************************************************************
 * CLASS SHARE CONSTRUCTOR
 **********************************************************************/
Share::Share(int newQuantity, double newPrice)
      : quantity(newQuantity), price(newPrice)
{
   // empty on purpose
}

/***********************************************************************
 * CLASS SHARES ACCOUNT
 *      Description:    Includes a deque for all purchased shares. Also
 *                      keeps track of over-all expeditures and earnings
 *                      which is not needed in this program but seemed
 *                      logical to have in an account class. Accounts
 *                      can only be opened with nothing in them, therefore
 *                      only a default constructor is available to the user.
 **********************************************************************/
class Account
{
private:
   deque<Share> shareAccount; // filled with shares
   double expenditures;
   double earnings;
   double totalProfit;
   
public:
   Account(); // starts and empty account
   stringstream ledger;
   void sell(int numberOfShares, double priceOfShares);
   void buy(int numberOfShares, double priceOfShares);
   double getBalance() { return (earnings - expenditures); }
   void readIn(char* fileName);
   void displaySummary();
};

/***********************************************************************
 * CLASS SHARES ACCOUNT - DISPLAY SUMMARY
 *      Description:    Displays an account summary. Besides, everything
 *                      needs a display function. It's not bogus, it's an
 *                      IBM standard.
 **********************************************************************/
void Account::displaySummary()
{
   string temp;
   while (!ledger.eof())
   {
      getline(ledger, temp);
      cout << temp << endl;
   }
   cout << "Total Profit: $";
   if (totalProfit < 0)
      cout << fixed << setprecision(2) << "(" << abs(totalProfit) << ")";
   else
      cout << fixed << setprecision(2) << totalProfit;
   cout << endl;

   cout << endl;
   cout << "Unsold Shares" << endl;
   if (!shareAccount.empty())
   {
      for (int i = 0; i < shareAccount.size(); i++)
      {
         cout << "   ";
         shareAccount[i].display();
      }
   }
}

/***********************************************************************
 * CLASS SHARES ACCOUNT - SELL
 *      Description:    Perfoms a sale of stock.
 * INPUT:       quantity of shares to sell
 *              price of each share sale
 * OUTPUT:      Records the sale in the account ledger
 *              adjusts total profit for the account
 *              adjusts total earnings for the account
 **********************************************************************/
void Account::sell(int shares, double price)
{
   int startShares = shares;
   double profit   = 0.00;
   double baseCost = 0.00;
   double baseIncome = shares * price;
   earnings += baseIncome;
   
   while (shares > 0)
   {
      double frontPrice = shareAccount.front().getPrice();
      double frontQuantity = shareAccount.front().getQuantity();
      // does fuzzy logic tickle?
      if (frontQuantity == shares)
      {
         baseCost += frontPrice * frontQuantity;
         shareAccount.pop_front();
         shares = 0;
      }
      else if (frontQuantity > shares)
      {
         baseCost += shares * frontPrice;
         shareAccount.front().setQuantity(frontQuantity - shares);
         shares = 0;
      }
      else if (frontQuantity < shares)
      {
         baseCost += frontQuantity * frontPrice;
         shares -= frontQuantity;
         shareAccount.pop_front();
      }
      else if (shareAccount.empty())
      {
         cout << "ERROR: CANNOT SELL WHAT YOU DO NOT HAVE, THOUGH THAT WOULD BE COOL\n"
              << "TRANSACTION CANCELLED\n";
         exit(1);
      }
      else
      {
         cout << "ERROR: EXCEPTION OCCURED IN SELL ALGORITHM\n";
         exit(1);
      }
   }
   
   profit = baseIncome - baseCost;
   totalProfit += profit;

   // record sale to the ledger
   ledger << "Sold " << startShares << " shares at $" << setprecision(2) << price
          << " for a profit of $";
   if (profit < 0)
      ledger << "(" << abs(profit) << ")";
   else
      ledger << profit;
   ledger << endl;
}

/***********************************************************************
 * CLASS SHARES ACCOUNT - BUY
 *      Description:    Performs a buy function for the account.
 * INPUT:       quantity of shares to purchase
 *              price of each share being purchased
 * OUTPUT:      adjusts total expeditures on the account
 *              creates a new share for the account deque
 **********************************************************************/
void Account::buy(int shares, double price)
{
   Share temp(shares, price);
   expenditures += price * shares;
   shareAccount.push_back(temp);
   ledger << "Bought " << shares << " shares at $"
          << setprecision(2) << fixed << price << endl;
}

/***********************************************************************
 * CLASS SHARES ACCOUNT - READ IN
 *      Description:    Reads in a file of a certain format to quickly
 *                      create and adjust an account of any length.
 *                      Convenient for simulations.
 * INPUT:       file location
 * OUPUT:       performs sales and purchase on an account (pending
 *              the contents of the file)
 **********************************************************************/
void Account::readIn(char fileName[])
{
   ifstream fin(fileName);
   if (fin.fail())
   {
      // bad file name, go stand in the corner!
      cout << "ERROR: BAD FILE NAME, GO STAND IN THE CORNER!\n";
      exit(1);
   }
   
   string temp;
   int quantity;
   double price;

   fin >> temp;
   while (!fin.eof() || !fin.fail())
   {
      fin >> quantity;
      if (fin.fail())
      {
         cout << "ERROR: INTEGER OVERFLOW\n";
         exit(1);
      }
      
      fin >> price;
      if (fin.fail())
      {
         cout << "ERROR: DOUBLE OVERFLOW\n";
         exit(1);
      }
      
      if (temp == "BUY")
         buy(quantity, price);
      else if (temp == "SELL")
         sell(quantity, price);
      fin >> temp;
   }
   fin.close();
}

/***********************************************************************
 * CLASS SHARES ACCOUNT DEFAULT CONSTRUCTOR
 *      Description:    Creates an empty account--ready to start an
 *                      adventure of stocks and such!
 **********************************************************************/
Account::Account()
      : expenditures(0.00), earnings(0.00), totalProfit(0.00)
{
   // empty on purpose
}

int main(int argv, char* argc[])
{
   char *fileName;
   if (argv > 1)
      fileName = argc[1];
   else
   {
      string temp;
      cout << "Please specify a file: ";
      cin  >> temp;
      fileName = &temp[0];
   }
   
   Account myAccount;
   myAccount.readIn(fileName);
   myAccount.displaySummary();
   return 0;
}
