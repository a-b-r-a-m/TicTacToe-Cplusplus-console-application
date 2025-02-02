// AZ_XO.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <chrono>
#include <thread>

#include "MainMenu.h"
//#include<stdio.h>
//#include<stdlib.h>
//#include<ctype.h>
//#include<string.h>
//#include<math.h>
//#include "NoPlayers.h"
//#include"AI.h"
//using std::cout;
//using std::cin;
//using std::endl;
//using std::string;

int main() {
	string grid = "123456789";
	char choice = '?';

	PrintTitle();
	PrintGrid(grid);

	while (choice != '0')
		MainMenu(grid, choice);

	cout << endl << "Thank you for playing." << endl << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
