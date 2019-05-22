#include <stc12.h>
#include <stdint.h>
#include <delay.h>
#include <uart.h>

static const uint8_t isp_down_cmd[4] = {0x12, 0x34, 0x56, 0x78};
static uint8_t send_flags = 0;
static struct buffer send_buf = {{0}, 0, 0, 0};
static struct buffer recv_buf = {{0}, 0, 0, 0};
void uart_delay(uint32_t count)
{
	uint32_t i, j;
	for (i = 0; i < count; i++)
		for (j = 0; j < 1000; j++)
			;
}

void reboot(uint8_t chr)
{
	static char i = 0;
	if (chr == isp_down_cmd[i])
	{
		i++;
		if (i == 4)
		{
			uart_delay(200);
			IAP_CONTR = 0x60;
		}
	}
	else
	{
		i = 0;
	}
}

int get_byte(struct buffer *buf)
{
	uint8_t bytes;
	if (buf->count == 0)
		return ERROR_NUM;

	bytes = buf->buf[buf->read];
	buf->read = (buf->read + 1) % BUF_SIZE;
	buf->count--;
	return bytes;
}

int set_byte(struct buffer *buf, uint8_t data)
{
	if (buf->count == BUF_SIZE)
		return ERROR_NUM;

	buf->buf[buf->write] = data;
	buf->write = (buf->write + 1) % BUF_SIZE;
	buf->count++;
	return 1;
}
int uart_send_byte(uint8_t data)
{
	int ret;
	uint8_t a = 1;
	ES = 0;
	do
	{
		ret = set_byte(&send_buf, data);
	} while (ret == ERROR_NUM);
	if (send_flags == 0)
	{
		TI = 1;
		send_flags = 1;
	}
	ES = 1;
	return ret;
}

uint8_t uart_send_string(const char *str)
{
	uint8_t count = 0;
	while (*str)
	{
		if (uart_send_byte((uint8_t)*str) == ERROR_NUM)
			break;
		str++;
		count++;
	}
	return count;
}

int uart_recv_byte(void)
{
	int data;
	ES = 0;
	data = get_byte(&recv_buf);
	ES = 1;
	return data;
}

uint8_t uart_recv_bytes(uint8_t *buf, uint8_t num)
{
	uint8_t i;
	int data;
	for (i = 0; i < num; i++)
	{
		data = uart_recv_byte();
		if (data == ERROR_NUM)
			break;
		buf[i] = (uint8_t)data;
	}
	return i;
}

void uart_isr(void) __interrupt 4
{
	uint8_t data = 0;
	if (RI == 1)
	{
		RI = 0;
		data = SBUF;
		set_byte(&recv_buf, data);
		reboot(data);
	}
	if (TI == 1)
	{
		TI = 0;
		if (send_buf.count)
		{
			// P0 = send_buf.count;
			SBUF = (uint8_t)get_byte(&send_buf);
		}
		else
		{
			send_flags = 0;
		}
	}
}

void uart_init(void)
{
	PCON &= 0x7f;
	SCON = 0x50;
	BRT = 0xFA;
	AUXR |= 0x04;
	AUXR |= 0x01;
	AUXR |= 0x10;

	T1 = 0;
	ES = 1;
	EA = 1;
}