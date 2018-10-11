#include <iostream>
#include <ctime>

#include "InputValidate.hpp"

using std::cout;
using std::cin;
using std::endl;

#ifndef CASINO_H
#define CASINO_H

class Casino
{
public:
	Casino();
	//----------------Get User Information------------------------------

	void getUserInfo(); // Retrieve user information => Balance and name
	void setUserBalance(double balance);  // Set user's balance
	void setUserWinnings(double winnings); // Set user's winnings
	void setUserLosses(double losses);   // Set user's losses
	void setWinningsPerSession(double sessionWinnings); // Set user's winnings for the session

	//--------------------Borrow Money Functions-------------------------

	void borrowMoney(); // Borrow money from the casino
	void setUserLoanAmount(int number);
	void getUserLoanAmount();

	//-------------------Character Stats Functions------------------------

	void saveUserData(); // Save all user data => Balance, outstanding loans & number of loans, total winnings => save all into .dat file
	void tipDealer(); // Tip the dealer
	void setUserLuck(int luckAmount); // Set the amount of luck the user has
	int getUserLuck(); // The amount of luck the user has based upon the drinks they consumed
	void setUserMisfortune(int badluck);
	int getUserMisfortune();
	//----------------Return user information------------------------------

	double getUserBalance(); // Return user's balance
	double getUserWinnings(); // Return user's winnings
	double getWinningsForSession(); // Get user's winnings for the session

	~Casino();

private:
	double totalBalance;
	double sessionWinnings;
	double totalUserWinnings;
	double totalUserLosses;
	double userWinnings;
	double winningPerSession;
	double loanAmount;
    int numOfLoans;
	int luck;
	int misfortune;
};

#endif