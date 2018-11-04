#include "Slots.hpp"

/*
Function Name: Slot Machine Simulator
Description: Program simulates a slot machine.

Features:
	1) Credits are required for the machine to operate. Credits can be redeemed from the slot machine. The user must exchange cash for credits.
	2) If the user exits the machine and there are remaining credits, the program will automatically convert the remaining credits into cash and deposit it into the user's account.
	3) Slot machine can play up to 17 lines. The winnings lines can be accessed and viewed from the built-in menu by selecting the option to print winnings lines.
	4) Slot machine can play different credit amounts. The lowest amount a user can bet is 5 credits and the highest amount is 500 credits.
	5) The bet multiplier and payout is calculated by the following formula: BET AMOUNT / NUMBER of ACTIVATED PAYLINES
	6) Multiple built-in error prevention features such as incorrect user input, lack of credits to execute desired spin, or inadequate user cash balance to withdraw additional credits. 
	7) Option to respin after each spin.
	8) Winning odds are different for each bet amount. Lower bet amounts have higher winnings odds and higher bet amounts have lower winning odds.
	9) Special BONUS feature that can only be activated if user has the luck or misfortune stat. This stat can be acquired from drinking a beverage at the bar.
		9.a) If the user has the credentials for the BONUS feature to execute, the function will have a 50% chance of executing based on random chance. If the BONUS feature executes, the function will determine if the LUCK feature is 
			 executed or the MISFORTUNE feature is activated. The probability of a respective execution is based on the number of LUCK points and the number of MISFORTUNE points.
			9.a.i) If LUCK feature executes then the program will randomly select a fixed value to multiply the user's winnings.
			9.a.ii)If MISFORTUNE feature executes then the program will randomly select a fixed value to multiply the user's winnings and deduct it from the user's total winnings for that round.
		9.b) If BONUS feature does not execute then we continue to next step.
	10) User can exit the slot machine via two ways. The first way is to exit the machine after a spin. The second way is to exit the machine from the in-game menu.


Technical Features:
	1) Slot Machine is a struct.
	2) Multiple pointers are used to keep track of user data (name, balance, number of credits).
	3) Random_Shuffle and seed time are critical in shuffling the fixed arrays of symbols.
	4) Program is optimized to reduce time and space complexity. The volume of IF statements O(1) exceed the volume of LOOP statements O(N) due to time complexity.
	5) User's winnings are calculated via the check lines function. The line checking functions that are activated are dependent upon the number of activated lines.
	6) Program uses vectors for storing symbols.
	7) Pointer to pointer array is used for storing the "spin" in a 3x3 grid array.
	8) Multiple messages are displayed to inform the user of certain events. Such as which lines are winners, the number of credits they won, the number of credits they have before a spin, etc.

*/



Slots::Slots() // Default Constructor
{
}

void Slots::startSlots(Account *user) // User is greeted with message when they choose to play slots. Then the function executes the start slot machine function. 
{
	cout << "  Hello " << user->getName() << endl;
	cout << endl;
	startMachine(user);
}

double Slots::getCredits() 
{
	return credits;
}

//--------------------------------------------------------------SLOT MACHINE------------------------------------------------------------------------------------------
// Function: Acts as main interface between user and the machine. It is responsible for getting user options and executing orders based on user commands. 
// This function is ponsible for setting up the initialization of the machine and getting it prepared for the user.
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Slots::startMachine(Account *user) // Start the machine function. It initializes all variables and prepares the machine for user - machine interaction. 
{
	SlotMachine machine; // Create struct object machine which contains all the inner slot machine features
	Validate validate; // Create a validation object to check user's input for error detection
	bool play = true; // Bool play is used to determine whether or not the user wants to stay at the machine. If bool is true then machine continues to loop and if bool is false it exits loop.

	machine.userName = user->getName(); // Retrieve the user's name and store the user's name in the machine
	machine.creditAmount = 0; // Initialize the machine's credit amount to zero
	double creditUpdate = 0;  // Credit update variable is used to update the struct objects variables. This is used due to struct scope.

	while (play) // Main while loop. If this loop is false then the program exits the slot machine. Else if this loop is true we continue to execute slot functions.
	{
		bool status = false; // Controls second while loop. This loop is responsible for printing the slot machine's main menu

		int userOption = 0; // Variable to hold if user wants to spin again
		int slotOption = 0; // Variable to hold user's menu selection

		int *activatedLines; // Variable points to the number of lines the user activates
		int lines = 0; // Intialize the number of lines in play to zero 
		activatedLines = &lines; // Initialize pointer to lines variable which will hold the number of lines the user activates

		double *credit; // Variable points to the number of credits in the machine
		credit = &creditUpdate; // This pointer is pointing to the global scope creditUpdate variable which is responsible for intializing and updating the slot machine's credit amount variable

		int betAmount = 0; // Initialize bet amount to zero. 

		bool running = true; // Bool indicator for in-game menu while loop

		machine.creditAmount = creditUpdate; // Set the machine's credit to creditUpdate

		while(running) // While loop responsible for main interaction between user and machine
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

			bool status = true; // Bool responsible for inner while loop
			bool betFlag = false; // Bool responsible to check that user has placed a bet
			bool lineFlag = false; // Bool responsible to check that user has activated at least one line

			while (status) // This while loop is responsible for printing the menu so the user can interact with the different options
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
			
			slotOption = 0; // After every iteration of the while loop set slot option to zero so user can activate other built-in menu options
			userOption = 0; // User option is only used to determine whether user wants to spin the wheel or exit the machine
	
			slotOption = validate.inputValidate(1, 8); // Validate the user's input
			
				if (slotOption == 1) // Option 1 is to spin the wheel. User must betFlag and lineFlag cleared before this function can execute. Bet Flag means the user has set a bet and Line Flag means the user has activated some lines.
				{
					if (betFlag && lineFlag) // If both flags are set to true the we execute the spin
					{
						int bet_amount[] = { 5, 10, 25, 50, 75, 100, 250, 500};

						if (credits < (bet_amount[betAmount-1] * (*activatedLines))) // If user clears bet flag and line flag but does not have enough credits to execute desired spin we print a message that the user has insufficient credits 
						{
							cout << "Not enough credits" << endl;
						}

						else // User is cleared to spin
						{
							userOption = 1; // Activate userOption to one to execute spin
							status = false; // Set status flag to false to exit menu while loop
							running = false; // Set running flag to false to exit loop outside menu and to proceed to spin activation
						}
					}

					else if (betFlag && !lineFlag) // IF user has placed a bet but has not entered the number of lines, print error
					{
						cout << "Please enter the number of lines you wish to play" << endl;
						cout << endl;
					}

					else if (lineFlag && !betFlag) // IF user has entered the number of lines but has not placed a bet, print error
					{
						cout << "Please enter a bet amount you wish to play" << endl;
						cout << endl;
					}

					else if (!lineFlag && !betFlag) // IF user has not placed a bet and has NOT entered the number of lines, print erro
					{
						cout << "Please enter the bet amount and the number of lines first" << endl;
						cout << endl;
					}

				}

				else if (slotOption == 2) // User has selected to execute max bet. Set the number of activated lines to the max 17 lines and max bet (500);
				{
					cout << "MAX BET ACTIVATED" << endl;
					cout << "Playing 17 lines at 500 credits per spin" << endl;
					*activatedLines = 17; // Activated lines set to max
					betAmount = 7; // Bet amount set to max bet amount index
					betFlag = true; // Status flags are set for spin execution
					lineFlag = true;
				}

				else if (slotOption == 3) // User has chosen to display lines table
				{
					displayLines();
					slotOption = 0;
				}

				else if (slotOption == 4) // User has chosen to enter a bet amount
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
					betAmount = validate.inputValidate(1, 8); // Validate user's selection to make sure it is a valid option
					cout << "BET AMOUNT: " << betAmount << endl;
					betFlag = true; // Set bet flag to true since user has placed a bet
				}

				else if (slotOption == 5) // User has chosen to enter the number of lines they wish to play
				{
					cout << "----- LINES -----" << endl;
					cout << "Enter the number ";
					cout << "of lines (1 - 17): ";
					*activatedLines = validate.inputValidate(1, 17); // Validate user's selection to make sure it is a valid option
					cout << "LINES: " << *activatedLines << endl;
					lineFlag = true; // Set line flag to true since user has entered the number of lines to play
				}

				else if (slotOption == 6) // User chooses to put credits into the machine
				{
					int creditSelection = 0; // Variable is responsible for the option the user selects

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
					
					creditSelection = validate.inputValidate(1, 6); // Check user's selection to make sure it is a valid option

					double creditLine[6] = { 100, 1000, 5000, 10000, 50000, 100000 }; // Array that holds the credit amounts
					double deductAmount[6] = { -1, -10, -50, -100, -500, -1000 }; // Array that holds the cash amount to deduct from user's balance
					
					if (user->getUserBalance() <= (-1 * (deductAmount[creditSelection - 1]))) // If user does not have enough money in their account to execute credit transaction
					{
						cout << "You do not have enough money" << endl;
					}

					else // User has enough money to execute cash-credit transaction and we execute
					{
						user->setUserBalance(deductAmount[creditSelection - 1]); // Send the expense to user's account to be deducted from their balance
						credits = creditLine[creditSelection - 1]; // Set credits amount to the option the user has selected
						cout << credits << " CREDITS ADDED" << endl;
						machine.creditAmount += credits; // Add the credits to the machine
					}

				}

				else if (slotOption == 7) // User chooses to exit machine
				{
					running = false; // Bool to exit main loop
					status = false; // Bool to exit in-game menu loop
					userOption = 2; // User has chosen to exit the machine

				}
			}
		}

		cout << endl;
		
		//---------------------------------------------------------------SLOT MACHINE SPIN FUNCTION-----------------------------------------------------------------------------------
		// Function: This function is responsible for executing all spin related operations ranging from credit deduction/addition, bonus features, user-error checking, and more.
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		if (userOption == 1) // Function executes all the slot machine functions 
		{
			bool respin = true; // Bool respin is set to true. This is used later after the spin is completed and the user has the option to spin again. If they choose to spin again we will execute respin loop again else we exit to game menu.
			vector<string> slots; // This vector will hold the 9 symbols that refresh every spin
			double bet_amount[] = { 5, 10, 25, 50, 75, 100, 250, 500}; // Array of the bet amounts

			while (respin) // While loop that spins again if bool respin is true or exits while loop if respin is set to false
			{
				double creditBet = 0; // Credit bet is the variable that holds the total bet amount per spin. This is calculated as bet amount multiplied by number of activated lines
				double betMultiplier = 0; // Bet multiplier is the amount the user wins per line. This is calculated bet amount divided by number of lines

				cout << "------------------ SPIN -------------------" << endl;
				cout << endl;

				betMultiplier = (bet_amount[betAmount - 1] / (*activatedLines / 10)); // Initialize bet multiplier with user input variables
				creditBet = ((bet_amount[betAmount - 1] / 100) * (*activatedLines)); // Initialize credit bet with user input variables

				if ((machine.creditAmount / 10) < (bet_amount[betAmount - 1])) // If the user does not have enough credits then we execute the option for the user to enter more credits
				{
					int addCredit = 0;
					cout << "You do not have enough credits" << endl;
					cout << "Would you like to enter more credits?" << endl;
					cout << "1. Yes" << endl;
					cout << "2. No" << endl;
					addCredit = validate.inputValidate(1, 2); // Check user's input to make sure option is valid
					switch (addCredit) // Execute switch option based on user's input
					{
						case(1): // User chooses to add more credits. We exit to in game menu
							respin = false; 
							machine.creditAmount = creditUpdate;
							break;
						
						case(2): // User chooses to not enter more credits and we exit the slot machine
							machine.creditAmount = creditUpdate;
							respin = false;
							play = false;
							break;
					}

				}

				else if((machine.creditAmount) > bet_amount[betAmount - 1]) // If user has enough credits in their account to execute spin
				{
					cout << "BET MULTIPLIER = " << betMultiplier << endl; // Display the bet multiplier
					cout << "CREDIT BET = " << creditBet << endl; // Display the credit bet amount
					cout << "BET AMOUNT: $" << std::setprecision(2) << std::fixed << creditBet << endl; // Display the bet denomination
					cout << "LINES IN PLAY: " << *activatedLines << endl; // Display the number of lines in play
					cout << "BALANCE: $" << ((machine.creditAmount / 100)) << endl; // Display the user's cash balance. The cash balance is the credit conversion to cash
					cout << "MACHINE CREDIT AMOUNT " << machine.creditAmount << endl; // Display the number of credits in the machine
					
					switch (betAmount) // Switch statement is responsible for deducting the total bet amount from the user's credits
					{
						case (1):
						{
							machine.creditAmount -= ((5) * (*activatedLines)); // Deduct bet amount multiplied by activated lines from the user's credits
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

						for (int i = 0; i < 30; i++) // Push all symbols into vector
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


					//-----------------------------------------------------------------SLOT EVALUATOR and WINNER-------------------------------------------------------------------------
					// Function: Shuffles symbols derived from betting odds. Places symbols into 3x3 grid and is sent to line checking functions to determine if there exists a winner
					//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
					
					string *symbol; // String pointer that points to the symbol array. This pointer will passed to the check lines function. The reason for a pointer is to save space.
					string symbolSet[4] = { "$", "#","&", "@" }; // Array of symbols
					symbol = symbolSet; // Symbol pointer set to point to symbol array

					unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Random seed to shuffle the array of symbols
					int size = sizeof(slots); // Retrieve the size of the array for vector use

					string **slotDisplay; // 2D array that we will pass as parameters for line checking
					slotDisplay = new string*[3]; // Create 3x3 array that represents the slot lines
					
					for (int i = 0; i != 3; i++)
					{
						slotDisplay[i] = new string[3];
					}


					int numRandomize = rand() % 100 + 1; // Generate random number between 1 ~ 100. Use this variable to act as the number of times a shuffle of the array occurs
					
					for (int i = 0; i < numRandomize; i++) // Loop iteration is depenedent upon random number generated
					{
						std::shuffle(begin(slots), end(slots), std::default_random_engine(seed)); // For each loop iteration shuffle the vector of symbols
					}

					for (int i = 0; i < 3; i++) // Rows
					{
						for (int k = 0; k < 3; k++) // Columns
						{
							int selection = rand() % slots.size(); // Randomize the element index the slots picks from. Use the vector's size as a max for the random number generator
							slotDisplay[i][k] = slots[selection]; // Retrieve the element and the randomized index inside slots vector and place into the 2d array
							slots.erase(slots.begin() + selection); // Erase the element that was found at the index so it does not repeat
							slots.shrink_to_fit(); // After removal of element, shrink the vector to resize it. This will also update the vector's capacity so it can retrieve a value within range
						}
					}

					for (int i = 0; i < 3; i++) // Display the symbols to the user
					{
						for (int k = 0; k < 3; k++)
						{
							cout << slotDisplay[i][k] << " ";
						}
						cout << endl;
					}

					//-------------------------------------------------------------------LINE CHECKING FUNCTION CALLS---------------------------------------------------------------------------------------
					// Function: Call appropriate lines to check for winners in the 3x3 array. If statements will execute according to their respetive activated lines variable.
					// If 17 lines are activated we will check all lines from 1 - 17. If 1 line is activated we only check 1 line.
					//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

					double winnings = 0; // Variable that will hold the winnings from each line check

					if (*activatedLines <= 3) // Line check for 3 lines or less
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 3 && *activatedLines <= 5) // Line check for 4 - 5 activated lines
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);				
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 5 && *activatedLines <= 7) // Line check for 6 - 7 activated lines
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 7 && *activatedLines <= 9) // Line check for 8 - 9 activated lines
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings += eightLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 9 && *activatedLines <= 11) // Line check for 10 - 11 activated lines
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings += eightLines(symbol, slotDisplay, activatedLines);
						winnings += tenLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 11 && *activatedLines <= 13) // Line check for 12 - 13 activated lines
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines);
						winnings += fiveLines(symbol, slotDisplay, activatedLines);
						winnings += sixLines(symbol, slotDisplay, activatedLines);
						winnings += eightLines(symbol, slotDisplay, activatedLines);
						winnings += tenLines(symbol, slotDisplay, activatedLines);
						winnings += twelveLines(symbol, slotDisplay, activatedLines);
						winnings *= betMultiplier;
					}

					else if (*activatedLines > 13 && *activatedLines <= 15) // Line check for 14 - 15 activated lines
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

					else if (*activatedLines > 15 && *activatedLines <= 17) // Line check for 16 - 17 activated lines
					{
						winnings += threeLines(symbol, slotDisplay, activatedLines); // Check 3 lines first and assign any winners from that call
						winnings += fiveLines(symbol, slotDisplay, activatedLines); // Same as above. Check lines and if there are any winners add that to the winnings variable.
						winnings += sixLines(symbol, slotDisplay, activatedLines);  
						winnings += eightLines(symbol, slotDisplay, activatedLines);
						winnings += tenLines(symbol, slotDisplay, activatedLines);
						winnings += twelveLines(symbol, slotDisplay, activatedLines);
						winnings += fourteenLines(symbol, slotDisplay, activatedLines);
						winnings += sixteenLines(symbol, slotDisplay, activatedLines); // At this point, all lines have been checked. Lines 1 - 17
						winnings *= betMultiplier; // Multiply the winnings by the bet multiplier
					}

		
					if (winnings > 0 && user->getUserLuck() > 0 && user->getUserMisfortune() > 0) // If the user has any winnings and the user has a luck stat and misfortune stat we execute this feature
					{
						int bonusActivation = rand() % 2; // Generate a random number between 1 and 0 and this will determine if the bonus feature is activated

						if (bonusActivation == 0) // If the randomly generated number is 0 then we execute the BONUS feature. If the randomly generated number is 1 then we just exit this if statement and continue to the next if statment
						{
							int luckAmount = user->getUserLuck(); // Retrieve user's luck 
							int misfortuneAmount = user->getUserMisfortune(); // Retrieve user's misfortune
							int symbolTotal = (luckAmount + misfortuneAmount); // Compute the sum of luck and misfortune. We will use this to fill sum to create a vector of size sum and select a symbol from the array which will execute a correspsonding activator

							vector<char> symbolArray; // Vector to hold the symbols derived from luck and misfortune

							int j, k, n;
							j = k = n = 0;

							// For the following functions we retrieve the user's luck/misfortune stat. Each stat will be an int variable. We take the int variable for each stat and insert a symbol into the vector.
							// For example, if the user has 4 luck and 3 misfortune, we insert 4 luck symbols into the vector and insert 3 misfortune symbols into the vector

							for (j = 0; j < luckAmount; j++) // Insert the luck symbols into the vector
							{
								symbolArray.push_back('x'); // Luck is represented by an x
							}

							for (k = 0; k < misfortuneAmount; k++) // Insert the misfortune symbols into the vector
							{
								symbolArray.push_back('o'); // Misfortune is represented by an o
							}

							std::random_shuffle(std::begin(symbolArray), std::end(symbolArray)); // Shuffle the symbols inside vector - We shuffle ths vector so we dont have a normal order of symbols such as x, x, x, x, o, o, o

							int selectNum = rand() % symbolTotal; // Generate a random number that we will use to pull a random symbol from the vector

							char symbolPulled = symbolArray[selectNum]; // Assign randomly pulled symbol to symbolPulled variable


							if (symbolPulled == 'x') // If the symbol x is pulled we activate luck feature
							{

								float bonusFactor = 0;
								float luckBonus[] = { 2, 3, 3.5 }; // The luck bonus array holds three values, one of which will be multiplied to the user's winnings
								int luckyDraw = rand() % 3; // Generate a random number to select a lucky multiplier from the array
								bonusFactor = luckBonus[luckyDraw]; // Bonus factor variable is equal to the element at the luckyDraw index of the luck bonus array
								cout << "It must be your lucky day! You have won an additional " << (bonusFactor * winnings) * 10 << " credits!" << endl; // Display the additional winnings the user has won
								winnings += (bonusFactor * winnings); // Update the machine's credit to reflect the bonus winnings
							}


							else if (symbolPulled == 'o') // If the symbol o is pulled we activate misfortune
							{
								float bonusFactor = 0;
								float misfortuneBonus[] = { -.05, -.07, -.1 }; // Misfortune bonus holds 3 values that will be multiplied with the winnings to deduct an amount from the user's overall winnings for the round
								int misfortuneDraw = rand() % 3; // Generate a random number to select an element from the misfortune bonus array
								bonusFactor = misfortuneBonus[misfortuneDraw]; // Assign bonus factor the value that is pulled from the misfortune bonus array
								cout << "Uh oh! Today might no be your lucky day. You have just lost " << (bonusFactor * winnings) * 10 << " credits from your winnings!" << endl; // Display the amount of credits the user has lost
								winnings += (bonusFactor * winnings); // Deduct the amount from the user's winnings
							}

							winnings *= 10; // Multiply the winnings by 10 to convert the cash to credit - so $1.00 win appears as 100 credits
							machine.creditAmount += winnings; // Add the winnings to the credit amount in the machine
							credits = machine.creditAmount; // Set credits equal to the credit amount inside the machine
							symbolArray.clear(); // Clear the symbol vector so it is ready for the next bonus round if execution occurs
						}
					}

					else if (winnings > 0) // If user has winnings and no luck or misfortune stat or user has winnings and has the luck/misfortune stat but the bonus did not execute we come here
					{
						winnings *= 10;
						machine.creditAmount += winnings; // Add the winnings to the credit amount
						credits = machine.creditAmount; // Set credits equal to the credit amount inside the machine
					}

					delete[] slotDisplay; // Delete 2d Array to prevent memory leaks

					cout << endl;
					cout << "WIN : $" << (winnings / 100) << endl; // Display the cash dollar winnings to the user. That is why we divide by 100 since the credit cash conversion is 100 = $1.00
					cout << "-------------------------------------------" << endl;
					cout << "Would you like to spin again?" << endl; // Display a play again message to the user
					cout << "1. Spin again!" << endl;
					cout << "2. Slot Main Menu" << endl;
					cout << "3. Exit" << endl;

					int playAgain = 0; // Variable used to hold the user's selection
					creditUpdate = machine.creditAmount;
					playAgain = validate.inputValidate(1, 3); // Check the user's input to make sure that it is a valid option
					
					if (playAgain == 1 && machine.creditAmount < bet_amount[betAmount - 1])  // If user chooses to spin again but does not have enough credits to execute another spin we execute the following statement
					{
						int addCredit = 0;
						cout << "You do not have enough credits" << endl; // User is asked if they wish to add more credits
						cout << "Would you like to enter more credits?" << endl;
						cout << "1. Yes" << endl;
						cout << "2. No" << endl;

						addCredit = validate.inputValidate(1, 2); // Check if user inputs a valid option
						
						switch (addCredit) // This switch statment executes the respective option entered by the user
						{
							case(1): // User chooses to enter more credits
								respin = false; // Exit respin loop
								break;

							case(2): // User chooses to exit and we go back to in-game menu
								respin = false; // Exit respin loop
								break;
						}
					}

					else if (playAgain == 1) // If statement executes if user has enough credits
					{
						creditUpdate = machine.creditAmount; // Update the credits variable to hold the amount inside the machine
					}

					
					else if (playAgain == 2) // User chooses to go back to main menu
					{
						machine.creditAmount = creditUpdate;
						respin = false; // Exit respin loop
						symbol = NULL; // Leave no dangling pointers
						delete symbol; // Delete symbol pointer
					}
					
				
					else if (playAgain == 3) // User chooses to exit entire program
					{
						creditUpdate = machine.creditAmount; // Update the credit amount inside the machine via the creditUpdate variable
						exitMachine(user, credit); // User chooses to exit machine so we convert their credits into cash
						running = false; // Set all bools to false to exit the machine
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

		else if (userOption == 2) // User chooses to exit machine
		{
			running = false; // Set bools to false to exit while loops
			play = false;
			credits = machine.creditAmount;
			exitMachine(user, credit); // User chooses to exit machine so we convert their credits into cash
			credit = NULL;
			delete credit;
		}
		}

	}


double Slots::threeLines(string *symbol, string **reel, int *lines) // Check 3 lines or less
{
	
	double winnings = 0;
	double test = 0;
	int i, k, j = 0;

	if (*lines == 1) // ONLY ONE LINE ACTIVATED
	{
		for (i = 0; i < 4; i++)
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 1 ONLY
			{
				cout << "WINNER ON LINE 1" << endl;
				winnings ++; // If there is a winner we increment winnings by one
			}
		}

	}

	else if (*lines == 2) // ONLY TWO LINES ACTIVATED
	{
		for (i = 0; i < 4; i++)
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 1 ONLY
			{ 
				cout << "WINNER ON LINE 1" << endl;
				winnings++; // Increment winnings by one if there is a winner

				if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // WINNER LINE 1 AND LINE 2
				{
					cout << "WINNER ON LINE 1 AND LINE 2" << endl;
					winnings++; // Increment winnings by one again if there is another winner
				}
			}

			else if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // WINNER LINE 2 ONLY
			{
				cout << "WINNER ON LINE 2" << endl;
				winnings++;
			}
		}
	}

	else if (*lines >= 3) // THREE LINES ACTIVATED
	{
		for (i = 0; i < 4; i++)
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // LINE 1 WINNER ONLY
			{
				cout << "WINNER ON LINE 1" << endl;
				winnings++;
				if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // LINE 1 AND LINE 2 WINNER
				{
					cout << "WINNER ON LINE 1 AND LINE 2" << endl;
					winnings++;

					if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // LINE 1 AND LINE 2 AND LINE 3 WINNER
					{
						cout << "WINNER ON LINE 1 AND LINE 2 AND LINE 3" << endl;
						winnings++;
					}
				}
			}

			else if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i] && reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // LINE 1 AND LINE 3 WINNER
			{
				cout << "WINNER ON LINE 1 and LINE 3" << endl;
				winnings++;
			}

			else if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i] && reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // LINE 2 AND LINE 3 WINNER
			{
				cout << "WINNER ON LINE 2 and LINE 3" << endl; // WINNER ON LINE 2 AND LINE 3
				winnings++;
			}

			else if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // LINE 2 WINNER
			{
				cout << "WINNER ON LINE 2" << endl;
				winnings++;
			}

			else if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // LINE 3 WINNER
			{
				cout << "WINNER ON LINE 3" << endl;
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
			if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i]) // LINE 4 WINNER
			{
				cout << "WINNER LINE 4" << endl;
				winnings++;
			}
		}

		else if (*lines > 4)
		{
			if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i]) // LINE 4 WINNER
			{
				cout << "WINNER LINE 4" << endl;
				winnings++;

				if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i]) // WINNER ON LINE 4 AND LINE 5
				{
					cout << "WINNER ON LINE 4 and LINE 5" << endl;
					winnings++;;
				}
			}

			else if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i]) // WINNER ON LINE 5
			{
				cout << "WINNER ON LINE 5" << endl;
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
		if (*lines == 6) 
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i]) // WINNER ON LINE 6
			{
				cout << "WINNER ON LINE 6" << endl;
				winnings++;
			}

		}

		else if (*lines > 6) // LINE SIX AND LINE SEVEN ACTIVATED
		{
			if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i]) // WINNER LINE 6
			{
				cout << "WINNER ON LINE 6" << endl;
				winnings++;

				if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i]) // WINNER LINE 6 AND LINE 7
				{
					cout << "WINNER ON LINE 6 AND LINE 7" << endl;
					winnings++;
				}
			}

			else if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i]) // WINNER LINE 7
			{
				cout << "WINNER ON LINE 7" << endl;
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
	
			if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 8
			{
				cout << "WINNER ON LINE 8" << endl;
				winnings++;
			}
		}

		else if (*lines > 8) // LINE 8 AND LINE 9 ACTIVATED
		{
			if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 8
			{
				cout << "WINNER ON LINE 8" << endl;
				winnings++;

				if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // WINNER LINE 8 AND LINE 9 
				{
					cout << "WINNER ON LINE 8 AND LINE 9" << endl;
					winnings++;
				}
			}

			else if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 9
			{
				cout << "WINNER ON LINE 9" << endl;
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
			if (reel[1][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // WINNER LINE 10
			{
				cout << "WINNER ON LINE 10" << endl;
				winnings++;
			}
		}

		else if (*lines > 10) // LINE 10 AND LINE 11 ACTIVATED
		{
			if (reel[1][0] == symbol[i] && reel[0][1] == symbol[i] && reel[0][2] == symbol[i]) // WINNER LINE 10
			{
				cout << "WINNER ON LINE 10" << endl;
				winnings++;

				if (reel[1][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // WINNER LINE 10 AND LINE 11
				{
					cout << "WINNER ON LINE 10 AND LINE 11" << endl;
					winnings++;
				}
			}
			
			else if (reel[1][0] == symbol[i] && reel[2][1] == symbol[i] && reel[2][2] == symbol[i]) // WINNER LINE 11 
			{
				cout << "WINNER ON LINE 11" << endl;
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

			if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 12
			{
				cout << "WINNER ON LINE 12" << endl;
				winnings++;
			}
		}
		
		else if (*lines > 12) // LINE 12 and LINE 13 ACTIVATED
		{
			if (reel[0][0] == symbol[i] && reel[0][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 12
			{
				cout << "WINNER ON LINE 12" << endl;
				winnings++;

				if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 13
				{
					cout << "WINNER ON LINE 12 and LINE 13" << endl;
					winnings++;
				}
			}

			else if (reel[2][0] == symbol[i] && reel[2][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 13
			{
				cout << "WINNER ON LINE 13" << endl;
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
			if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i]) // WINNER LINE 14
			{
				cout << "WINNER ON LINE 14" << endl;
				winnings++;
			}
		}

		else if (*lines > 14)
		{
			if (reel[0][0] == symbol[i] && reel[1][1] == symbol[i] && reel[0][2] == symbol[i]) // WINNER LINE 14
			{
				cout << "WINNER ON LINE 14" << endl;
				winnings++;

				if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i]) // WINNER LINE 14 and LINE 15
				{
					cout << "WINNER ON LINE 14 and LINE 15" << endl;
					winnings++;
				}
			}

			else if (reel[2][0] == symbol[i] && reel[1][1] == symbol[i] && reel[2][2] == symbol[i]) // WINNER LINE 15
			{
				cout << "WINNER ON LINE 15" << endl;
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
			if (reel[1][0] == symbol[i] && reel[0][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 16
			{
				cout << "WINNER ON LINE 16" << endl;
				winnings++;
			}
		}

		else if (*lines > 16) // LINE 16 AND LINE 17 ACTIVATED
		{
			if (reel[1][0] == symbol[i] && reel[0][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 16
			{
				cout << "WINNER ON LINE 16" << endl;
				winnings++;

				if (reel[1][0] == symbol[i] && reel[2][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 16 and LINE 17
				{
					cout << "WINNER ON LINE 16 and LINE 17" << endl;
					winnings++;
				}
			}

			else if (reel[1][0] == symbol[i] && reel[1][1] == symbol[i] && reel[1][2] == symbol[i]) // WINNER LINE 17
			{
				cout << "WINNER ON LINE 17" << endl;
				winnings++;
			}
		}

	}
	return winnings;
}

void Slots::displayLines() // Display the winning lines
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

	user->setUserBalance(conversion); // Deposit the credit converted to cash into the user's account 
	user->setUserLuck(0); // Remove luck since drink has worn off
	user->setUserMisfortune(0); // Remove misfortune since drink has worn off
	cout << "$" << conversion << " has been deposited into your account" << endl;
}

Slots::~Slots()
{

}