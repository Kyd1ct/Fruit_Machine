#include <conio.h> // Library providing console I/O (checks if a specific key is pressed)
#include "Graphics.h" // Header file containing functions in Graphics.cpp
#include <iostream>


using namespace std;


// Macros

#define SCROLL_POS 29 // Taken from LaMothe in case scrolling is required
#define ROW 7		  // Number of rows in array
#define COLUMN 7	  // Number of columns in array


// Globals

Graphics graphics;


int coins = 100;
int spent = 0;
int earned = 0;
int tempprof = 0;
int profit = 0;
int combo = 0;

// Prototypes

void Update_Coins();
void Update_Spent();
void Update_Won();
void Update_Profit();
void Update_Profit_Loss();
void Update_Profit_Win_2();
void Update_Profit_Win_Doubled();
void Update_Profit_Win_3();
void Update_Profit_Win_Jackpot();
void Update_Profit_Win_Diag();
void Update_Combo();


int main() {
	
	// Calls function from Graphics class which hides the cursor
	graphics.Hide_Cursor(false);

	// Boolean value which indicates if game is running or not
	bool game_running = true;
	
	// Char variable used to store the button's ASCII code
	char key;

	// "\234" is the octal value for pound sterling symbol
	string slot[ROW][COLUMN] = {
		{"#", " ", "?", " ", "\234", " ", "?"},
		{"@", " ", "\234", " ", "!", " ", "\234"},
		{"!", " ", "#", " ", "@", " ", "7"},
		{"7", " ", "$", " ", "?", " ", "!"},
		{"?", " ", "7", " ", "$", " ", "@"},
		{"$", " ", "@", " ", "7", " ", "$"},
		{"\234", " ", "!", " ", "#", " ", "#"}
	};
	char symbol = 0;

	// Calls function from Graphics class which initalises graphics
	graphics.Init_Graphics();

	// Prints game's title
	graphics.Draw_String(12, 1, "F R U I T  M A C H I N E");
	// Prints instructions
	graphics.Draw_String(11, 15, "Please press space to begin!");

	// Set-up statistics 
	Update_Coins();
	Update_Won();
	Update_Spent();
	Update_Profit();
	Update_Combo();
	
	// Calls function from Graphics class which prints indicators
	graphics.Draw_Indicators();

	// Sets coordinates of where the array will be printed
	graphics.Draw_String(16, 5, " ");

	// Prints array on game launch
	for (int i = 0; i < ROW; ++i) {

		for (int j = 0; j < COLUMN; ++j) {
			cout << slot[i][j] << ' ';
		}
		cout << endl;
		graphics.Draw_String(16, 5 + i, " "); // Used to print the array as a matrix
	}

	bool started = false;	// Used to indicate when rotors start spinning and statistics are updated
	int columnCounter = 0;  // Counts columns


	while (game_running) { // Main game loop

		if (_kbhit()) {
			key = toupper(_getch());
			if (key == 32) { // Space key
				graphics.Set_Color(15, 0);
				graphics.Draw_String(3, 15, "Please press space to stop the wheels or Q to quit!");
				if (!started)
				{
					started = true;
					// Update coins and spent
					coins -= 10;
					spent += 10;

					// Set-up statistics
					Update_Profit_Loss();
					Update_Spent();
					Update_Coins();
					Update_Combo();

					graphics.Set_Color(15, 0); // Sets initial colour to white
					graphics.Draw_String(3, 13, "                                                           "); // Overwrites Jackpot string when user presses space again

					columnCounter = 0; // Counter used to count the columns for the spin
				}
				else
				{
					columnCounter += 2; // Set to += 2 due to the empty columns used for a clearer view of the slot machine
					if (columnCounter >= COLUMN)  // If the counter has reached the last column
					{

						started = false; // Started value changes back to false so the game can be restarted with space after all rotors stop spinning

						// String variables for the elements
						string sym1 = slot[3][0];
						string sym2 = slot[3][2];
						string sym3 = slot[3][4];
						string sym4 = slot[3][6];
						string sym5 = slot[0][0];
						string sym6 = slot[2][2];
						string sym7 = slot[4][4];
						string sym8 = slot[6][6];
						string sym9 = slot[6][0];
						string sym10 = slot[4][2];
						string sym11 = slot[2][4];
						string sym12 = slot[0][6];

						// Checks if there's 4 same symbols diagonally

						if ((sym5 == sym6 && sym6 == sym7 && sym7 == sym8) || (sym9 == sym10 && sym10 == sym11 && sym11 == sym12)) {
							coins += 100;
							earned += 100;
							Update_Coins(); // Overwrites coins
							Update_Profit_Win_Diag(); // Updates Profit/Loss
							Update_Won(); // Updates Won
							graphics.Diag_Jackpot(); // Function indicating diagonal jackpot
							combo++;
						}

						// If 4 match update coins and profit + make the array golden and display jackpot
						else if (sym1 == sym2 && sym2 == sym3 && sym3 == sym4 && sym1 == sym4) {
							coins += 50;
							earned += 50;
							Update_Coins(); // Overwrites coins
							Update_Profit_Win_Jackpot(); //Updates Profit/Loss
							Update_Won(); // Updates Won
							graphics.Jackpot(); // Function indicating normal jackpot and making the array golden
							combo++;
						}

						 /* 
						 *  If 3 match update coins and won + make the array green
						 *  Comments are the same for the functions in the else if statements below
						 *  The array turns green by putting the Update_Won(); function at the bottom, which updates the statistics but also changes colour
						 */

						else if (sym1 == sym2 && sym2 == sym3 || sym1 == sym3 && sym3 == sym4 || sym1 == sym2 && sym2 == sym4 || sym2 == sym3 && sym3 == sym4) {
							coins += 20;
							earned += 20;
							Update_Coins();
							Update_Profit_Win_3();
							Update_Won();
							combo++;
						}

						// If two coupled neighbour symbols match, update coins and won + make array green
						else if (sym1 == sym2 && sym3 == sym4) {
							coins += 15;
							earned += 15;
							Update_Coins();
							Update_Profit_Win_Doubled();
							Update_Won();
							combo++;
						}

						// If 2 neighbour symbols match, update coins and won + make the array green
						else if (sym1 == sym2 || sym2 == sym3 || sym3 == sym4) {
							coins += 10;
							earned += 10;
							Update_Coins();
							Update_Profit_Win_2();
							Update_Won();
							combo++;
						}


						else { // Set array to red when none match
							graphics.Set_Color(4, 0);
							combo = 0;
						}

						if (coins == 0) { // Game loss
							graphics.Game_Over(); // Indicates game loss and changes colour to red
							game_running = false; // Stops game loop
							Sleep(5000); // Closes console after 5 seconds
						}

					}
				}
			}
			else if (key == 81 || key == 113){ // Quits game when Q/q is pressed
			graphics.Game_Quit(); // Function for game quit text
			game_running = false;  // Stops game loop
			Sleep(5000); // Closes console after 5 seconds
			}

		}

		// Sets same coordinates as the original ones but overprints the old values
		graphics.Draw_String(16, 5, " "); 
		for (int i = 0; i < ROW; ++i) {

			for (int j = 0; j < COLUMN; ++j) {
				cout << slot[i][j] << ' ';
			}
			cout << endl;
			graphics.Draw_String(16, 5 + i + 1, " ");
		}




		if (started) // Game has started (Space button is pressed)
		{
			//Sleep(500); // Slows all columns for the whole gameplay (The higher the number, the slower the spinning). Remove comment to apply
			
			// Nested for loops below used to spin the array
			for (int i = columnCounter; i < COLUMN; i++) { // Sets i's value to columnCounter and keeps incrementing while i is less than the column macro.

				string tmp = slot[0][i]; // Sets a temporary string to hold the value of the first element


				for (int j = 0; j < ROW - 1; j++) { // Sets j's value to row macro minus one and increments
					graphics.Set_Color(15, 0); // Sets colour to white
					string temp = slot[j][i]; // Changes temp string to the incremented j value (first element of the column) and keeps the number of the column

					slot[j][i] = slot[j + 1][i]; // Moves the second element in the column one place above and overwrites the first element
				}

				//Sleep(60); // Speeds up columns gradually. Remove comment to apply
				slot[ROW - 1][i] = tmp; // After the loop ends, it sets the first element of the column as the last one

			}

		}

	}
}


void Update_Coins() { // Function setting up Coins statistics

	graphics.Set_Color(15, 0);
	graphics.Draw_String(45, 3, "Coins: " + to_string(coins) + "    ");
}

void Update_Spent() { // Function setting up Spent statistics

	graphics.Set_Color(4, 0); // Sets Spent colour to red. If there is no win, array also changes colour to red
	graphics.Draw_String(45, 5, "Spent: " + to_string(spent) + "    ");
}

void Update_Won() { // Function setting up Won statistics

	graphics.Set_Color(10, 0); // Sets Won colour to green. If the win is of a normal type (no kind of jackpot), array turns green
	graphics.Draw_String(45, 7, "Won: " + to_string(earned) + "    ");
}

void Update_Profit() { // Function setting up Profit/Loss statistics

	graphics.Set_Color(14, 0);
	graphics.Draw_String(45, 9, "Profit/Loss: " + to_string(profit) + "    ");
}

void Update_Profit_Loss() { // Function to update the profit upon loss

	profit -= 10;
	graphics.Set_Color(14, 0); // Sets colour to yellow
	graphics.Draw_String(45, 9, "Profit/Loss: " + to_string(profit) + "    ");
}

void Update_Profit_Win_2() { // Function updating the profit upon 2 neighbour matched symbols

	profit += 10;
	graphics.Set_Color(14, 0); // Sets colour to yellow
	graphics.Draw_String(45, 9, "Profit/Loss: " + to_string(profit) + "    ");
}

void Update_Profit_Win_Doubled() { // Function updating the profit upon two couples of matched symbols

	profit += 15;
	graphics.Set_Color(14, 0); // Sets colour to yellow
	graphics.Draw_String(45, 9, "Profit/Loss: " + to_string(profit) + "    ");
}

void Update_Profit_Win_3() { // Function updating the profit upon 3 matched symbols

	profit += 20;
	graphics.Set_Color(14, 0); // Sets colour to yellow
	graphics.Draw_String(45, 9, "Profit/Loss: " + to_string(profit) + "    ");
}

void Update_Profit_Win_Jackpot() { // Function updating the profit upon Jackpot

	profit += 50;
	graphics.Set_Color(14, 0); // Sets colour to yellow
	graphics.Draw_String(45, 9, "Profit/Loss: " + to_string(profit) + "    ");
}

void Update_Profit_Win_Diag() { // Function updating the profit upon Diagonal Jackpot

	profit += 100;
	graphics.Set_Color(14, 0); // Sets colour to yellow
	graphics.Draw_String(45, 9, "Profit/Loss: " + to_string(profit) + "    ");
}

void Update_Combo() { // Function updating the combo counter

	graphics.Set_Color(11, 0); // Sets colour to light blue
	graphics.Draw_String(45, 11, "Combo streak: " + to_string(combo) + "    ");
}