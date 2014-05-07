/**************************************************************************
* Program:
*    Assignment 11, Bank
*    Brother Ercanbrack, CS165
* Author:
*    Trevor Meyer
* Summary:
*    Bank program that shows some pretty awesome uses of virtual functions,
*    polymorphism, and inheritance.
* Note:
*    
****************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

/************************************************************
*******************DATA STRUCTURE STARTS HERE****************
*************************************************************/

/***************************************************************
 * BASE CLASS ACCOUNT
 *      Base class for all accounts in the bank. 
 ****************************************************************/
class Account
{
public:
   Account();
   int accountNumber;
   virtual void update();
   virtual bool trans(double amount);
   
   void setBalance(double newBalance);
   double getBalance();
   
   void setName(string newName);
   string getName();

   void setType(string newType);
   string getType();

   void setRate(double newRate);
   double getRate();
   friend ostream& operator << (ostream& outputStream,
                               const Account& account);
   
private:
   string name;
   double balance;
   string type;
   double rate;
};

/*****************************************************************
 * ACCOUNT CLASS DEFAULT CONSTRUCTOR:
 *      Sets all values to NULL since the base class is only used
 *      as a place holder for derivative classes.
 ****************************************************************/
Account::Account()
      : accountNumber(0), balance(0.00), name("NULL"), type("NULL"), rate(0.00)
{
}

/*****************************************************************
 * INSERTION OPERATOR:
 *      Allows the insertion operator to work with any account class.
 ****************************************************************/
ostream& operator << (ostream& outputStream, const Account& account)
{
   outputStream << account.name << " (" << account.type;
   outputStream << "):  ";
   outputStream << "balance is " << fixed << setprecision(2) << "$"
                << account.balance << endl;

   return outputStream;
}

/*****************************************************************
 * ACCOUNT MUTATOR:
 *      Set the rate.
 ****************************************************************/
void Account::setRate(double newRate)
{
   rate = newRate;
}

/*****************************************************************
 * ACCOUNT ACCESSOR
 *      Get the rate.
 ****************************************************************/
double Account::getRate()
{
   return rate;
}

/*****************************************************************
 * ACCOUNT NULL TRANSACTION:
 *      Filler virtual function never actually used.
 ****************************************************************/
bool Account::trans(double amount)
{
   return false;
}

/*****************************************************************
 * ACCOUNT NULL UPDATE:
 *      Filler virtual function never actually used.
 ****************************************************************/
void Account::update()
{
}

/*****************************************************************
 * ACCOUNT MUTATOR BALANCE:
 *      Sets the balance for any account.
 ****************************************************************/
void Account::setBalance(double newBalance)
{
   balance = newBalance;
}

/*****************************************************************
 * ACCOUNT ACCESSOR BALANCE:
 *      Get balance.
 ****************************************************************/
double Account::getBalance()
{
   return balance;
}

/*****************************************************************
 * ACCOUNT MUTATOR TYPE:
 *      Set type of account.
 ****************************************************************/
void Account::setType(string newType)
{
   type = newType;
}

/*****************************************************************
 * ACCOUNT ACCESSOR TYPE:
 *      Get type.
 ****************************************************************/
string Account::getType()
{
   return type;
}

/*****************************************************************
 * ACCOUNT MUTATOR NAME:
 *      Set name of account.
 ****************************************************************/
void Account::setName(string newName)
{
   name = newName;
}

/*****************************************************************
 * ACCOUNT ACCESSOR NAME:
 *      Get name.
 ****************************************************************/
string Account::getName()
{
   return name;
}

/*****************************************************************
 * DERIVATIVE CLASS SAVINGS:
 *      Redefines the virtual transaction and update functions.
 ****************************************************************/
class Savings : public Account
{
public:
   Savings();
   virtual bool trans(double amount);
   virtual void update();
};

/*****************************************************************
 * SAVINGS DEFAULT CONSTRUCTOR:
 *      Creates a fresh, blank savings account from the account
 *      base class.
 ****************************************************************/
Savings::Savings(/*parameters intentionally left blank*/)
      : Account()
{
   setType("savings");
}
      
/*****************************************************************
 * SAVINGS TRANSACTION METHOD:
 *      Defines how savings account transations should be used.
 *      Simply allows a transaction unless the account will be
 *      overdrawn.
 * OUTPUT: overdrawn or not - true, false
 ****************************************************************/
bool Savings::trans(double amount)
{
   bool overdrawn = false;
   if (getBalance() + amount > 0)
   {
      setBalance(getBalance() + amount);
      cout << getName() << " (" << getType() << "):  "
        << setprecision(2) << fixed
        << "$" << amount << " applied to account\n";
   }
   else
      overdrawn = true;

   return overdrawn;
}

/*****************************************************************
 * SAVINGS UPDATE METHOD:
 *      Defines how savings accounts should be update with the
 *      correct interest and math.
 ****************************************************************/
void Savings::update()
{
   double amount;

   amount = getBalance() * getRate();

   setBalance(getBalance() * (1 + getRate()));

   cout << getName() << " (" << getType() << "):  "
        << setprecision(2) << fixed
        << "$" << amount << " applied to account\n";
}

/*****************************************************************
 * CHECKING DERIVATIVE CLASS:
 *      Redefines the virtual functions and adds a check counter
 *      to count how many checks have been used before the last
 *      update period.
 ****************************************************************/
class Checking : public Account
{
public:
   Checking();
   virtual bool trans(double amount);
   virtual void update();

private:
   int checkCount;
};

/*****************************************************************
 * CHECKING DEFAULT CONSTRUCTOR:
 *      Creates a blank checking account.
 ****************************************************************/
Checking::Checking(/*intentionally blank*/)
      : Account(), checkCount(0)
{
   setType("checking");
}

/*****************************************************************
 * CHECKING TRANSACTION METHOD:
 *      Checking account's version of how transactions should be
 *      done. Varies from savings and loans in that transaction
 *      rates must be accounted for.
 * OUTPUT: overdrawn or not - true, false
 ****************************************************************/
bool Checking::trans(double amount)
{
   bool overdrawn = false;

   if (amount < 0)
   {
      checkCount++;
      if ((getBalance() + amount - getRate()) > 0)
      {
         setBalance(getBalance() + amount);
         cout << getName() << " (" << getType() << "):  "
              << setprecision(2) << fixed
              << "$" << amount << " applied to account\n";
      }
      else
      {
         setBalance(getBalance() - 25.00);
         overdrawn = true;
         cout << getName() << " (" << getType() << "):  "
              << setprecision(2) << fixed
              << "$" << amount << " rejected (insufficient funds)\n";
         cout << getName() << " (" << getType() << "):  "
              << "$-25.00 applied to account\n";
      }
   }
   else
   {
      setBalance(getBalance() + amount);
      cout << getName() << " (" << getType() << "):  "
           << setprecision(2) << fixed
           << "$" << amount << " applied to account\n";
   }
   
   return overdrawn;
}

/*****************************************************************
 * CHECKING UPDATE METHOD:
 *      Redefines how checking accounts should be updated with the
 *      proper checking fees and rates.
 ****************************************************************/
void Checking::update()
{
   double amount = checkCount * getRate();
   
   setBalance(getBalance() - (checkCount * getRate()));
   checkCount = 0;

   cout << getName() << " (" << getType() << "):  "
        << setprecision(2) << fixed
        << "$-" << amount << " applied to account\n";
}

/*****************************************************************
 * DERIVATIVE CLASS LOAN:
 *      Redefines the transaction and update methods for a loan.
 ****************************************************************/
class Loan : public Account
{
public:
   Loan();
   virtual bool trans(double amount);
   virtual void update();
};

/*****************************************************************
 * LOAN BASE CONSTRUCTOR:
 *      Generates an empty loan account.
 ****************************************************************/
Loan::Loan(/*intentionally blank*/)
      : Account()
{
   setType("loan");
}

/*****************************************************************
 * LOAN TRANSACTION METHOD:
 *      Redefines how loans should be treated when transfering
 *      funds. Doesn't allow for the possibility of over-drawing.
 ****************************************************************/
bool Loan::trans(double amount)
{
   bool overdrawn = false;
   if ((getBalance() + amount) > 0)
   {
      overdrawn = true;
      setBalance(getBalance() + amount);
      cout << getName() << " (" << getType() << "):  "
           << setprecision(2) << fixed
           << "$" << amount << " applied to account\n";
     
   }
   else
   {
      setBalance(getBalance() + amount);
      cout << getName() << " (" << getType() << "):  "
           << setprecision(2) << fixed
           << "$" << amount << " applied to account\n";
   }

   return overdrawn;
}

/*****************************************************************
 * LOAN UPDATE METHOD:
 *      Redefines how a loan should be updated including appropriate
 *      rates and fees.
 ****************************************************************/
void Loan::update()
{
   double amount = getBalance() * getRate();
   setBalance(getBalance() * (1 + getRate()));
   cout << getName() << " (" << getType() << "):  "
        << setprecision(2) << fixed
        << "$" << amount << " applied to account\n";

}

/************************************************************
*******************DATA STRUCTURE ENDS HERE******************
*************************************************************/

/*****************************************************************
 * CREATE ACCOUNT:
 *      Determines what kind of account to generate and allocates
 *      the requested parameters accordingly into new accounts.
 ****************************************************************/
void createAccount(Account *pAccount[], string input, int accountNum)
{
   // create account
   if (input[0] == 's')
      pAccount[accountNum] = new Savings;
   else if (input[0] == 'c')
      pAccount[accountNum] = new Checking;
   else 
      pAccount[accountNum] = new Loan;

   pAccount[accountNum]->accountNumber = accountNum;
   cout << "new account...\n";

   char temp[20];
   int y;
   int x;

   // the following loops do not require constructor overloading.

   for (x = 4, y = 0; input[x] != ' '; x++, y++)
      temp[y] = input[x];
   temp[y] = '\0';

   // name account
   pAccount[accountNum]->setName(temp);
   
   for (x++, y = 0; input[x] != ' '; x++, y++)
      temp[y] = input[x];
   temp[y] = '\0';

   // set account balance
   pAccount[accountNum]->setBalance(atof(temp));

   for (x++, y = 0; input[x]; x++, y++)
      temp[y] = input[x];
   temp[y] = '\0';

   // set account rates
   pAccount[accountNum]->setRate(atof(temp));

   // loan negative exception handling
   if (pAccount[accountNum]->getType() == "loan")
      pAccount[accountNum]->setBalance( -
                                        (pAccount[accountNum]->getBalance()));
   
   return;
}

/*****************************************************************
 * TRANSACTION:
 *      Not to be confused with the class method transaction.
 *      Passes values by reference to required account object.
 * INPUT:       account number to send funds
 *              account pointer
 *              amount of funds to transfer
 ****************************************************************/
void transaction(Account *pAccount[], string input, int accountNum)
{
   char temp[20];
   int y;
   int x;

   cout << "transaction...\n";
   
   for (x = 4, y = 0; input[x]; x++, y++)
      temp[y] = input[x];
   temp[y] = '\0';

   pAccount[accountNum]->trans(atof(temp));

   return;
}

/*****************************************************************
 * MAIN:
 *      Main driver function for bank software. Accesses required
 *      files and checks for errors.
 ****************************************************************/
int main()
{
   bool loop = true;
   
   ifstream fin;

   fin.open("/home/ercanbracks/cs165-examples/assign11-bank/bank.txt");

   if (fin.fail())
   {
      cout << "Input Fail\n\n";
      loop = false;
   }

   Account *pAccount[100] = {new Account};
   
   for (int p = 0; p < 99; p++)
      pAccount[p] = new Account;

   string input;

   int x = 0;
   int accountNum;

   // main loop function. Searches for the end of file.
   while (!fin.eof())
   {
      getline(fin, input);

      // char to int conversion, ascii style
      accountNum = input[2] - '0';

      /**********************************************
       * Determines how each line in the input file
       * should be handled. Is the main subroutine
       * for the whole program.
       *********************************************/
      if (pAccount[accountNum]->getName() == "NULL")
      {
         createAccount(pAccount, input, accountNum);
         cout << *pAccount[accountNum] << endl;
      }
      else if (input[0] == 't')
      {
         transaction(pAccount, input, accountNum);
         cout << *pAccount[accountNum] << endl;
      }
      else if (input[0] == 'u')
      {
         cout << "update...\n";
         pAccount[accountNum]->update();
         cout << *pAccount[accountNum] << endl;
      }
   }

   delete *pAccount;

   return 0;
}
