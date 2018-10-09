#include <iostream>

#ifndef CASINO_H
#define CASINO_H

class Casino
{
public:
	Casino();

	static double balance;

	void getUserInfo(); // Retrieve user information => Balance and name
	void setUserBalance(double balance);  // Set user's balance
	void setUserWinnings(); // Set user's winnings
	void setUserLosses();   // Set user's losses
	void setWinningsPerSession(); // Set user's winnings for the session
	void borrowMoney(); // Borrow money from the casino
	
	void tipDealer(); // Tip the dealer
	void buyDrink(); // Buy a drink - Beer, cola, champagne, wine, etc.

	double getUserBalance(); // Return user's balance
	double getUserWinnings(); // Return user's winnings
	double getWinningsForSession(); // Get user's winnings for the session

	~Casino();

private:
	double totalBalance;
	double totalUserWinnings;
	double userWinnings;
	double winningPerSession;

};

#endif