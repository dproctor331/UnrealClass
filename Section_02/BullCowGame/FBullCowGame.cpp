#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map
#include <iostream>

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "pla"; // This MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameWon = false;

	return;
}
// receives valid guess and increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	
	// loop through all letters in the guess
	for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++) { 
		for (int32 HWChar = 0; HWChar < WordLength; HWChar++) { // Compare letters against the hidden word
			if (Guess[GuessChar] == MyHiddenWord[HWChar]) { // if they match then
				if (GuessChar == HWChar) { // increment bulls if they are in the same place
					BullCowCount.Bulls++;
				}
				else { // increment cows if they are not
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == 6) { 
		bGameWon = true; 
	}
	else {
		bGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;  // Setup character map

	for (auto Letter : Word)  // For all letters of the Word
	{
		Letter = tolower(Letter); // Handle mixed case
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (islower(Letter) == false) { return false; }
	}
	
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if ( ! IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if ( ! IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != MyHiddenWord.length()) // if the length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise, it's ok
	{
		return EGuessStatus::OK; 
	}
}


