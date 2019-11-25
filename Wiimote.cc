#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "Wiimote.h"

bool Wiimote::isAPressed()
{
	char buffer[16];
	read(fd, buffer, 16);

	int code = buffer[10];
	return code == A_BUTTON;
}

bool Wiimote::isBPressed()
{
	char buffer[16];
	read(fd, buffer, 16);

	int code = buffer[10];
	return code == B_BUTTON;
}