// Copyright Felix Wilton 2024


#include "FrisbeeGolfHelperFunctions.h"

FString UFrisbeeGolfHelperFunctions::GetScoreStringDisplay(int64 strokes, int64 parStrokes)
{
	if (strokes == 1) {
		return "Hole in one!";
	}
	else if (strokes < parStrokes - 4) {
		return "Incredible work!";
	}
	else if (strokes == parStrokes - 4) {
		return "Condor!";
	}
	else if (strokes == parStrokes - 3) {
		return "Albatross!";
	}
	else if (strokes == parStrokes - 2) {
		return "Eagle!";
	}
	else if (strokes == parStrokes - 1) {
		return "Birdie!";
	}
	else if (strokes == parStrokes) {
		return "Par";
	}
	else if (strokes == parStrokes + 1) {
		return "Bogey";
	}
	else if (strokes == parStrokes + 2) {
		return "Double Bogey";
	}

	return "Over Double Bogey";
}

