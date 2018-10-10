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

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::numeric_limits;
using std::streamsize;
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
	int validate(int min, int max);
	~CasinoGame();
};

#endif