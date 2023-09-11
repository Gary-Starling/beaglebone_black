/*
 ============================================================================
 Name        : gpio_devmem.c
 Author      : gary
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include "gpio_devmem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

/* pointers to mapped register memory */
static volatile uint32_t * gpio0 = NULL, * gpio1 = NULL, * gpio2 = NULL, * gpio3 = NULL;

/**
 * @brief Test function for displaying registers address
 *
 * @param addr - pointer to structure of registers
 * @return - void 
 */
void test_print_mem_addr(const CM_PER_CLK_Def *const addr)
{
	static const char *clk_name[REG_MASS_NAME_SIZE] = {"L4LS_STC", "L3S_STC", "UNUSE1", "L3_STC", "UNUSE2", "CPGMAC0", "LCDC", "USB0", "UNUSE3", "TPTC0", "EMIF", "OCMCRAM", "GPMC",
													   "MCASP0", "UART5", "MMC0", "ELM", "I2C2", "I2C1", "SPI0", "SPI1", "UNUSE4", "UNUSE5", "UNUSE6", "L4LS", "L4FW", "MCASP1", "UART1", "UART2", "UART3", "UART4", "TIMER7",
													   "TIMER2", "TIMER3", "TIMER4", "UNUSE7", "UNUSE8", "UNUSE9", "UNUSE10", "UNUSE11", "UNUSE12", "UNUSE13", "UNUSE14", "GPIO1", "GPIO2", "GPIO3",
													   "UNUSE15", "TPCC", "DCAN0", "DCAN1", "UNUSE16", "EPWMSS1", "UNUSE17", "EPWMSS0", "EPWMSS2", "L3_INSTR", "L3_CLKCTR", "IEEE5000",
													   "PRUSS", "TIMER5", "TIMER6", "MMC1", "MMC2", "TPTC1", "TPTC2", "UNUSE18", "UNUSE19", "SPINLOCK", "MAILBOX0", "UNUSE20", "UNUSE21",
													   "L4HS_STC", "L4HS", "UNUSE22", "UNUSE23", "OCPWP_L3", "OCPWP", "UNUSE24", "UNUSE25", "UNUSE26", "PRUSS_STC,", "CPSW", "LCDC_STC",
													   "CLKDIV32K,", "CLK_24MHZ,"};

	uint32_t *addr_reg = (uint32_t *)addr;

	printf("Test addr for lib\n");

	for (size_t i = 0; i < REG_MASS_NAME_SIZE; i++)
		printf("%ld)%s - addr: %p\n", i, clk_name[i], addr_reg + i);
}


/**
 * @brief
 *
 * @param bankN
 * @return int
 */
int gpio_clk_init(eGpioBankN bankN)
{
	switch (bankN)
	{
	case GPIO1:
		break;
	case GPIO2:
		break;
	case GPIO3:
		break;
	default:
		return -1;
		break;
	}

	return -1;
}


/**
 * @brief open dev/mem/ (device)
 * @noparam
 * @return int - result (OK - 0) /(ERR -1)
 */
int gpio_devm_init(void)
{
	int res = 0;
	int fp;

	fp = open("/dev/mem", O_RDWR | O_SYNC);
	if (fp == -1)
	{
		printf("can not open /dev/mem\n  Erroro : %s\n", strerror(errno));
	    res = -1;
	}
	
	/*                             size 4kb                                                     */
	gpio0 = (uint32_t *)mmap( NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fp, GPIO0_BASE );
	gpio1 = (uint32_t *)mmap( NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fp, GPIO1_BASE );
	gpio2 = (uint32_t *)mmap( NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fp, GPIO2_BASE );
	gpio3 = (uint32_t *)mmap( NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fp, GPIO3_BASE );

	if(gpio0 == MAP_FAILED || gpio1 == MAP_FAILED || gpio2 == MAP_FAILED || gpio3 == MAP_FAILED)
	{
		printf("map failed\n  Erroro : %s\n", strerror(errno));
	    res = -1;
	}

	return res;
}
