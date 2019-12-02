#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include "ZedBoard.h"

const int gpio_led0_offset = 0x12C;  // Offset for LED0
const int gpio_led1_offset = 0x130;  // Offset for LED1
const int gpio_led2_offset = 0x134;  // Offset for LED2
const int gpio_led3_offset = 0x138;  // Offset for LED3
const int gpio_led4_offset = 0x13C;  // Offset for LED4
const int gpio_led5_offset = 0x140;  // Offset for LED5
const int gpio_led6_offset = 0x144;  // Offset for LED6
const int gpio_led7_offset = 0x148;  // Offset for LED7

void ZedBoard::RegisterWrite(int offset, int value)
{
	*(int *)(pBase + offset) = value;
}

int ZedBoard::RegisterRead(int offset)
{
	return *(int *)(pBase + offset);
}

void ZedBoard::Write1Led(int ledNum, int state)
{
	int letToWrite = 0x12C + (ledNum * 0x004);
	RegisterWrite(letToWrite, state);
}

void ZedBoard::WriteAllLeds()
{
	int arr[8];
	int i = 0, r;
	int value = buttonNum;

	while (value != 0)
	{
		r = value % 2 != 0;
		arr[i++] = r;
		value /= 2;
	}

	for (int j = i - 1; j >= 0; j--) {
		Write1Led(j, arr[j]);
	}
}

void ZedBoard::TurnOffLeds() {
	for (int i = 0; i <= 7; i++) {
		Write1Led(i, 0);
	}
}
