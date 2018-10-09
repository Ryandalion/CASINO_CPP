#include "area.hpp"

class PokerRoom : public Area
{
public:
	PokerRoom();
	Account* playGame(Account *user);
	~PokerRoom();
};