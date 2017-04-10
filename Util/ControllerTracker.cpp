#include "GameState.h"
#include "ControllerTracker.h"

enum controller_button_t getControllerButton(struct GameMemory *curFrame) {
    // Bit Flags:  xxxx xxxx UDLR UDLR xxxS YXBA xLRZ UDRL
    //                                    C BA98 7654 3210
    if (curFrame->ctrl1_digital & (1UL << 8)) {
        return A;
    }
    if (curFrame->ctrl1_digital & (1UL << 9)) {
        return B;
    }
    if (curFrame->ctrl1_digital & (1UL << 10)) {
        return X;
    }
    if (curFrame->ctrl1_digital & (1UL << 11)) {
        return Y;
    }
    
    return UNKNOWN;
}
