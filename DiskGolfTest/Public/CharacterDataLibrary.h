// Copyright Felix Wilton 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomStructsEnums.h"
#include "CharacterDataLibrary.generated.h"

/**
 * Helper functions for data associated with selectable characters
 */
UCLASS()
class DISKGOLFTEST_API UCharacterDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Golf Characters")
	static FSelectableCharacter GetCharacterData(EUnlockableCharacters Character);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Golf Characters")
	static float TimeToPower(float Time, bool bHasStrengthAbility);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Golf Characters")
	static float NormalFrisbeePower() { return 4000.0f; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Golf Characters")
	static float HighFrisbeePower() { return 6000.0f; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Golf Characters")
	static float ValidThrowTimeThreshold() { return 0.3f; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Golf Characters")
	static float MinimumPowerThreshold();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Golf Characters")
	static float NormalPowerTimeThreshold() { return 1.5f; }
	
};
