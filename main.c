#include "main.h"
#include "arm_math.h" 
#include "math.h"
#include "led.h"

// http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/DM00037051.pdf
// http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/REFERENCE_MANUAL/DM00031020.pdf

static __IO uint32_t TimingDelay;
static __IO uint32_t tick;
void Delay(__IO uint32_t nTime)
{
	TimingDelay = nTime*10;

	while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
	tick++;
}


GPIO_InitTypeDef  GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef     GPIO_InitStructureTimer;
/*void USART_puts(const char *text)
{
	while (*text)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, *text);
		text++;
	}

}
__attribute__( ( always_inline ) ) static __INLINE float __VSQRTF(float op1)
{
	float result;

	__ASM volatile ("vsqrt.f32 %0, %1" : "=w" (result) : "w" (op1) );
	return(result);
}
*/

int main(void)
{
	RCC_ClocksTypeDef RCC_Clocks;



	RCC_GetClocksFreq(&RCC_Clocks);
	/* SysTick end of count event each 0.1ms */
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 10000);
	
	initLed();
	/* GPIOD Periph clock enable */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
/*
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
*/
	/* Connect USART pins to AF */
/*	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); // USART1_TX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); // USART1_RX
*/

/*
	USART_InitStructure.USART_BaudRate = 230400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	GPIO_InitStructureTimer.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructureTimer.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructureTimer.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructureTimer.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructureTimer.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructureTimer);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TIM_TimeBaseStructure.TIM_Period = 32000; // auto reaload register
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_PrescalerConfig(TIM2, 19, TIM_PSCReloadMode_Immediate);
	TIM_Cmd(TIM2,ENABLE);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing ;
	TIM_OCInitStructure.TIM_OutputState = TIM_Channel_1;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable); 
*/

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

        GPIO_InitStructureTimer.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructureTimer.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructureTimer.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructureTimer.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructureTimer.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructureTimer);

        GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        TIM_OCInitTypeDef TIM_OCInitStructure;

        TIM_TimeBaseStructure.TIM_Period = 32000; // auto reaload register
        TIM_TimeBaseStructure.TIM_Prescaler = 0;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

        TIM_PrescalerConfig(TIM2, 52, TIM_PSCReloadMode_Immediate);

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 1000;
        TIM_OC2Init(TIM2, &TIM_OCInitStructure);
        TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);


        TIM_ARRPreloadConfig(TIM2, ENABLE);
        TIM_Cmd(TIM2,ENABLE);
        uint32_t winkel = 0;
        int led = 0;

	while (1)
	{
/*		USART_puts("test\n");

		char string[100];

		sprintf(string,"SystemCoreClock: %u \n",SystemCoreClock);
		USART_puts(string);
		sprintf(string,"RCC_Clocks.HCLK_Frequency: %u \n",RCC_Clocks.HCLK_Frequency);
		USART_puts(string);

		sprintf(string,"ticks: %u \n",tick);
		USART_puts(string);
*/
		TIM_SetCompare2(TIM2,sin(winkel/1000.0)*800+2400);
                Delay(2);
                winkel++;
		if (winkel==3.14*2*1000) {
                        winkel=0;
                }
		if (winkel==1000) {
                        setLed(1,1);
                }
                if (winkel==2000) {
                        setLed(2,1);
                }
                if (winkel==3000) {
                        setLed(3,1);
                }
                if (winkel==4000) {
                        setLed(4,1);
                }
                if (winkel==5000) {
                        setLed(1,0);
                        setLed(2,0);
                        setLed(3,0);
                        setLed(4,0);
                }

		/* PD12 to be toggled */
		//GPIO_SetBits(GPIOD, GPIO_Pin_12);
		//setLed(1,1);
		/* Insert delay */
		//	Delay(200);
		//setLed(1,0);
		/* PD13 to be toggled */
		//GPIO_SetBits(GPIOD, GPIO_Pin_13);

		/* Insert delay */
		//	Delay(200);
		//setLed(1,1);
		/* PD14 to be toggled */
		//GPIO_SetBits(GPIOD, GPIO_Pin_14);

		/* Insert delay */
		//	Delay(200);
		//setLed(1,0);
		/* PD15 to be toggled */
		//GPIO_SetBits(GPIOD, GPIO_Pin_15);

		/* Insert delay */
		//	Delay(200);
		//setLed(1,1);
		//GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

		/* Insert delay */
		//	Delay(200);
	}
}
