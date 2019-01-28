#include "Casino.hpp"
#include "Account.hpp"
#include "InputValidate.hpp"

#include <vector>
#include <algorithm>
#include <time.h>
#include <cstdlib>

#ifndef BLACKJACK_H
#define BLACKJACK_H

class Blackjack : public Casino
{
public:
	Blackjack();

	void startPlay(Account *user);
	void shoeSize();
	void initializeDeck(int shoeSize); // The shoe size will be determined by the user. The shoe size can be either 6 decks or 8 decks
	void shuffleDeck();
	void startGame(Account *user);
	int placeBet(Account *user);
	void currentBet();
	bool insufficientFunds(Account *user);
	void placeInsurance(Account *user);
	void buyChips(Account *user);
	void calculateWinnings(Account *user, int potSize);
	void dealerWin(Account *user, int potSize);

	bool checkBust(int hand);
	bool checkBlackjack(int hand);

	struct Card {
		string suit;
		string face;
		int value;
	};

	struct Player {
		string cards;
		int handValue;
	};


	~Blackjack();

private:
	Validate userInput;
	int betSize = 0;
	int betAmount = 0;
	bool insurance = false;
	int chipStack = 0;

	vector<Card> Cards;

};
#endif