#include "CasinoGame.hpp"

CasinoGame::CasinoGame()
{
	Location *lobby_room = new CasinoLobby();
	Location *slots_room = new SlotsRoom();
	Location *poker_room = new PokerRoom();
	Location *blackjack_room = new BlackjackRoom();
	Location *bar_room = new Bar();

	currentRoom = startingRoom = lobby_room; // Current Room and Starting Room is the Casino lobby

	lobby_room->bottom = slots_room; // Going down from the lobby leads to slots room
	
	slots_room->left = blackjack_room; // Going left from slots room leads to Blackjack Tables
	slots_room->right = poker_room; // Going right from slots room leads to Poker room
	slots_room->bottom = bar_room; // Going down from slots room leads to bar
	slots_room->top = lobby_room; // Going up from slots room leads to Casino lobby

	blackjack_room->right = slots_room; // Going right from blackjack room leads slots room

	poker_room->left = slots_room; // Going left from poker room leads to slots room

	bar_room->top = slots_room; // Going up from bar room leads to slots room

}

void CasinoGame::startGame(Account *user)
{
	int userSelection = 0;
	bool running = false;
	Validate userInput;

	while (running != true)
	{
		cout << endl;
		cout << "Please select an option" << endl;
		cout << "1. Travel" << endl;
		cout << "2. Manage Loans" << endl;
		cout << "3. Check Balance" << endl;
		cout << "4. View Map" << endl;
		cout << "5. Exit Casino" << endl;
		userSelection = userInput.inputValidate(1, 5);

		switch (userSelection)
		{
			case 1:
			{
				cout << "TRAVEL TO LOCATION" << endl;
				currentRoom = travel();
				currentRoom->enter(user);
				break;
			}

			case 2:
			{
				int option = 0;
				cout << "MANAGE LOANS" << endl;
				cout << "1. Take out loan" << endl;
				cout << "2. Check loan balance" << endl;
				option = userInput.inputValidate(1, 2);
				if (option == 1)
				{
					user->borrowMoney(user);
				}
				else if (option == 2)
				{
					if(user->getUserLoanAmount(user))
					{
					}
					else
					{
						cout << "You do not have any active loans" << endl;
					}
				}
				break;
			}

			case 3:
			{
				cout << "Account Balance" << endl;
				cout << user->getUserBalance() << endl;
				break;
			}

			case 4:
			{
				cout << "PRINT MAP" << endl;
				printMap();
				break;
			}

			case 5:
			{
				user->saveUserData(user);
				running = true;
				break;
			}

		}
	}


}

Location *CasinoGame::travel()
{
	int count = 0;

	std::vector<Location*> rooms;

	if (currentRoom->top != nullptr)
	{
		rooms.push_back(currentRoom->top);
		cout << ++count << ". " << currentRoom->top->getRoomName() << endl;
	}

	if (currentRoom->bottom != nullptr)
	{
		rooms.push_back(currentRoom->bottom);
		cout << ++count << ". " << currentRoom->bottom->getRoomName() << endl;
	}

	if (currentRoom->left != nullptr)
	{
		rooms.push_back(currentRoom->left);
		cout << ++count << ". " << currentRoom->left->getRoomName() << endl;
	}

	if (currentRoom->right != nullptr)
	{
		rooms.push_back(currentRoom->right);
		cout << ++count << ". " << currentRoom->right->getRoomName() << endl;
	}


	int userSelection = userInput.inputValidate(1, count);

	return rooms[userSelection - 1];
}

void CasinoGame::printMap()
{

	cout << "=====================================================================" << endl;
	cout << "|                          CASINO MAP                               |" << endl;
	cout << "=====================================================================" << endl;
	cout << "|                                                                   |" << endl;
	cout << "|                  __________________________                       |" << endl;
	cout << "|                 |                          |   _______________    |" << endl;
	cout << "|                 |          LOBBY           |  |               |   |" << endl;
	cout << "|                 |                          |  |               |   |" << endl;
	cout << "|   ____________  |____               _______|  |               |   |" << endl;
	cout << "|  |            |______|             |__________|               |   |" << endl;
	cout << "|  |                                                            |   |" << endl;
	cout << "|  |  BLACKJACK           SLOTS ROOM                POKER ROOM  |   |" << endl;
	cout << "|  |    ROOM                           _________                |   |" << endl;
	cout << "|  |              ______              |         |               |   |" << endl;
	cout << "|  |             |     _|             |_______  |_______________|   |" << endl;
	cout << "|  |             |    |                      |                      |" << endl;
	cout << "|  |             |    |      BAR             |                      |" << endl;
	cout << "|  |_____________|    |______________________|                      |" << endl;
	cout << "|                                                                   |" << endl;
	cout << "|                                                                   |" << endl;
	cout << "=====================================================================" << endl;
	cout << endl;
	cout << "Press any button to close map" << endl;
	cin.ignore();
	cin.ignore();
}

CasinoGame::~CasinoGame()
{

}