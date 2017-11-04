//Kevin Beltran, 4/4/2017, Small Program 3 - Hangman

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <ctype.h> 
#include <string.h>
#define WSIZE 30

//Determines if the player wants to play again 
void Quit(char *againPtr);

//Displays instructions 
void Rules();

//initializes the word to be guessed to *** based on word size 
void InitializeWord(char starWord[], int wordsize);

//play a round of the game, returns a 1 if the user wins and a 0 if the user did not win 
int PlayOneRound(char solutionWord [], char starWord[]);

//gets a letter guess from the user 
void GetLetter(char *letterPtr);

//compares two char arrays returns 1 if match, 0 if dont match 
int CompareArrays( char wordGuess[], char solutionWord[]);

//notifies the user if they won or lost 
void WonLost(char solutionWord[], int win);

//replaces the star with the letter guessed 
//returns a 1 if the letter is in the word, returns a 0 if the letter 
//is not in the word 
int PlaceLetter(char solutionWord[], char starWord[], char target);

//changes a word to upper or lower case 
void ChangeCase(char word[]);

//draws the hangman 
void DrawHangman(int num);

//compare wordguess to solutionword
//returns 1 if they match, 0 if they don't
int CompareAr(char sol[], char wordguess[]);

int main()
{
	char *GuessLetter;
	char letter;
	char solutionWord[WSIZE], starWord[WSIZE];
	char *PlayGame;
	int len;
	int win = 0;
	int round = 0;
	int i;
	char list[5][WSIZE];
	FILE* hangmanWordsPtr;
	PlayGame = 'y';
	Rules();
	while (PlayGame == 'y' || PlayGame == 'Y')
	{
		win = 0;
		//get solution words from file
		hangmanWordsPtr = fopen("hangmanWords.txt", "r");
		for (i = 0; i < 5; i++)
		{
			fscanf(hangmanWordsPtr, " %s", &list[i]);
			//test
			//printf("\n%s", list[i]);
		}
		//test
		//printf("\nwin = %d", win);

		//get solution word for round
		strcpy(solutionWord, list[round]);

		//change solution to uppercase
		ChangeCase(solutionWord);
		//test
		//printf("\nchanged solutionWord = %s", solutionWord);

		//generate starword
		len = strlen(solutionWord);
		InitializeWord(starWord, len);

		//play round
		win = PlayOneRound(solutionWord, starWord);
		//test
		//printf("win = %d", win);

		//check if user has won or lost the round
		WonLost(solutionWord, win);

		//ask user if they would like to play again
		Quit(&PlayGame);

		//next round
		round++;

		//reset list of solution words once limit is reached
		if (round > 4)
		{
			round = 0;
		}
	}
	fclose(hangmanWordsPtr);
	return 0;
}

//Determines if the player wants to play again 
void Quit(char *againPtr)
{
	//ask user if they would like to play again
	printf("\nWould you like to play again?\nEnter Y to CONTINUE, anything else to QUIT: ");

	//get answer from user
	scanf(" %c", againPtr);
}

//Displays instructions 
void Rules()
{
	printf("\n\tWELCOME TO HANGMAN!\n\nPlease read the following instructions before you play.\n\t- You will be presented with a word to be guessed\n\t- Guess letters one at a time\n\t- You can have up to six incorrect letter guesses\n\t- YOU CAN ONLY GUESS THE WORD IF YOU HAVE MADE A CORRRECT LETTER GUESS!\n\n\t- The game will be OVER when you have guessed\n\t\tthe word correctly\n\t\tor when you have guessed SIX letters incorrectly.\n\n\tHAVE FUN!");
}

//initializes the word to be guessed to *** based on word size 
void InitializeWord(char starWord[], int wordsize)
{
	int i;
	for (i = 0; i < wordsize; i++)
	{
		starWord[i] = '*';
	}
	starWord[wordsize] = '\0';
}

//play a round of the game, returns a 1 if the user wins and a 0 if the user did not win 
int PlayOneRound(char solutionWord[], char starWord[])
{
	int totalletters = 0, wrongletters = 0, same, match = 0;
	char guessletters[WSIZE] = "";
	char* userletterPtr;
	int i, wordlength, guesslength;
	char userletter;
	char wordGuess[WSIZE];
	while (wrongletters < 6)
	{
		same = 0;
		wordlength = strlen(solutionWord);
		guesslength = strlen(guessletters);
		//test
		//printf("\n\nwrongletters = %d", wrongletters);
		//printf("\nmatch = %d", match);
		//printf("\nsame = %d", same);
		//printf("\n\nwordlength = %d", wordlength);

		//present letters guessed
		printf("\n\n--------------------\n\n\nHere are the letters guessed so far: %s", guessletters);

		//present starword
		printf("\nGuess a letter: %s", starWord);

		//ask + get guess
		//change case
		GetLetter(&userletterPtr);
		userletter = userletterPtr;
		//test
		//printf("\n\nuserletter = %c", userletter);

		//add the letter to the guessed letters
		guessletters[guesslength] = userletter;
		guessletters[guesslength + 1] = '\0';
		//test
		//printf("\nguessletters = %s", guessletters);

		//check if letter is in word, if not wrongletter++(draw hangman)
		same = PlaceLetter(solutionWord, starWord, userletter);
		if (same == 1)
		{
			//tell user the letter is in the word
			printf("\n\nThe letter %c is in the word!", userletter);

			//ask user to guess word
			printf("\nGuess the word: %s\n\n", starWord);

			//get guess word from user
			scanf(" %s", &wordGuess);

			//change guess word to uppercase
			ChangeCase(wordGuess);

			////check if guessword matches solutionword, if it does wrongletters=6
			match = CompareArrays(wordGuess, solutionWord);
			if (match == 1)
			{
				wrongletters = 6;
				return 1;
			}
			else
			{
				printf("\nSorry, but %s is not the word", wordGuess);
			}
		}
		if (same == 0)
		{
			//tell user the letter is not in the word
			printf("\n\nThe letter %c is not in the word!", userletter);

			//draw part of hangman
			DrawHangman(wrongletters);

			//wrongletters++
			wrongletters++;
		}
	}
	return match;
}

//gets a letter guess from the user 
void GetLetter(char *letterPtr)
{
	//ask user for a letter guess
	printf("\nEnter a guess: ");

	//get letter guess
	scanf(" %c", letterPtr);

	//change letter to uppercase
	*letterPtr = toupper(*letterPtr);

	//printf("%c", *letterPtr);
}

//compares two char arrays returns 1 if match, 0 if dont match 
int CompareArrays(char wordGuess[], char solutionWord[])
{
	if (strcmp(wordGuess, solutionWord) == 0)
	{
		return 1;
	}
	else return 0;
}

//notifies the user if they won or lost 
void WonLost(char solutionWord[], int win)
{
	if (win == 1)
	{
		printf("\n\nYay! Congratulations! You won!!! The word was %s", solutionWord);
	}
	else
	{
		printf("\n\nSorry, you did not win. The word was %s", solutionWord);
	}
}

//replaces the star with the letter guessed 
//returns a 1 if the letter is in the word, returns a 0 if the letter 
//is not in the word 
int PlaceLetter(char solutionWord[], char starWord[], char target)
{
	int same = 0;
	int wordlength = strlen(solutionWord);
	int i;
	for (i = 0; i < wordlength; i++)
	{
		//test
		//printf("\n\nword[%d] = %c", i, solutionWord[i]);
		//printf("\n\nuserletter = %c", target);

		//if letter is in the word, make same = 1 and add to starWord
		if (solutionWord[i] == target)
		{
			same = 1;
			starWord[i] = target;
		}
	}
	return same;
}

//changes a word to upper or lower case 
void ChangeCase(char word[])
{
	int len = strlen(word);
	int i;
	for (i = 0; i < len; i++)
	{
		word[i] = toupper(word[i]);
		//test
		//printf("\n%c", word[i]);
	}
}

//draws the hangman 
void DrawHangman(int num)
{
	char *hangman[] = {
	"HEAD",
	"LEFT HAND",
	"RIGHT HAND",
	"TORSO",
	"LEFT LEG",
	"RIGHT LEG"
	};
	printf("\n\n*********************************************\n\nDrawing Part %d: THE %s\n\nYou have made %d wrong letter guesses\n\n%d wrong letter guesses left", num + 1, hangman[num],num + 1, 5 - num);
}

//compare wordguess to solutionword
//returns 1 if they match, 0 if they don't
int CompareAr(char sol[], char wordguess[])
{
	if (strcmp(wordguess, sol) == 0)
	{
		return 1;
	}
	else return 0;
}