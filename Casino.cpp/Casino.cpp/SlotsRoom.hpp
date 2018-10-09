#include "area.hpp"
#include "Account.hpp"
#include "Slots.hpp"


class SlotsRoom : public Area
{
public:
	SlotsRoom();
	Account* playGame(Account *user);
	~SlotsRoom();

};