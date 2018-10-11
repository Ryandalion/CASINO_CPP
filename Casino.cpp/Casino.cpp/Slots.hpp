#include "Casino.hpp"
#include "Account.hpp"

#ifndef SLOTS_H
#define SLOTS_H

class Slots
{
public:
	Slots();
	void startSlots(Account *user);
	void setCredits(Account *user);
	double getCredits();
	~Slots();

private:
	double credits;
	double totalBet;
	int	numLines;
	int betsPerLine;
};

#endif

