#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_joystick.h>

#define MAX_CONTROLLERS 4

class JoypadController {
public:
	JoypadController() : m_is_connected(false), m_gamepad(0), m_instance_id(-1), m_haptic(0), m_id(0) {}
	~JoypadController() {
		int i = 0;
		for (i = 0; i < MAX_CONTROLLERS; i++) {
			if (m_controllers[i] == NULL) {
				delete m_controllers[i];
			}
		}
	}

	int processEvent(const SDL_Event *event);
private:
	SDL_GameController *m_gamepad;
	SDL_Haptic *m_haptic;
	SDL_JoystickID m_instance_id;
	bool m_is_connected;

	static JoypadController *m_controllers[MAX_CONTROLLERS];
	static int GetControllerIndex(SDL_JoystickID instance);

	int m_id;

	void Open(int device);
	void Close();
};

#endif
