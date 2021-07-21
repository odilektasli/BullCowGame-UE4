// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    TArray<FString> ValidWords = {};

    for(int32 Index = 0; Index < Words.Num(); Index++)
    {
        if(IsIsogram(Words[Index]))
        {
            ValidWords.Emplace(Words[Index]);
        }
    }

    PrintLine(TEXT("The number of possible word is %i"), ValidWords.Num());
    SetupGame(); //Setting up the game
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    /* 
    if game is not over then do ClearScreen() and SetupGame()
    else checkinG PlayerGues */

    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // checking player guess
    {
        ProcessGuess(Input);
            
    }    
    
}

void UBullCowCartridge::SetupGame()
{
    const TArray<FString> WordList = Words;
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Hidden word is %s "), *HiddenWord); //Debug Line
    PrintLine(TEXT("Welcome to Bull Cows! \nGuess the %i letter word"), HiddenWord.Len()); //Welcoming
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Press enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    
    PrintLine(TEXT("\nPress enter to play again"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You Have Won!"));
        EndGame();
        return;
    }

    // Prompt To Guess Again
    // Check Right Number Of Characters
    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Hidden word is %i letters"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
        return;
    }
    // // Check If Isogram
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repating letters, guess again"));
    }

    // Remove Life
    PrintLine(TEXT("Lost a life!"));
     --Lives;
    // Check If Lives > 0
    if(Lives <= 0) 
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!\nThe hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
    // Show the player Bulls and Cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
    // If Yes GuessAgain
    // Show Lives Left
    // If No Show GameOver and HiddenWord?
    // Prompt To Play Again, Press Enter To Play Again?
    // Check User Input
    // PlayAgain or Quit
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{

    for(int32 Index = 0; Index < Word.Len(); Index++)
    {
        for(int32 Comparison = Index; Comparison < Word.Len(); Comparison++)
        {
            if(Comparison + 1 != Word.Len())
            {
                if(Word[Comparison] == Word[Comparison + 1])
                {
                    return false;
                }
            }
        }
    }

    return true;
}