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

string Account::getName()
{
	return name;
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
			getUserInfo(name);
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
		string userName;
		bool tryAgain = false; // Bool to allow while loop to continue until user enters a username that is not taken
		while (tryAgain != true)
		{
			if (checkUser(name)) // Username does not exist
			{
			
				tryAgain = true;
				if (createAccount(name, password))
				{
					double deposit;
					userName = name;
					cout << "Account creation successful" << endl;
					cout << "In order to proceed forward you must make an initial deposit into your account" << endl;
					cout << "Please enter the deposit amount (minimum $100): ";
					cin >> deposit;
					while (deposit < 100)
					{
						cout << "Deposit must be at least $100" << endl;
						cin >> deposit;
					}
					if (loadDeposit(deposit, userName))
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
	passWordFile << password << endl << endl; // Input password into passDord.dat

	userNameFile.close(); // Close userNameFile object
	passWordFile.close(); // Close passWordFile object

	return true;
}

bool Account::loadDeposit(double deposit, string name) // Load the user's deposit into the accountBalance file
{
	string depositAmount; // Deposit amount is converted to a string so we can store in .dat file and read easily via a string vector
	double userDeposit = deposit;	// Convert the deposit (double) into a string so it can be stored into the .dat file
	std::stringstream ss; // Convert the deposit amount (double) to a string
	ss << userDeposit << endl; 
	depositAmount = ss.str(); // Set variable depositAmount (string) equal to the converted double

	ofstream initialDeposit; // Create output file stream object to write to the accountBalance file

	initialDeposit.open("accountBalance.dat", fstream::app | std::ios_base::out); // Open the accountBalance.dat to store the user's name and deposit information

	initialDeposit << name << endl; // Store user's name then start a new line for organization and search purposes
	initialDeposit << depositAmount << endl; // Store user's deposit amount

	initialDeposit.close(); // Close the output file stream object

	return true; // Return true to confirm to caller that deposit was successful
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
	bool empty = true;
	bool loanStatus = false;
	string loanQty;
	double loanNum = 0;

	ifstream loanData;
	vector<string> loanInformation;
	loanData.open("userLoanBalance.dat");
	
	if (loanData.peek() == ifstream::traits_type::eof()) // We check to see if loan data file is empty and set the bool to false
	{
		empty = false;
	}

	if (empty)
	{
		while (!loanData.eof()) // *File is not empty so we execute this statement* => Extract all data and load it into a string vector
		{
			string loan;

			while (loanData >> loan) // Extract and place each individual string loan data into a string vector  
			{
				loanInformation.push_back(loan);
			}
			loanData.close(); // Close the input file stream object
		}

		int k = 0;
		bool userExists = false;

		for (unsigned int k = 0; k < loanInformation.size(); k++)
		{
			if (name == loanInformation[k])
			{
				userExists = true;
				break;
			}
		}

		if (userExists != false)
		{
			int i = 0;
			while (i < loanInformation.size()) // Sift through string vector until we find the user's name
			{
				if (name == loanInformation[i])
				{
					loanQty = loanInformation[i + 2];
					loanStatus = true;
					break; // Break out of function since we found the user and their loan information
				}
				i++; // If the name does not match the element found at index i we increment i and continue searching until we reach the end of the .dat file
			}
		}
	}
	

	if (loanNum < 1 && loanStatus == false) // Validate that user does not have any active loans
	{

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

	else if(loanNum >= 1)
	{
		cout << "You can only have one active loan at a time" << endl;
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
	string numOfLoans = "1";

	userLoanFile.open("userLoanBalance.dat", fstream::app | std::ios_base::out);
	userLoanFile << user->name << endl;
	userLoanFile << loanAmount << endl;
	userLoanFile << numOfLoans << endl;
	userLoanFile << endl;

	userLoanFile.close();
}

bool Account::getUserLoanAmount(Account *user) // This function retrieves the user's loan amount
{
	string name = user->name;
	string loanAmount;
	bool empty = false;
	bool loanStatus = false;

	vector <string> loanData; // Create a string vector to hold the loan data
	ifstream checkLoan; // Create an input file stream to load data from .dat file into the vector of strings

	checkLoan.open("userLoanBalance.dat");

	if (checkLoan.peek() == ifstream::traits_type::eof()) // We check to see if loan data file is empty and set the bool to false
	{
		empty = true;
	}

	else if (!checkLoan.eof()) // *File is not empty so we execute this statement* => Extract all data and load it into a string vector
	{
		string loan;

		while (checkLoan >> loan) // Extract and place each individual string loan data into a string vector  
		{
			loanData.push_back(loan);
		}
		checkLoan.close(); // Close the input file stream object
	}

	int i = 0; // Intialize i to zero to prepare it for the while loop

	while (i < loanData.size()) // Sift through string vector until we find the user's name
	{
		if (name == loanData[i]) // Once we find the user's name we extract the data from the element after the user's name which is the loan amount
		{
			loanAmount = loanData[i + 1]; // Set loanAmount (string) equal to the value found at the index + 1;
			loanStatus = true;
			
			break; // Break out of function since we found the user and their loan information
		}
		i++; // If the name does not match the element found at index i we increment i and continue searching until we reach the end of the .dat file
	}

	if (loanStatus == true)
	{
		double loanBalance = stod(loanAmount); // Convert the loanAmount (string) to a double via stod so we can preare it to be used with functions that accept only double

		if (loanBalance > 0 && empty != true) // If the user has a loan balance and the file is not empty then we execute this statement
		{
			double userBalance = user->getUserBalance();
			double loanAmount = 0;
			int option = 0;
			Validate validate; // Create a Validate object to verify user's inputs

			cout << "You have an oustanding loan of $" << loanBalance << endl; // Display the outstanding loan balance to the user and give them the option to pay off the loan or exit from the menu
			cout << "1. Pay Loan" << endl;
			cout << "2. Exit" << endl;
			option = validate.inputValidate(1, 2); // Validate user's input

			if (option == 1) // If user chooses option 1 then we execute loan repayment statement
			{
				if (userBalance >= loanBalance) // First we check the user's balance and see if they have enough money in their account to pay off the loan
				{

					loanAmount = (loanBalance * -1); // Set the user balance equal to the user's balance minus the loan balance because of loan payment
					user->setUserBalance(loanAmount); // Set the user's new balance via a call to the parent class

					for (unsigned int i = 0; i < loanData.size(); i++)
					{
						cout << loanData[i] << endl;
					}
					for (unsigned int i = 0; i < loanData.size() - 1; i++) // Loop through vector that hold's user loan amounts. If user's name is found we will erase the name and the element after the name (loan balance) from the vector.
					{
						
						if (name == loanData[i]) // We find the user's name in the vector and erase their name and balance
						{
							int index = 0;
							do
							{
								loanData.erase(loanData.begin() + i);
								index++;
							} while (index < 3);
							break;
						}
					}

					for (unsigned int i = 0; i < loanData.size(); i++)
					{
						cout << loanData[i] << endl;
					}

					ofstream updateLoanData; // Create an output stream object to update the loan data

					remove("userLoanBalance.dat");
					updateLoanData.open("userLoanBalance.dat");

					while (updateLoanData.is_open())
					{
						for (unsigned int i = 0; i < loanData.size(); i++)
						{
							updateLoanData << loanData[i] << endl;

						}

						updateLoanData.close();
					}
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

		return true;
	}

	else
		return false;
}

//------------------------------------------------------------------SAVE USER DATA FUNCTIONS---------------------------------------------------------------------------------

void Account::saveUserData(Account *user) // This function is excuted prior to program termination via user's selection to exit program
{
	
	double balancenum; // This double variable will hold the user's current balance
	string accountBalance; // This string variable will hold the converted value of balancenum (double ---> string)
	balancenum = user->getUserBalance(); // Set balancenum equal to the user's current total balance
	string userName = user->name; // This string variable will hold the user's name

	vector <string> userData; // Create a vector of string to hold ALL user's data that will be read from the accountBalance.dat

	ifstream saveUser; // Input file stream object to read the accountBalance.dat file
	saveUser.open("accountBalance.dat");

	std::stringstream ss; // Stringstream object to convert the balance (double) to a string
	ss << balancenum << endl; // Input the double that hold's the user's total balance
	accountBalance = ss.str(); // Convert the total balance to a string and set it equal to the string variable userName
	string str; // Create a string variable to hold the extracted data elements from the .dat file

	while (!saveUser.eof()) // Loop until we reach the end of the accountBalance.dat file
	{
		{
			saveUser >> str; // Move extracted data from accountBalance.dat file to string variable
			userData.push_back(str); // Add the string variable to the string vector
		}
	}
	saveUser.close(); // Close input file stream

	for (unsigned int i = 0; i < userData.size() - 1; i++) // Sift through the vector and find the user's name and update the balance which is found one element after the user's name
	{
		if (userName == userData[i]) // If we find the name then we update the account balance of the user
		{
			userData[i + 1] = accountBalance;
			cout << endl;
		}
	}

	ofstream newData; // Create an output filestream object to write the updated data into the .dat file

	remove("accountBalance.dat"); // Remove the old accountBalance.dat file 
	
	newData.open("accountBalance.dat"); // Create the new accountBalance.dat file and update it with the new information

	while (newData.is_open()) // Keep looping until the ouput file stream object is closed
	{
		for (unsigned int i = 0; i < userData.size() - 1; i++) // Transfer user name and user balance data from the vector into the new updated accountBalance.dat file
		{
			newData << userData[i] << endl;
			
		}

		newData.close(); // Close the output file once we reach the vector's max size and exit the while loop
	}
}

Account::~Account()
{

}

