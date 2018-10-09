#include "Game.hpp"

Game::Game()
{
	Area *SlotsArea = new SlotsRoom();
	Area *CasinoLobby = new Lobby();
	Area *PokerArea = new PokerRoom();
	Area *BlackJackTable = new BlackjackRoom();

	currentRoom = startRoom = CasinoLobby;

	CasinoLobby->bottom = SlotsArea;
	CasinoLobby->right = BlackJackTable;
	
	SlotsArea->top = CasinoLobby;
	SlotsArea->right = PokerArea;

	PokerArea->top = BlackJackTable;
	PokerArea->left = SlotsArea;

	BlackJackTable->left = CasinoLobby;
	BlackJackTable->bottom = PokerArea;
}

void Game::startGame(Account *user)
{
	int choice = 0;
	bool running = false;
	while (running != true)
	{

		userChoose(choice);

		if (choice == 1)
		{
			cout << "Travel to which room?" << endl;
			currentRoom = travel();
		}

		else if (choice == 2)
		{
			currentRoom->playGame(user);
		}

		else if (choice == 3)
		{
			cout << "Current Balance: $" << user->getUserBalance();
		}

		else if (choice == 4)
		{
			user->buyDrink();
		}

		else if (choice == 5)
		{
			printArea();
		}

		else if (choice == 6)
		{
			running = true;
			exit(1);
		}
	}
}


void Game::printArea()
{
	cout << endl;
	cout << "=======================================================================" << endl;
	cout << "=                         CASINO MAP                                  =" << endl;
	cout << "=---------------------------------------------------------------------=" << endl;
	cout << "=       _____________                   ____________________          =" << endl;
	cout << "=      |             |_________________|                    |         =" << endl;
	cout << "=      |    LOBBY                             BLACKJACK     |         =" << endl;
	cout << "=      |             __________________         ROOM        |         =" << endl;
	cout << "=      |____        |                  |_____          _____|         =" << endl;
	cout << "=       ___|        |________           _____|        |______         =" << endl;
	cout << "=      |                     |         |                     |        =" << endl;
	cout << "=      |                     |_________|                     |        =" << endl;
	cout << "=      |     SLOTS ROOM                       POKER ROOM     |        =" << endl;
	cout << "=      |                      _________                      |        =" << endl;
	cout << "=      |_____________________|         |_____________________|        =" << endl;
	cout << "=                                                                     =" << endl;
	cout << "=======================================================================" << endl;

}


int Game::userChoose(int &choice)
{
	cout << "What would you like to do?" << endl;
	cout << "1. Go to a different room" << endl;
	cout << "2. Play the game in the room" << endl;
	cout << "3. Check Account Balance" << endl;
	cout << "4. Buy a beverage" << endl;
	cout << "5. Print Map" << endl;
	cout << "6. Exit Casino" << endl;
	cin >> choice;
	return choice;
}

Area * Game::travel()
{
	std::vector<Area*> roomsNearMe;
	int count = 0;

	if (currentRoom->bottom != nullptr)
	{
		roomsNearMe.push_back(currentRoom->bottom);
		 cout << ++count << ". " << currentRoom->bottom->getRoomName() << endl;
	}
	if (currentRoom->top != nullptr)
	{
		roomsNearMe.push_back(currentRoom->top);
		cout << ++count << ". " << currentRoom->top->getRoomName() << endl;
	}
	if (currentRoom->left != nullptr)
	{
		roomsNearMe.push_back(currentRoom->left);
		cout << ++count << ". " << currentRoom->left->getRoomName() << endl;
	}
	if (currentRoom->right != nullptr)
	{
		roomsNearMe.push_back(currentRoom->right);
		cout << ++count << ". " << currentRoom->right->getRoomName() << endl;
	}

	int choice = validateInput(1, count);
	return roomsNearMe[choice - 1];

}

int Game::validateInput(int min, int max)
{
	int tmp;

	cin >> tmp;

	while (tmp < min || tmp > max || cin.fail())
	{
		if (cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(256, '\n');

			cout << "Enter a valid input: ";
		}

		else
			cout << "Enter a valid input (" << min << " - " << max << "): ";

	
		cin >> tmp;
	}


	return tmp;
}

Game::~Game()
{

}