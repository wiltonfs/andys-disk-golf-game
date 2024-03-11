// Copyright Felix Wilton 2024


#include "CharacterDataLibrary.h"

FString UCharacterDataLibrary::SpeedStrengthToString(ESpeedStrength Value)
{
    FString Result;

    switch (Value)
    {
    case ESpeedStrength::LOW:
        Result = TEXT("Low");
        break;
    case ESpeedStrength::MEDIUM:
        Result = TEXT("Medium");
        break;
    case ESpeedStrength::HIGH:
        Result = TEXT("High");
        break;
    default:
        Result = TEXT("Unknown");
        break;
    }

    return Result;
}
