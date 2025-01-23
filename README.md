# Hangman 
This game was made in 2022-2023 when I was in high school and still had the time to enjoy the simpler things in life (C++ without objects). It's playable when you compile it and you can add as many words as you like to it by changing the _hangmanWords.txt_ file.

The game starts by running the *hangman()* function as a sort of "set-up". It chooses a word randomly (or as randomly as a program can choose something) and then shows a message on screen signaling the start of the game to the player.

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
This function's purpose is to generate the hidden word based on the word randomly chosen previously. This variable will be the one displayed to the user and not the actual word.
After it's generation, the *showedWord* is changed for every correct input. For the incorrect inputs the *mistakes* counter is raised.

```cpp
void wordInUse(char showedWord[251])
{

	int letter = 0;
	while (words[usedWord][letter] != NULL)
	{
		strcat(showedWord, "_ ");
		letter++;
	}
}
```

For the actual reading of user inputs, while the mistakes counter is still lower than 6, the *hangmanMsj* is being called.
Function *hangmanMsj* simply prints a message, reads the input given by the user and checks
if the guess was a word or a letter. For each type of guess it calls different functions meant to check the input: 
*hangmanWord* and *hangmanLetter* respectively.

```cpp
void hangmanMsj(int& mistakes, char showedWord[251])
{
	char guessed[251];
	cout << "\nGuess a letter or the word\n";
	cin >> guessed;
	if (guessed[1] != NULL) hangmanWord(mistakes, showedWord, guessed);
	else hangmanLetter(mistakes, showedWord, guessed);
}
```

The first function, *hangmanWord* is an extremely simple check 
to see if the word guessed is identical to the randomly picked word.
If it is it simply copies the chosen word's variable into the one that will be displayed,
else the game ends and the player lost.

```cpp
void hangmanWord(int& mistakes, char showedWord[251], char guessed[251])
{
	if (strcmp(guessed, words[usedWord]) == 0)
		strcpy(showedWord, guessed);
	else mistakes = 6;
}
```

The second function *hangmanLetter* is not only made to check if the 
letter given by the user appears in the chosen word, but also to show a 
message to the user with the letters that he already tried. The way the function does this
is by using an array to save the frequency of letters. If a letter has been used then
it's frequency will be higher than zero and the letter will be displayed.
This function makes it so you can't try a letter you've already tried in the past.
Besides generally taking care of the user and making
it so they won't accidentally type the same letter twice (what a nice quality of life feature)
it walks through every letter of the picked word, checking to see if it can be found or not.
If it is then the letter is placed in the correct spot of the *showedWord* variable. (since the generation of 
this variable appends two characters, *showedWord* and *currentWord* do not have the same lenght or
indexes for letters). If the guess is correct it shows a message afirming that to 
the user, otherwise, however, it raises the number of mistakes. At the end it calls the *hangmanProgress* function
which is meant to dislay a tiny image of the current number of mistakes made until that point 
(THE image drawn when your friend sucks at the game and you just can't wait for that little man to be fully
drawn and, well, "hanged" :P )
And because it does so many things I think the *hangmanLetter* function is, essentially, the core part of the
entire program.

```cpp
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
```