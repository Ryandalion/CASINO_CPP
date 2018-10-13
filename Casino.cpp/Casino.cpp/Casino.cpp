#include "Casino.hpp"


Casino::Casino()
{
	double totalBalance = 0;
	double sessionWinnings = 0;
	double totalUserWinnings = 0;
	double totalUserLosses = 0;
	double userWinnings = 0;
	double winningPerSession = 0;
	double loanAmount = 0;
	int numOfLoans = 0;
}


void Casino::getUserInfo(string name) // This function executes if user passes validation. It gathers the user's account balance and intializes it to their account.
{
	ifstream getData; // Input file stream object to gather user's data from .dat files
	vector<string>userData; // Vector to hold the user's information (string)

	getData.open("accountBalance.dat"); // Open the accountBalance.dat file to retrieve the user's balance

	if (!getData.eof()) // Keep reading the file until we encounter EOF - END OF FILE
	{
		std::string data; // Create a string variable to hold the data that will be extracted from the .dat file

		while (getData >> data) // We continue gathering data if more data exists in the .dat file
		{
			userData.push_back(data); // Add the extracted data to the userData vector
		}
	}
	getData.close(); // Close input file stream object

	string balance; 

	for (unsigned int i = 0; i < userData.size() - 1; i++) // Sift through data until we encounter user's name, then extract data one element after the index
	{
		if (name == userData[i]) // If the name is found within the vector
		{
			balance = userData[i + 1]; // Retrieve the balance that is one element after the user's name
		}
	}

	totalBalance = stod(balance); // Convert the balance from a string to a double using stod. Then we set totalBalance equal to the converted balance
}

void Casino::setUserBalance(double userBalance)
{
	totalBalance = totalBalance + userBalance;
}


void Casino::setUserWinnings(double winnings)
{
	totalUserWinnings = totalUserWinnings + winnings;
}

void Casino::setUserLosses(double losses)
{
	totalUserLosses = totalUserLosses + losses;
}

void Casino::setWinningsPerSession(double winningsForRound)
{
	this->sessionWinnings = winningsForRound;
}

void Casino::tipDealer() // Increase luck point by a bit
{
	int tipAmount = 0;
	int tipArray[] = { 5, 10, 50, 100 };
	Validate validate;

	cout << "How much would you like to tip the dealer?" << endl;
	cout << "1. $5" << endl;
	cout << "2. $10" << endl;
	cout << "3. $50" << endl;
	cout << "4. $100" << endl;
	tipAmount = validate.inputValidate(1, 4);

	cout << "You tipped the dealer $" << tipArray[tipAmount-1] << endl;

	int luckDraw = 0; // If the user tips an amount, execute the luckDraw function that will grant them extra luck if it produces the value 1.

	switch (tipAmount)
	{
		case 1:
		{
			luckDraw = rand() % 7 + 1;
			if (luckDraw == 1)
			{
				setUserLuck(4);
			}
			break;
		}

		case 2:
		{
			luckDraw = rand() % 5 + 1;
			if (luckDraw == 1)
			{
				setUserLuck(5);
			}
			break;
		}

		case 3:
		{
			luckDraw = rand() % 3 + 1;
			if (luckDraw == 1)
			{
				setUserLuck(3);
			}
			break;
		}
		
		case 4:
		{
			luckDraw = rand() % 2 + 1;
			if (luckDraw == 1)
			{
				setUserLuck(2);
			}
			break;
		}
	}
}

void Casino::setUserLuck(int luckAmount)
{
	luck = luck + luckAmount;
}

int Casino::getUserLuck()
{
	return luck;
}

void Casino::setUserMisfortune(int badluck)
{
	misfortune = misfortune + badluck;
}

int Casino::getUserMisfortune()
{
	return misfortune;
}

double Casino::getUserWinnings()
{
	return userWinnings;
}

double Casino::getWinningsForSession()
{
	return winningPerSession;
}

double Casino::getUserBalance()
{
	return totalBalance;
}

Casino::~Casino()
{

}