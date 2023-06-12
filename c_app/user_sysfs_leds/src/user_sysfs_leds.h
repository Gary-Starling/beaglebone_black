/*
 * user_sysfs_leds.h
 *
 *  Created on: 12 июн. 2023 г.
 *      Author: gary
 */

#ifndef USER_SYSFS_LEDS_H_
#define USER_SYSFS_LEDS_H_

#include <stdint.h>

typedef enum {
	LED0,
	LED1,
	LED2,
	LED3
}eLedN;

typedef enum {
	OFF,
	ON
}eState;


#define PATH_NAME_SIZE	((unsigned int)(512))
#define LEDS_PATH		"/sys/class/leds/beaglebone:green:"

int led_pin_set(eLedN pin, eState val);
int led_blink(void);

#endif /* USER_SYSFS_LEDS_H_ */
