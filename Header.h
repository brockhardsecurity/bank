#pragma once
#include <string>
#include <ctime>
#include <iostream>

using namespace std;

class BankAccounts
{
protected:
	string accountType;
	double balance;
	int accountNum;

public:

	// Function templates placed in the base class so that derived will have these 
	template<class D>
	void friend deposit(D* obj);
	template<class W>
	void friend withdraw(W* obj);
	template<class M>
	void friend monthlyInterest(M* obj);

	void accountInqury();

	void setAccount(string accT)
	{
		accountType = accT;
	}
	double getBalance()
	{
		return balance;
	}
	string getAccount()
	{
		return accountType;
	}
};

class CD : public BankAccounts
{
private:
	int cdType;						// Stores the duration/time of certificate.
	int monthCreated;				// This stores the month that the certificate was created.
	int withdrawMonth = 0;			// Month that money was withdrawn 
	double cdInterest = 0;			// Holds the interst for the cd, will be different based on cdType
	double cdPenalty = 0;			// Holds penalty for cd, will be different based on cdType
	double endingBal = 0;			// Stores the amount that the member made off the CD
	int terminationMonth = 0;		// Holds the month that the contract ends.
public:
	CD();
	void withdrawCD();
	void maturityPenalty();
	void cdInquiry();

};

class MMDA : public BankAccounts
{
private:
	double mmdaInterest = 0.0125;
	double nInterest;  // This is what will actually be added to balance 
public:
	MMDA()
	{
		cout << "How much do you want to deposit right now: $";
		cin >> balance;
	}


	void mmdaWithdraw();  // Tell user if they are going to have a withdraw penalty
						  // Similar to savings account, if they do not have minimum amount of money in account
};

class Savings : public BankAccounts
{
private: double savingsInterest = 0.0105;
		 double sInterest; // this is what will actually be added to balance 
public:
	Savings()
	{
		cout << "How much do you want to deposit right now: $";
		cin >> balance;
	}

	void savingsWithdraw();
};

class Checking : public BankAccounts
{
private: double checkingInterest = 0.0002;
		 double cInterest; // This is what will actually be added to balance 
public:
	Checking()
	{
		cout << "How much do you want to deposit right now: $";
		cin >> balance;
	}

};

////////////////////The classes pertaining to Member information//////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

class Person
{
protected:
	string fName;
	string lName;
	char mInitial;
	string address;
	string phone;
	string email;
	string password;
public:

	string getPassword()
	{
		return password;
	};
};

class Member : public Person
{
private:
	int memberID;
	int bankID = 1001002;
	int numOfAccount;
	CD *certificate;
	MMDA *market;
	Savings *savings;
	Checking *checking;



public:
	Member() {
		certificate = NULL;
		market = NULL;
		savings = NULL;
		checking = NULL;
	}
	~Member()
	{
		delete[] certificate;
		certificate = NULL;
	}
	int getBankID() { return bankID; }
	int getMemberID() { return memberID; }

	void enterInformation();
	void createAccounts(int);
	void menu();
	void accountsCreated();
};

/////////////Function Templates Placed in the Header instead of the Implementation/////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

template <class W>
void withdraw(W* obj)		// Function Template for the Withdraw action
{
	double takeOut;
	cout << "Current Balance: $" << obj->balance;
	cout << "\nHow much do you want to withdraw from your balance? |> $";
	cin >> takeOut;
	while (obj->balance - takeOut < 0)
	{
		cout << "Sorry you do not have enough money." << endl;
		cin.ignore();
		cin.get();
		cout << "Current Balance: $" << obj->balance;
		cout << "How much do you want to withdraw from your balance? |> $";
		cin >> takeOut;
	}
	obj->balance = obj->balance - takeOut;

}

template <class D>
void deposit(D* obj)			// Function Template for the Deposit action
{
	double add;
	cout << "Current Balance: $" << obj->getBalance();
	cout << "\nHow much do you want to deposit into your account? |> $";
	cin >> add;
	while (add < 0)		// In case they try to deposit negative numbers 
	{
		cout << "Sorry, no negative numbers. " << endl;
		cin.ignore();
		cin.get();
		cout << "Current Balance: $" << obj->balance;
		cout << "How much do you want to deposit into your account? |> $";
		cin >> add;
	}
	obj->balance = obj->balance + add;


}

template <class M>			/// Find a way to implement this
void monthlyInterest(M* obj)		// Function Template for calculation the Monthly Interest for one month
{
	if (obj->accountType == "Savings")
	{
		cout << "Savings account has a monthly interest of 1.05%. " << endl;
		obj->balance = obj->savingsInterest = obj->sInterest;

		cout << "Your account's interest for this month is $" >> obj->sInterest;
		obj->balance = obj->balance + obj->sInterest;
		cin.get();

		cout << "Balance has increased from $" >> obj->balance - obj->sInterest >> endl;
		cout << " to $" >> obj->balance;
	}

	else if (obj->accountType == "Checking")
	{
		cout << "Checkings account has a monthly interest of 0.02%. " << endl;
		obj->balance = obj->checkingInterest = obj->cInterest;

		cout << "Your account's interest for this month is $" >> obj->cInterest;
		obj->balance = obj->balance + obj->cInterest;
		cin.get();

		cout << "Balance has increased from $" >> obj->balance - obj->cInterest >> endl;
		cout << " to $" >> obj->balance;


	}
}