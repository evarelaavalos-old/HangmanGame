#include "FHangmanGame.h"

FHangmanGame::FHangmanGame() { Reset(); } // constructor

// public
int32 FHangmanGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FHangmanGame::GetLettersLeft() const { return MyLettersLeft; }
bool FHangmanGame::IsGameWon() const { return bGameIsWon; }

int32 FHangmanGame::GetMaxTries() const
{
	TMap<int32, int32> NonReapetedLettersToMaxTries{ {3,14}, {4,12}, {5,11},
													 {6,10}, {7,10}, {8,9},
													 {9,8}, {10,7}, {11,6} };
	return NonReapetedLettersToMaxTries[NonRepeatedLettersIn(MyHiddenWord)];
}

FString FHangmanGame::GetLettersEnteredAsStr() const
{
	FString LettersEnteredAsStr = "";
	// Another way of doing it
	/*
	for (auto LetterIt = MyLetterEntered.begin(); LetterIt != MyLetterEntered.end(); LetterIt++)
	{
		if (LetterIt != MyLetterEntered.begin())
		{
			LettersEnteredAsStr.append(", ");
		}
		LettersEnteredAsStr.push_back(LetterIt->first);
	}
	*/
	bool bIsFirstLetter = true;

	for (auto LetterIt : MyLetterEntered)
	{
		if (LetterIt.second)
		{
			if (!bIsFirstLetter)
			{
				LettersEnteredAsStr.append(", ");
			}
			LettersEnteredAsStr.push_back(LetterIt.first);

			bIsFirstLetter = false;
		}
	}

	return LettersEnteredAsStr;
}

FString FHangmanGame::GetWord()
{
	FString DiscoveredWord = "";

	for (auto Letter : MyHiddenWord)
	{
		if (MyLetterEntered[Letter]) {
			DiscoveredWord.push_back(Letter);
		}
		else {
			DiscoveredWord.push_back('_');
		}
	}

	return DiscoveredWord;
}

void FHangmanGame::Reset()
{
	const FString HIDDEN_WORD = "spinosaurus";

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	MyLettersLeft = MyHiddenWord.length();
	MyLetterEntered.clear();
	bGameIsWon = false;

	return;
}


ELetterStatus FHangmanGame::CheckLetterValidity(TCHAR Letter)
{
	if (!islower(Letter))
	{
		return ELetterStatus::Not_Lowercase;
	}
	else if (MyLetterEntered[Letter])
	{
		return ELetterStatus::Previously_Entered;
	}
	else
	{
		return ELetterStatus::OK;
	}
}

int32 FHangmanGame::SubmitValidLetter(TCHAR SubmitedLetter)
{
	MyLetterEntered[SubmitedLetter] = true;

	int32 LettersDiscovered = 0;

	for (auto Letter : MyHiddenWord)
	{
		if (SubmitedLetter == Letter)
		{
			LettersDiscovered++;
			MyLettersLeft--;
		}
	}

	if (MyLettersLeft == 0)	{
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}

	if (LettersDiscovered == 0)
	{
		MyCurrentTry++;
	}

	return LettersDiscovered;
}

int32 FHangmanGame::NonRepeatedLettersIn(FString Word) const
{
	int32 NonRepeatedLetters = 0;

	TMap<TCHAR, bool> LetterSeen;

	for (auto Letter : Word)
	{
		if (!LetterSeen[Letter])
		{
			NonRepeatedLetters++;
			LetterSeen[Letter] = true;
		}
	}

	return NonRepeatedLetters;
}
