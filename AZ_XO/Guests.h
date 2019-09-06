#pragma once

#include "Mandatory.h"

void Play(string& grid) {

	char choice = '?';
	int i;

	PrintGrid(grid);

	while (choice != '0') {
		for (i = 1; i < 10; ++i) {
			cout << endl << "Pick a cell: ";
			cin >> choice;

			while (IsTaken(grid, choice) || !isdigit(choice) || choice == '0') {
				cout << endl << "Invalid choice. Choose free cell from 1-9: ";
				cin >> choice;
			}

			if ((i & 1) == 1)
				UpdateGrid(grid, choice, 'X');
			else
				UpdateGrid(grid, choice, 'O');

			cout << endl << endl;

			PrintGrid(grid);

			if (SomeoneWon(grid)) {
				if ((i & 1) == 1)
					cout << endl << "Player 1 won." << endl;
				else
					cout << endl << "Player 2 won." << endl;
				break;
			}
		}
		if (i == 10)
			cout << endl << "It's a draw." << endl;

		while (choice != '1' && choice != '0') {
			cout << endl << "Enter" << endl << "     \"1\" to play new game" << endl
				<< "     \"0\" to go back to main menu" << endl << ": ";
			cin >> choice;
		}

		RestartGrid(grid);
	}
}