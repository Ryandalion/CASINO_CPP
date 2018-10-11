#include "Bar.hpp"

Bar::Bar() : Location("Bar/Restaurant")
{

}

void Bar::enter(Account *user)
{
	int choice = 0;
	Validate userInput;
	cout << "BAR/RESTAURANT" << endl;
	cout << "1. Go to a different room" << endl;
	cout << "2. Drink at the bar" << endl;
	choice = userInput.inputValidate(1, 2);
	if (choice == 2)
	{
		int numDrinks = 0;
		int beverage = 0;
		cout << endl;
		if (numDrinks < 3)
		{
			cout << "++++++++++++++++++++++++" << endl;
			cout << "|-------= MENU =-------|" << endl;
			cout << "|======================|" << endl;
			cout << "|--------DRINKS--------|" << endl;
			cout << "|1. Whiskey -------- $7|" << endl; 
			cout << "|2. Beer    -------- $4|" << endl; 
			cout << "|3. Gin and Tonic -- $9|" << endl; 
			cout << "|4. Wine    ---------$8|" << endl;
			cout << "|5. Redbull ---------$4|" << endl; 
			cout << "++++++++++++++++++++++++" << endl;
			cout << endl;
			cout << "Which beverage would you like to purchase?" << endl;
			beverage = userInput.inputValidate(1, 5);
			numDrinks++;
			beverageChoice(beverage, user);
		}

		else
		{
			cout << "You had too many drinks. Come back again later." << endl;
		}
	}

}

void Bar::beverageChoice(int beverage, Account *user)
{
	switch (beverage)
	{
		case 1: 
		{
			cout << "You chose whiskey" << endl;
			user->setUserLuck(4);
			user->setUserMisfortune(2);
			break;
		}

		case 2:
		{
			cout << "You chose beer" << endl;
			user->setUserLuck(3);
			user->setUserMisfortune(1);
			break;
		}

		case 3:
		{
			cout << "You chose Gin and Tonic" << endl;
			user->setUserLuck(5);
			user->setUserMisfortune(3);
			break;
		} 

		case 4:
		{
			cout << "You chose Wine" << endl;
			user->setUserLuck(5);
			user->setUserMisfortune(1);
			break;
		}

		case 5:
		{
			cout << "You chose Redbull" << endl;
			user->setUserLuck(6);
			user->setUserMisfortune(3);
			break;
		}
	}
}

Bar::~Bar()
{

}