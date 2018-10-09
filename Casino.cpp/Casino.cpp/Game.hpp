#include <iostream>
#include <vector>
#include <limits>
#include <string>

#include "Lobby.hpp"
#include "SlotsRoom.hpp"
#include "BlackjackRoom.hpp"
#include "PokerRoom.hpp"

#include "Account.hpp"
#include "Slots.hpp"
#include "Blackjack.hpp"
#include "Poker.hpp"

using std::numeric_limits;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::streamsize;

#ifndef GAME_H
#define GAME_H

class Game : public Casino
{
public:
	Game();
	
	void startGame(Account *user);
	void printArea();
	int validateInput(int minimum, int maximum);
	int userChoose(int &choice);
	
	Area *travel();
	

	~Game();
private:
	Area *currentRoom;
	Area *startRoom;
	Account *user;

};


#endif