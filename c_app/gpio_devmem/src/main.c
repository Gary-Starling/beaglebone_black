/*
 * main.c
 *
 *  Created on: 24 июн. 2023 г.
 *      Author: gary
 */
#include "gpio_devmem.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{ 
    test_ptint_mem_addr(CM_PER_CLK);
    return 0;
}
