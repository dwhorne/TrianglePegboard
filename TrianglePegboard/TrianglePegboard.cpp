// TrianglePegboard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<vector>
#include<string>


using namespace std;
class TrianglePegboard {
private:
	vector<char> Occupied;
	vector< vector <int > > validmoves;
	int pegToMove;
	int pegToJump;
	int pegEmpty;

	bool isMoveValid(vector< vector <int > >);
	bool anyMoreMoves(vector< vector <int > >);
	int calcNumberOccupiedPegholes();
	vector<char> setupBoard(int);
	vector<char> updateOccupiedEmptyPegholes();

public:
	void playGame();
	void displayPegboard();
};

void TrianglePegboard::playGame() {

	int intialEmptyPeg=0;

	vector<vector <int>> validmoves{
			{1,2,4}, {1,3,6},
			{2,4,7}, {2,5,9},
			{3,6,10}, {3,5,8},
			{4,2,1},{4,5,6} ,{4,7,11},{4,8,13},
			{5,8,12},{5,9,14},
			{6,3,1},{6,5,4},{6,9,13},{6,10,15},
			{7,8,9},{7,4,2},
			{8,9,10},{8,5,3},
			{9,5,2},{9,8,7},
			{10,6,3},{10,9,8},
			{11,7,4},{11,12,13},
			{12,13,14},{12,8,5},
			{13,12,11},{13,14,15}, {13,8,4},{13,9,6},
			{14,13,12},{14,9,5},
			{15,10,6},{15,14,13}


	};
	Occupied = setupBoard(intialEmptyPeg);
	displayPegboard();
	cout << "Pick a peg between 1 and 15 to be empty" << endl;
	cin >> intialEmptyPeg;
	Occupied = setupBoard(intialEmptyPeg);
	displayPegboard();

	while (anyMoreMoves(validmoves)) {
		cout << "Pick a peg to Move" << endl;
		cin >> pegToMove;
		cout << "Pick a peg to Jump" << endl;
		cin >> pegToJump;
		cout << "Pick a peg to Jump To" << endl;
		cin >> pegEmpty;
		if (isMoveValid(validmoves)) {
			updateOccupiedEmptyPegholes();
			displayPegboard();
		}
		else {
			cout << "Invalid move. Try again" << endl;
		}

	}

	int numberRemainingPegs = calcNumberOccupiedPegholes();
	cout << "There are " << numberRemainingPegs << "pegs left." << endl;
}
int TrianglePegboard::calcNumberOccupiedPegholes() {
	int numberOccupiedPegholes = 0;

	for (int i = 0; i < Occupied.size(); i++) {
		if (Occupied[i] == 'X') {
			numberOccupiedPegholes++;
		}
	}
	return numberOccupiedPegholes;
}



bool TrianglePegboard::anyMoreMoves(vector< vector <int > > validmoves) {
	int pegtoJump;
	int pegtoJumpOver;
	int pegtoLandIn;
	
	int numberofRemainingPegs = calcNumberOccupiedPegholes();
	   
	if (numberofRemainingPegs > 8) {

		return true;
	}
	else {
		for (int i = 0; i < validmoves.size(); i++) {
			for (int j = 0; j < validmoves[i].size(); j++) {
				pegtoJump = validmoves[i][0];
				pegtoJumpOver = validmoves[i][1];
				pegtoLandIn = validmoves[i][2];
				if (Occupied[pegtoJump - 1] == 'X' && Occupied[pegtoJumpOver - 1] == 'X' && Occupied[pegtoLandIn - 1] == 'O') {
					return true;

				}
			}
		}
	}
	return false;
}

vector<char> TrianglePegboard::updateOccupiedEmptyPegholes() {
	
	for (int i = 0; i < Occupied.size(); i++) {
		if (i + 1 == pegToMove) {
			Occupied[i] = 'O';
		}
		else if (i + 1 == pegToJump) {
			Occupied[i] = 'O';
		}
		else if (i + 1 == pegEmpty) {
			Occupied[i] = 'X';
		}

	}
	return Occupied;
}

vector<char> TrianglePegboard::setupBoard(int intialEmptyPeg) {
	vector<char> Occupied(15, 'X');

	for (int i = 0; i < Occupied.size(); i++) {
		if (i + 1 == intialEmptyPeg) {
			Occupied[i] = 'O';
			break;
		}
	}
	return Occupied;
}

bool TrianglePegboard::isMoveValid(vector< vector <int > > validmoves) {
	
	for (int i = 0; i < validmoves.size(); i++) {
		for (int j = 0; j < validmoves[i].size(); j++) {

			if (validmoves[i][0] == pegToMove && Occupied[pegToMove - 1] == 'X') {

				if ((validmoves[i][1] == pegToJump && Occupied[pegToJump - 1] == 'X') && (validmoves[i][2] == pegEmpty && Occupied[pegEmpty - 1] == 'O')) {
					return  true;
				}
			}
		}
	}

	return false;
}
void TrianglePegboard::displayPegboard() {
	cout << "         " << Occupied[0] << "1" << endl;
	cout << "        " << Occupied[1] << "2 " << Occupied[2] << "3" << endl;
	cout << "      " << Occupied[3] << "4 " << Occupied[4] << "5 " << Occupied[5] << "6" << endl;
	cout << "    " << Occupied[6] << "7 " << Occupied[7] << "8 " << Occupied[8] << "9 "
		<< Occupied[9] << "10" << endl;
	cout << " " << Occupied[10] << "11 " << Occupied[11] << "12 " << Occupied[12] << "13 "
		<< Occupied[13] << "14 " << Occupied[14] << "15" << endl;
}

int main()
{
	TrianglePegboard tp;
	tp.playGame();
	 
}
