#pragma once

#include <string>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;
using TCHAR = char;

enum class ELetterStatus
{
	Invalid_Status,
	OK,
	Not_Lowercase,
	Previously_Entered
};

class FHangmanGame
{
public:
	FHangmanGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetLettersLeft() const;
	FString GetWord();
	FString GetLettersEnteredAsStr() const;
	bool IsGameWon() const;

	void Reset();
	ELetterStatus CheckLetterValidity(TCHAR);
	int32 SubmitValidLetter(TCHAR);

private:
	TMap<TCHAR, bool> MyLetterEntered; // TODO look for a more descriptive name for the variable
	FString MyHiddenWord;
	int32 MyCurrentTry;
	int32 MyLettersLeft;
	bool bGameIsWon;

	int32 NonRepeatedLettersIn(FString) const;
};
