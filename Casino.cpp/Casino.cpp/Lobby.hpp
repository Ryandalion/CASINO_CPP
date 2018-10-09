#include "area.hpp"

class Lobby : public Area
{
public:
	Lobby();
	Account* playGame(Account *user);
	~Lobby();
};