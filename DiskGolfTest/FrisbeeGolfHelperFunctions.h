// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FrisbeeGolfHelperFunctions.generated.h"

/**
 * 
 */
UCLASS()
class DISKGOLFTEST_API UFrisbeeGolfHelperFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Disk Golf Helper Functions")
	static FString GetScoreStringDisplay(int32 strokes, int32 parStrokes);
	
};
