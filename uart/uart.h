#ifndef __AUTOISP_H_
#define __AUTOISP_H_

#define BUF_SIZE  32
#define ERROR_NUM -0xaabb
struct buffer {
    uint8_t buf[BUF_SIZE];
    uint8_t read;
    uint8_t write;
    uint8_t count;
};

void uart_init(void);
int uart_recv_byte(void);
uint8_t uart_recv_bytes(uint8_t *buf, uint8_t num);
uint8_t uart_send_string(const char *str);
int uart_send_byte(uint8_t dat);
void uart_isr(void) __interrupt 4;
#endif