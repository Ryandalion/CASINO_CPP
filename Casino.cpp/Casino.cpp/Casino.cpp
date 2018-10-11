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

void Casino::getUserInfo() // Pull user data from .dat file and sync to all necessary member components => Execute and sync after user successful login
{

}

void Casino::setUserBalance(double balance)
{
	totalBalance = totalBalance + balance;
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


void Casino::borrowMoney()
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
	cout << "How much money would you like to borrow from the Casino?" << endl;
	if (numOfLoans < 1)
	{
		option = validate.inputValidate(1, 4);

			switch (option)
			{
			case 1:
			{
				cout << "You have chosen to borrow $500. The amount has been transferred to your account." << endl;
				setUserLoanAmount(500);
				setUserBalance(500);
				numOfLoans++;
				break;
			}

			case 2:
			{
				cout << "You have chosen to borrow $1000. The amount has been transferred to your account." << endl;
				setUserLoanAmount(1000);
				setUserBalance(1000);
				numOfLoans++;
				break;
			}

			case 3:
			{
				cout << "You have chosen to borrow $2500. The amount has been transferred to your account." << endl;
				setUserLoanAmount(2500);
				setUserBalance(2500);
				numOfLoans++;
				break;
			}

			case 4:
			{
				cout << "You have chosen to borrow $5000. The amount has been transferred to your account." << endl;
				setUserLoanAmount(5000);
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

void Casino::setUserLoanAmount(int number)
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

}

void Casino::getUserLoanAmount()
{
	if (loanAmount > 0)
	{
		int option = 0;
		Validate validate;
		cout << "You have a oustanding loan of $" << loanAmount << endl;
		cout << "1. Pay Loan" << endl;
		cout << "2. Exit" << endl;
		option = validate.inputValidate(1, 2);

		if (option == 1)
		{
			if (totalBalance >= loanAmount)
			{
				totalBalance = totalBalance - loanAmount;
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

double Casino::getUserBalance()
{
	return totalBalance;
}

double Casino::getUserWinnings()
{
	return userWinnings;
}

double Casino::getWinningsForSession()
{
	return winningPerSession;
}

void Casino::saveUserData()
{

}

Casino::~Casino()
{

}