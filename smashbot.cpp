#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <csignal>
#include <string>
#include <time.h>

#include "Goals/KillOpponent.h"
#include "Goals/NavigateMenu.h"

#include "Util/GameState.h"
#include "Util/MemoryWatcher.h"
#include "Util/Logger.h"
#include "Util/Paths.h"
#include "Util/Training.h"
#include "Util/TrainingUtils.h"
#include "Util/TrainingState.h"
#include "Util/ControllerTracker.h"

#include "GUI/NotificationAPI.h"

bool isDebug = false;

QString make_status_string() {
    QString status_string;

    status_string += "Wavedash: ";

    if ((current_training_state.wavedash_cum == 0) && (current_training_state.wavedash_result == 0)) {
        status_string += "N/A";
    } else {
        if (current_training_state.wavedash_result == 0) {
            status_string += "Perfect!";
        } else if (current_training_state.wavedash_result > 0) {
            status_string += "(";
            status_string += QString::number(current_training_state.wavedash_result);
            status_string += " frames fast!)";
        } else {
            status_string += "(";
            status_string += QString::number(abs(current_training_state.wavedash_result));
            status_string += " frames slow!)";
        }

        /*
        status_string += " (";
        if (current_training_state.wavedash_cum > -1) {
            status_string += QString::number(current_training_state.wavedash_cum);
            status_string += " successes!)";
        } else {
            status_string += QString::number(abs(current_training_state.wavedash_cum));
            status_string += " failures!)";
        }
        */
        
    }

    status_string += "\nLCancel: ";

    if ((current_training_state.lcancel_cum == 0) && (current_training_state.lcancel_result == 0)) {
        status_string += "N/A";
    } else {
        if (current_training_state.lcancel_result == 1) {
            status_string += "You got it!";
        } else {
            status_string += "Missed!";
        }

        /*
        status_string += " (";
        if (current_training_state.lcancel_cum > -1) {
            status_string += QString::number(current_training_state.lcancel_cum);
            status_string += " successes!)";
        } else {
            status_string += QString::number(abs(current_training_state.lcancel_cum));
            status_string += " failures!)";
        }
        */
    }

    status_string += "\nShorthop: ";

    if ((current_training_state.shorthop_cum == 0) && (current_training_state.shorthop_result == 0)) {
        status_string += "N/A";
    } else {
        if (current_training_state.shorthop_result <= 0) {
            status_string += "Successful shorthop!";
        } else {
            status_string += "(";
            status_string += QString::number(abs(current_training_state.shorthop_result));
            status_string += " frames slow!)";
        }

        /*
        status_string += " (";
        if (current_training_state.shorthop_cum > -1) {
            status_string += QString::number(current_training_state.shorthop_cum);
            status_string += " successes!)";
        } else {
            status_string += QString::number(abs(current_training_state.shorthop_cum));
            status_string += " failures!)";
        }
        */
    }

    return status_string;
}

void FirstTimeSetup()
{
    std::string config_path = Paths::GetConfigPath();
    std::string mem_watcher_path = config_path + "MemoryWatcher/";
    std::string pipe_path = config_path + "Pipes/";

    //Create the MemoryWatcher directory if it doesn't already exist
    struct stat buffer;
    if(stat(mem_watcher_path.c_str(), &buffer) != 0)
    {
        if(mkdir(mem_watcher_path.c_str(), 0775) != 0)
        {
            std::cout << "ERROR: Could not create the directory: \"" << mem_watcher_path << "\". Dolphin seems to be installed, " \
                "But this is not working for some reason. Maybe permissions?" << std::endl;
            exit(-1);
        }
        std::cout << "WARNING: Had to create a MemoryWatcher directory in Dolphin just now. " \
            "You may need to restart Dolphin and SmashBot in order for this to work. (You should only see this warning once)" << std::endl;
    }

    std::ifstream src("Locations.txt", std::ios::in);
    std::ofstream dst(mem_watcher_path + "/Locations.txt", std::ios::out);
    dst << src.rdbuf();

    //Create the Pipes directory if it doesn't already exist
    if(stat(pipe_path.c_str(), &buffer) != 0)
    {
        if(mkdir(pipe_path.c_str(), 0775) != 0)
        {
            std::cout << "ERROR: Could not create the directory: \"" << pipe_path << "\". Dolphin seems to be installed, " \
                "But this is not working for some reason. Maybe permissions?" << std::endl;
            exit(-1);
        }
        std::cout << "WARNING: Had to create a Pipes directory in Dolphin just now. " \
            "You may need to restart Dolphin and SmashBot in order for this to work. (You should only see this warning once)" << std::endl;
    }
}

void signal_handler(int signal)
{
    std::string logpath = "Logs";
    struct stat buffer;

    Controller *controller = Controller::Instance();
    controller->emptyInput();

    if(isDebug)
    {
        Logger *logger = Logger::Instance();
        std::string logdump = logger->DumpLog();

        if(stat(logpath.c_str(), &buffer) != 0)
        {
            if(mkdir(logpath.c_str(), 0775) != 0)
            {
                std::cout << "ERROR: Could not create the directory: \"" << logpath << "\". Maybe permissions?" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        //Name the file as a timestamp
        static char name[20];
        time_t now = time(0);
        strftime(name, sizeof(name), "%Y%m%d_%H%M%S", localtime(&now));
        std::string filename = std::string(name);

        std::cout << "\nINFO: Log file written to: " << logpath + "/" + filename + ".csv" << std::endl;

        std::ofstream dst(logpath + "/" + filename + ".csv", std::ios::out);
        dst << logdump;
        dst.close();
    }

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        std::string arg = std::string(argv[1]);
        if(arg == "--debug")
        {
            isDebug = true;
        }
    }

    //Do some first-time setup
    FirstTimeSetup();

    std::signal(SIGINT, signal_handler);

    Logger *logger = Logger::Instance();
    logger->SetDebug(isDebug);
    GameState *state = GameState::Instance();

    MemoryWatcher *watcher = new MemoryWatcher();
    uint last_frame = 0;
    //Get our goal
    Goal *goal = NULL;
    MENU current_menu;

    // GUI INIT
    initializeNotification();
    processAllEvents();

	struct GameMemory *WDstart = 0;
	struct GameMemory *WDend = 0;

  struct GameMemory *SHstart = 0;
  struct GameMemory *SHend = 0;

	struct GameMemory *prevFrame = (struct GameMemory *)malloc(sizeof(struct GameMemory));
	bool jumped = false;
  bool jump_released = false;
	bool triggered = false;
	bool lCancelBuf[7] = {false};
	int lCancelIndex = 0;

    //Main frame loop
    for(;;)
    {
        processAllEvents();

        //If we get a new frame, process it. Otherwise, keep reading memory
        if(!watcher->ReadMemory())
        {
            continue;
        }

        current_menu = (MENU)state->m_memory->menu_state;

        if(state->m_memory->frame != last_frame)
        {
            if(state->m_memory->frame > last_frame+1)
            {
                logger->Log(WARNING, "FRAME MISSED");
                logger->Log(INFO, "FRAME MISSED");
            }
            last_frame = state->m_memory->frame;

            //If we're in a match, play the match!
            if(state->m_memory->menu_state == IN_GAME)
            {
				lCancelBuf[lCancelIndex] = lCancelFrame(prevFrame, state->m_memory);
				lCancelIndex++;
				lCancelIndex %= 7;
				analyzeLCancel(state->m_memory, prevFrame, lCancelBuf);
				jumped = jumpFrame(prevFrame, state->m_memory);
				if (!WDstart && jumped)
				{
						// if x or y are being pressed and we're not currently wavedashing
						WDstart = (struct GameMemory *)malloc(sizeof(struct GameMemory));
						memcpy(WDstart, state->m_memory, sizeof(struct GameMemory));
				}

				if (!SHstart && state->m_memory->player_one_on_ground && jumped)
				{
					// if x or y are being pressed and we're not currently wavedashing
					SHstart = (struct GameMemory *)malloc(sizeof(struct GameMemory));
					memcpy(SHstart, state->m_memory, sizeof(struct GameMemory));
				}

				jump_released = jumpReleaseFrame(prevFrame, state->m_memory);
				if (!SHend && SHstart && jump_released) {
					// if x or y are being released and we're jumping
					SHend = (struct GameMemory *)malloc(sizeof(struct GameMemory));
					memcpy(SHend, state->m_memory, sizeof(struct GameMemory));
					analyzeShortHop(SHstart, SHend);

					free(SHstart);
					free(SHend);
					SHstart = 0;
					SHend = 0;
				}

				triggered = triggerFrame(prevFrame, state->m_memory);
				if (!WDend && WDstart && triggered)
				{
						// if x or y are being pressed and we're not currently wavedashing
						WDend = (struct GameMemory *)malloc(sizeof(struct GameMemory));
						memcpy(WDend, state->m_memory, sizeof(struct GameMemory));
						analyzeWavedash(WDstart, WDend);

						free(WDstart);
						free(WDend);
						WDstart = 0;
						WDend = 0;
				}

                // Handle GUI update
                updateNotification("MeleeTutor", make_status_string(), QString(), "Exit", QString(), -1);

				memcpy(prevFrame, state->m_memory, sizeof(struct GameMemory));
                /*if(goal == NULL )
                {
                    goal = new KillOpponent();
                }
                if(typeid(*goal) != typeid(KillOpponent))
                {
                    delete goal;
                    goal = new KillOpponent();
                }
                goal->Strategize();*/
            }
            //If we're in a menu, then let's navigate the menu
            else if(state->m_memory->menu_state == CHARACTER_SELECT ||
                state->m_memory->menu_state == STAGE_SELECT ||
                state->m_memory->menu_state == POSTGAME_SCORES)
            {
                updateNotification("MeleeTutor", "Navigate to the arena to begin training.", QString(), "Exit", QString(), -1);
                if(goal == NULL )
                {
                    goal = new NavigateMenu();
                }
                if(typeid(*goal) != typeid(NavigateMenu))
                {
                    delete goal;
                    goal = new NavigateMenu();
                }
                goal->Strategize();
            }
        }
        //If the menu changed
        else if(current_menu != state->m_memory->menu_state)
        {
            last_frame = 1;
            current_menu = (MENU)state->m_memory->menu_state;
        }

        Controller::Instance()->flush();
        logger->SetGoal(goal);
        logger->LogFrame();
    }

    return EXIT_SUCCESS;
}
