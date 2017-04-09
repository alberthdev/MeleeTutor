#ifndef _TRAININGUTILS
#define _TRAININGUTILS

bool jumpFrame(struct GameMemory *prevFrame, struct GameMemory *curFrame);
bool jumpReleaseFrame(struct GameMemory *prevFrame, struct GameMemory *curFrame);
bool triggerFrame(struct GameMemory *prevFrame, struct GameMemory *curFrame);
bool lCancelFrame(struct GameMemory *prevFrame, struct GameMemory *curFrame);

#endif
