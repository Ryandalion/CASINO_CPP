#include "Bar.hpp"

Bar::Bar() : Location("Bar/Restaurant")
{

}

void Bar::enter(Account *user)
{
	cout << "Inside the bar" << endl;
}

Bar::~Bar()
{

}