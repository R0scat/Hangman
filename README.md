# Hangman 
This game was made in 2022-2023 when I was in high school and still had the time to enjoy the simpler things in life (C++ without objects). It's playable when you compile it and you can add as many words as you like to it by changing the _hangmanWords.txt_ file.

The game starts by running the *hangman()* function that sets up the game. It chooses a word randomly (or as randomly as a program can choose something) and then shows a message on screen signaling the start of the game to the player.

```cpp
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
```

Choosing the random word is made with a separate function that reads the words from the *hangmanWords.txt* file and, using a pointer and the *strtok()* function breaks that raw input down: it removes the spaces between words and puts those words into a char matrix. From then it simply generates a random position from that matrix and marks the global variable *usedWord* with the word from that position.

```cpp
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
```

Besides the *randomWord()* function, the *hangman()* function also uses a function called *wordInUse(char[])*.

README in progress... :(
