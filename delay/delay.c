#include <stdint.h>

void delay(uint32_t count)
{
	uint32_t i, j;
	for (i = 0; i < count; i++)
		for (j = 0; j < 100; j++)
			;
}