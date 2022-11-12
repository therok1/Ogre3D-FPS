#include "Time.h"

Time::Time() : 
    m_frameStart(0), 
    m_lastFrame(0), 
    m_frameTime(0)
{

}

unsigned int Time::computeDeltaTime()
{
    m_frameStart = SDL_GetTicks();

    unsigned int dt = m_frameStart - m_lastFrame;
    dt = std::min(dt, MAX_DT);

    timeSinceStart += static_cast<float>(dt) / 1000.0f;

    m_lastFrame = m_frameStart;

    return dt;
}

void Time::delayTime()
{
    m_frameTime = SDL_GetTicks() - m_frameStart;
    if (m_frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - m_frameTime);
    }
}

double Time::timeSinceStart = 0.0f;