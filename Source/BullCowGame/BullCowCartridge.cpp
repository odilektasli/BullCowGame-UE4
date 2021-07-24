// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    

    Isograms = GetValidWords(Words);

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
    HiddenWord = Isograms[FMath::RandRange(0, (Isograms.Num() - 1))];
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Welcome to Bull Cows! \nGuess the %i letter word"), HiddenWord.Len()); //Welcoming
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Press enter to continue..."));
    PrintLine(TEXT("Hidden word is: %s "), *HiddenWord); //Debug Line
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    
    PrintLine(TEXT("\nPress enter to play again"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
    // If Yes GuessAgain
    // Show Lives Left
    // If No Show GameOver and HiddenWord?
    // Prompt To Play Again, Press Enter To Play Again?
    // Check User Input
    // PlayAgain or Quit
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{

    for(int32 Index = 0; Index < Word.Len(); Index++)
    {
        for(int32 Comparison = Index; Comparison + 1 < Word.Len(); Comparison++)
        {
            if(Word[Comparison] == Word[Comparison + 1])
            {
                return false;
            }
        }
        
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;
    //for every index the Guess as index Hidden, BullCount ++
    // if not a bull was it a cow ? if yes cow count ++
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls ++;
            continue;
        }

        for (int32 Comparison = 0; Comparison < HiddenWord.Len(); Comparison++)
        {
            if (HiddenWord[Comparison] == Guess[GuessIndex])
            {
                Count.Cows ++;
                break;
            }
        }

    }

    return Count;
}