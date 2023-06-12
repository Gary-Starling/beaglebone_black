/*
 * uleds.c
 *
 *  Created on: 12 июн. 2023 г.
 *      Author: gary
 *
 *      !!! lsmod | grep leds
 *      >
 *      leds_gpio
 * 		led_class
 *
 */
#include "user_sysfs_leds.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int led_blink(void)
{
	for (eLedN ledn = LED0; ledn < LED3; ledn++)
	{
		if(led_pin_set(ledn, ON) == -1)
			return -1;
		usleep(100000);
	}

	for (eLedN ledn = LED0; ledn < LED3; ledn++)
	{
		if(led_pin_set(ledn, OFF) == -1)
			return -1;
		usleep(100000);
	}

	return 0;
}

int led_pin_set(eLedN pin, eState val)
{
	size_t cntwrb;
	const char *usr_leds_names[4] = { LEDS_PATH"heartbeat/brightness",\
			LEDS_PATH"usr2/brightness"\
			, LEDS_PATH"mmc0/brightness"\
			, LEDS_PATH"usr3/brightness" };
	const char *state[2] = { "0", "1" };
	FILE *fp = NULL;

	if (pin > 3 || val > 1)
		return 1;

	fp = fopen(usr_leds_names[pin], "rwb+");

	if (fp == NULL)
	{
		fprintf(stderr, "Can't open path\r\n");
		return -1;
	}

	cntwrb = fwrite(state[val], sizeof(char), strlen(state[val]) + 1, fp);

	if (cntwrb == 0)
	{
		fclose(fp);
		fprintf(stderr, "Error setting led\r\n");
		return -1;
	}

	fclose(fp);

	return 0;		//OK
}

