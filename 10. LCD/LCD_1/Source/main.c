#include "stm32f10x.h"
#include "LiquidCrystal_I2C.h"
#include "delay.h"

GPIO_InitTypeDef 					GPIO_InitStructure;
I2C_InitTypeDef						I2C_InitStructure;       // khai bao bien de su dung thu vien chuan I2C cua ST.

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
void Delay_msST(uint16_t nTime);              // ham delay tuyet doi bang system tick timer
void I2C_LCD_Configuration(void);              // chuong trinh con cau hinh I2C

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	GPIO_Configuration();
	I2C_LCD_Configuration();
	lcd_init ();                                 // ham khoi dong LCD16x2
	lcd_send_string ("DRUM COLLECTOR TEST1");
  while (1)
  {
		GPIO_WriteBit(GPIOB,GPIO_Pin_7,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)));
		delay_ms(100);
  }
}

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

