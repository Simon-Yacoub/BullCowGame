#pragma once
#include "FBullCowGame.h"
#include <map>
//to make syntax unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
    TMap<int32, int32> WordLengthToMaxTries { {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
    return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "play";//this MUST be an isogram
    MyHiddenWord = HIDDEN_WORD;

    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if(!IsIsogram(Guess))//if the guess isnt isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess)) //if the guess isnt all lowercase
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

//recieves a valid guess, increments turn #, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();// assuming same length as guess

    //loop through all letters in the hiddenword
    for(int32 MHWChar = 0; MHWChar < WordLength; MHWChar++){
        //compare letters against the guess
        for(int32 GChar = 0; GChar < WordLength; GChar++){
            if(Guess[GChar] == MyHiddenWord[MHWChar]){//if they match then 
                if(MHWChar == GChar){//increment bulls if they are in the same place
                    BullCowCount.Bulls++;
                }else{//increment cows if they are not
                    BullCowCount.Cows++;
                }
            }
        }
    }
    //check if the answer was correct (game is won)
    if(WordLength == BullCowCount.Bulls){
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    //treat 0 and 1 letter words as isograms
    if(Word.length() <= 1) { return true; }

    TMap<char, bool> LetterSeen; //setup our map
    for (auto Letter : Word)
    {
        Letter = tolower(Letter); // handle mixed cases
        if(LetterSeen[Letter]) // if the letter is in the map
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
    for(auto Letter : Word) //loop through the word checking if a letter is uppercase
    {
        if(!islower(Letter)) // if the letter is not lowercase
        {
            return false; //the word has atleast one uppercase letter (IsLowercase returns false)
        }
    }
    return true; //if none of the letters are uppercase return true
}