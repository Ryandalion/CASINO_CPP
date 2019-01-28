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
	cout << "Welcome to Blackjack. My name is " << dealer << " and I will be your dealer today. " << endl;
	cout << "Please select a minimum bet amount. This amount will be automatically placed every round." << endl;
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

	shuffleDeck();
	
}

void Blackjack::shuffleDeck()
{
	std::random_shuffle(Cards.begin(), Cards.end());

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
	Player player;
	Player dealer_player;

	bool running = false;

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

		int *player_score = new int;
		int *dealer_score = new int;

		player_score = &player_1;
		dealer_score = &dealer;

		int player_card = 0;
		int dealer_card = 0;

		int potSize = 0;

		string players_hand = "";
		string dealers_hand = "";

		bool deal = false;
		bool firstHand = true;
		bool firstRound = true;

		bool playerStandby = false;
		bool dealerStandby = false;

		bool playerStand = false;
		bool dealerStand = false;
		bool dealerStay = false;

		bool dealerAce = false;
		bool playerAce = false;

		bool playerBust = false;
		bool dealerBust = false;

		bool playerBlackjack = false;
		bool dealerBlackjack = false;


		if (chipStack < betSize)
		{
			cout << "Not enough funds to place the minimum bet of $" << betSize << endl;
			running = true;
		}

		potSize = placeBet(user);

		cout << "Dealing cards..." << endl;
		cout << endl;
		while (deal != true)
		{	
			cout << "----------------------------------------------------" << endl;
			if (firstHand) // First Hand
			{
				cout << "Player's Hand: ";
				players_hand = Cards.front().face + " of " + Cards.front().suit;
				cout << players_hand << endl;
				if (Cards.front().value == 0)
				{
					player_card = 10;
					if (Cards.front().face == "Ace")
					{
						playerAce = true;
						cout << "*Ace is either 1 or 11" << endl;
						player_card = 11;
					}
				}

				else
				{
					player_card = Cards.front().value;
				}

				player_1 = player_1 + player_card;
				player.cards = players_hand;
				player.handValue = player_1;
				cout << "Player's Hand Value: " << player_1 << endl;
				cout << "----------------------------------------------------" << endl;
				Cards.erase(Cards.begin(), Cards.begin() + 1);

				cout << "Dealer's Hand: ";
				dealers_hand = Cards.front().face + " of " + Cards.front().suit;
				cout << dealers_hand << endl;
				if (Cards.front().value == 0)
				{
					dealer_card = 10;

					if (Cards.front().face == "Ace")
					{
						cout << "*Ace is either 1 or 11" << endl;
						placeInsurance(user);
						dealer_card = 11;
						dealerAce = true;
					}
				}

				else
				{
					dealer_card = Cards.front().value;
				}

				dealer = dealer + dealer_card;
				dealer_player.cards = dealers_hand;
				dealer_player.handValue = dealer;
				cout << "Dealer's Hand Value: " << dealer << endl;
				Cards.erase(Cards.begin(), Cards.begin() + 1);
				firstHand = false;
			}

			// After First Round
			if (!playerStand && !firstRound) // If player has chose to hit we allow execution, stop execution if the player chooses to stand
			{
				cout << endl;
				cout << "Player's Hand: ";
				players_hand = Cards.front().face + " of " +Cards.front().suit;
				cout << players_hand << endl;
				if (Cards.front().value == 0)
				{
					player_card = 10;
					if (Cards.front().face == "Ace")
					{
						cout << "*Ace is either be 1 or 11" << endl;
						player_card = 11;
					}
				}

				else
				{
					player_card = Cards.front().value;
				}

				player_1 = player_1 + player_card;
				player.cards = players_hand;
				player.handValue = player_1;
				cout << "Player's Hand Value: " << player_1 << endl;
				cout << "----------------------------------------------------" << endl;
				Cards.erase(Cards.begin(), Cards.begin() + 1);	
			}


			if (playerStand && !dealerStand)
			{
				if (17 <= dealer && dealer < 21)
				{
					dealerStay = true;
				}

				else
				{
					cout << "Dealer's Hand: ";
					dealers_hand = Cards.front().face + " of " + Cards.front().suit;
					cout << dealers_hand << endl;
					if (Cards.front().value == 0)
					{
						dealer_card = 10;

						if (Cards.front().face == "Ace")
						{
							dealer_card = 11;
							dealerAce = true;
						}
					}
					
					else
					{
						dealer_card = Cards.front().value;
					}
					dealer = dealer + dealer_card;
					dealer_player.cards = dealers_hand;
					dealer_player.handValue = dealer;
					cout << "Dealer's Hand Value: " << dealer << endl;
					cout << "----------------------------------------------------" << endl;
					Cards.erase(Cards.begin(), Cards.begin() + 1);
				}
			}

	
			if (dealerStandby)
			{
				cout << "STRUCT PRINT" << endl;
				cout << "Dealer's Hand: " << dealer_player.cards << endl;
				cout << "Dealer's Hand Value: " << dealer_player.handValue << endl;
			}

			if (playerStandby)
			{
				cout << "STRUCT PRINT" << endl;
				cout << "Player's Hand: " << player.cards << endl;
				cout << "Player's Hand Value: " << player.handValue << endl;
			}

			playerBust = checkBust(player_1);
			dealerBust = checkBust(dealer);

			playerBlackjack = checkBlackjack(player_1);
			dealerBlackjack = checkBlackjack(dealer);

			firstRound = false;

			if (playerBust)
			{
				cout << "----------------------------------------------------" << endl;
				cout << "Player has bust" << endl;
				cout << "Dealer wins" << endl;
				calculateWinnings(user, potSize);
				deal = true;
			}

			if (dealerBust) 
			{
				cout << "----------------------------------------------------" << endl;
				cout << "Dealer has bust" << endl;
				cout << "Player wins" << endl;
				calculateWinnings(user, potSize);
				deal = true;
			}

			if (playerBlackjack)
			{
				cout << "----------------------------------------------------" << endl;
				cout << "Player has hit Blackjack" << endl;
				calculateWinnings(user, potSize);
				deal = true;
			}

			if (dealerBlackjack)
			{
				cout << "----------------------------------------------------" << endl;
				cout << "Dealer has hit Blackjack" << endl;
				dealerWin(user, potSize);
				deal = true;
			}

			if (dealerStay)
			{
				cout << "----------------------------------------------------" << endl;
				if (player_1 > dealer)
				{
					cout << "Player has won" << endl;
					calculateWinnings(user, potSize);
				}

				else
				{
					cout << "Dealer has won" << endl;
					calculateWinnings(user, potSize);
				}

				playerBust = false;
				dealerBust = false;
				playerBlackjack = false;
				dealerBlackjack = false;
				deal = true;
			}

			if (!playerBust && !dealerBust && !dealerBlackjack && !playerBlackjack && !playerStand)
			{
				bool repeat = true;

				while (repeat == true)
				{
					cout << "---------------------------------------------------" << endl;
					cout << "Please make a selection" << endl;
					cout << "1. Hit" << endl;
					cout << "2. Stand" << endl;
					cout << "3. View chip stack" << endl;
					cout << "4. View pot size" << endl;
					cout << "----------------------------------------------------" << endl;
					int choice = userInput.inputValidate(1, 3);
					cout << "----------------------------------------------------" << endl;
					if (choice == 1)
					{
						potSize += placeBet(user);
						dealerStand = true;
						playerStand = false;
						dealerStandby = true;
						playerStandby = false;
						repeat = false;
					}

					else if (choice == 2)
					{
						cout << "You have chosen to stand" << endl;
						cout << endl;
						playerStand = true;
						dealerStand = false;
						playerStandby = true;
						dealerStandby = false;
						repeat = false;
					}

					else if(choice == 3)
					{
						cout << "Current chip stack: $" << chipStack << endl;
						cout << endl;
					}

					else
					{
						cout << "Current pot size: $" << potSize << endl;
						cout << endl;
					} 
				}

			}


		}

		cout << "----------------------------------------------------" << endl;
		cout << "Would you like to play another round?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. Exit Blackjack" << endl;
		cout << "----------------------------------------------------" << endl;
		int choice = userInput.inputValidate(1, 2);
		cout << "----------------------------------------------------" << endl;
		if (choice == 1)
		{
			running = false;
		}
		else if (choice == 2)
		{
			running = true;

			player_score = NULL;
			dealer_score = NULL;

			delete player_score;
			delete dealer_score;

		}
	}
}

void Blackjack::dealerWin(Account *user, int potSize)
{
	if (insurance)
	{
		cout << "Player has insurance" << endl;
	}
}

bool Blackjack::checkBust(int hand)
{
	bool userBust = false;

	if (hand > 21)
	{
		userBust = true;
	}

	return userBust;
}

void Blackjack::calculateWinnings(Account *user, int potsize)
{

}

bool Blackjack::checkBlackjack(int hand)
{
	bool blackjack = false;

	if (hand == 21)
	{
		blackjack = true;
	}

	return blackjack;
}

void Blackjack::placeInsurance(Account *user)
{

	insurance = false;
	bool insuranceLoop = false;
	while (insuranceLoop != true)
	{
		cout << "----------------------------------------------------" << endl;
		cout << "Would you like to buy insurance?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cout << "3. What is insurance?" << endl;
		cout << "----------------------------------------------------" << endl;
		int choice = 0;
		choice = userInput.inputValidate(1, 3);
		cout << "----------------------------------------------------" << endl;
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

int Blackjack::placeBet(Account *user)
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

	return betAmount;
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