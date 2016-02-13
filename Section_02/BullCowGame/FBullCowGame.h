/* The game logic (no view code or direct user interaction)
The game is a simple gguess the word game based on Mastermind
*/

#pragma once
#include <string>

// to make the syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 
	
	void Reset(); 
	// Count bulls and cows and increase try number (assumes guess is valid)
	FBullCowCount SubmitValidGuess(FString);

// Please try and ignore this and focus on the interface above
private:
	// See constructor for initialization 
	bool IsIsogram(FString Word) const;
	bool IsLowercase(FString Word) const;
	
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameWon = false;
};