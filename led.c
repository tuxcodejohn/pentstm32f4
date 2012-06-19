#include "main.h"
static GPIO_InitTypeDef  GPIO_InitStructure;
void initLed(void) {
     
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void setLed(int led, int state) { //1:green, 2:orange, 3:red, 4:blue
        if (led>4) {
                return;
        }   
        if (state==1) {
                GPIO_SetBits(GPIOD, GPIO_Pin_11<<led);
        }   
        if (state==0) {
                GPIO_ResetBits(GPIOD, GPIO_Pin_11<<led);
        }   
}

