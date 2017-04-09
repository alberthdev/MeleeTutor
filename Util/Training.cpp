#include <pwd.h>
#include <iostream>
#include <math.h>

#include "Training.h"
#include "GameState.h"

void analyzeWavedash(struct GameMemory *WDstart, struct GameMemory *WDend) {
	int startFrame = 0, endFrame = 0, jumpSquat = 0;
	int frameDiff = 0;
	startFrame = WDstart->frame;
	endFrame = WDend->frame;
	jumpSquat = WDend->player_one_jump_squat;
	frameDiff = endFrame - startFrame;
	if (frameDiff - (int)jumpSquat > (int)jumpSquat + 6) {
		return;		// false input
	}
	printf("Wavedash: ");
	if (frameDiff == ((int)jumpSquat)) {
		printf("Perfect\n");
	} 
	else if (frameDiff > ((int)jumpSquat)) {
		printf("Slow (%d frames)\n", frameDiff - (int)jumpSquat);
	}
	else {
		printf("Fast (%d frames)\n", (int)abs(frameDiff - (int)jumpSquat));
	}
}
