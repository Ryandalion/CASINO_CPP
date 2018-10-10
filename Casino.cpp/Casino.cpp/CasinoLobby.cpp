#include "CasinoLobby.hpp"

CasinoLobby::CasinoLobby() : Location ("Casino Lobby")
{

}

void CasinoLobby::enter(Account *user)
{
	cout << "Buy some shit in the lobby" << endl;
}

CasinoLobby::~CasinoLobby()
{

}