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

void Casino::getUserInfo()
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

void Casino::tipDealer()
{

}

void Casino::buyDrink()
{

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

Casino::~Casino()
{

}