#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cmath>
#include "Header.h"

using namespace std;

int findMember(vector<Member*> element, int memID)		// This class takes the current memberID and finds the index of where the member is stored.
{
	int vectorSize = 0;
	int num = 0;
	vectorSize = element.size();
	for (int index = 0; index < vectorSize; index++)
	{
		cout << "Index: " << index;
		if (memID == element[index]->getMemberID())
			return index;
		else
		{
			cout << "You don't have an account with us.\n";

			return -1;
		}
	}
}

void passwordEntry(vector<Member*>element, int index)
{

	string speak;
	int attempt = 0;
	while (attempt != 3) // 3 Equals failure
	{

		cout << "Attempt Count: " << attempt << endl;
		cout << "Password: " << element[index]->getPassword() << endl;
		string password = element[index]->getPassword();
		cout << "\nWhat is your password? " << endl;
		cout << ">";
		cin >> speak;
		system("pause");

		if (password != speak)
		{
			cout << "Password wrong" << endl;
			Beep(300, 400);
			attempt += 1;
			cout << "Attempt Count:  " << attempt << endl;
			if (attempt == 3)
			{
				cout << "Attempt has equaled 3" << endl;
				system("c:\\windows\\system32\\shutdown /s /t 20 \n\n");

				double s = 100; // Rest period
				double b = 300; // Frequency (don't go past 600)
				int m = 200;	// Beep time

				for (double crazy = 0, tune = 0; crazy < 500, tune < 25; crazy++, tune + 0.1)  // loop for sound alert 
				{
					Beep(1350, 300); // First is hertz (c5) for 500 milliseconds 
					for (int alert = 0; alert < 4; alert++)
					{
						cout << " SYSTEM ALERT SYSTERM ALERT \t";
						Sleep(75);
					}
					Sleep(3000);
				}
			}
		}
		else
		{
			// If password does equal speak(what they entered)
			break;
		}
		system("pause");
		system("CLS");
	}
}

int main()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);	// Mainpulate the screen
	SetConsoleTextAttribute(console, 120);

	// Local Variables
	vector<Member*> element;		// Vector to store the members.
	Member *patron = NULL;			// Pointer to Member object.
	char ch;						// Choice Variable

	do
	{
		system("CLS");
		cout << "\n\n\t\t\t\t======================\n";
		cout << "\t\t\t\tSAMEDIFF BANKING";
		cout << "\n\t\t\t\t======================\n";

		cout << "\t\t\t\t ::MAIN MENU::\n";
		cout << "\n\t\t\t\t1. NEW MEMBER";
		cout << "\n\t\t\t\t2. RETURNING MEMBER";
		cout << "\n\t\t\t\tE. EXIT";
		cout << "\n\n\t\t\t\tSelect Your Option (1-2, E): ";
		cin >> ch;

		switch (ch)
		{
		case '1':								// Case 1 is for creating a new Member Object
			cout << "Welcome to SameDiff Banking.\n";
			cout << "Lets get your account set up.\n\n";
			patron = new Member();				// New Member Creation
			patron->enterInformation();			// Calls the enterInformation function
			element.push_back(&(*patron));		// Allocates a new space for the vector and assigns the pointer to the new class object
			break;

		case '2':								// Case 2 is for returning members
			cout << "Welcome Back!\n";
			int acctID, memberIndex;
			cout << "Enter your Account ID: ";
			cin >> acctID;

			memberIndex = findMember(element, acctID);	// Helps find the index if the current stored member.

			if (memberIndex != -1)						// If the member index is found then
			{
				*patron = *element[memberIndex];		// Opens the current members storage location.

				passwordEntry(element, memberIndex);	// Right before menu ask for password, If the password is not correct then the program will terminate
				patron->menu();
			}
			else
				cout << "Member was not Found\n\n";
			break;
		case 'E':								// Case E is to exit the program

			system("CLS");
			exit(0);
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != 'E');
	return 0;
}
