#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <iostream>
#include <cmath>

#ifndef ZEDBOARD_H
#define ZEDBOARD_H

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;

// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;

class ZedBoard
{
	char *pBase;
	int fd;
	int buttonNum;

public:
	ZedBoard()
	{
		fd = open("/dev/mem", O_RDWR);
		buttonNum = 0;
		pBase = (char *)mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, gpio_address);
	}
	~ZedBoard()
	{
		munmap(pBase, gpio_size);
		close(fd);
	}

	void RegisterWrite(int offset, int value);
	int RegisterRead(int offset);
	void Write1Led(int ledNum, int state);
	void WriteAllLeds();
	void TurnOffLeds();
};

#endif
