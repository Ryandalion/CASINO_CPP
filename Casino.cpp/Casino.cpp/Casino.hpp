#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "InputValidate.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::vector;
using std::string;


#ifndef CASINO_H
#define CASINO_H

class Casino
{
public:
	Casino();
	//----------------Get User Information------------------------------

	void getUserInfo(string name); // Retrieve user information => Balance and name
	void setUserBalance(double balance);  // Set user's balance
	void setUserWinnings(double winnings); // Set user's winnings
	void setUserLosses(double losses);   // Set user's losses
	void setWinningsPerSession(double sessionWinnings); // Set user's winnings for the session


	//-------------------Character Stats Functions------------------------

	
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
	

	double sessionWinnings;
	double totalUserWinnings;
	double totalUserLosses;
	double userWinnings;
	double winningPerSession;
	double totalBalance;
	
	int luck;
	int misfortune;
};

#endif