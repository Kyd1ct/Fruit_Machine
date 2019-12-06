#include "Graphics.h" //Includes the header file which holds these functions as public members
#include <time.h> // Library used for the randomisation of Diagonal Jackpot colour

// Constructor
Graphics::Graphics() {

}

void Graphics::Init_Graphics() { // Taken from LaMothe
	// Initializes the console graphics engine

	COORD console_size = { GAME_X, GAME_Y };
	// Console size, using X and Y in the names because it's a 2D Space

	// Open i/o channel to console screen
	hconsole = CreateFile(TEXT("CONOUT$"), GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);

	// Randomising function used to randomise colour for some of the strings in other functions
	srand((unsigned)time(NULL));

	// Make sure we are in 80x25
	SetConsoleScreenBufferSize(hconsole, console_size);

	// Get details for console screen                       
	GetConsoleScreenBufferInfo(hconsole, &con_info);
}


void Graphics::Hide_Cursor(bool showFlag) { // SetConsoleCursorInfo function hides the cursor from jumping all over the screen (Found in stackoverflow.com)
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // Set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

// Function which sets the color of the console output
void Graphics::Set_Color(int fcolor, int bcolor) {
	// Four bits for foreground and four for background
	// First bit is intensity, the rest are RGB
	SetConsoleTextAttribute(hconsole, (WORD)((bcolor << 4) | fcolor));
}


// Taken from LaMothe - overwrites a string at the given coordinates
void Graphics::Draw_String(int x, int y, string s)
{
	COORD cursor_pos;
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(hconsole, cursor_pos);

	cout << s;
}

// Function indicating the checked row
void Graphics::Draw_Indicators() {

	Set_Color(15, 0); // Sets colour to white
	Draw_String(14, 8, "->");
	Draw_String(31, 8, "<-");
}

// Function indicating the user has won a normal jackpot and sets array and string colour to golden
void Graphics::Jackpot() {

	Set_Color(6, 0); // Sets string and array colour to golden
	Draw_String(15, 13, "J A C K P O T !!!");
}

// Function indicating the user has won a diagonal jackpot
void Graphics::Diag_Jackpot() {
	Set_Color((rand() % 15)+1, 0); // +1 is added to avoid the string being coloured in black
	Draw_String(9, 13, "D I A G O N A L  J A C K P O T !!!");
	Set_Color(15, 0); // Sets colour back to white to keep the array white
}

// Function indicating the user lost the game (ran out of coins)
void Graphics::Game_Over() {
	Set_Color(4, 0); // Sets colour to red
	Draw_String(3, 15, "Oh, isn't that sad? Looks like I win and you lose! :)");
	cout << endl;
	cout << endl;
	Set_Color(15, 0);
}

// Function indicating the user has quit the game
void Graphics::Game_Quit() {
	Set_Color(1, 0); // Sets colour to dark blue
	Draw_String(3, 15, "                                                                              "); // Overwrites instructions string
	Draw_String(8, 15, "Oh, you gave up already? Sad :(");
	cout << endl;
	cout << endl;
	Set_Color(15, 0); // Sets colour back to white in order to preserve the white colour of the array
}