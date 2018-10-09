#include "area.hpp"

Area::Area(string areaName)
{
	top = bottom = left = right = nullptr;
	this->areaName = areaName;
}

void Area::setRoomName(string name)
{
	areaName = name;
}

string Area::getRoomName()
{
	return areaName;
}

Area::~Area()
{

}