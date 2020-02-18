#include <iostream>
#include <string>
#include "FHangmanGame.h"

using FText = std::string;
using int32 = int;
using TCHAR = char;

void PrintIntro();
void PlayGame();
TCHAR GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FText SpaceWord(FText);

FHangmanGame FHMGame;

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to the Hangman Game, a fun game of words!\n";
	std::cout << "             +-------+         \n";
	std::cout << "             |      \\O/       \n";
	std::cout << "             |       `         \n";
	std::cout << "             |       |         \n";
	std::cout << "             |      / \\      \n";
	std::cout << "            ---                \n";
	std::cout << "Can you guess this " << FHMGame.GetWord().length();
	std::cout << " letter word before using the " << FHMGame.GetMaxTries();
	std::cout << " tries?\n";
	std::cout << std::endl;
}

void PlayGame()
{
	FHMGame.Reset();

	int32 MaxTries = FHMGame.GetMaxTries();

	while (!FHMGame.IsGameWon() && FHMGame.GetCurrentTry() <= MaxTries)
	{
		TCHAR Guess = GetValidGuess();

		int32 LettersDiscovered = FHMGame.SubmitValidLetter(Guess);

		if (LettersDiscovered == 0)
		{
			std::cout << "Wrong Letter. Please try another one.\n";
		}
		else if (LettersDiscovered > 0)
		{
			std::cout << "You have discovered " << LettersDiscovered << " letters. ";
			std::cout << "You still have " << FHMGame.GetLettersLeft() << " letters left.\n";
		}

		std::cout << std::endl;
	}
}

TCHAR GetValidGuess()
{
	ELetterStatus Status = ELetterStatus::Invalid_Status;
	do {
		FText WordToPrint = SpaceWord(FHMGame.GetWord());

		std::cout << "Try " << FHMGame.GetCurrentTry();
		std::cout << " of " << FHMGame.GetMaxTries() << ". ";
		std::cout << WordToPrint;
		std::cout << " (Submited Words: " << FHMGame.GetLettersEnteredAsStr() << ")\n";

		std::cout << "Enter a letter: ";
		FText Guess = "";
		getline(std::cin, Guess);
		TCHAR FirstChar = Guess[0];

		Status = FHMGame.CheckLetterValidity(FirstChar);

		switch (Status)
		{
			case ELetterStatus::Not_Lowercase:
				std::cout << "Please enter a lowercase letter.\n";
				break;
			case ELetterStatus::Previously_Entered:
				std::cout << "This letter has been submited previously. Try another one.\n";
				break;
			case ELetterStatus::OK:
				return FirstChar;
		}

		std::cout << std::endl;
	} while (Status != ELetterStatus::OK);
}

void PrintGameSummary()
{
	if (FHMGame.IsGameWon())
	{
		int32 CurrentTry = FHMGame.GetCurrentTry();

		std::cout << "CONGRATULATIONS! YOU WON THE GAME! \n";
		std::cout << "The hidden word were " << FHMGame.GetWord();

		if (CurrentTry == 1)
		{
			std::cout << " and you beat it in your FIRST TRY.\n";
		}
		else
		{
			std::cout << " and it only takes you " << CurrentTry << " tries.\n";
		}
	}
	else
	{
		std::cout << "I'm sorry, you lose. Better luck next time.\n";
	}

	std::cout << std::endl;
}

bool AskToPlayAgain()
{
	std::cout << "Would you like to play again (y/n)? ";

	FText Answer;
	getline(std::cin, Answer);

	std::cout << std::endl;

	return Answer[0] == 'y' || Answer[0] == 'Y';
}

FText SpaceWord(FText WordToSpace)
{
	FText SpacedWord = "";
	bool bIsFirstLetter = true;

	for (auto Letter : WordToSpace)
	{
		if (!bIsFirstLetter)
		{
			SpacedWord.push_back(' ');
		}
		SpacedWord.push_back(Letter);

		bIsFirstLetter = false;
	}

	return SpacedWord;
}