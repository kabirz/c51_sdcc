#include <stc12.h>
#include <stdint.h>

static const uint8_t ISP_DownCmd[4] = {0x12, 0x34, 0x56, 0x78};

static void delay(uint32_t count)
{
	uint32_t i, j;
	for (j = 0; j < count; j++)
		for (i = 0; i++; i < 10000)
			;
}

char ISP_CmpDownCmd(uint8_t chr)
{
	static char i = 0;
	if (chr == ISP_DownCmd[i]) {
		i++;
		if (i == 4) {
			delay(100000);
			IAP_CONTR = 0x60;
		}
	}
	else {
		i = 0;
	}
	return 0;
}

void UART_SendChar(char chr)
{
	ES = 0;
	TI = 0;
	SBUF = chr;
	while (TI == 0)
		;
	TI = 0;
	ES = 0;
}

void UART_SendString(const char *str)
{
	while (*str) {
		UART_SendChar(*str++);
	}
}

void UART_Interrupt_Receive(void) __interrupt 4
{
	char k = 0;
	if (RI == 1) {
		RI = 0;
		k = SBUF;
		ISP_CmpDownCmd(k);
	}
	if (TI == 1)
	{
		TI = 0;
	}
}

void UartInit(void)
{
	PCON &= 0x7f;
	SCON = 0x50;
	BRT = 0xFA;
	AUXR |= 0x04;
	AUXR |= 0x01;
	AUXR |= 0x10;

	TI = 0;
	ES = 1;
	EA = 1;
}