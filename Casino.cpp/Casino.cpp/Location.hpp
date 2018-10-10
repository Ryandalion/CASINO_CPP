#include <iostream>
#include <string>

#include "Account.hpp"

using std::string;

#ifndef LOCATION_H
#define LOCATION_H

class Location
{
protected:
	string roomName;
public:

	Location *top;
	Location *bottom;
	Location *left;
	Location *right;

	Location(string roomName);
	void setRoomName(string name);
	virtual void enter(Account *user) = 0;
	string getRoomName();

	~Location();
};

#endif