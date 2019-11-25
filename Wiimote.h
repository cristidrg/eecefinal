#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "Zedboard.h"
#ifndef Wiimote_H
#define Wiimote_H

const int A_BUTTON = 48;
const int B_BUTTON = 49;

class Wiimote
{
	int fd;

public:
	Wiimote() 
	{
		fd = open("/dev/input/event0", O_RDONLY);
		if (fd == -1)
		{
			std::cerr << "Error: Could not open event file - forgot sudo? \n";
			exit(1);
		}
	}

	~Wiimote()
	{
		close(fd);
	}


	bool isAPressed();
	bool isBPressed();
};

#endif