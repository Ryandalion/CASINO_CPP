#include "Casino.hpp"

double Casino::balance;

Casino::Casino()
{

}

void Casino::getUserInfo()
{

}

void Casino::setUserBalance(double balance)
{
	totalBalance = totalBalance + balance;
}

void Casino::setUserWinnings()
{

}

void Casino::setUserLosses()
{

}

void Casino::setWinningsPerSession()
{

}

void Casino::borrowMoney()
{

}

void Casino::tipDealer()
{

}

void Casino::buyDrink()
{

}

double Casino::getUserBalance()
{
	return totalBalance;
}

double Casino::getUserWinnings()
{
	return userWinnings;
}

double Casino::getWinningsForSession()
{
	return winningPerSession;
}

Casino::~Casino()
{

}