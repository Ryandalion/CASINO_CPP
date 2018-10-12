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