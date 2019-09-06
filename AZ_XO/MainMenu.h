#pragma once

#include "Mandatory.h"
#include "Guests.h"
#include "Players.h"

void MainMenu(string& grid, char& choice) {

	cout << "Enter " << endl << "     \"1\" to play as guests" << endl << "     \"2\"         for stats"
		<< endl << "     \"3\"         for stats against AI" << endl << endl << "     \"4\" for stats" << endl
		<< "     \"0\" to exit game" << endl << endl << ": ";

	cin >> choice;

	while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '0') {
		cout << "Invalid choice. Enter " << endl << "     \"1\" to play as guests" << endl
			<< "     \"2\"         for stats" << endl
			<< "     \"3\"         for stats against AI" << endl << endl << "     \"4\" for stats" << endl
			<< "     \"0\" to exit game" << endl << endl << ": ";
		cin >> choice;
	}

	Player p1;
	Player p2;

	switch (choice) {
	case '1':
		Play(grid);
		break;
	case '2':
		ChooseNames(p1, p2);
		PlayWithStats(grid, p1, p2);
		break;
	case '3':
		cout << endl << "AI doesn't want to play, maybe later." << endl << endl;
		break;
	case '4':
		PrintStats();
		break;
	case '0':
		return;
	}
}
