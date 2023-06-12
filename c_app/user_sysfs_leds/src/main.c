/*
 * main.c
 *
 *  Created on: 12 июн. 2023 г.
 *      Author: gary
 */
#include "user_sysfs_leds.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	uint32_t iter = 0;

	led_pin_set(LED0, OFF);
	led_pin_set(LED1, OFF);
	led_pin_set(LED2, OFF);
	led_pin_set(LED3, OFF);

	while(iter++ < 10)
	{
		if(led_blink() == -1)
			exit(1);
	}

	exit(0);
}
