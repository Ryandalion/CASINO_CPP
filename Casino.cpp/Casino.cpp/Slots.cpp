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

void Slots::setCredits(Account* user)
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

	startMachine(user, credits);
}


double Slots::getCredits()
{
	return credits;
}

//--------------------------------------------------------------SLOT FUNCTIONS------------------------------------------------------------------------------

void Slots::startMachine(Account *user, int credits)
{
	SlotMachine machine;
	Validate validate;
	bool play = true;

	machine.userName = user->getName(); // Set user's name to the machine name
	machine.creditAmount = credits;
	// ADD LUCK AND MISFORTUNE FEATURE IN THIS LINE

		cout << R"(
	 .----------------.  .----------------.  .----------------.  .----------------.  .----------------. 
	| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |
	| |    _______   | || |   _____      | || |     ____     | || |  _________   | || |    _______   | |
	| |   /  ___  |  | || |  |_   _|     | || |   .'    `.   | || | |  _   _  |  | || |   /  ___  |  | |
	| |  |  (__ \_|  | || |    | |       | || |  /  .--.  \  | || | |_/ | | \_|  | || |  |  (__ \_|  | |
	| |   '.___`-.   | || |    | |   _   | || |  | |    | |  | || |     | |      | || |   '.___`-.   | |
	| |  |`\____) |  | || |   _| |__/ |  | || |  \  `--'  /  | || |    _| |_     | || |  |`\____) |  | |
	| |  |_______.'  | || |  |________|  | || |   `.____.'   | || |   |_____|    | || |  |_______.'  | |
	| |              | || |              | || |              | || |              | || |              | |
	| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |
	 '----------------'  '----------------'  '----------------'  '----------------'  '----------------' 
	)" << endl;

	

	while (play) 
	{
		int activatedLines = 0;
		int betAmount = 0;
		int userOption = 0; // Variable to hold if user wants to spin again
		vector<string> slots = { "$","#","&","@","$","#","&","$","#","&","@","$","#","&","$","#","&","$","#","&","@","$","#","&","@","$","#","&","@", "#","#" };
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Random seed to shuffle the array of symbols
		int size = sizeof(slots); // Retrieve the size of the array

		cout << "---BET AMOUNT---" << endl;
		cout << "1) 1  CREDIT    " << endl;
		cout << "2) 5  CREDITS   " << endl;
		cout << "3) 10 CREDITS   " << endl;
		cout << "4) 50 CREDITS   " << endl;
		cout << "5) MAX CREDITS  " << endl; // MAX CREDITS IS 100 CREDITS
		cout << "ENTER BET AMOUNT: " << endl;
		betAmount = validate.inputValidate(1, 5);
		cout << endl;
		cout << "---------LINES---------" << endl;
		cout << "1 - 17 Lines Available" << endl;
		cout << "Please enter the number " << endl;
		cout << "of lines you would like " << endl;
		cout << "to play: ";
		activatedLines = validate.inputValidate(1, 17);
		cout << endl;
		cout << R"(	
                                                 +----------+
                                                 |          |
		+--------------------------------+----------+-------------------------------+
		|                                                                           |
		|  +---------------------------------------------------------------------+  |
		|  |                                                                     |  |
		|  |                     ^^^^^^PRESS 1 to SPIN^^^^^^                     |  |  +------+
		|  |                                                                     |  |  |      |
		|  |                              C++ SLOTS                              |  |  |      |
		|  |                                                                     |  |  ++----++
		|  |      ------SYMBOLS------               ------LINES------            |  |   |    |
		|  |        $  = 1x Multiplier                Lines 1 ~ 17               |  |   |    |
		|  |        #  = 2x Multiplier                                           |  |   |    |
		|  |        &  = 3x Multiplier                                           |  |   |    |
		|  |          Free Spins - @                                             |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                           ---PAYOUT---                              |  |   |    |
		|  |                     Lines * Symbol Multiplier                       |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  +---------------------------------------------------------------------+  +---++   |
		|                                                                           |    |   |
		|  +---------------------+ +---------------------+ +---------------------+  |    |   |
		|  |                     | |                     | |                     |  |    |   |
		|  |      BET AMOUNT     | |        LINES        | |       CREDITS       |  |    +---+
		|  |                     | |                     | |                     |  |    |
		|  +---------------------+ +---------------------+ +---------------------+  |    |
		|                                                                           |    |
		|                      +--------------------------------+                   +----+
		|                      |                                |                   |
		|                      |            WINNINGS            |                   |
		|                      |                                |                   |
		|                      +--------------------------------+                   |
		|                                                                           |
		|                                                                           |
		+---------------------------------------------------------------------------+




)";
		cin >> userOption;
		if (userOption == 1)
		{
			string slotDisplay[3][3];
			int numRandomize = rand() % 100 + 1; // Generate random number between 1 ~ 100. Use this variable to act as the number of times a shuffle of the array occurs
			for (int i = 0; i < numRandomize; i++)
			{
				std::shuffle(begin(slots), end(slots), std::default_random_engine(seed));
			}

			for (int i = 0; i < 3; i++) // Rows
			{
				for (int k = 0; k < 3; k++) // Columns
				{
					int selection = rand() % slots.capacity(); // Randomize the element it picks from. Use the vector's size as a max for the random number generator
					slotDisplay[i][k] = slots[selection]; // Retrieve the element and the randomized index inside slots vector and place into the 2d array
					slots.erase(slots.begin() + selection); // Erase the element that was found at the index so it does not repeat
					slots.shrink_to_fit(); // After removal of element, shrink the vector to resize it. This will also update the vector's capacity so it can retrieve a value within range
				}
			} // **Important Note: The vector will be reset and be restored to all original values after all symbols are placed on the screen ** 

			int winnings = 0;

			for (int i = 0; i < 3; i++)
			{
				for (int k = 0; k < 3; k++)
				{
					cout << slotDisplay[i][k] << " ";
				}
				cout << endl;
			}

			if (activatedLines <= 3)
			{
				winnings += threeLines(slotDisplay, activatedLines);
			}

			else if (activatedLines > 3 && activatedLines <= 5)
			{
				winnings += threeLines(slotDisplay, activatedLines);
				winnings += fiveLines(slotDisplay, activatedLines);
			}

			else if (activatedLines > 5 && activatedLines <= 7)
			{
				winnings += threeLines(slotDisplay, activatedLines);
				winnings += fiveLines(slotDisplay, activatedLines);
				winnings += sixLines(slotDisplay, activatedLines);
			}

			else if (activatedLines > 7 && activatedLines <= 9)
			{
				winnings += threeLines(slotDisplay, activatedLines);
				winnings += fiveLines(slotDisplay, activatedLines);
				winnings += sixLines(slotDisplay, activatedLines);
				winnings += eightLines(slotDisplay, activatedLines);
			}

			else if (activatedLines > 9 && activatedLines <= 11)
			{
				winnings += threeLines(slotDisplay, activatedLines);
				winnings += fiveLines(slotDisplay, activatedLines);
				winnings += sixLines(slotDisplay, activatedLines);
				winnings += eightLines(slotDisplay, activatedLines);
				winnings += tenLines(slotDisplay, activatedLines);
			}

			else if (activatedLines > 11 && activatedLines <= 13)
			{
				winnings += threeLines(slotDisplay, activatedLines);
				winnings += fiveLines(slotDisplay, activatedLines);
				winnings += sixLines(slotDisplay, activatedLines);
				winnings += eightLines(slotDisplay, activatedLines);
				winnings += tenLines(slotDisplay, activatedLines);
				winnings += twelveLines(slotDisplay, activatedLines);
			}

			else if (activatedLines > 13 && activatedLines <= 15)
			{
				winnings += threeLines(slotDisplay, activatedLines);
				winnings += fiveLines(slotDisplay, activatedLines);
				winnings += sixLines(slotDisplay, activatedLines);
				winnings += eightLines(slotDisplay, activatedLines);
				winnings += tenLines(slotDisplay, activatedLines);
				winnings += twelveLines(slotDisplay, activatedLines);
				winnings += fourteenLines(slotDisplay, activatedLines);
			}

			else if (activatedLines > 15 && activatedLines <= 17)
			{
				winnings += threeLines(slotDisplay, activatedLines);
				winnings += fiveLines(slotDisplay, activatedLines);
				winnings += sixLines(slotDisplay, activatedLines);
				winnings += eightLines(slotDisplay, activatedLines);
				winnings += tenLines(slotDisplay, activatedLines);
				winnings += twelveLines(slotDisplay, activatedLines);
				winnings += fourteenLines(slotDisplay, activatedLines);
				winnings += sixteenLines(slotDisplay, activatedLines);
			}

			cout << winnings << endl;

		}

		cout << "Would you like to spin again?" << endl;
		cout << "1. Spin again!" << endl;
		cout << "2. Exit" << endl;
		userOption = validate.inputValidate(1, 2);
		if (userOption == 1)
		{
			play = true;
		}

		else if (userOption == 2)
		{
			play = false;
		}

	}

}

double Slots::threeLines(string reel[][3], int lines)
{
	string symbol[4] = { "$", "#","&", "@" };
	int winnings = 0;
	double test = 0;
	int i, k, j = 0;

	if (lines == 1) // ONLY ONE LINE ACTIVATED
	{
		cout << "LINE 1 ACTIVATED" << endl;
		for (i = 0; i < 4; i++)
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i])
			{
				cout << "WINNER - 3 in a row" << endl;
			}
		}

	}

	else if (lines == 2) // ONLY TWO LINES ACTIVATED
	{
		cout << "LINE 2 ACTIVATED" << endl;
		for (i = 0; i < 4; i++)
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i])
			{
				cout << "WINNER ON LINE 1" << endl;
				winnings += 100;
				if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i])
				{
					cout << "WINNER ON LINE 2 in addition to line 1" << endl;
					winnings += 200;
				}
			}

			else if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i])
			{
				cout << "WINNER ON LINE 2 ONLY" << endl;
				winnings += 100;
			}
		}
	}

	else if (lines == 3) // THREE LINES ACTIVATED
	{
		cout << "LINE 3 ACTIVATED" << endl;
		for (i = 0; i < 4; i++)
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // Line 1 winner
			{
				cout << "WINNER ON LINE 1" << endl;
				winnings += 100;
				if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // Line 1 and Line 2 winner
				{
					cout << "WINNER ON LINE 2 in addition to line 1" << endl;
					winnings += 200;

					if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // Line 1 and Line 2 and Line 3 winner
					{
						cout << "WINNER ON LINE 3 in addition to LINE 1 and LINE 2" << endl;
						winnings += 100;
					}
				}
			}

			else if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i] && reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // Line 1 and Line 3 winner
			{
				cout << "WINNER ON LINE 1 and LINE 3" << endl;
				winnings += 100;
			}

			else if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i] && reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // Line 2 and Line 3 winner
			{
				cout << "WINNER ON LINE 2 and LINE 3" << endl;
				winnings += 100;
			}

			else if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // Line 2 winner
			{
				cout << "WINNER ON LINE 2 ONLY" << endl;
				winnings += 100;
			}

			else if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // Line 3 winner
			{
				cout << "WINNER ON LINE 3 ONLY" << endl;
				winnings += 100;
			}
		}
		
	}

	return winnings;
}

double Slots::fiveLines(string reel[][3], int lines) // 3 ~ 5 lines activated
{
	return 5;
}


double Slots::sixLines(string reel[][3], int lines) // 6 ~ 7 lines activated
{
	return 5;
}

double Slots::eightLines(string reel[][3], int lines) // 8 ~ 9 lines activated
{
	return 5;
}

double Slots::tenLines(string reel[][3], int lines) // 10 ~ 11 lines activated
{
	return 5;
}

double Slots::twelveLines(string reel[][3], int lines) // 12 ~ 13 lines activated
{
	return 5;
}

double Slots::fourteenLines(string reel[][3], int lines) //14 ~ 16 lines activated
{
	return 5;
}

double Slots::sixteenLines(string reel[][3], int lines) // 16 ~ 17 lines activated
{
	return 5;
}

Slots::~Slots()
{

}