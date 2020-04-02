#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;


FBullCowGame BCGame;

void Printintro()
{
	system("CLS");
	std::cout << "Welcome To BUll and Cows, A fun word Game\n";
	std::cout << "         }   {             ___" << std::endl;
	std::cout << "         (o o)            (o o)" << std::endl;
	std::cout << "  /-------\\ /              \\ /--------\\" << std::endl;
	std::cout << " / | BULL |O                O|  COW   |\\" << std::endl;
	std::cout << "*  |-,--  |                  |--------| *" << std::endl;
	std::cout << "   ^      ^                  ^        ^" << std::endl;

	std::cout << "\nCan you guess the ";
	std::cout << BCGame.GetHiddenWordLength();
	std::cout << " letters isogram I'm thinking of?\n";
}

void PrintGuessError(EGuessStatus guessStatus)
{
	switch (guessStatus)
	{
	case EGuessStatus::Not_Isogram:
		std::cout << "Please Enter word without repeating letters" << std::endl;
		break;
	case EGuessStatus::Not_Lowercase:
		std::cout << "Please Enter only lowercase word" << std::endl;
		break;
	case EGuessStatus::Wrong_Length:
		std::cout << "Please Enter a ";
		std::cout << BCGame.GetHiddenWordLength();
		std::cout << " letters word" << std::endl;
		break;
	default:
		break;
	}
}

FText GetValidGuess()
{
	FText guess = "";
	EGuessStatus GuessStatus = EGuessStatus::InvalidStatus;
	do
	{
		std::cout << "Enter Guess Number ";
		std::cout << BCGame.GetCurrentTry();
		std::cout << "/";
		std::cout << BCGame.GetMaxTry();
		std::cout << " : ";
		std::getline(std::cin, guess);

		GuessStatus = BCGame.CheckGuessValidity(guess);
		if (GuessStatus != EGuessStatus::OK)
			PrintGuessError(GuessStatus);
	} while (GuessStatus != EGuessStatus::OK);

	return guess;
}

void PrintGuess(FText guess)
{
	std::cout << "Your Guess is: " << guess;
	std::cout << std::endl;
}

void PrintAvailableTries()
{
	std::cout << "You have ";
	std::cout << (BCGame.GetMaxTry() - BCGame.GetCurrentTry());
	std::cout << " guesses left" << std::endl;
}

void PrintBullCowCount(FBullCowCount BullCowCount)
{
	std::cout << "Number of Bulls: ";
	std::cout << BullCowCount.bulls;
	std::cout << std::endl;
	std::cout << "Number of Cows: ";
	std::cout << BullCowCount.cows;
	std::cout << std::endl;
}

void PrintGameSummery()
{
	if (BCGame.IsGameWon())
		std::cout << "GOOOOD JOB YOU WON !!\n";
	else
		std::cout << "Better Luck Next Time :(\n";

}

void PlayGame()
{
	BCGame.Reset();
	FString guess = "";
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() < BCGame.GetMaxTry())
	{
		guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		PrintGuess(guess);
		PrintBullCowCount(BullCowCount);
		PrintAvailableTries();
	}
	PrintGameSummery();
}

bool AskToPlayAgain()
{
	std::cout << "Play Again (Y/N)?  ";
	FText answer = "";
	std::getline(std::cin, answer);
	return (answer[0] == 'Y' || answer[0] == 'y');
}

int main()
{
	do
	{
		Printintro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}