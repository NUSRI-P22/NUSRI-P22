#ifndef __PS2_H__
#define __PS2_H__

#include "headfile.h"
#define DI HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)

#define DO_H HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,1)
#define DO_L HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,0)

#define CS_H HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,1)
#define CS_L HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,0)

#define CLK_H HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1)
#define CLK_L HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0)


//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2         9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      26

//These are stick values
#define PSS_RX 5                
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8

extern uint8_t Data[9];
extern uint16_t MASK[16];
extern uint16_t Handkey;
extern int PS2_LX, PS2_LY, PS2_RX, PS2_RY, PS2_KEY;
void PS2_Init(void);
uint8_t PS2_RedLight(void);
void PS2_ReadData(void);
void PS2_Cmd(uint8_t CMD);		  
uint8_t PS2_DataKey(void);		  
uint8_t PS2_AnologData(uint8_t button); 
void PS2_ClearData(void);	  
void delay_init(uint8_t SYSCLK);
void delay_us(uint32_t nus);

void PS2_ShortPoll(void);
void PS2_EnterConfing(void);
void PS2_TurnOnAnalogMode(void);
void PS2_VibrationMode(void);
void PS2_ExitConfing(void);
void PS2_SetInit(void);
void PS2_Vibration(uint8_t motor1 ,uint8_t motor2);
void PS2_Receive(void);
void PS2_print(void);
void PS2_Vofa_print(void);

#endif
