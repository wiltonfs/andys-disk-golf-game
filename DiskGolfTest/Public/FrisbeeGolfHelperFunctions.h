// Copyright Felix Wilton 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomStructsEnums.h"
#include "FrisbeeGolfHelperFunctions.generated.h"

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
