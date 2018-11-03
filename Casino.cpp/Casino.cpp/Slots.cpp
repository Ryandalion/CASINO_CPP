#include "Slots.hpp"


Slots::Slots()
{

}

void Slots::startSlots(Account *user)
{
	cout << "  Hello " << user->getName() << endl;
	cout << endl;
	startMachine(user);
}

double Slots::getCredits()
{
	return credits;
}

//--------------------------------------------------------------SLOT FUNCTIONS------------------------------------------------------------------------------

void Slots::startMachine(Account *user)
{
	SlotMachine machine;
	Validate validate;
	bool play = true;

	machine.userName = user->getName(); // Set user's name to the machine name
	machine.creditAmount = 0;
	double creditUpdate = 0;

	while (play)
	{
		bool status = false; // Controls second while loop. This loop is responsible for printing the slot machine's main menu

		int userOption = 0; // Variable to hold if user wants to spin again
		int slotOption = 0;

		int *activatedLines;
		int lines = 0;
		activatedLines = &lines;

		double *credit;
		credit = &creditUpdate;

		int betAmount = 0; // Bet amounts = 1000, 500, 100, 50, 10

		bool running = true; // Bool indicator for main while loop

		machine.creditAmount = creditUpdate;

		while(running)
		{
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

			bool status = true;
			bool betFlag = false;
			bool lineFlag = false;

			while (status)
			{
			cout << " ---BET AMOUNT---                --------MENU---------          ----WINNING SYMBOLS----         ----LINE----" << endl;
			cout << "   5 CREDIT                       1. Spin the Wheel!                       $                    1 - 17 LINES" << endl;
			cout << "  10 CREDITS                      2. MAX BET                               #                                " << endl;
			cout << "  25 CREDITS                      3. View Lines Table                      &                                " << endl;
			cout << "  50 CREDITS                      4. Set Bet Amount                        @                                " << endl;
			cout << "  75 CREDITS                      5. Set Number of Lines                                                    " << endl;
			cout << " 100 CREDITS                      6. Enter Credits                                                          " << endl;
			cout << " 250 CREDITS                      7. Exit                                                                   " << endl;
			cout << " 500 CREDITS                                                                                                " << endl;
			cout << endl;
			cout << "                                                CREDITS: " << machine.creditAmount << endl;
			cout << "Please enter an option: ";
			
			slotOption = 0;
			userOption = 0;
	
			slotOption = validate.inputValidate(1, 8);

			
				if (slotOption == 1) // Spin the wheel
				{
					if (betFlag && lineFlag)
					{
						int bet_amount[] = { 5, 10, 25, 50, 75, 100, 250, 500};

						if (credits < bet_amount[betAmount-1])
						{
							cout << "Not enough credits" << endl;
						}
						else
						{
							userOption = 1;
							status = false;
							running = false;
						}
					}

					else if (betFlag && !lineFlag)
					{
						cout << "Please enter the number of lines you wish to play" << endl;
						cout << endl;
					}

					else if (lineFlag && !betFlag)
					{
						cout << "Please enter a bet amount you wish to play" << endl;
						cout << endl;
					}

					else if (!lineFlag && !betFlag)
					{
						cout << "Please enter the bet amount and the number of lines first" << endl;
						cout << endl;
					}

				}

				else if (slotOption == 2) // Max bet activation
				{
					cout << "MAX BET ACTIVATED" << endl;
					cout << "Playing 17 lines at 500 credits per spin" << endl;
					*activatedLines = 17;
					betAmount = 7;
					betFlag = true;
					lineFlag = true;
				}

				else if (slotOption == 3) // Display lines table
				{
					displayLines();
					slotOption = 0;
				}

				else if (slotOption == 4)
				{
					cout << "-- BET AMOUNTS --" << endl;
					cout << "1.   5 Credits   " << endl;
					cout << "2.  10 Credits   " << endl;
					cout << "3.  25 Credits   " << endl;
					cout << "4.  50 Credits   " << endl;
					cout << "5.  75 Credits   " << endl;
					cout << "6. 100 Credits   " << endl;
					cout << "7. 250 Credits   " << endl;
					cout << "8. 500 Credits   " << endl;
					cout << "Select bet amount: " << endl;
					betAmount = validate.inputValidate(1, 8);
					cout << "BET AMOUNT: " << betAmount << endl;
					betFlag = true;
				}

				else if (slotOption == 5)
				{
					cout << "----- LINES -----" << endl;
					cout << "Enter the number ";
					cout << "of lines (1 - 17): ";
					*activatedLines = validate.inputValidate(1, 17);
					cout << "LINES: " << *activatedLines << endl;
					lineFlag = true;
				}

				else if (slotOption == 6)
				{
					int creditSelection = 0;
					cout << "Select the number of credits you wish to put into the machine  " << endl;
					cout << " ______________________________________              " << endl;
					cout << "|               CREDITS                |             " << endl;
					cout << "|======================================|             " << endl;
					cout << "|       1. $1 = 100 Credits            |             " << endl;
					cout << "|       2. $10 = 1000 Credits          |             " << endl;
					cout << "|       3. $50 = 5000 Credits          |             " << endl;
					cout << "|       4. $100 = 10,000 Credits       |             " << endl;
					cout << "|       5. $500 = 50,000 Credits       |             " << endl;
					cout << "|       6. $1,000 = 100,000 Credits    |             " << endl;
					cout << "|______________________________________|             " << endl;
					
					creditSelection = validate.inputValidate(1, 6);

					double creditLine[6] = { 100, 1000, 5000, 10000, 50000, 100000 }; // Array that holds the credit amounts
					double deductAmount[6] = { -1, -10, -50, -100, -500, -1000 }; // Array that holds the cash amount to deduct from user's balance
					
					if (user->getUserBalance() <= (-1 * (deductAmount[creditSelection - 1])))
					{
						cout << "You do not have enough money" << endl;
					}

					else
					{
						user->setUserBalance(deductAmount[creditSelection - 1]);
						credits = creditLine[creditSelection - 1];
						cout << credits << " CREDITS ADDED" << endl;
						machine.creditAmount += credits;
					}

				}

				else if (slotOption == 7) // User chooses to exit machine
				{
					running = false;
					status = false;
					userOption = 2;

				}
			}
		}

		cout << endl;

		if (userOption == 1) // This executes the function to spin the reel
		{
			bool respin = true;
			vector<string> slots; 
			double bet_amount[] = { 5, 10, 25, 50, 75, 100, 250, 500};
			while (respin)
			{
				double creditBet = 0;
				double betMultiplier = 0;

				cout << "CREDITS BEFORE SPIN " << machine.creditAmount<< endl;
				cout << "------------------ SPIN -------------------" << endl;


				cout << endl;

				if (bet_amount[betAmount - 1] <= 50)
				{
					betMultiplier = (bet_amount[betAmount - 1] / (*activatedLines / 10));
					creditBet = ((bet_amount[betAmount - 1] / 100) * (*activatedLines));
				}

				else
				{
					betMultiplier = (bet_amount[betAmount - 1] / (*activatedLines / 10));
					creditBet = ((bet_amount[betAmount - 1] / 100) * (*activatedLines));
				}


				if ((machine.creditAmount / 10) < bet_amount[betAmount - 1])
				{
					int addCredit = 0;
					cout << "You do not have enough credits" << endl;
					cout << "Would you like to enter more credits?" << endl;
					cout << "1. Yes" << endl;
					cout << "2. No" << endl;
					addCredit = validate.inputValidate(1, 2);
					switch (addCredit)
					{
					case(1):
						respin = false;
						machine.creditAmount = credits;
						break;
					case(2):
						machine.creditAmount = credits;
						respin = false;
						play = false;
						break;
					}

				}

				else if((machine.creditAmount) > bet_amount[betAmount - 1])
				{
					cout << "BET MULTIPLIER = " << betMultiplier << endl;
					cout << "CREDIT BET = " << creditBet << endl;

					cout << "BET AMOUNT: $" << std::setprecision(2) << std::fixed << creditBet << endl;
					cout << "LINES IN PLAY: " << *activatedLines << endl;
					cout << "BALANCE: $" << ((machine.creditAmount / 100)) << endl;
					cout << endl;


					cout << "MACHINE CREDIT AMOUNT " << machine.creditAmount << endl;
					switch (betAmount) // Deduct bet amount from the slot machine; @param betAmount set by user
					{
					case (1):
					{
						machine.creditAmount -= ((5) * (*activatedLines));
						break;
					}

					case(2):
					{
						machine.creditAmount -= ((10) * (*activatedLines));
						break;
					}

					case(3):
					{
						machine.creditAmount -= ((25) * (*activatedLines));
						break;
					}

					case(4):
					{
						machine.creditAmount -= ((50) * (*activatedLines));
						break;
					}

					case(5):
					{
						machine.creditAmount -= ((75) * (*activatedLines));
						break;
					}

					case(6):
					{
						machine.creditAmount -= ((100) * (*activatedLines));
						break;
					}

					case(7):
					{
						machine.creditAmount -= ((250) * (*activatedLines));
						break;
					}

					case(8):
					{
						machine.creditAmount -= ((500) * (*activatedLines));
						break;
					}

					default:
						break;
					}


					if (betAmount == 1) // 5 CREDITS - 23% ODDS
					{
						string symbols[] = {"$","#","&","@","$","#","&","^","@","$","#","&","@","$","#","&","@","$","^","#","&","@","$","#","&","@","$","#","&","@"};

						for (int i = 0; i < 30; i++)
						{
							slots.push_back(symbols[i]);
						}
					}

					else if (betAmount == 2) // 10 CREDITS - 20% ODDS
					{
						string symbols[] = { "^","$","#","&","@","$","^","^","#","&","@","$","#","&","@","$","#","&","@","$","#","^","&","@","$","#","&","@","^","^" };

						for (int i = 0; i < 30; i++)
						{
							slots.push_back(symbols[i]);
						}
					}

					else if (betAmount == 3) // 25 CREDITS - 16.67% ODDS
					{
						string symbols[] = { "$","#","&","@","^","^","^","^","^","$","#","&","@", "$","#","&","@", "$","#","&","@","$","#","&","@", "^","^","^","^","^"};

						for (int i = 0; i < 30; i++)
						{
							slots.push_back(symbols[i]);
						}
					}

					else if (betAmount == 3) // 50 CREDITS - 13.45% ODDS
					{
						string symbols[] = { "$","#","&","@","^","^","^","^","$","#","&","@","$","#","&","@","$","#","&","@","^","^","^","^","^","^","^","^","#","$"};
						for (int i = 0; i < 30; i++)
						{
							slots.push_back(symbols[i]);
						}
					}

					else if (betAmount == 4) // 75 CREDITS - 13.45% ODDS
					{
						string symbols[] = {"$","#","&","@","^","^","^","^","$","#","&","@","$","#","&","@","$","#","&","@","^","^","^","^","^","^","^","^","#","$"};
						for (int i = 0; i < 30; i++)
						{
							slots.push_back(symbols[i]);
						}
					}

					else if (betAmount == 5) // 100 CREDITS - 13.28% ODDS
					{
						string symbols[] = {"$","#","&","@","^","^","^","^","$","#","&","@","$","#","&","@","$","#","&","@","^","^","^","^","^","^","^","^","^","^"};
						for (int i = 0; i < 30; i++)
						{
							slots.push_back(symbols[i]);
						}
					}

					else if (betAmount == 6) // 250 CREDITS - 3% ODDS
					{
						string symbols[] = { "$","#","&","@","^","^","^","^","^","^","$","#","&","@","^","^","^","^","^","^","$","#","&","@","^","^","^","^","^","^"};
						for (int i = 0; i < 30; i++)
						{
							slots.push_back(symbols[i]);
						}
					}

					else if (betAmount == 7) // 500 CREDITS - 3% ODDS
					{
						string symbols[] = { "$","#","&","@","^","^","^","^","^","^","$","#","&","@","^","^","^","^","^","^","$","#","&","@","^","^","^","^","^","^" };
						for (int i = 0; i < 30; i++)
						{
							slots.push_back(symbols[i]);
						}
					}


					string *symbol;
					string symbolSet[4] = { "$", "#","&", "@" };
					symbol = symbolSet;

					unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Random seed to shuffle the array of symbols
					int size = sizeof(slots); // Retrieve the size of the array

					string **slotDisplay; // 2D array that we will pass as parameters for line checking
					slotDisplay = new string*[3];
					for (int i = 0; i != 3; i++)
					{
						slotDisplay[i] = new string[3];
					}


					int numRandomize = rand() % 100 + 1; // Generate random number between 1 ~ 100. Use this variable to act as the number of times a shuffle of the array occurs
					for (int i = 0; i < numRandomize; i++)
					{
						std::shuffle(begin(slots), end(slots), std::default_random_engine(seed));
					}

					for (int i = 0; i < 3; i++) // Rows
					{
						for (int k = 0; k < 3; k++) // Columns
						{
							int selection = rand() % slots.size(); // Randomize the element it picks from. Use the vector's size as a max for the random number generator
							slotDisplay[i][k] = slots[selection]; // Retrieve the element and the randomized index inside slots vector and place into the 2d array
							slots.erase(slots.begin() + selection); // Erase the element that was found at the index so it does not repeat
							slots.shrink_to_fit(); // After removal of element, shrink the vector to resize it. This will also update the vector's capacity so it can retrieve a value within range
						}
					}

					for (int i = 0; i < 3; i++)
					{
						for (int k = 0; k < 3; k++)
						{
							cout << slotDisplay[i][k] << " ";
						}
						cout << endl;
					}

					double winnings = 0; // Variable that will hold the winnings from each line check

					if (*activatedLines <= 3)
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 3 && *activatedLines <= 5)
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);					// Line greater than or equal to 3
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 5 && *activatedLines <= 7)
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 7 && *activatedLines <= 9)
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings += eightLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 9 && *activatedLines <= 11)
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings += eightLines(symbol, slotDisplay, activatedLines);
						winnings += tenLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 11 && *activatedLines <= 13)
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings += eightLines(symbol, slotDisplay, activatedLines);
						winnings += tenLines(symbol, slotDisplay, activatedLines);
						winnings += twelveLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 13 && *activatedLines <= 15)
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings += eightLines(symbol, slotDisplay, activatedLines);
						winnings += tenLines(symbol, slotDisplay, activatedLines);
						winnings += twelveLines(symbol, slotDisplay, activatedLines);
						winnings += fourteenLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 15 && *activatedLines <= 17)
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings += eightLines(symbol, slotDisplay, activatedLines);
						winnings += tenLines(symbol, slotDisplay, activatedLines);
						winnings += twelveLines(symbol, slotDisplay, activatedLines);
						winnings += fourteenLines(symbol, slotDisplay, activatedLines);
						winnings += sixteenLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

		
					if (winnings > 0 && user->getUserLuck() > 0 && user->getUserMisfortune() > 0)
					{
						int bonusActivation = rand() % 2;

						if (bonusActivation == 0)
						{
							int luckAmount = user->getUserLuck(); // Retrieve user's luck 
							int misfortuneAmount = user->getUserMisfortune(); // Retrieve user's misfortune
							int symbolTotal = (luckAmount + misfortuneAmount); // Compute the sum of luck and misfortune. We will use this to fill sum to create a vector of size sum and select a symbol from the array which will execute a correspsonding activator

							vector<char> symbolArray;

							int j, k, n;
							j = k = n = 0;
							for (j = 0; j < luckAmount; j++) // LUCK represented by zeroes
							{
								symbolArray.push_back('x');
							}

							for (k = 0; k < misfortuneAmount; k++) // MISFORTUNE represented by ones
							{
								symbolArray.push_back('o');
							}

							std::random_shuffle(std::begin(symbolArray), std::end(symbolArray)); // Shuffle the symbols inside vector

							int selectNum = rand() % symbolTotal; // Generate a random number that we will use to pull a random symbol from the vector

							char symbolPulled = symbolArray[selectNum]; // Assign randomly pulled symbol to symbolPulled variable


							if (symbolPulled == 'x') // If the symbol x is pulled we activate luck
							{

								float bonusFactor = 0;
								float luckBonus[] = { 2, 3, 3.5 };
								int luckyDraw = rand() % 3;
								int megaKey = rand() % 3;
								bonusFactor = luckBonus[luckyDraw];
								cout << "It must be your lucky day! You have won an additional " << (bonusFactor * winnings) * 10 << " credits!" << endl;
								winnings += (bonusFactor * winnings);
							}


							else if (symbolPulled == 'o') // If the symbol o is pulled we activate misfortune
							{
								float bonusFactor = 0;
								float misfortuneBonus[] = { -.05, -.07, -.1 };
								int misfortuneDraw = rand() % 3;
								bonusFactor = misfortuneBonus[misfortuneDraw];

								cout << "Uh oh! Today might no be your lucky day. You have just lost " << (bonusFactor * winnings) * 10 << " credits from your winnings!" << endl;

								winnings += (bonusFactor * winnings);
							}

							winnings *= 10;
							machine.creditAmount += winnings; // Add the winnings to the credit amount
							credits = machine.creditAmount;
							symbolArray.clear(); // Clear vector
						}
					}
					

					else if (winnings > 0)
					{
						winnings *= 10;
						machine.creditAmount += winnings; // Add the winnings to the credit amount
						credits = machine.creditAmount;
					}

					delete[] slotDisplay; // Delete 2d Array

					cout << endl;
					cout << "WIN : $" << (winnings / 100) << endl;
					cout << "-------------------------------------------" << endl;

					cout << "Would you like to spin again?" << endl;
					cout << "1. Spin again!" << endl;
					cout << "2. Slot Main Menu" << endl;
					cout << "3. Exit" << endl;
					int playAgain = 0;
					playAgain = validate.inputValidate(1, 3);
					
					if (playAgain == 1 && machine.creditAmount < bet_amount[betAmount - 1])
					{
						int addCredit = 0;
						cout << "You do not have enough credits" << endl;
						cout << "Would you like to enter more credits?" << endl;
						cout << "1. Yes" << endl;
						cout << "2. No" << endl;
						addCredit = validate.inputValidate(1, 2);
						switch (addCredit)
						{
						case(1):
							respin = false;
							break;
						case(2):
							respin = false;
							break;
						}
					}

					else if (playAgain == 1)
					{
						creditUpdate = machine.creditAmount;
					}

					
					else if (playAgain == 2)
					{
						respin = false;
						symbol = NULL; // Leave no dangling pointers
						delete symbol; // Delete symbol pointer
					}
					
				
					else if (playAgain == 3)
					{
						creditUpdate = machine.creditAmount;
						cout << "CREDIT UPDATE AMOUNT " << creditUpdate << endl;
						exitMachine(user, credit); // User chooses to exit machine so we convert their credits into cash
						running = false;
						respin = false;
						play = false;
						symbol = NULL; // Leave no dangling pointers
						credit = NULL;
						delete symbol; // Delete symbol pointer
						delete credit;
					}
				}
			}
		}

		else if (userOption == 2)
		{
			running = false;
			play = false;
			cout << "CREDIT UPDATE AMOUNT WHEN USER OPTION == 2 " << creditUpdate<< endl;
			credits = machine.creditAmount;
			exitMachine(user, credit); // User chooses to exit machine so we convert their credits into cash
			credit = NULL;
			delete credit;
		}
		}

	}


double Slots::threeLines(string *symbol, string **reel, int *lines)
{
	
	double winnings = 0;
	double test = 0;
	int i, k, j = 0;

	if (*lines == 1) // ONLY ONE LINE ACTIVATED
	{
		for (i = 0; i < 4; i++)
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i])
			{
				cout << "WINNER ON LINE 1" << endl;
				winnings ++;
			}
		}

	}

	else if (*lines == 2) // ONLY TWO LINES ACTIVATED
	{
		for (i = 0; i < 4; i++)
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i])
			{
				cout << "WINNER ON LINE 1" << endl;
				winnings++;
				if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i])
				{
					cout << "WINNER ON LINE 2 in addition to line 1" << endl;
					winnings++;
				}
			}

			else if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i])
			{
				cout << "WINNER ON LINE 2 ONLY" << endl;
				winnings++;
			}
		}
	}

	else if (*lines >= 3) // THREE LINES ACTIVATED
	{
		for (i = 0; i < 4; i++)
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // Line 1 winner
			{
				cout << "WINNER ON LINE 1" << endl;
				winnings++;
				if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // Line 1 and Line 2 winner
				{
					cout << "WINNER ON LINE 2 in addition to line 1" << endl;
					winnings++;

					if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // Line 1 and Line 2 and Line 3 winner
					{
						cout << "WINNER ON LINE 3 in addition to LINE 1 and LINE 2" << endl;
						winnings++;
					}
				}
			}

			else if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i] && reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // Line 1 and Line 3 winner
			{
				cout << "WINNER ON LINE 1 and LINE 3" << endl;
				winnings++;
			}

			else if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i] && reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // Line 2 and Line 3 winner
			{
				cout << "WINNER ON LINE 2 and LINE 3" << endl;
				winnings++;
			}

			else if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // Line 2 winner
			{
				cout << "WINNER ON LINE 2 ONLY" << endl;
				winnings++;
			}

			else if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // Line 3 winner
			{
				cout << "WINNER ON LINE 3 ONLY" << endl;
				winnings++;
			}
		}
		
	}

	return winnings;
}

double Slots::fiveLines(string *symbol, string **reel, int *lines) // 3 ~ 5 lines activated
{
	double winnings = 0;
	for (int i = 0; i < 4; i++)
	{
		if (*lines == 4)
		{
			if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i]) // Line 4
			{
				cout << "WINNER LINE 4" << endl;
				winnings++;
			}
		}

		else if (*lines > 4)
		{
			if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i]) // Line 4
			{
				cout << "WINNER LINE 4" << endl;
				winnings++;

				if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i])
				{
					cout << "WINNER LINE 4 and 5" << endl;
					winnings++;;
				}
			}

			else if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i])
			{
				cout << "WINNER LINE 5" << endl;
				winnings++;;
			}
		}

		return winnings;
	}
}


double Slots::sixLines(string *symbol, string **reel, int *lines) // 6 ~ 7 lines activated
{
	double winnings = 0;

	for (int i = 0; i < 4; i++)
	{
		if (*lines == 6) // SIX LINES ACTIVATED
		{
			cout << "SIX LINES ACTIVATED" << endl;
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i])
			{
				cout << "WINNER LINE 6" << endl;
				winnings++;;
			}

		}

		else if (*lines > 6) // LINE SIX AND LINE SEVEN ACTIVATED
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i])
			{
				cout << "WINNER LINE 6" << endl;
				winnings++;

				if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i])
				{
					cout << "WINNER LINE 7" << endl;
					winnings++;
				}
			}

			else if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i])
			{
				cout << "WINNER LINE 7" << endl;
				winnings++;
			}
		}
	}

	return winnings;
}

double Slots::eightLines(string *symbol, string **reel, int *lines) // 8 ~ 9 lines activated
{
	double winnings = 0;

	for (int i = 0; i < 4; i++)
	{
		if (*lines == 8) // LINE 8 ACTIVATED
		{
			cout << "LINE 8 ACTIVATED" << endl;
			if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i])
			{
				cout << "WINNER LINE 8" << endl;
				winnings++;
			}
		}

		else if (*lines > 8)
		{
			if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i])
			{
				cout << "WINNER LINE 8" << endl;
				winnings++;

				if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i])
				{
					cout << "WINNER LINE 8 and LINE 9" << endl;
					winnings++;
				}
			}

			else if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i])
			{
				cout << "WINNER LINE 9" << endl;
				winnings++;
			}
		}

	}

	return winnings;
}

double Slots::tenLines(string *symbol, string **reel, int *lines) // 10 ~ 11 lines activated
{
	double winnings = 0;

	for (int i = 0; i < 4; i++)
	{
		if (*lines == 10) // TEN LINES ACTIVATED
		{
			if (reel[1][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i])
			{
				cout << "WINNER LINE 10" << endl;
				winnings++;
			}
		}

		else if (*lines > 10) // 11 LINES ACTIVATED
		{
			if (reel[1][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i])
			{
				cout << "WINNER LINE 10" << endl;
				winnings++;

				if (reel[1][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i])
				{
					cout << "WINNER LINE 10 AND LINE 11" << endl;
					winnings++;
				}
			}
			
			else if (reel[1][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i])
			{
				cout << "WINNER LINE 11" << endl;
				winnings++;
			}
		}
	}
	return winnings;
}

double Slots::twelveLines(string *symbol, string **reel, int *lines) // 12 ~ 13 lines activated
{
	double winnings = 0;

	for (int i = 0; i < 4; i++)
	{
		if (*lines == 12) // LINE 12 ACTIVATED
		{
			cout << "LINE 12 ACTIVATED" << endl;
			if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[1][2] == symbol[i])
			{
				cout << "WINNER LINE 12" << endl;
				winnings++;
			}
		}
		
		else if (*lines > 12) // LINE 12 and LINE 13 ACTIVATED
		{
			if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[1][2] == symbol[i]) // LINE 12
			{
				cout << "WINNER LINE 12" << endl;
				winnings++;
				if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[1][2] == symbol[i]) // LINE 12 and 13
				{
					cout << "WINNER LINE 12 and 13" << endl;
					winnings++;
				}
			}

			else if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[1][2] == symbol[i]) // LINE 13
			{
				cout << "WINNER LINE 13" << endl;
				winnings++;
			}
			
		}
	}

	return winnings;
}

double Slots::fourteenLines(string *symbol, string **reel, int *lines) //14 ~ 16 lines activated
{
	double winnings = 0;

	for (int i = 0; i < 4; i++)
	{
		if (*lines == 14)
		{
			if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i])
			{
				cout << "WINNER LINE 14" << endl;
				winnings++;
			}
		}

		else if (*lines > 14)
		{
			if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i]) // LINE 14
			{
				cout << "WINNER LINE 14" << endl;
				winnings++;

				if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i]) // LINE 14 and 15
				{
					cout << "WINNER LINE 14 and LINE 15" << endl;
					winnings++;
				}
			}

			else if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i]) // LINE 15
			{
				cout << "WINNER LINE 15" << endl;
				winnings++;
			}
		}


	}

	return winnings;
}

double Slots::sixteenLines(string *symbol, string **reel, int *lines) // 16 ~ 17 lines activated
{
	double winnings = 0;

	for (int i = 0; i < 4; i++)
	{
		if (*lines == 16)
		{
			if (reel[1][0] == symbol[i] && reel[0][1] == symbol[i] && reel[1][2] == symbol[i])
			{
				cout << "WINNER LINE 16" << endl;
				winnings++;
			}
		}

		else if (*lines > 16)
		{
			if (reel[1][0] == symbol[i] && reel[0][1] == symbol[i] && reel[1][2] == symbol[i]) // LINE 16 ACTIVATED
			{
				cout << "WINNER LINE 16" << endl;
				winnings++;

				if (reel[1][0] == symbol[i] && reel[2][1] == symbol[i] && reel[1][2] == symbol[i]) // LINE 16 and LINE 17 ACTIVATED
				{
					cout << "WINNER LINE 16 and LINE 17" << endl;
					winnings++;
				}
			}

			else if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // LINE 17 ACTIVATED
			{
				cout << "WINNER LINE 17" << endl;
				winnings++;
			}
		}

	}
	return winnings;
}

void Slots::displayLines()
{
	cout << R"(
                                           LINES TABLE
                                                                      
                  LINES 1 ~ 3                                        LINES 4 ~ 5
+--------------+---------------+--------------+    +--------------+---------------+--------------+
|              |               |              |    |              |               |              |
| LINE 2-------|---------------|-------LINE 2 |    | LINE 4-----  |               |  -----LINE 5 |
|              |               |              |    |            \ |               | /            |
|              |               |              |    |             \|               |/             |
+---------------------------------------------+    +---------------------------------------------+
|              |               |              |    |              |\             /|              |
| LINE 1-------|---------------|-------LINE 1 |    |              | \___________/ |              |
|              |               |              |    |              | /           \ |              |
|              |               |              |    |              |/             \|              |
+---------------------------------------------+    +---------------------------------------------+
|              |               |              |    |            / |               |\             |
| LINE 3-------|---------------|-------LINE 3 |    | LINE 5----/  |               | \-----LINE 4 |
|              |               |              |    |              |               |              |
|              |               |              |    |              |               |              |
+--------------+---------------+--------------+    +--------------+---------------+--------------+


                  LINES 6 ~ 7                                       LINES 8 ~ 9
+--------------+---------------+--------------+    +--------------+---------------+--------------+
|              |               |              |    |              |               |              |
|              |               |  /----LINE 6 |    | LINE 8----\  |               |
|              |               | /            |    |            \ |               |              |
|              |               |/             |    |             \|               |              |
+---------------------------------------------+    +---------------------------------------------+
|              |              /|              |    |              |\              |              |
| LINE 6-------|-------------/ |              |    |              | \-------------|------ LINE 8 |
| LINE 7-------|-------------\ |              |    |              | /-------------|------ LINE 9 |
|              |              \|              |    |              |/              |              |
+---------------------------------------------+    +---------------------------------------------+
|              |               |\             |    |             /|               |              |
|              |               | \-----LINE 7 |    | LINE 9-----/ |               |              |
|              |               |              |    |              |               |              |
|              |               |              |    |              |               |              |
+--------------+---------------+--------------+    +--------------+---------------+--------------+


                 LINES 10 ~ 11                                      LINES 12 ~ 13
+--------------+---------------+--------------+    +--------------+---------------+--------------+
|              |               |              |    |              |               |              |
|              |  /------------|------LINE 10 |    | LINE 12------|------------\  |              |
|              | /             |              |    |              |             \ |              |
|              |/              |              |    |              |              \|              |
+---------------------------------------------+    +---------------------------------------------+
|             /|               |              |    |              |               |\             |
| LINE 10----/ |               |              |    |              |               | \----LINE 12 |
| LINE 11----\ |               |              |    |              |               | /----LINE 13 |
|             \|               |              |    |              |               |/             |
+---------------------------------------------+    +---------------------------------------------+
|              |\              |              |    |              |              /|              |
|              | \             |              |    |              |             / |              |
|              |  \------------|------LINE 11 |    | LINE 13------|------------/  |              |
|              |               |              |    |              |               |              |
+--------------+---------------+--------------+    +--------------+---------------+--------------+


                 LINES 14 ~ 15                                      LINES 16 ~ 17
+--------------+---------------+--------------+    +--------------+---------------+--------------+
|              |               |              |    |              |               |              |
| LINE 14---\  |               |  /---LINE 14 |    |              |  ___________  |              |
|            \ |               | /            |    |              | /           \ |              |
|             \|               |/             |    |              |/             \|              |
+---------------------------------------------+    +---------------------------------------------+
|              |\_____________/|              |    |             /|               |\             |
|              |               |              |    | LINE 16----/ |               | \----LINE 16 |
|              | _____________ |              |    | LINE 17----\ |               | /----LINE 17 |
|              |/             \|              |    |             \|               |/             |
+---------------------------------------------+    +---------------------------------------------+
|             /|               |\             |    |              |\             /|              |
|            / |               | \            |    |              | \___________/ |              |
| LINE 15---/  |               |  \---LINE 15 |    |              |               |              |
|              |               |              |    |              |               |              |
+--------------+---------------+--------------+    +--------------+---------------+--------------+

)";

}

void Slots::exitMachine(Account *user, double *credit) // Convert user's credits into cash and deposit into account
{
	double conversion = 0;
	conversion = (*credit / 100);

	cout << "CREDIT UPDATE IN EXIT MACHINE AMOUNT " << *credit << endl;
	user->setUserBalance(conversion);
	user->setUserLuck(0); // Remove luck since drink has worn off
	user->setUserMisfortune(0); // Remove misfortune since drink has worn off
	cout << "$" << conversion << " has been deposited into your account" << endl;
}

Slots::~Slots()
{

}