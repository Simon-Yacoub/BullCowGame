/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on mastermind*/
#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//All values initialized to zero
struct FBullCowCount 
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame{
    public:
    FBullCowGame();//constructor

    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;

    EGuessStatus CheckGuessValidity(FString) const;

    void Reset(); 

    //counts bulls and cows and incrementing turn number assuming valid guess   
    FBullCowCount SubmitValidGuess(FString);

    //^^ Please try and ignore this and focus on interface above ^^
    private:
    //see constructor for initialization
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;

    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};