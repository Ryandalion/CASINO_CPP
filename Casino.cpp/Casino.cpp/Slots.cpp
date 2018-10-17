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
		cout << "Press 1 to Spin!" << endl;
		cout << endl;
		cout << R"(	
                                                 +----------+
                                                 |          |
		+--------------------------------+----------+-------------------------------+
		|                                                                           |
		|  +---------------------------------------------------------------------+  |
		|  |                                                                     |  |
		|  |                                                                     |  |  +------+
		|  |                                                                     |  |  |      |
		|  |                                                                     |  |  |      |
		|  |                                                                     |  |  ++----++
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  |                                                                     |  |   |    |
		|  +---------------------------------------------------------------------+  +---++   |
		|                                                                           |    |   |
		|  +---------------------+ +---------------------+ +---------------------+  |    |   |
		|  |                     | |                     | |                     |  |    |   |
		|  |                     | |                     | |                     |  |    +---+
		|  |                     | |                     | |                     |  |    |
		|  +---------------------+ +---------------------+ +---------------------+  |    |
		|                                                                           |    |
		|                      +--------------------------------+                   +----+
		|                      |                                |                   |
		|                      |                                |                   |
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
			
		
			// Now we have to calculate the winning lines


			for (int i = 0; i < 3; i++)
			{
				for (int k = 0; k < 3; k++)
				{
					cout << slotDisplay[i][k] << " ";
				}
				cout << endl;
			}




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

Slots::~Slots()
{

}