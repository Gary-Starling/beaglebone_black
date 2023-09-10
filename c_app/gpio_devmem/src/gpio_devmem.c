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

/**
 * @brief
 *
 * @param addr
 */
void test_ptint_mem_addr(CM_PER_CLK_Def *addr)
{
	static const char *clk_name[70] = {"L4LS_STC", "L3S_STC", "UNUSE1", "L3_STC", "UNUSE2", "CPGMAC0", "LCDC", "USB0", "UNUSE3", "UNUSE4", "TPTC0",
									   "EMIF", "OCMCRAM", "GPMC", "MCASP0", "UART5"
																			"MMC0",
									   "ELM", "I2C2", "I2C1", "SPI0", "SPI1", "UNUSE3", "UNUSE4", "L4LS", "L4FW", "MCASP", "UART1", "UART2",
									   "UART3", "UART4", "TIMER", "TIMER", "TIMER", "TIMER", "UNUSE5", "UNUSE6", "UNUSE7", "UNUSE8",
									   "UNUSE9", "UNUSE10", "UNUSE11", "UNUSE12", "GPIO1", "GPIO2", "GPIO3", "UNUSE6", "TPCC", "DCAN0", "DCAN1", "UNUSE13", "EPWMSS1",
									   "UNUSE14", "EPWMSS0", "EPWMSS2", "L3_INSTR", "L3_CLKCTR", "IEEE5000", "PRUSS", "TIMER5", "TIMER6", "MMC1", "MMC2", "TPTC1", "TPTC2", "UNUSE15",
									   "UNUSE16",
									   "SPINLOCK", "MAILBOX0", "UNUSE17", "UNUSE18", "L4HS_STC", "L4HS", "UNUSE19", "UNUSE20", "OCPWP_L3", "OCPWP", "UNUSE12[3]", "PRUSS_STC", "CPSW", "LCDC_STC", "CLKDIV32K",
									   "CLK_24MHZ"};

	printf("Test addr for lib\r\n");

	/*
	for(uint32_t i = 0, step = 0; i < 70; i++)
	{
		printf("%s : addr - %p\r\n", clk_name[i], (uint32_t *)(addr + step));
		step = sizeof((*((CM_PER_CLK_Def *)(addr + step))));
	}
	*/
	printf("%p\n", &addr->L4LS_STC);
	printf("%p size - %ld\n", (uint32_t *)(addr) + 0, sizeof(*(uint32_t *)(addr) + 0)); // UNUSE5
	printf("%p size - %ld\n", &addr->UNUSE5, sizeof(addr->UNUSE5));
	printf("%p size - %ld\n", &addr->UNUSE5, sizeof(*((CM_PER_CLK_Def *)(0x44e0008C))));
	printf("%p\n", (uint32_t *)(addr) + 1);
	printf("%p\n", &addr->L3S_STC);
	printf("%p\n", &addr->UNUSE1);
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
}
