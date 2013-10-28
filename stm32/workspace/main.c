#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <semihosting/semihosting.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <cmsis/core_cm3.h>

#define FLUSH fputc(0x0a, stdout)
#define SYS_WRITE0 0x04
#define SYS_SYSTEM 0x12

//static char cmd[] = "dir";

void SysTick_Handler(void) {
    GPIOC->ODR ^= GPIO_Pin_8;
    GPIOC->ODR ^= GPIO_Pin_9;
}

void UsageFault_Handler(void) {
	CONTROL_Type control = (CONTROL_Type)__get_CONTROL();
	IPSR_Type ipsr = (IPSR_Type)__get_IPSR();
}

int main(void)
{
	// This MCU support 4 bits of priority level. Configure these
	// bits as 4 preempt priority levels and 4 sub-priority levels.
	NVIC_SetPriorityGrouping(5);

    GPIO_InitTypeDef  GPIO_InitStructure;

    // Enable the clock to GPIOC module
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIOC->ODR |= GPIO_Pin_9;

    // Enable the clock to CRC module
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

    // Take the CRC module out for a spin
    CRC->DR = 0xA5A5;
    CRC->DR = 0x5A5A;
    CRC->CR = CRC_CR_RESET;
    CRC->DR = 0x0001;
    CRC->DR = 0x0000;
    CRC->IDR = 0x15;

//	SysTick_Config(0xFFFFFF);
	SysTick_Config(0x700000);

//	printf("Calling SYS_WRITE0 ..."); FLUSH;
//	SH_DoCommand(SYS_WRITE0, (int)cmd, NULL); FLUSH;
//	printf("Call returned"); FLUSH;
//
//	int cmdArgs[2] = {(int)cmd, sizeof(cmd)};
//	int cmdRet = 0;
//	printf("Calling SYS_SYSTEM ..."); FLUSH;
//	SH_DoCommand(SYS_SYSTEM, (int)cmdArgs, &cmdRet);
//	printf("Call returned: %d", cmdRet); FLUSH;

	uint32_t cnt = 0x3FFFFF;
	while(cnt--) {};

	// Enable usage fault exception
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;

	// Enable usage fault on divide by zero
	SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;

	__set_PRIMASK(0);
	__set_FAULTMASK(0);
	__set_BASEPRI(5);

	// Divide by zero
	uint8_t quo = 4/0;

    return 0;
}

