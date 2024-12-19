#include "LTimer.h"

LTimer::LTimer()
{
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = 0;
    mStarted = 0;
}

void LTimer::start()
{ //mark timer and get the current tick count
    mStarted = 1;
    mPaused = 0;

    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    mStarted = 0;
    mPaused = 0;

    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    if (mStarted && !mPaused)
    {
        mPaused = 1;

        mPausedTicks = SDL_GetTicks() - mStartTicks; //how many ticks have passed since we started
        mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    if (mStarted && mPaused)
    {
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    if(mStarted)
    {
        if (mPaused)
        { // the timer is paused
            return mPausedTicks;
        } else
        { // the timer is running and we need current time
            return SDL_GetTicks() - mStartTicks;
        }
    } else
    { // clock was never running
        return 0;
    }
}

bool LTimer::isStarted()
{
    return mStarted;
}

bool LTimer::isPaused()
{
    return mPaused && mStarted;
}