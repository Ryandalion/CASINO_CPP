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
		string dealerFirst = "";

		bool revealHand = false;
		bool firstBlackjack = false;
		
		int dealerFirstVal = 0;
		
		bool insuranceStatus = false;

		bool deal = false;
		bool firstHand = true;
		bool firstRound = true;

		bool playerStandby = false;
		bool dealerStandby = false;

		bool playerStand = false;
		bool dealerStand = false;
		bool dealerStay = false;

		bool dealerAceFirst = false;
		bool dealerAce = false;
		bool playerAce = false;

		bool tieStatus = false;

		bool playerBust = false;
		bool dealerBust = false;

		bool playerBlackjack = false;
		bool dealerBlackjack = false;


		if (chipStack < betSize)
		{
			cout << "Not enough funds to place the minimum bet of $" << betSize << endl;
			cout << "1. Purchase more chips" << endl;
			cout << "2. Leave table" << endl;
			int choice = userInput.inputValidate(1, 2);
			if (choice == 1)
			{
				buyChips(user);
			}
			else
			{
				deal = true;
				running = true;
			}
		}

		potSize = placeBet(user);

		cout << "Dealing cards..." << endl;
		cout << endl;
		while (deal != true)
		{
			cout << "----------------------------------------------------" << endl;
			if (firstHand) // First Hand
			{
				bool dealerHidden = false; // Dealer only shows the first card and the second card remains hidden
				bool p_blackjack = false;
				bool d_blackjack = false;

				for (int i = 0; i < 2; i++)
				{
					players_hand = players_hand + Cards.front().face + " of " + Cards.front().suit + "\n";

					if (Cards.front().value == 0)
					{
						player_card = 10;
						if (Cards.front().face == "Ace")
						{
							playerAce = true;
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
					Cards.erase(Cards.begin(), Cards.begin() + 1);

					// Dealer draw
					dealers_hand = dealers_hand + Cards.front().face + " of " + Cards.front().suit + "\n";

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
					Cards.erase(Cards.begin(), Cards.begin() + 1);

					if (!dealerHidden)
					{
						if (dealer_card == 11)
						{
							dealerAceFirst = true;
						}

						dealerFirst = dealers_hand;
						dealerFirstVal = dealer;
						dealerHidden = true;
					}

				}

				p_blackjack = checkBlackjack(player.handValue);
				d_blackjack = checkBlackjack(dealer_player.handValue);


				cout << "Player's Hand: ";
				cout << endl;
				for (int i = 0; i < player.cards.size(); i++)
				{
					cout << player.cards[i];
				}

				cout << "\nPlayer's Hand Value: " << player.handValue << endl;
				cout << "----------------------------------------------------" << endl;
				cout << "Dealer's Hand: " << endl;
				cout << dealerFirst << endl;
				cout << "Dealer's Hand Value (Only one value showing): " << endl;
				cout << dealerFirstVal << endl;

				if (p_blackjack)
				{
					cout << "Player has blackjack" << endl;
					firstBlackjack = true;
					deal = true;
					if (d_blackjack)
					{
						cout << "Dealer has blackjack" << endl;
						cout << "Push" << endl;
					}

					else
					{
						cout << "Player wins" << endl;
					}
				}

				if (dealerAceFirst) // Dealer has an Ace, ask user if they want to purchase insurance
				{
					cout << "----------------------------------------------------" << endl;
					cout << "Dealer has an Ace" << endl;
					insuranceStatus = placeInsurance(user); // User is led to insurance menu
					if (d_blackjack) // If the dealer has blackjack
					{
						cout << "Dealer has blackjack" << endl; // Notify player that dealer has blackjack
						firstBlackjack = true;
						deal = true;
						if (insuranceStatus) // If the player has insurance
						{
							cout << "Player has insurance" << endl;
							cout << "Original Pot Size: " << potSize << endl;
							potSize = (potSize * .50);
							cout << "Payout after insurance: " << potSize << endl;
							// Deduct half the player's bet
						}
						else // Player does not have insurance and loses bet
						{
							cout << "Dealer wins" << endl;
						}
					}
				}
			}

			// ---------------------------- AFTER FIRST HAND --------------------------------------

			if (!firstBlackjack && !deal) // If there is no blackjack in the first round we execute
			{
				cout << "We in here" << endl;
				// After First Round
				if (!playerStand && !firstRound) // Player hits and it's not the first round
				{
					
					cout << "player hit, not first round" << endl;
					cout << endl;
					cout << "Player's Hand: " << endl;
				
					for (int i = 0; i < player.cards.size(); i++)
					{
						cout << player.cards[i];
					}

					players_hand = Cards.front().face + " of " + Cards.front().suit + "\n";
					cout << players_hand << endl;
					if (Cards.front().value == 0)
					{
						player_card = 10;

						if (Cards.front().face == "Ace")
						{
							if (player_1 > 10) // If the player's score is greater than 10, then the ace is worth 1 
							{
								player_card = 1;
							}
							else // If the player's score is less than 10, then the ace is worth 11
							{
								player_card = 11;
							}
						}
					}

					else // Card is not a face card or Ace and we get the corresponding value
					{
						player_card = Cards.front().value;
					}

					player_1 = player_1 + player_card;
					player.cards += players_hand;
					player.handValue = player_1;
					cout << "Player's Hand Value: " << player_1 << endl;
					cout << "----------------------------------------------------" << endl;

					Cards.erase(Cards.begin(), Cards.begin() + 1);


				}



				// Player has chosen to stand and dealer hits
				if (playerStand && !dealerStand)
				{
					cout << "Player stand, dealer hit" << endl;

					if (dealer >= 17) // If the dealer has a score of 17 or greater, the dealer stands
					{
						dealerStay = true; // Dealer stand set to true
						dealerStandby = true; // Dealer stand by set to true
					}

					else // Else the dealer has a score less than 17 and the dealer will hit
					{
						dealers_hand = Cards.front().face + " of " + Cards.front().suit + "\n";
						if (Cards.front().value == 0) // Dealer pulls a face card
						{
							dealer_card = 10; // Set card value to 10

							if (Cards.front().face == "Ace") // If dealer pulled an ace
							{
								if (dealer > 10) // If the dealer's score exceeds 10, we set the card value (Ace) to 1
								{
									dealer_card = 1;
								}
								else // If the dealer's score is less than 10, we set the card value (Ace) to 11
								{
									dealer_card = 11;
								}
							}
						}

						else // Dealer did not pull a face card or Ace so we just get the normal corresponding value
						{
							dealer_card = Cards.front().value;
						}

						dealer = dealer + dealer_card; // Update the dealer's new hand value

						for (int i = 0; i < dealers_hand.length(); i++)
						{
							dealer_player.cards.push_back(dealers_hand[i]);
						}
					}

					cout << "Dealer's Hand: " << endl;
					for (int i = 0; i < dealer_player.cards.size(); i++)
					{
						cout << dealer_player.cards[i];
					}

					dealer_player.handValue = dealer; // Set the dealer's object hand value to the new updated hand value
					cout << "Dealer's Hand Value: " << dealer_player.handValue << endl;
					cout << "----------------------------------------------------" << endl;
					Cards.erase(Cards.begin(), Cards.begin() + 1); // Remove the cards from the deck
				}


				playerBust = checkBust(player_1); // Check if the player has bust
				dealerBust = checkBust(dealer); // Check if the dealer has bust

				playerBlackjack = checkBlackjack(player_1); // Check if the player has blackjack
				dealerBlackjack = checkBlackjack(dealer); // Check if the dealer has blackjack

				tieStatus = checkTie(dealer, player_1); // Check if there is a tie between the dealer and player

				firstRound = false;

				if (dealerStandby) // Dealer is on standby - Player is still in action or dealer has a score greater than 17
				{
					cout << "DEALER STANDBY" << endl;
					cout << "Dealer's Hand: " << endl;

					if (!playerStandby && !playerBust)
					{
						cout << dealerFirst << endl;

						cout << "Dealer's Hand Value: " << dealerFirstVal << endl;
					}

					else
					{
						for (int i = 0; i < dealer_player.cards.size(); i++)
						{
							cout << dealer_player.cards[i];
						}

						cout << "Dealer's Hand Value: " << dealer_player.handValue << endl;
					}
				}

				if (playerStandby) // Player is on standby - Dealer is in action
				{
					cout << "PLAYER STANDBY" << endl;
					cout << "Player's Hand: " << endl;
					for (int i = 0; i < player.cards.size(); i++)
					{
						cout << player.cards[i];
					}
					cout << endl;
					cout << "Player's Hand Value: " << player.handValue << endl;
				}

				if (playerBust && !deal) // Player has busted
				{
					if (dealerBust) // Check to see if dealer has busted also. If dealer has busted then it is a tie so we push.
					{
						tieStatus = true;
						deal = true;
					}

					else // Player has bust and dealer has not bust so dealer wins
					{
						cout << "----------------------------------------------------" << endl;
						cout << "Player has bust" << endl;
						cout << "Dealer wins" << endl;
						calculateWinnings(user, potSize);
						deal = true;
					}
				}

				else if (dealerBust && !deal) // Dealer has bust and player wins
				{
					cout << "----------------------------------------------------" << endl;
					cout << "Dealer has bust" << endl;
					cout << "Player wins" << endl;
					calculateWinnings(user, potSize);
					deal = true;
				}

				else if (playerBlackjack && !deal) // Player has blackjack
				{
					if (dealerBlackjack) // Check if dealer has blackjack also. If dealer also has blackjack then it is a tie.
					{
						tieStatus = true;
						deal = true;
					}

					else // Player has blackjack and dealer does not have blackjack and player wins
					{
						cout << "----------------------------------------------------" << endl;
						cout << "Player has hit Blackjack" << endl;
						calculateWinnings(user, potSize);
						deal = true;
					}
				}

				else if (dealerBlackjack && !firstHand && !deal && playerStandby) // Dealer hits blackjack
				{
					cout << "----------------------------------------------------" << endl;
					cout << "Dealer has hit Blackjack" << endl;
					dealerWin(user, potSize);
					deal = true;
				}

				else if (tieStatus && !firstHand && !deal && playerStandby) // There exists a tie between the player and dealer
				{
					cout << "Player and Dealer have tied" << endl;
					cout << "Push" << endl;
					deal = true;
				}

				else if (dealerStandby && playerStandby && !deal) // Both player and dealer are standing
				{
					cout << "----------------------------------------------------" << endl;
					if (player_1 > dealer) // If player has a score higher than dealer then player has won
					{
						cout << "Player has won" << endl;
						calculateWinnings(user, potSize);
					}

					else // Dealer has won
					{
						cout << "Dealer has won" << endl;
						calculateWinnings(user, potSize);
					}

					deal = true;
				}


				else if (!deal && !playerStandby)
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

						else if (choice == 3)
						{
							cout << "Current chip stack: $" << chipStack << endl;
							cout << endl;
						}

						else if (choice == 4)
						{
							cout << "Current pot size: $" << potSize << endl;
							cout << endl;
						}
					}

				}

				firstHand = false;
			}

			cout << "PLAYER'S SCORE: " << player_1 << endl;
			cout << "DEALER'S SCORE: " << dealer << endl;
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

bool Blackjack::checkTie(int dealerHand, int playerHand)
{
	bool tie = false;
	if (dealerHand == playerHand)
	{
		tie = true;
	}

	return tie;
}

bool Blackjack::placeInsurance(Account *user)
{

	bool insurance = false;
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

	return insurance;
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
	bool running = true;

	while (running)
	{
		cout << "Not enough funds to place the bet" << endl;
		cout << "Please select an option" << endl;
		cout << "1. Place another bet" << endl;
		cout << "2. Buy more chips" << endl;
		cout << "3. Exit Blackjack" << endl;
		choice = userInput.inputValidate(1, 3);
		if (choice == 1)
		{
			buyChips(user);
			running = false;
			playAgain = false;
			return playAgain;
		}

		else if (choice == 2)
		{
			buyChips(user);
			running = false;
		}

		else
		{
			playAgain = true;
			running = false;
			return playAgain;
		}
	}
}

Blackjack::~Blackjack()
{
}