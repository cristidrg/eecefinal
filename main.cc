#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <iostream>
#include <cmath>
#include "ZedBoard.h"
#include "Wiimote.h"
#include "GameLogic.h"

using namespace std;

int main()
{
    ZedBoard zed_board;
    Wiimote wiimote;
    GameLogic theGame(&zed_board, &wiimote, 8, 2);

    theGame.start();
}