#include <iostream>
#include <string>
#include <limits>


#include "Blackjack.hpp"
#include "Poker.hpp"
#include "Slots.hpp"
#include "Account.hpp"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::numeric_limits;
using std::streamsize;

int main()
{
	int choice = 0; // User intial choice
	string username;
	string password;

	Account *user;
	Account userinfo;
	user = &userinfo;

	bool verified = false;
	bool running = false;
	
	while (running != true)
	{
		cout << "Welcome to C++ Casino" << endl; // Greeting message
		cout << "1. Member Login" << endl;				 // User login
		cout << "2. Create New Account" << endl; // Create new user account
		cin >> choice;
		while (true)
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Please select a valid option from the menu: " << endl;
				cin >> choice;
			}
			if (!cin.fail() && (choice == 1 || choice == 2))
				break;
			else
			{
				cout << "Please select a valid option from the menu:\n";
				cin >> choice;
			}
		}

		if (choice == 1)
		{
			cout << endl;
			cout << "MEMBER LOGIN" << endl;
			cout << endl;
			cout << "Username: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
			user->verifyUser(username, password, 1, verified); // Send user info to be validated via verifyUser function located in Account.cpp
		}

		else if (choice == 2)
		{
			cout << endl;
			cout << "CREATE NEW ACCOUNT" << endl;
			cout << endl;
			cout << "Enter a username: ";
			cin >> username;
			cout << "Enter a password: ";
			cin >> password;
			user->verifyUser(username, password, 2, verified);
		}

		if (verified)
		{
			cout << "Welcome back to the Casino " << user << endl;
			running = true;
		}
	}
	delete user;
	system("pause");

	return 0;
}
