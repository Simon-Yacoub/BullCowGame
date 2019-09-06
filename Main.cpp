#pragma once
/* This is the console executable, that makes use of the 
class FBullCowGame. This acts as the view in a MVC pattern, and is 
responsible for all user interaction. For game logic see the FBullCowGame class
 */
//cl Main.cpp FBullCowGame.cpp /EHsc

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game

int main()
{
    bool bPlayAgain = false;
    do{
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }while(bPlayAgain); 
    return 0;
}

void PrintIntro()
{
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << " /\\    /\\" << std::endl;
	std::cout << "/ /    \\ \\" << std::endl;
	std::cout << "\\ \\    / /   O_____O" << std::endl;
	std::cout << " \\ \\__/ /   / ^   ^ \\" << std::endl;
	std::cout << "( ^   ^ )   ( (o o) ) " << std::endl;
	std::cout << " \\(o o)/     \\     /" << std::endl;
	std::cout << "  \\_U_/       \\_O_/" << std::endl;

    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength()
    << " letter isogram I'm thinking of?\n";
    return;
}

//plays a single game to completon
void PlayGame(){
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    //loop number of turns asking for guess while game is NOT won
    //and there are still tries remaining 
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
        FText Guess = GetValidGuess(); 

        //submit valid guess to the game and recieve count 
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        //print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows;
        std::cout << std::endl;
        std::cout << std::endl;
    }
    PrintGameSummary();
    return;
}
//loop continually until user gives a valid guess
FText GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    do 
    {
        //get a guess from a player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);

        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n\n";
                break;
        }
    }while (Status != EGuessStatus::OK);
    return Guess;
}

//ask to play again
bool AskToPlayAgain(){
    std::cout << "Would you like to play again (y/n)? ";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] ==  'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
    if(BCGame.IsGameWon())
    {
        std::cout << "Well Done - You Win!\n";
    }
    else
    {
        std::cout << "You Lost - Better luck next time.\n";
    }
    
}