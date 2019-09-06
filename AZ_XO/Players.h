#pragma once

#include "Mandatory.h"

using std::ofstream;

class Player {
	string name;
	int w, d, l;

	public:

		Player() {}

		Player(const string& pname) : name(pname), w(0), d(0), l(0) {}

		~Player() {}

		string getName() {
			return this->name;
		}

		void Win() {
			++(this->w);
		}
		void Draw() {
			++(this->d);
		}
		void Lose() {
			++(this->l);
		}
		int getW() {
			return this->w;
		}
		int getD() {
			return this->d;
		}
		int getL() {
			return this->l;
		}
};

void ChooseNames(Player& p1, Player& p2) {
	string pName;
	char confirm = '?';

	for (int i = 1; i < 3; ++i) {
		while (confirm != 'y') {
			cout << "Enter desired name Player " << i << ": ";
			cin >> pName;
			cout << "You chose " << pName << " as your name." << endl << endl <<
				"Enter" << endl << "     \"y\" to confirm" << endl << "     any other key otherwise" << endl << ": ";
			cin >> confirm;
			if (pName.length() > 20) {
				cout << "Your name is too long, it should be up to 20 characters long." << endl;
				confirm = '?';
			}
		}
		confirm = '?';
		if (i == 1) {
			p1 = Player(pName);
		}
		else {
			p2 = Player(pName);
		}
	}
}
void UpdateWDL(string& line, int beg, int end, int numCurr) {

	string wdl = line.substr(beg, end);
	int numTot = std::stoi(wdl);
	numTot += numCurr;
	int numDig = (int)log10(numTot) + 1;
	char digit;
	--end;

	for (int i = 0; i < numDig; ++i) {
		digit = (char)((numTot % 10) + 48);
		numTot /= 10;
		line[end--] = digit;
	}
}
void UpdateStats(Player& p, string& line) {
	UpdateWDL(line, 23, 31, p.getW());
	UpdateWDL(line, 34, 42, p.getD());
	UpdateWDL(line, 45, 53, p.getL());
}

void SaveStats(Player& p1, Player& p2) {

	ifstream readStats("TicTacToeStats.txt");
	string line(53, '\0');	//

	int nameLength1 = (p1.getName()).length();
	int blanksLength1 = 20 - nameLength1;
	string blanks1(blanksLength1 + 1, '\0');

	int nameLength2 = (p2.getName()).length();
	int blanksLength2 = 20 - nameLength2;
	string blanks2(blanksLength2 + 1, '\0');

	bool oldUser1 = false, oldUser2 = false;

	ofstream tempStats("TicTacToeStatsTEMP.txt");

	if (readStats.is_open()) {

		while (getline(readStats, line)) {
			string savedName1 = line.substr(0, nameLength1);
			string savedName2 = line.substr(0, nameLength2);

			bool flag = false;

			if (p1.getName() == savedName1) {
				UpdateStats(p1, line);
				
				if (tempStats.is_open()) {
					tempStats.clear();
					tempStats << line << endl;
					flag = true;
				}
				oldUser1 = true;
			}
			else if (p2.getName() == savedName2) {
				UpdateStats(p2, line);

				if (tempStats.is_open()) {
					tempStats.clear();
					tempStats << line << endl;
					flag = true;
				}
				oldUser2 = true;
			}
			if (!flag)
				tempStats << line << endl;
		}
		readStats.close();
	}

	if (tempStats.is_open()) {
		if (!oldUser1) {
			tempStats.clear();
			tempStats << p1.getName() << blanks1 << "W:       " << p1.getW() << " D:       " << p1.getD() << " L:       " << p1.getL() << endl;
		}
		if (!oldUser2) {
			tempStats.clear();
			tempStats << p2.getName() << blanks2 << "W:	      " << p2.getW() << " D:       " << p2.getD() << " L:       " << p2.getL() << endl;
		}
		tempStats.close();
	}
	else
		cout << "Unable to save results of this duel. Sorry for the inconvenience.. :/" << endl << endl;

	/*ofstream writeStats("TicTacToeStats.txt");
	ifstream readTemp("TicTacToeStatsTEMP.txt");
	writeStats << readTemp.rdbuf();
	writeStats.close();
	readTemp.close();
	remove("TicTacToeStatsTEMP.txt");*/
	remove("TicTacToeStats.txt");
	rename("TicTacToeStatsTEMP.txt", "TicTacToeStats.txt");
}

void PlayWithStats(string& grid, Player& p1, Player& p2) {

	char choice = '?';
	int i;

	PrintGrid(grid);

	while (choice != '0') {
		for (i = 1; i < 10; ++i) {
			if ((i & 1) == 1)
				cout << endl << "Pick a cell " << p1.getName() << ": ";
			else
				cout << endl << "Pick a cell " << p2.getName() << ": ";

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
				if ((i & 1) == 1) {
					cout << endl << p1.getName() << " won." << endl;
					p1.Win();
					p2.Lose();
				}
				else {
					cout << endl << p2.getName() << " won." << endl;
					p2.Win();
					p1.Lose();
				}
				break;
			}
		}
		if (i == 10) {
			cout << endl << "It's a draw." << endl;
			p1.Draw();
			p2.Draw();
		}
		
		SaveStats(p1, p2);

		while (choice != '1' && choice != '0') {
			cout << endl << "Enter" << endl << "     \"1\" to play new game" << endl
				<< "     \"0\" to go back to main menu" << endl << ": ";
			cin >> choice;
		}

		RestartGrid(grid);
		Player tmp = p2;
		p2 = p1;
		p1 = tmp;
	}
}