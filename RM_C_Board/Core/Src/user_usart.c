//user_usart.c
//2023.10.20
//by gjx

#include "user_usart.h"


void usart_printf(const char *fmt,...)
{
    static uint8_t tx_buf[256] = {0};
    static va_list ap;
    static uint16_t len;
    va_start(ap, fmt);

    //return length of string 
    //·µ»Ø×Ö·û´®³¤¶È
    len = vsprintf((char *)tx_buf, fmt, ap);

    va_end(ap);

    HAL_UART_Transmit_DMA(&huart1,tx_buf, len);

}


