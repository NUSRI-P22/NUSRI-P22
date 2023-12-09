#ifndef LED_H
#define LED_H
#include "headfile.h"


void led_blue_start(void);
void led_green_start(void);
void led_red_start(void);
void led_white_start(void);

void led_blue_stop(void);
void led_green_stop(void);
void led_red_stop(void);
void led_white_stop(void);

void led_blue_blink(void);
void led_green_blink(void);
void led_red_blink(void);
void led_white_blink(void);
#endif
