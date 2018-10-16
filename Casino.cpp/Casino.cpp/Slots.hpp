#include "Casino.hpp"
#include "Account.hpp"

#include <algorithm>
#include <random>
#include <chrono>

#ifndef SLOTS_H
#define SLOTS_H

struct SlotMachine
{
	string userName;
	double creditAmount;
	double winnings;
	double losses;

	double numLines;
	double betPerLine;

	//SlotMachine();
	//double pull(double creditAmount);
};

//SlotMachine::SlotMachine()
//{
//	string userName = "";
//	double creditAmount = 0; 
//	double winnings = 0;
//	double losses = 0;
//	double numLines = 0;
//	double betsPerLine = 0;
//}

//double SlotMachine::pull(double creditAmount)
//{
//
//}
//

class Slots
{
public:
	Slots();
	void setCredits(Slots *machine, int credits);
	void startSlots(Account *user);
	void setCredits(Account *user);
	double getCredits();

	void startMachine(Account *user, int credits);
	~Slots();

private:
	double credits;

};

#endif

