#pragma once

#include<iostream>
#include<string>
#include<fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

void PrintTitle() {
	cout << endl << "    TIC - TAC - TOE" << endl << endl;
}

void PrintGrid(const string& grid) {
	cout << "         |   |   " << endl << "       " << grid[0] << " | " << grid[1] << " | " << grid[2] << endl 
		 << "      ___|___|___" << endl 
		 << "         |   |   " << endl << "       " << grid[3] << " | " << grid[4] << " | " << grid[5] << " " << endl 
		 << "      ___|___|___" << endl 
		 << "         |   |   " << endl << "       " << grid[6] << " | " << grid[7] << " | " << grid[8] << " " << endl 
		 << "         |   |   " << endl << "";
}

bool IsTaken(const string& grid, char choice) {
	if(grid[(int)choice - 49] != choice)
		return true;
	return false;
}

void UpdateGrid(string& grid, char choice, char c) {
	grid[(int)choice - 49] = c;
}

void RestartGrid(string& grid) {
	grid = "123456789";
}

bool SomeoneWon(const string& grid) {
	if (grid[0] == grid[1] && grid[1] == grid[2])
		return true;
	if (grid[3] == grid[4] && grid[4] == grid[5])
		return true;
	if (grid[6] == grid[7] && grid[7] == grid[8])
		return true;
	if (grid[0] == grid[3] && grid[3] == grid[6])
		return true;
	if (grid[1] == grid[4] && grid[4] == grid[7])
		return true;
	if (grid[2] == grid[5] && grid[5] == grid[8])
		return true;
	if (grid[0] == grid[4] && grid[4] == grid[8])
		return true;
	if (grid[2] == grid[4] && grid[4] == grid[6])
		return true;

	return false;
}

void PrintStats() {
	string line;
	ifstream stats("TicTacToeStats.txt");

	if (stats.is_open()) {
		cout << endl << endl;
		while (getline(stats, line)) {
			cout << line << endl;
		}
		cout << endl << endl;
		stats.close();
	}
	else
		cout << endl << "There are no stats yet." << endl << endl;
}