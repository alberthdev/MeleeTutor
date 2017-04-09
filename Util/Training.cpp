#include <pwd.h>
#include <iostream>

#include "Training.h"

void analyzeWavedash(struct GameMemory *WDstart, struct GameMemory *WDend) {
	int startFrame = 0, endFrame = 0, jumpSquat = 0;
	startFrame = WDstart->frame;
	endFrame = WDend->frame;
	jumpSquat = WDend->player_one_jump_squat;
	printf("Wavedash: ");
	if (endFrame - startFrame == ((int)jumpSquat)) {
		printf("Perfect\n");
	}
	else if (endFrame - startFrame > ((int)jumpSquat)) {
		printf("Slow\n");
	}
	else {
		printf("Fast\n");
	}
}
