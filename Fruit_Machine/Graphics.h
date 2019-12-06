// Preprocessor directive causing the source file to compile only once
#pragma once

#include <windows.h> //Contains declaration for all Windows API Functions
#include <string>
#include <iostream>

using namespace std;


// Macros
// Taken from the LaMothe code. Those macros define the width and the height of the game
#define GAME_Y 35
#define GAME_X 80


class Graphics
{
public:
	Graphics();
	void Init_Graphics();
	void Hide_Cursor(bool);
	void Set_Color(int fcolor, int bcolor = 0);
	void Draw_String(int x, int y, string s);
	void Draw_Indicators();
	void Jackpot();
	void Diag_Jackpot();
	void Game_Over();
	void Game_Quit();
private:
	CONSOLE_SCREEN_BUFFER_INFO con_info; // Holds information about the screen
	HANDLE hconsole; // Handle the console
};
