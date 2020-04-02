#include "FBullCowGame.h"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTry() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,15} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}
int32 FBullCowGame::GetCurrentTry() const { return _myCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return _myHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return _bIsGameWon; }
bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1)
		return true;

	TMap<char, bool> lettersMap;
	for (auto letter : Guess)
	{
		letter = tolower(letter);
		if (lettersMap[letter])
			return false;
		lettersMap[letter] = true;
	}

	return true;
}
bool FBullCowGame::IsLowerCase(FString Guess) const
{
	for (auto letter : Guess)
	{
		if (!islower(letter))
			return false;
	}
	return true;
}
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
		return EGuessStatus::Not_Isogram;
	if (!IsLowerCase(Guess))
		return EGuessStatus::Not_Lowercase;
	if (Guess.length() != GetHiddenWordLength())
		return EGuessStatus::Wrong_Length;

	return EGuessStatus::OK;
}

void FBullCowGame::Reset()
{
	_myCurrentTry = 1;
	const FString HIDDEN_WORD = "magic";
	_myHiddenWord = HIDDEN_WORD;
	_bIsGameWon = false;
}
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	_myCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLengh = _myHiddenWord.length();
	bool Match = false;
	for (int32 i = 0; i < WordLengh; i++)
	{
		Match = false;
		for (int32 j = 0; j < WordLengh; j++)
		{
			if (Guess[j] == _myHiddenWord[i] && i == j)
			{
				Match = true;
				BullCowCount.bulls++;
			}
		}
		if (!Match)
			BullCowCount.cows++;
	}
	if (BullCowCount.cows == 0)
		_bIsGameWon = true;

	return BullCowCount;
}
