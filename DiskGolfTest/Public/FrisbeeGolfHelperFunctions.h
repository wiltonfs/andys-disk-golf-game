// Copyright Felix Wilton 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FrisbeeGolfHelperFunctions.generated.h"

USTRUCT(BlueprintType)
struct FGolfLevelParameters
{
	GENERATED_BODY()

	// What number this hole is on the course
	UPROPERTY(BlueprintReadWrite)
	uint8 HoleNumber;

	// A catchy name for this hole
	UPROPERTY(BlueprintReadWrite)
	FString HoleName;

	// Number of strokes to reach par
	UPROPERTY(BlueprintReadWrite)
	uint8 ParStrokes;

	// The Level to load once this hole is complete
	UPROPERTY(BlueprintReadWrite)
	FName NextLevelToLoad;
};

USTRUCT(BlueprintType)
struct FGolfRoundScoreEntry
{
	GENERATED_BODY()

	// Who player was playing as
	UPROPERTY(BlueprintReadWrite)
	FName SelectedCharacter;

	// What hole this record is for
	UPROPERTY(BlueprintReadWrite)
	FGolfLevelParameters Hole;

	// Number of strokes player took
	UPROPERTY(BlueprintReadWrite)
	uint8 PlayerStrokes;

	// Player score on the hole
	UPROPERTY(BlueprintReadWrite)
	int32 PlayerScore;

	// Time taken on the hole
	UPROPERTY(BlueprintReadWrite)
	float ElapsedTime;
};

/**
 * Helper functions for data associated with golf rounds
 */
UCLASS()
class DISKGOLFTEST_API UFrisbeeGolfHelperFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//Flavor string associated with score ("Birdie!", "Hole in one!")
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Golf Data")
	static FString GetScoreStringDisplay(int64 strokes, int64 parStrokes);
	
};
