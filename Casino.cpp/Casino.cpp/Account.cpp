#include "Account.hpp"


Account::Account()
{
	name = " ";
	password = " ";
	balance = 0;
	accountFlag = false;
	passwordFlag = false;
}

void Account::setName(string username)
{
	this->name = username;
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

	initialDeposit.open("accountBalance.dat", fstream::app | std::ios_base::out);

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


//--------------------------------------------------------CASINO LOAN FUNCTIONS--------------------------------------------------------------

void Account::borrowMoney(Account *user)
{
	int option = 0;
	Validate validate;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "=========  CASINO LOAN  ========|" << endl;
	cout << "|    BORROW      |    REPAY     |" << endl;
	cout << "================================|" << endl;
	cout << "|1.   $500       |    $600      |" << endl;
	cout << "|2.   $1000      |    $1100     |" << endl;
	cout << "|3.   $2500      |    $2550     |" << endl;
	cout << "|4.   $5000      |    $5050     |" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << endl;
	cout << "Please enter the number that corresponds with the amount you wish to borrow" << endl;
	if (numOfLoans < 1) // Validate that user does not have any active loans
	{
		option = validate.inputValidate(1, 4);

		switch (option)
		{
		case 1:
		{
			cout << "You have chosen to borrow $500. The amount has been transferred to your account." << endl;
			setUserLoanAmount(500, user);
			setUserBalance(500);
			numOfLoans++;
			break;
		}

		case 2:
		{
			cout << "You have chosen to borrow $1000. The amount has been transferred to your account." << endl;
			setUserLoanAmount(1000, user);
			setUserBalance(1000);
			numOfLoans++;
			break;
		}

		case 3:
		{
			cout << "You have chosen to borrow $2500. The amount has been transferred to your account." << endl;
			setUserLoanAmount(2500, user);
			setUserBalance(2500);
			numOfLoans++;
			break;
		}

		case 4:
		{
			cout << "You have chosen to borrow $5000. The amount has been transferred to your account." << endl;
			setUserLoanAmount(5000, user);
			setUserBalance(5000);
			numOfLoans++;
			break;
		}
		}
	}

	else
	{
		cout << "You can only have one loan activet at a time" << endl;
	}

}


void Account::setUserLoanAmount(int number, Account *user) // Set the user loan amount
{
	if (number == 500)
	{
		loanAmount = 600;
	}

	else if (number == 1000)
	{
		loanAmount = 1100;
	}

	else if (number == 2500)
	{
		loanAmount = 2550;
	}

	else if (number == 5000)
	{
		loanAmount = 5050;
	}

	// Create a write object to record the user's name and the loan amount into a .dat file
	ofstream userLoanFile;

	userLoanFile.open("userLoanBalance.dat", fstream::app | std::ios_base::out);
	userLoanFile << user->name << endl;
	userLoanFile << loanAmount << endl;

	userLoanFile.close();
}

void Account::getUserLoanAmount(Account *user)
{
	string name = user->name;
	string loanAmount;
	bool empty = false;

	//-------------------------------------------------------------------
	vector <string> loanData;
	ifstream checkLoan;

	// Use object read file to load all loan data into vector
	checkLoan.open("userLoanBalance.dat");

	if (checkLoan.peek() == ifstream::traits_type::eof()) // If loan data file is empty make it false
	{
		empty = true;
	}

	else if (!checkLoan.eof()) // Write data into vector until the end of the .dat file
	{
		string loan;

		while (checkLoan >> loan)
		{
			loanData.push_back(loan);
		}
	}

	checkLoan.close();
	//-----------------------------------------------------------------------

	int i = 0;

	while(i < loanData.size()) // Sift through vector and find user's name and retrieve their loan amount
	{
		if (name == loanData[i])
		{
			loanAmount = loanData[i + 1];
			break;
		}
		i++;
	}

	double loanBalance = stod(loanAmount); // Convert the variable loanAmount(string) into a double 

	//-------------------------------------------------------------------------
	if (loanBalance > 0 && empty != true) // If loanBalance is greater than zero and the file is not empty execute loan repayment function
	{
		double userBalance = user->getUserBalance();
		int option = 0;
		Validate validate;
	
		cout << "You have a oustanding loan of $" << loanBalance << endl;
		cout << "1. Pay Loan" << endl;
		cout << "2. Exit" << endl;
		option = validate.inputValidate(1, 2);

		if (option == 1) // User chooses to pay off loan
		{
			if (userBalance >= loanBalance) // Check user balance and see if they have enough money to pay off loan
			{
				userBalance = userBalance - loanBalance; // Set the new user balance equal to the user's balance minus the loan balance
				user->setUserBalance(userBalance); // Set the user's new balance

				for (unsigned int i = 0; i < loanData.size(); i++) // Loop through vector that hold's user loan amounts. If user's name is found we will erase the name and the element after the name (loan balance) from the vector.
				{
					if (name == loanData[i])
					{
						loanData.erase(loanData.begin() + i); // Erase name
						loanData.erase(loanData.begin() + i + 1); // Erase loan balance
					}
				}

				//------------------------------------------------------------------------------
				// Write all vector data into userLoan data
				ofstream updateLoanData;

				updateLoanData.open("userLoanBalance.dat");

				while (updateLoanData.is_open())
				{
					for (unsigned int i = 0; i < loanData.size() - 1; i++)
					{
						updateLoanData << name << endl;
						updateLoanData << loanData[i] << endl;
					}

					updateLoanData.close();
				}
				//--------------------------------------------------------------------------------
			}
			else
			{
				cout << "You do not have enough money to pay your loan." << endl;
			}
		}

	}

	else
	{
		cout << "You have no outstanding loans" << endl;
	}
}

Account::~Account()
{

}

string Account::getName()
{
	return name;
}