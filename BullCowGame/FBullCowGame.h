#pragma once
#include <string>


using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus
{
	InvalidStatus,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class  FBullCowGame
{
public:
	FBullCowGame();

	int32 GetMaxTry() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 _myCurrentTry;
	FString _myHiddenWord;
	bool _bIsGameWon;
	bool IsIsogram(FString Guess) const;
	bool IsLowerCase(FString Guess) const;

};

