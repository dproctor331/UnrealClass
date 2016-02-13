/* 
This is the console executable that makes use of the BullCow class
This acts as the view in the MVC pattern, and it is responsible for all
user interaction.  For game logic see the FBullCowGame class
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

//Entry Point for our application
int main() 
{	
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
}

// Plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//Loop asking for guesses while the game is NOT won and there are still turns
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess(); 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}

void PrintIntro() 
{
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "\n\n|||||/--------------------------------------------------------------\\|||||\n";
	std::cout << "||||/----------------------------------------------------------------\\||||\n";
	std::cout << "|||||     Welcome to Bulls and Cows, a fun word game.                |||||\n";
	std::cout << "|||||     Can you get the " << WORD_LENGTH << " letter isogram that I'm thinking of?     |||||\n";
	std::cout << "||||\\----------------------------------------------------------------/||||\n";
	std::cout << "|||||\\--------------------------------------------------------------/|||||\n\n";
	return;
}

//get a guess from the user
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter the word using all lowercase letters.\n";
			break;
		default:
			break; // Assume guess is valid
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations, you won!! \n";
	}
	else
	{
		std::cout << "Sorry, you lose! \n";
	}
}


