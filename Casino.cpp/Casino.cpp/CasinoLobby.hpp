#include "Location.hpp"

#ifndef CASINOLOBBY_H
#define CASINOLOBBY_H

class CasinoLobby : public Location
{
public:
	CasinoLobby();
	void enter(Account *user);
	~CasinoLobby();
};

#endif
