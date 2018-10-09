#include <iostream>
#include <string>

#include "Account.hpp"

using std::string;

#ifndef AREA_H
#define AREA_H

class Area
{
public:
	Area(string areaName);
	Area *top;
	Area *bottom;
	Area *left;
	Area *right;

	void setRoomName(string name);
	string getRoomName();

	virtual Account* playGame(Account *user) = 0;

	~Area();

protected:
	string areaName;
};

#endif