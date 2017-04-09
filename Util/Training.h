#ifndef _TRAINING
#define _TRAINING

void analyzeWavedash(struct GameMemory *WDstart, struct GameMemory *WDend);
void analyzeLCancel(struct GameMemory *curState, struct GameMemory *prevState, bool lCancelBuf[]);
void analyzeShortHop(struct GameMemory *SHstart, struct GameMemory *SHend);

#endif
