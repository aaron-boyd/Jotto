#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

string arrwords[3036],pickedword, pickword(), Uniqueness(string word);
void openwords(),Game();
int Turn(), CheckJots(string w), AP=0, numoguess=0, CheckScore();

int main() {
	openwords();
	Game();
	return 0;
}


void openwords() {
	int x = 0;
	fstream textfile;
	textfile.open("jotto.txt");
	while (!textfile.eof()) {
		textfile >> arrwords[x];
		x++;
	}
}

string pickword() {
	int rnum;
	srand((unsigned)time(0));
	rnum = (rand() % 3036) + 1;
	//cout << arrwords[rnum] << endl;
	return(arrwords[rnum]);
}

void Game() {
	string initials,ans;
	int jots = 0,score;


	/// ENTER INITIALS ///
	if (AP == 0) {
		cout << "Welcome to Jotto! Please enter your initials: ";
		AP = 1;
	}
	else if (AP == 1) {
		cout << "Please enter your initials: ";
	}
	cin >> initials;
	if (initials.length() > 3 | initials.length() < 3) {
		do {
			cout << "ERROR: Please enter three(3) initials..." << endl;
			cout << "Please enter your initials: ";
			cin >> initials;
		} while (initials.length() > 3 | initials.length() < 3);
	}


	/// PICK WORD AND PLAY GAME ///
	pickedword = pickword();
	//cout << pickedword.length() << endl;
	numoguess = 0;
	do {
		jots = Turn();
		if (jots < 5) {
			cout << "You recieved " << jots << " jots!" << endl;
		}
	} while (jots < 5);


	/// GAME OVER ///
	/// CHECK TO PLAY AGAIN ///
	score = CheckScore();
	cout << "Your score is " << score << endl;
	cout << "Congrats! Would you like to play again? (Y/N): ";
	cin >> ans;

	if (ans == "Y" | ans == "y") {
		Game();
	}
	else if (ans == "N" | ans == "n") {
		cout << "Goodbye! Thanks for playing!" << endl;
		system("PAUSE");
	}
}

int Turn() {
	/// ENTER GUESS ///
	string guess;
	int score;
	cout << "Please enter your guess: ";
	cin >> guess;
	numoguess++;
	score = CheckJots(guess);
	return(score);
}

string Uniqueness(string word) {
	/// RUNS WORD THROUGH UNIQUENESS ALGORITHM ///
	string arrUni[5], unique;
	int limit, p, uc;
	p = 0;
	uc = 0;
	limit = 0;

	limit = word.length()-1;
	arrUni[0] = word.substr(0, 1);
	unique = word.substr(0, 1);

	for (int x = 0; x <= limit; x++) {
		p = 0;
		for (int y = 0; y <= limit; y++) {
			if (word.substr(x, 1) == arrUni[y]) {
				p = 1;
				break;
			}
		}
		if (p == 0) {
			uc++;
			arrUni[uc] = word.substr(x, 1);
			unique += word.substr(x, 1);
		}
		p = 0;
	}
	//cout << unique << endl;
	return(unique);
}

int CheckJots(string w) {
	/// CHECK HOW MANY JOTS ///
	string Uguess, Uword;
	int jots = 0;
	if (w == pickedword) {
		return(5);
	}
	else if (w != pickedword) {
		Uguess = Uniqueness(w);
		Uword = Uniqueness(pickedword);
		//cout << Uguess << endl << Uword << endl << Uguess.length() << endl << Uword.length() << endl;
		for (int x = 0; x < Uguess.length(); x++) {
			for (int y = 0; y < Uword.length(); y++) {
				if (Uguess.substr(x, 1) == Uword.substr(y, 1)) {
					jots++;
				}
			}
		}
	}
	return(jots);
}

int CheckScore() {
	int num;
	//cout << numoguess << endl;
	if (numoguess == 1) {
		return(100);
	}
	else if (numoguess > 1 | numoguess <= 12) {
		num = 100 - ((numoguess-1) * 5);
		return(num);
	}
	else if (numoguess == 13, 14, 15, 16) {
		return(40);
	}
	else if (numoguess == 17, 18, 19, 20) {
		return(35);
	}
	else if (numoguess > 20) {
		return(0);
	}
}