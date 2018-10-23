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

};

class Slots
{
public:
	Slots();
	void setCredits(Slots *machine, int credits);
	void startSlots(Account *user);
	void setCredits(Account *user);
	double getCredits();

	double calculateWinner(string reel[][3], int lines);

	double threeLines(string *symbol, string **reel, int *lines); // 3 or less lines activated
	double fiveLines(string *symbol,string **reel, int *lines); // 3 ~ 5 lines activated
	double sixLines(string *symbol,string **reel, int *lines); // 6 ~ 7 lines activated
	double eightLines(string *symbol, string **reel, int *lines); // 8 ~ 9 lines activated
	double tenLines(string *symbol, string **reel, int *lines); // 10 ~ 11 lines activated
	double twelveLines(string *symbol, string **reel, int *lines); // 12 ~ 13 lines activated
	double fourteenLines(string *symbol, string **reel, int *lines); //14 ~ 16 lines activated
	double sixteenLines(string *symbol,string **reel, int *lines); // 16 ~ 17 lines activated

	void startMachine(Account *user, int credits);
	void displayLines();
	~Slots();

private:
	double credits;

};

#endif

