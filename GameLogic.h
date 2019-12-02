#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "Zedboard.h"
#include "Wiimote.h"
#ifndef Gamelogic_H
#define Gamelogic_H

const int STATE_INIT = 0;
const int STATE_PLAY = 1;
const int STATE_GAME_OVER = 2;
const int DIR_UP = 0;
const int DIR_DOWN = 1;

class GameLogic
{
    int activeLED;
    double timeToTick;
    int currentState;
    int direction;
    int maxLeds;
    int startingLED;
    int score;

    ZedBoard *zedboard;
    Wiimote *wiimote;

public:
    GameLogic(ZedBoard *zed_board, Wiimote *wii_mote, int max_leds, int starting_led)
    {
        zedboard = zed_board;
        wiimote = wii_mote;
        maxLeds = max_leds - 1;         // cause mapping starts from 0
        startingLED = starting_led - 1; // cause users don't know counting starts from 0
        currentState = STATE_INIT;
    }

    bool isAPressed();
    void init();
    void start();
    void play();
    void game_over();
};

#endif