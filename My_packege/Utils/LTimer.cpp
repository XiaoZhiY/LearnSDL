#include "LTimer.h"


LTimer::LTimer()
{
    //Initialize the variables
    m_StartTicks = 0;
    m_PausedTicks = 0;

    m_Paused = false;
    m_Started = false;
}

void LTimer::start()
{
    //Start the timer
    m_Started = true;

    //Unpause the timer
    m_Paused = false;

    //Get the current clock time
    m_StartTicks = SDL_GetTicks();
	m_PausedTicks = 0;
}

void LTimer::stop()
{
    //Stop the timer
    m_Started = false;

    //Unpause the timer
    m_Paused = false;

	//Clear tick variables
	m_StartTicks = 0;
	m_PausedTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and isn't already paused
    if( m_Started && !m_Paused )
    {
        //Pause the timer
        m_Paused = true;

        //Calculate the paused ticks
        m_PausedTicks = SDL_GetTicks() - m_StartTicks;
		m_StartTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if( m_Started && m_Paused )
    {
        //Unpause the timer
        m_Paused = false;

        //Reset the starting ticks
        m_StartTicks = SDL_GetTicks() - m_PausedTicks;

        //Reset the paused ticks
        m_PausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

    //If the timer is running
    if( m_Started )
    {
        //If the timer is paused
        if( m_Paused )
        {
            //Return the number of ticks when the timer was paused
            time = m_PausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - m_StartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
    return m_Started;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
    return m_Paused && m_Started;
}