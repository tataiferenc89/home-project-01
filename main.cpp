// BullCowGame.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using Fstring = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
Fstring GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main() {	
	do {
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());
	return 0;
}

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows Nyomi!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?";
	std::cout << std::endl;
	return;
}

void PlayGame() {
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	Fstring Guess = "";

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << std::endl;
	}

	PrintGameSummary();

	return;
}

Fstring GetValidGuess() {
	EWordStatus Status = EWordStatus::Invalid_Status;
	Fstring Guess;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() <<"."<< std::endl;
		std::cout << "Take your guess" << std::endl;
		getline(std::cin, Guess);
		std::cout << std::endl;
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please do not repeat letters. \n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please use only lowercase characters. \n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EWordStatus::OK);
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Want to play again? Y/N" << std::endl;
	Fstring Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'Y') || (Response[0] == 'y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU WIN! \n";
	}
	else {
		std::cout << "Better luck next time! \n";
	}
		return;
}