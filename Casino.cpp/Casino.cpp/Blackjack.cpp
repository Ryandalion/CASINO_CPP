#include "Blackjack.hpp"

Blackjack::Blackjack()
{
}

void Blackjack::startPlay(Account *user)
{
	Validate userInput;
	int choice = 0;
	string dealerNames[] = { "Alfred", "Ashley", "Martin", "Petrie", "Yu", "Jameer", "Karl", "Janice"};
	
	srand(time(NULL));
	int dealerNumber = rand() % 8;
	string dealer = dealerNames[dealerNumber];

	cout << "Hello " << user->getName() << endl;
	cout << endl;
	cout << "Welcome to Blackjack. My name is " << dealer << " and I will be your dealer for today. ";
	cout << "Please select the minimum bet amount. This amount will automatically placed every round." << endl;
	cout << "1. $5" << endl;
	cout << "2. $10" << endl;
	cout << "3. $25" << endl;
	cout << "4. $100" << endl;
	cout << "5. $500" << endl;

	choice = userInput.inputValidate(1, 5);
	switch (choice)
	{
		case 1:
			cout << "You have selected $5" << endl;
			betSize = 5;
			shoeSize();
			break;
		case 2:
			cout << "You have selected $10" << endl;
			betSize = 10;
			shoeSize();
			break;
		case 3:
			cout << "You have selected $25" << endl;
			betSize = 25;
			shoeSize();
			break;
		case 4:
			cout << "You have selected $100" << endl;
			betSize = 100; 
			shoeSize();
			break;
		case 5:
			cout << "You have selected $500" << endl;
			betSize = 500;
			shoeSize();
			break;
	}
	

	startGame(user);
}

void Blackjack::shoeSize()
{
	int choice = 0;
	bool running = false;
	while (running != true)
	{
		cout << "Please select the size of the shoe" << endl;
		cout << "1. 6 Decks" << endl;
		cout << "2. 8 Decks" << endl;
		cout << "3. What is a shoe?" << endl;

		choice = userInput.inputValidate(1, 3);
		if (choice == 1)
		{
			cout << "You have selected 6 decks" << endl;
			initializeDeck(6);

			running = true;
		}

		else if (choice == 2)
		{
			cout << "You have selected 8 decks" << endl;
			initializeDeck(8);

			running = true;
		}

		else if (choice == 3)
		{
			cout << endl;
			cout << "A shoe is a device that holds a certain number of decks." << endl;
			cout << "If a shoe contains six decks, it will contain 312 cards, which is 6 * 52 (number of cards)." << endl;
			cout << "The idea of the shoe was first introduced in the 1960's by the Nevada Gaming Comission." << endl;
			cout << "Ever since, the shoe has been implemented in casinos around the world" << endl;
			running = false;
		}
	}
}

void Blackjack::initializeDeck(int size)
{
	const string suits[] = { "Hearts", "Clubs", "Diamonds", "Spades" };
	const string face[] = { "2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace" };
	int index = 0;

	for (int k = 0; k < size; k++) // Iterate the amount of the user selected shoe size
	{
		for (int i = 0; i < 4; i++) // Iterate through the four suits
		{

			for (int j = 0; j < 13; j++) // Iterate through the 13 face cards
			{
				Cards.push_back(Card());
				Cards[index].face = face[j];
				Cards[index].suit = suits[i];
				int convertInt = atoi(face[j].c_str());
				Cards[index].value = convertInt;
				index++;
			}
		}
	}


	for (int i = 0; i < Cards.size(); i++)
	{
		cout << Cards[i].suit + " of " + Cards[i].face + " VALUE: " << Cards[i].value << endl;
	}

	cout << "Size of the deck: " << Cards.size() << endl;

	shuffleDeck();
	
}

void Blackjack::shuffleDeck()
{
	std::random_shuffle(Cards.begin(), Cards.end());
	
	for (int i = 0; i < Cards.size(); i++)
	{
		cout << Cards[i].suit + " of " + Cards[i].face + " VALUE: " << Cards[i].value << endl;
	}

}

void Blackjack::buyChips(Account *user)
{
	bool buyMore = false;
	int choice = 0;
	int buyAgain = 0;

	while (buyMore != true)
	{
		cout << "Select the dollar amount in chips you would like to purchase" << endl;
		cout << "1. $50" << endl;
		cout << "2. $100" << endl;
		cout << "3. $250" << endl;
		cout << "4. $500" << endl;
		cout << "5. $1000" << endl;
		choice = userInput.inputValidate(1, 5);
		switch (choice)
		{
			case(1):
				if (user->getUserBalance() >= 50)
				{
					user->setUserBalance(-50);
					chipStack += 50;
					break;
				}
				else
				{
					cout << "Insufficient Funds" << endl;
					break;
				}
			case(2):
				if (user->getUserBalance() >= 100)
				{
					user->setUserBalance(-100);
					chipStack += 100;
					break;
				}
				else
				{
					cout << "Insufficient Funds" << endl;
					break;
				}
			case(3):
				if (user->getUserBalance() >= 250)
				{
					user->setUserBalance(-250);
					chipStack += 250;
					break;
				}
				else
				{
					cout << "Insufficient Funds" << endl;
					break;
				}
			case(4):
				if (user->getUserBalance() >= 500)
				{
					user->setUserBalance(-500);
					chipStack += 500;
					break;
				}
				else
				{
					cout << "Insufficient Funds" << endl;
					break;
				}
			case(5):
				if (user->getUserBalance() >= 1000)
				{
					user->setUserBalance(-1000);
					chipStack += 1000;
					break;
				}

				else
				{
					cout << "Insufficient Funds" << endl;
					break;
				}
		}

		cout << "Would you like to purchase more chips?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		buyAgain = userInput.inputValidate(1, 2);
		if (buyAgain == 1)
		{
			buyMore = false;
		}
		else
		{
			buyMore = true;
		}
	}
}

void Blackjack::startGame(Account *user) // Start Game
{
	bool running = false;
	bool deal = false;
	bool player_turn = false;
	bool dealer_turn = false;
	bool player_funds = false;

	buyChips(user); // Get chips for user

	cout << "All set, thank you " << user->getName() << endl;
	cout << "Now let's play some Blackjack!" << endl;
	betAmount = betSize;

	// All financial transactions from here are done via chips
	while (running != true)
	{
		int player_1 = 0;
		int dealer = 0;
		bool firstHand = true;
		bool dealerAce = false;

		if (chipStack < betSize)
		{
			cout << "Not enough funds to place the minimum bet of $" << betSize << endl;
			running = true;
		}

		placeBet(user);
		cout << "Dealing cards..." << endl;
		while (deal != true)
		{	
			if (player_turn != true)
			{
				if (player_1 == 21)
				{
					cout << "Player has hit Blackjack" << endl;
				}

				else if (player_1 > 21)
				{
					cout << "Player has bust" << endl;
				}

				else
				{
					cout << "Player's turn" << endl;
					cout << Cards.front().face + " of " + Cards.front().suit;
					int player_card = Cards.front().value;
					player_1 += player_card;
					cout << "Current Hand Value: " << player_1 << endl;
					Cards.erase(Cards.begin(), Cards.begin() + 1);
					player_turn = true;
					dealer_turn = false;
				}
			}

			else if (dealer_turn != true)
			{
				if (17 <= dealer < 21)
				{
					dealer_turn = true;
				}

				else if (dealer == 21)
				{
					cout << "Dealer has hit Blackjack" << endl;
				}

				else
				{
					int dealer_card = 0;
					cout << "Dealer's turn" << endl;
					cout << Cards.front().face + " of " + Cards.front().suit;
					if (Cards.front().value == 0)
					{
						dealer_card = 10;

						if (Cards.front().face == "Ace")
						{
							dealer_card = 11;
							dealerAce = true;
						}
					}

					if (Cards.front().face == "Ace" && firstHand == true)
					{
						placeInsurance(user);
						firstHand = false;
						dealer_card = 11;
						dealerAce = true;
					}

					dealer += dealer_card;
					cout << "Current Hand Value: " << dealer << endl;
					Cards.erase(Cards.begin(), Cards.begin() + 1);
					dealer_turn = true;
					player_turn = false;
				}
			}

			cout << "Please make a selection" << endl;
			cout << "1. Hit" << endl;
			cout << "2. Stand" << endl;
			int choice = userInput.inputValidate(1, 2);
			if (choice == 1)
			{
				player_funds = placeBet(user);
			}

		}
	}
}


void Blackjack::placeInsurance(Account *user)
{
	// ONLY EXECUTE INSURANCE IF DEALER HAS ACE
	insurance = false;
	bool insuranceLoop = false;
	while (insuranceLoop != true)
	{
		cout << "Would you like to buy insurance?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cout << "3. What is insurance?" << endl;
		int choice = 0;
		choice = userInput.inputValidate(1, 3);
		if (choice == 1)
		{
			double insurancePrice = (betSize * .5);
			if (user->getUserBalance() < insurancePrice)
			{
				cout << "Not enough funds to purchase insurance" << endl;
				insuranceLoop = true;
			}

			else
			{
				user->setUserBalance((-1) * insurancePrice);
				cout << "You have purchased insurance for $" << insurancePrice << endl;
				insurance = true;
				insuranceLoop = true;
			}
		}

		else if (choice == 2)
		{
			cout << "Insurance not purchased" << endl;
			insuranceLoop = true;
		}

		else if (choice == 3)
		{
			cout << "Insurance ensures that the player wins " << endl;
		}
	}
}

bool Blackjack::placeBet(Account *user)
{
	bool valid = false;
	while (valid != true)
	{
		int choice = 0;
		int choice2 = 0;
		cout << "Please place your bet" << endl;
		cout << "1. $5" << endl;
		cout << "2. $10" << endl;
		cout << "3. $25" << endl;
		cout << "4. $100" << endl;
		cout << "5. $500" << endl;
		choice = userInput.inputValidate(1, 5);
		
		if (choice == 1)
		{
			if (chipStack >= 5)
			{
				chipStack -= 5;
				betAmount += 5;
				cout << "You placed a bet for $5" << endl;
				valid = true;
			}

			else
			{
				valid = insufficientFunds(user);
			}
		}

		else if (choice == 2)
		{
			if (chipStack >= 10)
			{
				chipStack -= 10;
				betAmount += 10;
				cout << "You placed a bet for $10" << endl;
				valid = true;
			}

			else
			{
				valid = insufficientFunds(user);
			}
		}

		else if (choice == 3)
		{
			if (chipStack >= 25)
			{
				chipStack -= 25;
				betAmount += 25;
				cout << "You placed a bet for $25" << endl;
				valid = true;
			}

			else
			{
				valid = insufficientFunds(user);
			}
		}

		else if (choice == 4)
		{
			if (chipStack >= 100)
			{
				chipStack -= 100;
				betAmount += 100;
				cout << "You placed a bet for $100" << endl;
				valid = true;
			}

			else
			{
				valid = insufficientFunds(user);
			}
		}

		else if (choice == 5)
		{
			if (chipStack >= 500)
			{
				chipStack -= 500;
				betAmount += 500;
				cout << "You placed a bet for $500" << endl;
				valid = true;
			}
			
			else
			{
				valid = insufficientFunds(user);
			}
		}
	}
}

void Blackjack::currentBet()
{
	cout << "Current Bet: $" << betAmount << endl;
}

bool Blackjack::insufficientFunds(Account *user)
{
	int choice = 0;
	bool playAgain = false;
	cout << "Not enough funds to place the bet" << endl;
	cout << "Please select an option" << endl;
	cout << "1. Place another bet" << endl;
	cout << "2. Buy more chips" << endl;
	cout << "3. Exit Blackjack" << endl;
	choice = userInput.inputValidate(1, 3);
	if (choice == 1)
	{
		return playAgain;
	}

	else if (choice == 2)
	{
		buyChips(user);
		return playAgain;
	}

	else
	{
		playAgain = true;
		return playAgain;
	}
}

Blackjack::~Blackjack()
{
}