/*
 * gpio_devmem.h
 *
 *  Created on: 24 июн. 2023 г.
 *      Author: gary
 */

#ifndef GPIO_DEVMEM_H_
#define GPIO_DEVMEM_H_

#include <stdint.h>
#include <stdbool.h>

#define GPIO_SET			(0x194)
#define GPIO_RESET		 	(0x190)

typedef enum
{
	GPIO1,
	GPIO2,
	GPIO3
} eGpioBankN;

#define CM_PER_BASE ((uint32_t)0x44E00000)

/* Clock Module Registers 
	   	start             end		  size
CM_PER 	0x44E0_0000 0x44E0_3FFF 1KB
AM335x ARM Cortex-A8 Microprocessors (MPUs) Technical Reference Manual (Rev. C)
*/
#define REG_MASS_NAME_SIZE	(85)
typedef struct
{
	volatile uint32_t L4LS_STC; // 0h  1
	volatile uint32_t L3S_STC;	// 4h  1
	uint32_t UNUSE1;			// 8h  1
	volatile uint32_t L3_STC;	// Ch  1
	uint32_t UNUSE2;			// 10h 1
	volatile uint32_t CPGMAC0;	// 14h 1
	volatile uint32_t LCDC;		// 18h 1
	volatile uint32_t USB0;		// 1Ch 1
	uint32_t UNUSE3;			// 20h 1
	volatile uint32_t TPTC0;	// 24h 1
	volatile uint32_t EMIF;		// 28h 1
	volatile uint32_t OCMCRAM;	// 2Ch 1
	volatile uint32_t GPMC;		// 30h 1
	volatile uint32_t MCASP0;	// 34h 1
	volatile uint32_t UART5;	// 38h 1
	volatile uint32_t MMC0;		// 3Ch 1
	volatile uint32_t ELM;		// 40h 1
	volatile uint32_t I2C2;		// 44h 1
	volatile uint32_t I2C1;		// 48h 1
	volatile uint32_t SPI0;		// 4Ch 1
	volatile uint32_t SPI1;		// 50h 1
	uint32_t UNUSE4;			
	uint32_t UNUSE5;
	uint32_t UNUSE6;
	volatile uint32_t L4LS;	  // 60h 1
	volatile uint32_t L4FW;	  // 64h 1
	volatile uint32_t MCASP1; // 68h 1
	volatile uint32_t UART1;  // 6Ch 1
	volatile uint32_t UART2;  // 70h 1
	volatile uint32_t UART3;  // 74h 1
	volatile uint32_t UART4;  // 78h 1
	volatile uint32_t TIMER7; // 7Ch 1
	volatile uint32_t TIMER2; // 80h 1
	volatile uint32_t TIMER3; // 84h 1
	volatile uint32_t TIMER4; // 88h 1
	uint32_t UNUSE7;		  // 8ch 8
	uint32_t UNUSE8;
	uint32_t UNUSE9;
	uint32_t UNUSE10;
	uint32_t UNUSE11;
	uint32_t UNUSE12;
	uint32_t UNUSE13;
	uint32_t UNUSE14;
	volatile uint32_t GPIO1;	  // ACh 1
	volatile uint32_t GPIO2;	  // B0h 1
	volatile uint32_t GPIO3;	  // B4h 1
	uint32_t UNUSE15;	  // b8h 1
	volatile uint32_t TPCC;		  // BCh 1
	volatile uint32_t DCAN0;	  // C0h 1
	volatile uint32_t DCAN1;	  // C4h 1
	uint32_t UNUSE16;			  // c8h 1
	volatile uint32_t EPWMSS1;	  // CCh 1
	uint32_t UNUSE17;			  // d0h 1
	volatile uint32_t EPWMSS0;	  // D4h 1
	volatile uint32_t EPWMSS2;	  // D8h 1
	volatile uint32_t L3_INSTR;	  // DCh 1
	volatile uint32_t L3_CLKCTRL; // E0h 1
	volatile uint32_t IEEE5000;	  // E4h 1
	volatile uint32_t PRUSS;	  // E8h 1
	volatile uint32_t TIMER5;	  // ECh 1
	volatile uint32_t TIMER6;	  // F0h 1
	volatile uint32_t MMC1;		  // F4h 1
	volatile uint32_t MMC2;		  // F8h 1
	volatile uint32_t TPTC1;	  // FCh 1
	volatile uint32_t TPTC2;	  // 100h 1
	uint32_t UNUSE18;			  // 104h 1
	uint32_t UNUSE19;
	volatile uint32_t SPINLOCK;   // 10Ch 1
	volatile uint32_t MAILBOX0;   // 110h 1
	uint32_t UNUSE20;			  // 114h 1
	uint32_t UNUSE21;  
	volatile uint32_t L4HS_STC;   // 11Ch 1
	volatile uint32_t L4HS;		  // 120h 1
	uint32_t UNUSE22;			  // 124h
	uint32_t UNUSE23;
	volatile uint32_t OCPWP_L3;	 // 12Ch
	volatile uint32_t OCPWP;	 // 130h
	uint32_t UNUSE24;			 //
	uint32_t UNUSE25;			 //
	uint32_t UNUSE26;			 //
	volatile uint32_t PRUSS_STC; // 140h
	volatile uint32_t CPSW;		 // 144h
	volatile uint32_t LCDC_STC;	 // 148h
	volatile uint32_t CLKDIV32K; // 14Ch
	volatile uint32_t CLK_24MHZ; // 150h
} CM_PER_CLK_Def;

#define CM_PER_CLK ((CM_PER_CLK_Def *)CM_PER_BASE)

/* Clock Module Wakeup Registers
		 start             end		   size
CM_WKUP  0x44E0_0400 	   0x44E0_04FF 256bytes
*/
#define CM_WKUP_BASE ((uint32_t)0x44E00400)
#define CM_WKUP_GPIO0_CLKCTRL  ((uint32_t *)(CM_WKUP_BASE+0x8))

/* CM_WKUP_GPIO0_CLKCTRL Register Field Descriptions */
//#define GPIO_CLK_EN	

/*
GPIO0 0x44E07000 0x44E07FFF 4KB 
GPIO1 0x4804C000 0x4804CFFF 4KB
GPIO2 0x481AC000 0x481ACFFF 4KB 
GPIO3 0x481AE000 0x481AEFFF 4KB 
*/
#define GPIO0_BASE ((uint32_t)(0x44E07000))
#define GPIO1_BASE ((uint32_t)(0x4804C000))
#define GPIO2_BASE ((uint32_t)(0x481AC000))
#define GPIO3_BASE ((uint32_t)(0x481AE000))


/* */
void test_print_mem_addr(const CM_PER_CLK_Def * const addr);

/* gpio init system */
int gpio_devm_init(void);

/* */
int gpio_clk_init(eGpioBankN);

/* */
void gpio_init(uint32_t pin);

/* */
void gpio_set(uint32_t pin, bool st);

#endif /* GPIO_DEVMEM_H_ */
