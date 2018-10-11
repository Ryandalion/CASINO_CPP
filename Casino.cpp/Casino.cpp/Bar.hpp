#include "Location.hpp"
#include "Casino.hpp"

#ifndef BAR_H
#define BAR_H

class Bar : public Location
{
public:
	Bar();
	void listMenu();
	void enter(Account *user);
	void beverageChoice(int drink, Account *user);
	~Bar();
 private:

};

#endif