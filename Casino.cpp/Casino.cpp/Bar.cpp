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
			cout << "|1. Whiskey -------- $7|" << endl; // Increased payout by 5% => No luck added
			cout << "|2. Beer    -------- $4|" << endl; // Increase winning by 10%
			cout << "|3. Gin and Tonic -- $9|" << endl; // Increase loss rate by 10% => Increase payout by 15%
			cout << "|4. Wine    ---------$8|" << endl; // Increase winning by 5%
			cout << "|5. Redbull ---------$4|" << endl;  // Increase winning by 5%
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
			break;
		}

		case 2:
		{
			cout << "You chose beer" << endl;
			break;
		}

		case 3:
		{
			cout << "You chose Gin and Tonic" << endl;
			break;
		} 

		case 4:
		{
			cout << "You chose Wine" << endl;
			break;
		}

		case 5:
		{
			cout << "You chose Redbull" << endl;
			break;
		}
	}
}

Bar::~Bar()
{

}