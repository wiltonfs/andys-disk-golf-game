// Copyright Felix Wilton 2024


#include "CharacterDataLibrary.h"


float UCharacterDataLibrary::MinimumPowerThreshold()
{
	return ValidThrowTimeThreshold() / NormalPowerTimeThreshold() * NormalFrisbeePower();
}


float UCharacterDataLibrary::TimeToPower(float Time, bool bHasStrengthAbility)
{

	float MaxPower = HighFrisbeePower();
	float NormalPower = NormalFrisbeePower();
	float NormalTime = NormalPowerTimeThreshold();
	float MaxTime = (MaxPower / NormalPower) * NormalTime;

	if (!bHasStrengthAbility) 
	{
		// Normal strength. 

		if (Time <= NormalTime)
		{
			// Linear interp between [0.0f, NormalTime]
			// to [0.0f, NormalPower] based on Time
			return FMath::Clamp(FMath::Lerp(0.0f, NormalPower, Time / NormalTime), 0.0f, NormalPower);
		}
		else
		{
			// Power linearly decays back down to zero
			// Linear interp between [NormalTime, NormalTime * 3]
			// to [NormalPower, 0.0f] based on Time
			return FMath::Clamp(FMath::Lerp(NormalPower, 0.0f, 0.5f * (Time - NormalTime) / NormalTime), 0.0f, NormalPower);
		}
	}

	// Has strength ability
	if (Time <= MaxTime)
	{
		// Linear interp between [0.0f, MaxTime]
		// to [0.0f, MaxPower] based on Time
		return FMath::Clamp(FMath::Lerp(0.0f, MaxPower, Time / MaxTime), 0.0f, MaxPower);
	}
	else
	{
		// Power linearly decays back down to zero
		// Linear interp between [MaxTime, MaxTime * 3]
		// to [MaxPower, 0.0f] based on Time
		return FMath::Clamp(FMath::Lerp(MaxPower, 0.0f, 0.5f *  (Time - MaxTime) / MaxTime), 0.0f, MaxPower);
	}
}







FSelectableCharacter UCharacterDataLibrary::GetCharacterData(EUnlockableCharacters Character)
{
	FSelectableCharacter CharacterData;

	// Set default values
	CharacterData.CharacterEnum = Character;
	CharacterData.CharacterName = "";
	CharacterData.CharacterDesc = "";
	CharacterData.bSpeedAbility = false;
	CharacterData.bStrengthAbility = false;
	CharacterData.bWaterAbility = false;
	CharacterData.bTrajectoryAbility = false;
	CharacterData.bRethrowAbility = false;

	// Update character data based on the selected character
	switch (Character)
	{
	case EUnlockableCharacters::ANDY:
		CharacterData.CharacterName = "Andy";
		CharacterData.CharacterDesc = "This isn't Andy's first time playing disk golf. And he loves to play in the water!";
		CharacterData.bWaterAbility = true;
		CharacterData.bTrajectoryAbility = true;
		break;
	case EUnlockableCharacters::RENEA:
		CharacterData.CharacterName = "Renea";
		CharacterData.CharacterDesc = "She's never afraid to get muddy or wet, and she's new enough to the game to get some special treatment.";
		CharacterData.bWaterAbility = true;
		CharacterData.bRethrowAbility = true;
		break;
	case EUnlockableCharacters::KATARINA:
		CharacterData.CharacterName = "Katarina";
		CharacterData.CharacterDesc = "Katarina has spent years training to be the fastest runner on the disk golf course. If you give her a re-throw here and there, you can be sure she'll finish a game quickly.";
		CharacterData.bSpeedAbility = true;
		CharacterData.bRethrowAbility = true;
		break;
	case EUnlockableCharacters::FELIX:
		CharacterData.CharacterName = "Felix";
		CharacterData.CharacterDesc = "Did you know the name Felix means strong and quick in Spanish?";
		CharacterData.bSpeedAbility = true;
		CharacterData.bStrengthAbility = true;
		break;
	case EUnlockableCharacters::ANIA:
		CharacterData.CharacterName = "Ania";
		CharacterData.CharacterDesc = "Did you know Poland invented disk golf? We'll if that's true, we'd better trust Ania's interpretation of the rules.";
		CharacterData.bRethrowAbility = true;
		CharacterData.bStrengthAbility = true;
		break;
	case EUnlockableCharacters::ZARIAH:
		CharacterData.CharacterName = "Zariah";
		CharacterData.CharacterDesc = "Zariah has raced across much deeper rivers and ponds. This disk golf course should be a breeze.";
		CharacterData.bSpeedAbility = true;
		CharacterData.bWaterAbility = true;
		break;
	case EUnlockableCharacters::ELIZABETH:
		CharacterData.CharacterName = "Elizabeth";
		CharacterData.CharacterDesc = "Elizabeth is mighty, and loves to wakeboard.";
		CharacterData.bStrengthAbility = true;
		CharacterData.bWaterAbility = true;
		break;
	case EUnlockableCharacters::JONATHAN:
		CharacterData.CharacterName = "Jonathan";
		CharacterData.CharacterDesc = "Decades of ultimate frisbee are finally paying off!";
		CharacterData.bSpeedAbility = true;
		CharacterData.bTrajectoryAbility = true;
		break;
	case EUnlockableCharacters::SETH:
		CharacterData.CharacterName = "Seth";
		CharacterData.CharacterDesc = "A powerful arm that knows where to aim!";
		CharacterData.bStrengthAbility = true;
		CharacterData.bTrajectoryAbility = true;
		break;
	case EUnlockableCharacters::CHUNKY:
		CharacterData.CharacterName = "Chunky";
		CharacterData.CharacterDesc = "Roughly half of Chunky's brain is dedicated to frisbee flight mechanics.";
		CharacterData.bTrajectoryAbility = true;
		CharacterData.bWaterAbility = true;
		CharacterData.bSpeedAbility = true;
		CharacterData.bRethrowAbility = true;
		CharacterData.bStrengthAbility = true;
		break;
	default:
		// Handle default case if necessary
		break;
	}

	return CharacterData;
}
 
