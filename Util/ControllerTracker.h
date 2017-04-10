#ifndef CONTROLLERTRACKER_H
#define CONTROLLERTRACKER_H

enum controller_button_t {A, B, X, Y, UNKNOWN};
enum controller_button_t getControllerButton(struct GameMemory *curFrame);

#endif
