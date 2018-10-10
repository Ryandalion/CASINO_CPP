#include <iostream>
#include <string>
#include <limits>
#include <vector>

#include "CasinoLobby.hpp"
#include "SlotsRoom.hpp"
#include "PokerRoom.hpp"
#include "BlackjackRoom.hpp"
#include "Bar.hpp"

#include "Blackjack.hpp"
#include "Poker.hpp"
#include "Slots.hpp"
#include "Account.hpp"
#include "Location.hpp"
#include "InputValidate.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

#ifndef CasinoGame_H
#define CasinoGame_H

class CasinoGame
{
	Location *currentRoom;
	Location *startingRoom;
public:
	CasinoGame();
	void startGame(Account *user);
	void printMap();
	Location *travel();
	Validate userInput;
	~CasinoGame();
};

#endif