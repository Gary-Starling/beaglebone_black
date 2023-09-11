/*
 * main.c
 *
 *  Created on: 24 июн. 2023 г.
 *      Author: gary
 */
#include "gpio_devmem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    test_print_mem_addr(CM_PER_CLK);

    if (!gpio_devm_init())
        return EXIT_FAILURE;

    return 0;
}
