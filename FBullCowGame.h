#pragma once

#include <string>
#include <map>
#define TMap std::map


using Fstring = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	// constructor
	FBullCowGame();
	
	// Const Get Methods
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	
	// Other const Methods
	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(Fstring) const;
	
	//Other Methods
	void Reset();
	FBullCowCount SubmitValidGuess(Fstring);

private:
	int32 MyCurrentTry;
	Fstring MyHiddenWord;
	bool bIsGameWon = false;

	bool IsIsogram(Fstring) const;
	bool IsLowerCase(Fstring) const;
};