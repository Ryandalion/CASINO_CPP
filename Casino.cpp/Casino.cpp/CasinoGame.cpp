#include "CasinoGame.hpp"

CasinoGame::CasinoGame()
{


	Location *lobby_room = new CasinoLobby();
	Location *slots_room = new SlotsRoom();

	currentRoom = startingRoom = lobby_room;

	lobby_room->right = slots_room;
	slots_room->left = lobby_room;
}

void CasinoGame::startGame(Account *user)
{
	int userSelection = 0;
	bool running = false;

	while (running != true)
	{
		cout << "Please select an option" << endl;
		cout << "1. Travel" << endl;
		cout << "2. Play game in the room " << endl;
		cout << "3. Check Balance" << endl;
		cout << "4. View Map" << endl;
		cout << "5. Exit Casino" << endl;
		userSelection = validate(1, 5);

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
				cout << "Play game in the room" << endl;
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
				running = true;
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


	int userSelection = validate(1, count);

	return rooms[userSelection - 1];
}


int CasinoGame::validate(int min, int max)
{
	int temp = 0;

	cin >> temp;
	while (temp < min || temp > max || cin.fail())
	{
		if (cin.fail())
		{
			std::cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter a valid input: ";
		}

		else
		{
			cout << "Enter a valid input (" << min << " - " << max << "): ";
		}

		cin >> temp;
	}
	return temp;
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
	cout << "|   ____________  |_____              _______|  |               |   |" << endl;
	cout << "|  |            |______|             |__________|               |   |" << endl;
	cout << "|  |                                                            |   |" << endl;
	cout << "|  |  BLACKJACK           SLOTS ROOM                POKER ROOM  |   |" << endl;
	cout << "|  |    ROOM                              _____                 |   |" << endl;
	cout << "|  |              ______                 |     |                |   |" << endl;
	cout << "|  |             |     _|                |___  |________________|   |" << endl;
	cout << "|  |             |    |                      |                      |" << endl;
	cout << "|  |             |    |         BAR          |                      |" << endl;
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