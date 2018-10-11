#include "InputValidate.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#ifndef CASINO_H
#define CASINO_H

class Casino
{
public:
	Casino();


	void getUserInfo(); // Retrieve user information => Balance and name
	void setUserBalance(double balance);  // Set user's balance
	void setUserWinnings(double winnings); // Set user's winnings
	void setUserLosses(double losses);   // Set user's losses
	void setWinningsPerSession(double sessionWinnings); // Set user's winnings for the session
	void borrowMoney(); // Borrow money from the casino
	void setUserLoanAmount(int number);
	void getUserLoanAmount();

	void tipDealer(); // Tip the dealer
	void buyDrink(); // Buy a drink - Beer, cola, champagne, wine, etc.

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
};

#endif