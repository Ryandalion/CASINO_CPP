#include "Location.hpp"

#ifndef BAR_H
#define BAR_H

class Bar : public Location
{
public:
	Bar();
	void enter(Account *user);
	~Bar();
private:

};

#endif