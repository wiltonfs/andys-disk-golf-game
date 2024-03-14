#pragma once

#include "CoreMinimal.h"
#include "CustomStructsEnums.generated.h"

// ---------------------------------------------------------------- Golf Characters

UENUM(BlueprintType)
enum class EUnlockableCharacters : uint8 {
	ANDY = 0 UMETA(DisplayName = "Andy"),
	RENEA = 1 UMETA(DisplayName = "Renea"),
	KATARINA = 2 UMETA(DisplayName = "Katarina"),
	FELIX = 3 UMETA(DisplayName = "Felix"),
	ANIA = 4 UMETA(DisplayName = "Ania"),
	ZARIAH = 5 UMETA(DisplayName = "Zariah"),
	ELIZABETH = 6 UMETA(DisplayName = "Elizabeth"),
	JONATHAN = 7 UMETA(DisplayName = "Jonathan"),
	SETH = 8 UMETA(DisplayName = "Seth"),
	CHUNKY = 9 UMETA(DisplayName = "Chunky")
};

USTRUCT(BlueprintType)
struct FSelectableCharacter
{
	GENERATED_BODY()

	// Character
	UPROPERTY(BlueprintReadWrite)
	EUnlockableCharacters CharacterEnum;

	// Character's name
	UPROPERTY(BlueprintReadWrite)
	FString CharacterName;

	// Character's description
	UPROPERTY(BlueprintReadWrite)
	FString CharacterDesc;

	// Character speed
	UPROPERTY(BlueprintReadWrite)
	bool bSpeedAbility;

	// Character strength
	UPROPERTY(BlueprintReadWrite)
	bool bStrengthAbility;

	// Character can swim
	UPROPERTY(BlueprintReadWrite)
	bool bWaterAbility;

	// Character can see trajectory
	UPROPERTY(BlueprintReadWrite)
	bool bTrajectoryAbility;

	// Character can rethrow
	UPROPERTY(BlueprintReadWrite)
	bool bRethrowAbility;
};


// ---------------------------------------------------------------- Golf Scoring

USTRUCT(BlueprintType)
struct FGolfLevelParameters
{
	GENERATED_BODY()

	// What number this hole is on the course
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 HoleNumber;

	// A catchy name for this hole
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText HoleName;

	// Number of strokes to reach par
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 ParStrokes;

	// The Level to load once this hole is complete
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextLevelToLoad;
};

USTRUCT(BlueprintType)
struct FGolfRoundScoreEntry
{
	GENERATED_BODY()

	// Who player was playing as
	UPROPERTY(BlueprintReadWrite)
	EUnlockableCharacters SelectedCharacter;

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