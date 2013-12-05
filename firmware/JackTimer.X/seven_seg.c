#include <xc.h>

#include <stdint.h>

const uint8_t seven_seg_table[]={
        //a  b  c  d  e  f  g
0x7E,    //1  1  1  1  1  1  0   0              a
0x30,    //0  1  1  0  0  0  0   1             f b 
0x6D,    //1  1  0  1  1  0  1   2              g 
0x79,    //1  1  1  1  0  0  1   3             e c 
0x33,    //0  1  1  0  0  1  1   4              d 
0x5B,    //1  0  1  1  0  1  1   5 
0x5F,    //1  0  1  1  1  1  1   6 
0x70,    //1  1  1  0  0  0  0   7 
0x7F,    //1  1  1  1  1  1  1   8 
0x7B,    //1  1  1  1  0  1  1   9 
0x37,    //1  1  1  0  1  1  1   A
0x1F,    //0  0  1  1  1  1  1   B
0x0D,    //0  0  0  1  1  0  1   C
0x3D,    //0  1  1  1  1  0  1   D
0x4F,    //1  0  0  1  1  1  1   E
0x47    //1  0  0  0  1  1  1   F
};

void AllDigitsOff()
{
	LATB |= 0x7FF0;
	LATA |= 0x00C0;
}

void Digit2On()
{
	LATB &= ~0x4000;
}
void Digit1On()
{
	LATB &= ~0x2000;
}
void Digit3On()
{
	LATB &= ~0x1000;
}

void Digit0On()
{
	LATB &= ~0x0800;
}

void SevenSegSetDigit(uint8_t position, uint8_t value)
{
	uint8_t bitmap;
	AllDigitsOff();

	bitmap = seven_seg_table[value];

	switch (position)
	{
		case 0:
		{
			Digit0On();
		}
		break;
			
		case 1:
		{
			Digit1On();
		}
		break;
			
		case 2:
		{
			Digit2On();
		}
		break;
			
		case 3:
		{
			Digit3On();
		}
		break;

		default:
		
		break;
	}

	if (bitmap & 0x01)
	{
		LATB &= ~0x0400;
	}
	if (bitmap & 0x02)
	{
		LATA &= ~0x0040;
	}
	if (bitmap & 0x04)
	{
		LATA &= ~0x0080;
	}
	if (bitmap & 0x08)
	{
		LATB &= ~0x0200;
	}
	if (bitmap & 0x10)
	{
		LATB &= ~0x0100;
	}
	if (bitmap & 0x20)
	{
		LATB &= ~0x0080;
	}
	if (bitmap & 0x40)
	{
		LATB &= ~0x0010;
	}
}
			

