#include <pwd.h>
#include <iostream>
#include <math.h>

#include "Training.h"
#include "GameState.h"
#include "TrainingState.h"

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
		current_training_state.wavedash_result = 0;
		current_training_state.wavedash_cum++;
	}
	else if (frameDiff > ((int)jumpSquat)) {
		printf("Slow (%d frames)\n", frameDiff - (int)jumpSquat);
		current_training_state.wavedash_result = (int)jumpSquat - frameDiff;
		current_training_state.wavedash_cum--;
	}
	else {
		printf("Fast (%d frames)\n", (int)abs(frameDiff - (int)jumpSquat));
		current_training_state.wavedash_result = (int)abs(frameDiff - (int)jumpSquat);
		current_training_state.wavedash_cum++;
	}
}

void analyzeLCancel(struct GameMemory *curState, struct GameMemory *prevState,
					bool lCancelBuf[]) {
	bool success = false;
	int i = 0;
	if ((curState->player_one_action >= 0x46 && 
		curState->player_one_action <= 0x4A) &&
		((prevState->player_one_action < 0x46) || 
		(prevState->player_one_action > 0x4A))) {
		// landing during an aerial
		for (i = 0; i < 7; i++) {
			if (lCancelBuf[i]) {
				success = true;
			}
		}
		printf("L Cancel: %s\n", (success) ? "Success" : "Missed");
		current_training_state.lcancel_result = (success) ? 1 : 0;
		if (success) {
			current_training_state.lcancel_cum++;
		} else {
			current_training_state.lcancel_cum--;
		}
	}
}

void analyzeShortHop(struct GameMemory *SHstart, struct GameMemory *SHend) {
	int startFrame = 0, endFrame = 0, jumpSquat = 0;
	int frameDiff = 0;
	startFrame = SHstart->frame;
	endFrame = SHend->frame;
	jumpSquat = SHend->player_one_jump_squat;
	frameDiff = endFrame - startFrame;
	printf("Shorthop: ");
	if (frameDiff < ((int)jumpSquat)) {
		printf("Successful\n");
		current_training_state.shorthop_result = frameDiff - (int)jumpSquat + 1;
		current_training_state.shorthop_cum++;
	}
	else if (frameDiff >= ((int)jumpSquat)) {
		printf("Slow (%d frames)\n", frameDiff - (int)jumpSquat + 1);
		current_training_state.shorthop_result = frameDiff - (int)jumpSquat + 1;
		current_training_state.shorthop_cum--;
	}
}
