#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include "GameLogic.h"

using namespace std;

static double diffclock(clock_t clock1, clock_t clock2)
{
    double diffticks = clock1 - clock2;
    double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
    return diffms;
}

void GameLogic::init()
{
    zedboard->TurnOffLeds();

    score = 0;
    activeLED = 1;
    timeToTick = 500; //ms
    direction = DIR_UP;
    currentState = STATE_PLAY;
}

void GameLogic::start()
{
    currentState = STATE_INIT;

    while (true)
    {
        switch (currentState)
        {
        case STATE_INIT:
        {
            init();
            break;
        }
        case STATE_PLAY:
        {
            play();
            break;
        }
        case STATE_GAME_OVER:
        {
            game_over();
            break;
        }
        }
    }
}

// TODO: Replace hardcoded ints with actual time values
void GameLogic::play()
{
    double timeOnThisStep = 0;
    clock_t timeWhenStepStarted = clock();

    /*
     TODO: timeToTick should change to a random reasonable value every time
     activeLED is changed to make the game not boring and predictable.
    */
    while (currentState == STATE_PLAY)
    {
        clock_t timeNow = clock();
        timeOnThisStep = timeOnThisStep + diffclock(timeNow, timeWhenStepStarted);
        if (score == maxLeds)
        {
            currentState = STATE_GAME_OVER;
        }
        else if (activeLED == startingLED - 1)
        {
            currentState = STATE_GAME_OVER;
        }
        else if (wiimote->isAPressed() && activeLED == startingLED)
        {
            activeLED = startingLED + 1;
            direction = DIR_UP;
            score = score + 1;
        }
        else if (timeOnThisStep > timeToTick)
        {
            if (activeLED == maxLeds)
            {
                activeLED = maxLeds - 1;
                direction = DIR_DOWN;
            }
            else if (direction == DIR_DOWN)
            {
                activeLED = activeLED - 1;
            }
            else
            {
                activeLED = activeLED + 1;
            }
        }
    }
}

void GameLogic::game_over()
{
    zedboard->TurnOffLeds();
    while (score >= 0)
    {
        zedboard->Write1Led(score, 1);
        score = score - 1;
    }

    while (currentState == STATE_GAME_OVER)
    {
        if (wiimote->isBPressed())
        {
            currentState = STATE_INIT;
        }
    }
}
