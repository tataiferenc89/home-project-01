
#include "FBullCowGame.h"


//Constructor
FBullCowGame::FBullCowGame() {
	Reset();
}

//Get methods

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{{3,5}, {4,7}, {5,8}, {6,16}, {7,20}};
	return WordLengthToMaxTries[GetHiddenWordLength()]; 
}

bool FBullCowGame::IsIsogram(Fstring Word) const { 
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}

	}

	return true; 

}

bool FBullCowGame::IsLowerCase(Fstring Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

//Other methods

void FBullCowGame::Reset() {
	const Fstring HIDDEN_WORD = "kal";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

EWordStatus FBullCowGame::CheckGuessValidity(Fstring Guess) const{
	if (!IsIsogram(Guess)) {
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) {
		return EWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EWordStatus::Wrong_Length;
	}
	else {
		return EWordStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(Fstring Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	for (size_t i = 0; i < WordLength; i++)
	{
		for (size_t j = 0; j < WordLength; j++)
		{
			if (Guess[i] == MyHiddenWord[j] && i == j) {
				BullCowCount.Bulls++;
			} 
			else if (Guess[i] == MyHiddenWord[j]) {
				BullCowCount.Cows++;
			}
		}

	}
	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;
}
