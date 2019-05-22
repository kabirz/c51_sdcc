#include <stc12.h>
#include <stdint.h>
#include <uart.h>
#include <delay.h>

void main(void)
{
	uint8_t a = 1;
	uart_init();
	while (1)
	{
		P0 = ~a;
		delay(10000);
		a = a << 1;
		if (a == 0)
			a = 1;
		uart_send_string("Hello World\r\n");
	}
}
