#include "Location.hpp"


Location::Location(string roomName)
{
	left = right = top = bottom = nullptr;
	this->roomName = roomName;
}

void Location::setRoomName(string name)
{
	roomName = name;
}


string Location::getRoomName()
{
	return roomName;
}

Location::~Location()
{

}