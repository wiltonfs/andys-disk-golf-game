// Copyright Felix Wilton 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CharacterDataLibrary.generated.h"

//ESpeedStrength strength = ESpeedStrength::Medium;
UENUM(BlueprintType)
enum class ESpeedStrength : uint8 {
	LOW = 0 UMETA(DisplayName = "Low"),
	MEDIUM = 1 UMETA(DisplayName = "Medium"),
	HIGH = 2 UMETA(DisplayName = "High")
};

USTRUCT(BlueprintType)
struct FSelectableCharacter
{
	GENERATED_BODY()

	// Character's name
	UPROPERTY(BlueprintReadWrite)
	FName CharacterName;

	// Character's description
	UPROPERTY(BlueprintReadWrite)
	FString CharacterDesc;

	// Character speed
	UPROPERTY(BlueprintReadWrite)
	ESpeedStrength Speed;

	// Character strength
	UPROPERTY(BlueprintReadWrite)
	ESpeedStrength Strength;

	// If character is unlocked
	UPROPERTY(BlueprintReadWrite)
	bool bIsUnlocked;
};

/**
 * Helper functions for data associated with selectable characters
 */
UCLASS()
class DISKGOLFTEST_API UCharacterDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Golf Characters")
	static FString SpeedStrengthToString(ESpeedStrength Value);
	
};
