#include "Joystick.h"

// Opens the joystick controller
void JoypadController::Open(int device)
{
	m_gamepad = SDL_GameControllerOpen(device);
	SDL_Joystick *j = SDL_GameControllerGetJoystick(m_gamepad);
	m_instance_id = SDL_JoystickInstanceID(j);
	m_is_connected = true;
	if (SDL_JoystickIsHaptic(j)) {
		m_haptic = SDL_HapticOpenFromJoystick(j);
		printf("Haptic Effects: %d\n", SDL_HapticNumEffects(m_haptic));
		printf("Haptic Query: %x\n", SDL_HapticQuery(m_haptic));
		if (SDL_HapticRumbleSupported(m_haptic)) {
			if (SDL_HapticRumbleInit(m_haptic) != 0) {
				printf("Haptic Rumble Init: %s\n", SDL_GetError());
				SDL_HapticClose(m_haptic);
				m_haptic = 0;
			}
		} else {
			SDL_HapticClose(m_haptic);
			m_haptic = 0;
		}
	}
}

void JoypadController::Close()
{
	if (m_is_connected) {
		m_is_connected = false;
		if (m_haptic) {
			SDL_HapticClose(m_haptic);
			m_haptic = 0;
		}
		SDL_GameControllerClose(m_gamepad);
		m_gamepad = 0;
	}
}

int JoypadController::GetControllerIndex(SDL_JoystickID instance)
{
	for (int i = 0; i < MAX_CONTROLLERS; ++i)
	{
		if (m_controllers[i]->m_is_connected &&  m_controllers[i]->m_instance_id == instance) {
			return i;
		}
	}
	return -1;
}

int JoypadController::processEvent(const SDL_Event *event)
{
	switch (event->type) {
		case SDL_CONTROLLERAXISMOTION: {
			// handle axis motion
			printf("Axis motion!\n");
			break;
		}
		case SDL_CONTROLLERBUTTONDOWN:
			if (event->cbutton.button == SDL_CONTROLLER_BUTTON_A) {
				printf("[Joystick %d] Button up! (A)\n", m_id);
			} else if (event->cbutton.button == SDL_CONTROLLER_BUTTON_B) {
				printf("[Joystick %d] Button up! (B)\n", m_id);
			} else if (event->cbutton.button == SDL_CONTROLLER_BUTTON_X) {
				printf("[Joystick %d] Button up! (X)\n", m_id);
			} else if (event->cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
				printf("[Joystick %d] Button up! (Y)\n", m_id);
			} else if (event->cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
				printf("[Joystick %d] Button up! (BACK)\n", m_id);
			} else if (event->cbutton.button == SDL_CONTROLLER_BUTTON_GUIDE) {
				printf("[Joystick %d] Button up! (GUIDE)\n", m_id);
			} else if (event->cbutton.button == SDL_CONTROLLER_BUTTON_START) {
				printf("[Joystick %d] Button up! (START)\n", m_id);
			} else {
				printf("[Joystick %d] Button up! (UNKNOWN)\n", m_id);
			}
			
			break;
		case SDL_CONTROLLERBUTTONUP: {
			// handle button up/down
			printf("[Joystick %d] Button down!\n", m_id);
			break;
		}
		case SDL_CONTROLLERDEVICEADDED: {
			if (event->cdevice.which < MAX_CONTROLLERS ) {
				JoypadController *jc;
				if (m_controllers[event->cdevice.which] == NULL) {
					m_controllers[event->cdevice.which] = new JoypadController();
				}
				jc = m_controllers[event->cdevice.which];
				jc->Open(event->cdevice.which);
			}
			break;
		}
		case SDL_CONTROLLERDEVICEREMOVED: {
			int cIndex = GetControllerIndex(event->cdevice.which);
			if (cIndex < 0) return 0; // unknown controller?
			JoypadController *jc;
			if (m_controllers[cIndex] == NULL) {
				m_controllers[cIndex] = new JoypadController();
			}
			jc = m_controllers[cIndex];
			jc->Close();
			break;
		}
	}
	return 0;
}
