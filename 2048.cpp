#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

struct leaderBoard{
	string name;
	int score;
};

leaderBoard leaderboard[10000];

void sortData(leaderBoard leaderboard[], int num){
	for (int i = 0; i < num; i++)
		if (leaderboard[num - 1].score > leaderboard[i].score){
			for (int j = num - 1; j >= i; j--){
				leaderboard[j+1].name = leaderboard[j].name;
				leaderboard[j+1].score = leaderboard[j].score;
			}
			leaderboard[i].name = leaderboard[num].name;
			leaderboard[i].score = leaderboard[num].score;
		}
}

int numberofDigits(int a){
	int num = 1;
	while (a / 10 > 0){
		num++;
		a /= 10;
	}
	return num;
}

void printChart(int game[4][4], int score) {

	int row = 0; // use for print the numbers of the game
	for (int counter = 1; counter < 16; counter++) {
		if (counter == 1 || counter == 5 || counter == 9 || counter == 13) {
			for (int  i = 0; i < 4; i++)
				cout << "\033[0;33m" << "\u2554" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u2557" << " " << "\033[0m";
			cout << endl;
		}
		if (counter == 3 || counter == 7 || counter == 11 || counter == 15) {
			for (int  i = 0; i < 4; i++)
				cout << "\033[0;33m" << "\u255A" << "\u2550" << "\u2550" << "\u2550" << "\u2550" << "\u255D" << " " << "\033[0m";
			cout << endl;
		}
		if (counter == 4 || counter == 8 || counter == 12)
			cout << endl;
		if (counter == 2 || counter == 6 || counter == 10 || counter == 14) {
			for (int  i = 0; i < 4; i++) {
				if (numberofDigits(game[row][i]) == 1){
					if (game[row][i] == 0)
						cout << "\033[0;33m" << "\u2551" << "\033[0m" << "    " << "\033[0;33m" << "\u2551" << "\033[0m" << " ";
					else
						cout << "\033[0;33m" << "\u2551" << "\033[0m" << " " << "\033[0;35m" << game[row][i] << "\033[0m" << "  " << "\033[0;33m" << "\u2551" << "\033[0m" << " ";
					}
				else if (numberofDigits(game[row][i]) == 2)
					cout << "\033[0;33m" << "\u2551" << "\033[0m" << " "  << "\033[0;35m" << game[row][i] << "\033[0m" << " " << "\033[0;33m" << "\u2551" << "\033[0m" << " ";
				else if(numberofDigits(game[row][i]) == 3)
					cout << "\033[0;33m" << "\u2551" << "\033[0m" << "\033[0;35m" << game[row][i] << "\033[0m" << " " << "\033[0;33m" << "\u2551" << "\033[0m" << " ";
				else
					cout << "\033[0;33m" << "\u2551" << "\033[0m" << "\033[0;35m" << game[row][i] << "\033[0m" << "\033[0;33m" << "\u2551" << "\033[0m" << " ";
				}

			row++;
			cout << endl;

		}
	}
	cout << "Score : " << score;

}

void operatorW(int game[4][4], int &score, bool &W){
    W = false;
	for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				if (game[i][j] != 0)
					for (int k = 0; k < i; k++)
						if (game[k][j] == 0){
							game[k][j] = game[i][j];
							game[i][j] = 0;
							W = true;
						}

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 4; j++)
            if (game[i][j] == game[i+1][j] && game[i][j] != 0) {
                game[i][j] += game[i+1][j];
                game[i+1][j] = 0;
                score += game[i][j];
                W = true;
            }

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (game[i][j] != 0)
                for (int k = 0; k < i; k++)
                    if (game[k][j] == 0){
                        game[k][j] = game[i][j];
                        game[i][j] = 0;
                        W = true;
                    }
}


void operatorA(int game[4][4], int &score, bool &A){
    A = false;
	for(int j = 0; j < 4; j++)
			for(int i = 0; i < 4; i++)
				if (game[i][j] != 0)
					for (int k = 0; k < j; k++)
						if (game[i][k] == 0){
							game[i][k] = game[i][j];
							game[i][j] = 0;
							A = true;
						}

    for(int j = 0; j < 3; j++)
        for(int i = 0; i < 4; i++)
            if (game[i][j] == game[i][j+1] && game[i][j] != 0) {
                game[i][j] += game[i][j+1];
                game[i][j+1] = 0;
                score += game[i][j];
                A = true;
            }

    for(int j = 0; j < 4; j++)
        for(int i = 0; i < 4; i++)
            if (game[i][j] != 0)
                for (int k = 0; k < j; k++)
                    if (game[i][k] == 0){
                        game[i][k] = game[i][j];
                        game[i][j] = 0;
                        A = true;
                    }
}

void operatorS(int game[4][4], int &score, bool &S){
    S = false;
	for(int i = 3; i > -1; i--)
			for(int j = 0; j < 4; j++)
				if (game[i][j] != 0)
					for (int k = 3; k > i; k--)
						if (game[k][j] == 0){
							game[k][j] = game[i][j];
							game[i][j] = 0;
							S = true;
						}

    for(int i = 3; i > 0; i--)
        for(int j = 0; j < 4; j++)
            if (game[i][j] == game[i-1][j] && game[i][j] != 0) {
                game[i][j] += game[i-1][j];
                game[i-1][j] = 0;
                score += game[i][j];
                S = true;
            }

    for(int i = 3; i > -1; i--)
        for(int j = 0; j < 4; j++)
            if (game[i][j] != 0)
                for (int k = 3; k > i; k--)
                    if (game[k][j] == 0){
                        game[k][j] = game[i][j];
                        game[i][j] = 0;
                        S = true;
                    }
}

void operatorD(int game[4][4], int &score, bool &D){
    D = false;
	for(int j = 3; j > -1; j--)
			for(int i = 0; i < 4; i++)
				if (game[i][j] != 0)
					for (int k = 3; k > j; k--)
						if (game[i][k] == 0){
							game[i][k] = game[i][j];
							game[i][j] = 0;
							D = true;
						}
    for(int j = 3; j > 0; j--)
        for(int i = 0; i < 4; i++)
            if (game[i][j] == game[i][j-1] && game[i][j] != 0) {
                game[i][j] += game[i][j-1];
                game[i][j-1] = 0;
                score += game[i][j];
                D = true;
            }

    for(int j = 3; j > -1; j--)
        for(int i = 0; i < 4; i++)
            if (game[i][j] != 0)
                for (int k = 3; k > j; k--)
                    if (game[i][k] == 0){
                        game[i][k] = game[i][j];
                        game[i][j] = 0;
                        D = true;
                    }
}


//functions numW and numA use to check if there is a state for playing or not
int numW(int game[4][4]){
	int num = 0;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 4; j++)
			if (game[i][j] == game[i+1][j] && game[i][j] != 0)
				num++;
	return num;
}

int numA(int game[4][4]){
	int num = 0;
	for(int j = 0; j < 3; j++)
		for(int i = 0; i < 4; i++)
			if (game[i][j] == game[i][j+1] && game[i][j] != 0)
				num++;
	return num;
}

bool haveSpace(int game[4][4]){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (game[i][j] == 0)
                return 1;
    return 0;
}

void randNumber(int game[4][4], int randnum[4]) { //put randumnymber in the play
	if(haveSpace(game)){
		int i = rand()%4;
		int j = rand()%4;
		if (game[i][j] == 0)
			game[i][j] = randnum[rand()%4];
		else
			randNumber(game,randnum);
	}
}

void sortfile(){

    int num = 0; //counting number of playing game
    string name, name1; //name1 use for read names from files and sort them
    int score;

    //read file2048 and sort datas
    ifstream readLeaderBoard("file2048.txt");

	while(readLeaderBoard >> name) {
        if (name == ":") {
            readLeaderBoard >> score;
            leaderboard[num].score = score;
            leaderboard[num].name = name1;
            num++;
            name1 = "";
            }
        else {
            name1 += name;
            name1 += ' ';
    	}
	}
    readLeaderBoard.close();

    sortData(leaderboard, num);

    ofstream saveData("file2048.txt");

	if (saveData.is_open()){
		for (int i = 0; i < num; i++)
			saveData << leaderboard[i].name << ": " << leaderboard[i].score << '\n';
	}
	saveData.close();
}

void theGame(string name, int &score) {
	int randnum[4] = {2, 2, 2, 4};
	int game[4][4];
	bool W,A,S,D; //booleans check if a change has been made in the game or not
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			game[i][j] = 0;

	srand(time(0));
	randNumber(game,randnum);
	randNumber(game,randnum);
	printChart(game,score);

	while (1){
		char move = getch();
		system("cls");

		if (move == 'W'){
			operatorW(game,score,W);
			if (W)
                randNumber(game,randnum);
		}

		if (move == 'A'){
			operatorA(game,score,A);
            if (A)
                randNumber(game,randnum);
		}

		if (move == 'S'){
			operatorS(game,score,S);
			if (S)
                randNumber(game,randnum);
		}

		if (move == 'D'){
			operatorD(game,score,D);
			 if (D)
                randNumber(game,randnum);
		}
		if (move == 'Z'){
            cout << "\033[0;34m" << "Press space to return to the menu" << "\033[0m";
			break;
		}

		bool y = false;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (game[i][j] == 2048){
					cout << "\033[0;32m" << "You win the Game!" << "\033[0m";
					y = true;
				}
		if (y)
			break;

		bool x = true;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (game[i][j] == 0)
					x = false;
		if (numW(game) > 0 || numA(game) > 0)
			x = false;
		if (x) {
			cout << "\033[0;31m" << "Game Over" << "\033[0m" << endl;
			cout << name << "\033[0;33m" << "'s score is: " << score << "\033[0m";
			break;
		}

		printChart(game,score);
	}
}

int main() {
	cout << "\033[0;36m" << "Press space to start the game :)" << "\033[0m";


	while (1) {
		int n = getch();
		string name, line; //line use for read datas from file
		int score = 0;

        if (n == 32){ //MENU
            system("cls");
            cout <<  "\033[0;33m" << "Choose your desired operation:\n1)New Game\n2)Leaderboard\n3)Exit\n" << "\033[0m";
        }

		else if (n == 49){  //NEW GAME
			system("cls");
			cout << "Enter your name: ";
			getline(cin,name);
			system("cls");
			theGame(name,score);

			ofstream saveLeaderBoard("file2048.txt", ios::app); //save datas in file2048
			if (saveLeaderBoard.is_open()){
				saveLeaderBoard << name << " : " << score << '\n';
            }
			saveLeaderBoard.close();

            sortfile();
		}

		else if (n == 50){  //LEADERBOARD
			system("cls");

			ifstream readData("file2048.txt");

			if (readData.is_open())
				while(getline(readData, line))
					cout << line << endl;
			readData.close();

			cout << endl << "\033[0;31m" << "Press space to return to the menu." << "\033[0m";

		}

		else if (n == 51){ //EXIT
			system("cls");
			cout << "\033[0;36m" <<"Thanks for playing the game^^\n" << "\033[0m";
			return 0;
		}
		else{
			system("cls");
			cout << "\033[0;31m" <<"You enter a wrong number! Press space to return to the menu." << "\033[0m";
		}
	}
}
