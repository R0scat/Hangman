
#pragma warning(disable : 4996)
#include <fstream>;
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

int wordNr; // total number of words 
int usedWord; // randomly selected word number
int all[27], counterMiss[6][6]; // frequency vector to check which letters were correct; vector to see which letters were introduced into the game
int tried; //used only to check if it's the start of the game or not (da e cam useless dupa yk)
char words[251][50];

ifstream fin("hangmanWords.txt");

void randomWord()
{
	char* p, selectWord[251];
	int wrdCounter = 0;
	fin.get(selectWord, 2400);
	//cout << selectWord << endl;
	p = strtok(selectWord, " ");
	while (p != NULL)
	{
		strcpy(words[wrdCounter++], p);
		p = strtok(NULL, " ");

	}
	wordNr = wrdCounter;
	//int randomNr = rand() % 20 + 1;
	//cout << "randomNr = " << randomNr << "\n";
	//for (int i = 0; i <= randomNr; i++) // intotdeauna o sa imi dea acelasi cuvant idk how to fix it fr
	usedWord = rand() % (wordNr - 1) + 0;
	//cout << wordNr << " " << usedWord << endl;
}
void wordInUse(char showedWord[251])
{

	int letter = 0;
	while (words[usedWord][letter] != NULL)
	{
		strcat(showedWord, "_ ");
		letter++;
	}
}
// counterMiss variables vs how they should appear:
// 010   0     010
// 423  /|\    423
// 605  / \    403
// lines and columns for each change
//l1 c2; l2 c2, l2 c3, l2 c1; l3 c3, l3 c1;
// mis1; mis2;  mis3;   mis4;  mis5; mis6;
void hangmanColumns(int line)
{
	int column;
	for (column = 1; column <= 3; column++)
		switch (counterMiss[line][column])
		{
		case 0: cout << " "; break;
		case 1: cout << 0; break;
		case 2: cout << "|"; break;
		case 3: cout << "\\"; break;
		case 4: cout << "/"; break;
		}
	cout << "\n";
}
void checkMiss(int& mistakes)
{
	cout << "\nThe word does not contain this letter, sorry...\n";
	mistakes++;
	switch (mistakes)
	{
	case 1: counterMiss[1][2] = 1; break;
	case 2: counterMiss[2][2] = 2; break;
	case 3: counterMiss[2][3] = 3; break;
	case 4: counterMiss[2][1] = 4; break;
	case 5: counterMiss[3][3] = 3; break;
	case 6: counterMiss[3][1] = 4; break;
	}
}
void hangmanProgress()
{
	cout << " -----\n";
	cout << " |   |\n";
	cout << " |  "; hangmanColumns(1);
	cout << " |  "; hangmanColumns(2);
	cout << " |  "; hangmanColumns(3);
	cout << " --------\n";
}
void hangmanWord(int& mistakes, char showedWord[251], char guessed[251])
{
	if (strcmp(guessed, words[usedWord]) == 0)
		strcpy(showedWord, guessed);
	else mistakes = 6;
}
void hangmanLetter(int& mistakes, char showedWord[251], char guessed[251])
{
	char guessedltr = 'a', currentWord[251];
	int letter = 1, correct = 0, foundLetter = 0, totalLetters;
	while (foundLetter == 0)
	{

		guessedltr = guessed[0];
		if (all[guessedltr - 'a'] != 0) cout << "\nLetter already tried, try another one: ", cin >> guessed[0];
		else all[guessedltr - 'a'] = 1, foundLetter = 1;
	}
	if (tried)
	{
		cout << "\nLetters you've already tried: ";
		for (int i = 0; i < 26; i++)
			if (all[i]) cout << (char)(i + 'a') << " ";
	}
	cout << "\n";
	tried = 1;
	totalLetters = letter;
	strcpy(currentWord, words[usedWord]);
	if (strchr(currentWord, guessedltr) != NULL)
	{
		letter = 0;
		while (currentWord[letter] != NULL)
		{
			if (currentWord[letter] == guessedltr)
				showedWord[letter * 2] = guessedltr;
			letter++;
		}
		correct = 1;
	}
	cout << showedWord << "\n";
	if (correct) cout << "Guessed a correct letter!\n";
	else checkMiss(mistakes);
	hangmanProgress();
	cout << "\n";
}
void hangmanMsj(int& mistakes, char showedWord[251])
{
	char guessed[251];
	cout << "\nGuess a letter or the word\n";
	cin >> guessed;
	if (guessed[1] != NULL) hangmanWord(mistakes, showedWord, guessed);
	else hangmanLetter(mistakes, showedWord, guessed);
}
void hangman()
{
	char showedWord[251] = "_ ";
	int mistakes = 0;
	srand(time(NULL));
	randomWord();
	wordInUse(showedWord);
	cout << "Welcome to hangman! The random word looks like this:\n" << showedWord;
	while (mistakes <= 5)
	{
		hangmanMsj(mistakes, showedWord);
		if (strchr(showedWord, '_') == NULL)
		{
			cout << "Nice! You won!\n";
			mistakes = 7;
		}
	}
	if (mistakes == 6) cout << "Offf, you lost...\n" << "The word was: " << words[usedWord] << "\n";
}

int main()
{
	hangman();
	return 0;
}

