#include "Account.hpp"

Account::Account()
{
	name = " ";
	password = " ";
	balance = 0;
	accountFlag = false;
	passwordFlag = false;
}

void Account::setName(string name)
{
	this->name = name;
}

void Account::setPassword(string password)
{
	this->password = password;
}

void Account::initialBalance(double balance)
{
	this->balance = balance;
}

void Account::verifyUser(string name, string password, int option, bool &verified)
{
	if (option == 1) // Check for user ID and password
	{
		verifyUser(name);
		checkPassword(password);
		if (accountFlag && passwordFlag)
		{
			cout << "Login Successful" << endl;
			cout << "Welcome back " << name << endl;
			verified = true;
		}

		else
		{
			cout << "Login Unsuccessful" << endl;
			cout << "Please try again" << endl;
		}
	}

	if (option == 2) // Create new user ID
	{
		bool tryAgain = false; // Bool to allow while loop to continue until user enters a username that is not taken
		while (tryAgain != true)
		{
			if (checkUser(name)) // Username does not exist
			{
			
				tryAgain = true;
				if (createAccount(name, password))
				{
					double deposit = 0;

					cout << "Account creation successful" << endl;
					cout << "In order to proceed forward you must make an initial deposit into your account" << endl;
					cout << "Please enter the deposit amount (minimum $100): ";
					cin >> deposit;
					while (deposit < 100)
					{
						cout << "Deposit must be at least $100" << endl;
						cin >> deposit;
					}
					if (loadDeposit(deposit))
					{
						initialBalance(deposit);
						cout << "Here are your account details" << endl;
						cout << "Account Username: " << name << endl;
						cout << "Account Password: " << password << endl;
						cout << "Account Balance: " << balance << endl;
						cout << endl;
						verified = false;
					}
				}
			}

			else
			{
				cout << "Sorry user name is taken. Please enter a different username: ";
				cin >> name;
				cout << "Please re-enter your password: ";
				cin >> password;
				cout << endl;
				tryAgain = false;

			}
		}
	}
}


bool Account::checkUser(string name)
{
	ifstream checkUser;
	string temp;
	string line;
	bool userNameExists = true;

	checkUser.open("userName.dat");

	if (checkUser.is_open())
	{
		while (getline(checkUser, temp))
		{
			line.append(temp);

			if (line.find(name) != std::string::npos)
			{
				userNameExists = false;
			}
		}
	}
	checkUser.close();

	return userNameExists;
}

bool Account::createAccount(string name, string password)
{

	ofstream userNameFile; // Used to create .dat file holding all user names
	ofstream passWordFile; // Used to create .dat file holding all user password

	userNameFile.open("userName.dat", fstream::app | std::ios_base::out); // Create/open .dat file that holds usernames
	passWordFile.open("passWord.dat", fstream::app | std::ios_base::out); // Create/open .dat file that holds passwords

	userNameFile << name << endl;	// Input username into userName.dat
	passWordFile << password << endl; // Input password into passDord.dat

	userNameFile.close(); // Close userNameFile object
	passWordFile.close(); // Close passWordFile object

	return true;
}

bool Account::loadDeposit(double deposit)
{
	ofstream initialDeposit;

	initialDeposit.open("accountBalance.dat");

	initialDeposit << deposit;

	initialDeposit.close();

	return true;
}

void Account::checkPassword(string password)
{
	ifstream checkPassword;
	string temp;
	string line;


	checkPassword.open("passWord.dat");

	if (checkPassword.is_open())
	{
		while (getline(checkPassword, temp))
		{
			line.append(temp);

			if (line.find(password) != std::string::npos)
			{
				passwordFlag = true;
			}
		}
	}
	checkPassword.close();
}

void Account::verifyUser(string name)
{
	ifstream checkUser;
	string temp;
	string line;

	checkUser.open("userName.dat");

	if (checkUser.is_open())
	{
		while (getline(checkUser, temp))
		{
			line.append(temp);

			if (line.find(name) != std::string::npos)
			{
				accountFlag = true;
			}
		}
	}
	checkUser.close();
}

Account::~Account()
{

}