#include "main.h"
#include "arm_math.h"
#include "math.h"

#include "platf_led.h"
#include "platf_i2c3.h"

static __IO uint32_t TimingDelay;
static __IO uint32_t tick;

void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime * 10;
	while (TimingDelay != 0) ;
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00) {
		TimingDelay--;
	}
	tick++;
}

void main(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	/* SysTick end of count event each 0.1ms */
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 10000);

	initLEDs();
	setLed((LED_NORTH_PIN | LED_EAST_PIN |
		LED_SOUTH_PIN | LED_WEST_PIN), 0);

	i2cinit();
	Delay(2);
	setLed(LED_NORTH_PIN, 1);
	Delay(2);
	I2C_GenerateSTART(I2C3, ENABLE);
	Delay(2);
	setLed(LED_SOUTH_PIN, 1);
	while (I2C_CheckEvent(I2C3, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS) ;

	setLed((LED_NORTH_PIN | LED_EAST_PIN | LED_SOUTH_PIN | LED_WEST_PIN),
	       1);

	for (;;) {
		;
	Delay(2);

	}

	//never get here
	return;
}
