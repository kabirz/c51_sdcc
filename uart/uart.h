#ifndef __AUTOISP_H_
#define __AUTOISP_H_
char ISP_CmpDownCmd(char chr);
void UART_send(char chr);
void UartInit(void);
void UART_SendString(const char *str);
void UART_SendChar(char chr);
void UART_Interrupt_Receive(void) __interrupt 4;
#endif