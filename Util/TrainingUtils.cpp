#include <pwd.h>
#include <iostream>

#include "TrainingUtils.h"
#include "GameState.h"

bool jumpFrame(struct GameMemory *prevFrame, struct GameMemory *curFrame) {
	// if didn't jump on previous frame and jumping on current frame
	return (((!(prevFrame->ctrl1_digital & (1UL << 10)) &&
		!(prevFrame->ctrl1_digital & (1UL << 11))) &&
		(curFrame->ctrl1_digital & (1UL << 10) ||
		curFrame->ctrl1_digital & (1UL << 11))));
}

bool jumpReleaseFrame(struct GameMemory *prevFrame, struct GameMemory *curFrame) {
	// if held jump on previous frame and released jump on current frame
	return ((prevFrame->ctrl1_digital & (1UL << 10)) ||
		(prevFrame->ctrl1_digital & (1UL << 11))) &&
		!((curFrame->ctrl1_digital & (1UL << 10)) ||
		(curFrame->ctrl1_digital & (1UL << 11)));
}

bool triggerFrame(struct GameMemory *prevFrame, struct GameMemory *curFrame) {
	// if didn't press L on previous frame and pressing L on current frame
	// or if didn't press R on previous frame and pressing R on current frame
	return ((!(prevFrame->ctrl1_digital & (1UL << 5)) &&
			curFrame->ctrl1_digital & (1UL << 5)) ||
			(!(prevFrame->ctrl1_digital & (1UL << 6)) &&
			curFrame->ctrl1_digital & (1UL << 6)));
}

bool lCancelFrame(struct GameMemory *prevFrame, struct GameMemory *curFrame) {
	// triggerFrame and didn't press Z on previous frame and pressing 
	// Z on current frame
	
	// if l, r or z is pressed with analog input
	return (((curFrame->player_one_l_analog >= 0.35 && curFrame->player_one_l_analog <= 1) && (prevFrame->player_one_l_analog < 0.35 )) ||
			((curFrame->player_one_r_analog >= 0.35 && curFrame->player_one_r_analog <= 1) && (prevFrame->player_one_r_analog < 0.35 )) ||
			((curFrame->player_one_z_analog >= 0.35 && curFrame->player_one_z_analog <= 1) && (prevFrame->player_one_z_analog < 0.35 )));
}
