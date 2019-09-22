#ifndef __LTIMER__H_
#define __LTIMER__H_

#include <string>
#include <cstring>
#include <SDL.h>
#include "../Defines.h"

class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		uint32 m_StartTicks;

		//The ticks stored when the timer was paused
		uint32 m_PausedTicks;

		//The timer status
		bool m_Paused;
		bool m_Started;
};

#endif