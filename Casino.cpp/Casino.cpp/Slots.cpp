#include "Slots.hpp"


Slots::Slots()
{

}

void Slots::startSlots(Account *user)
{


	cout << "Hello " << user->getName() << endl;
	cout << endl;
	setCredits(user); // Set the credits
}

void Slots::setCredits( Account* user)
{
	int inputAmount = 0;
	Validate validate;

	cout << "Select the number of credits you wish to play" << endl;
	cout << " ______________________________________" << endl;
	cout << "|               CREDITS                |" << endl;
	cout << "|======================================|" << endl;
	cout << "|       1. $1 = 100 Credits            |" << endl;
	cout << "|       2. $10 = 1000 Credits          |" << endl;
	cout << "|       3. $50 = 5000 Credits          |" << endl;
	cout << "|       4. $100 = 10,000 Credits       |" << endl;
	cout << "|       5. $500 = 50,000 Credits       |" << endl;
	cout << "|       6. $1,000 = 100,000 Credits    |" << endl;
	cout << "|______________________________________|" << endl;
	cout << endl;
	inputAmount = validate.inputValidate(1, 6);

	double deduct = 0;
	switch (inputAmount)
	{
		case 1:
		{
			deduct = -1;
			user->setUserBalance(deduct);
			credits = 100;
			break;
		}

		case 2:
		{
			deduct = -10;
			user->setUserBalance(deduct);
			credits = 1000;
			break;
		}

		case 3:
		{
			deduct = -50;
			user->setUserBalance(deduct);
			credits = 5000;
			break;
		}

		case 4:
		{
			deduct = -100;
			user->setUserBalance(deduct);
			credits = 10000;
			break;
		}

		case 5:
		{
			deduct = -500;
			user->setUserBalance(deduct);
			credits = 50000;
			break;
		}

		case 6:
		{
			deduct = -1000;
			user->setUserBalance(deduct);
			credits = 100000;
			break;
		}
	}
}

double Slots::getCredits()
{
	return credits;
}

Slots::~Slots()
{

}