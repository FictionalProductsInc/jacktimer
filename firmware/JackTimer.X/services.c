
#include <stdint.h>
#include <xc.h>
#include "services.h"

volatile uint8_t next_tick = 0;
void sleep_until_next_tick()
{
    while (next_tick == 0);
    next_tick = 0;
}

void sleep_until_switch()
{

}

void init_hardware()
{
	LATB = 0xFFFF;
	LATA = 0x00C0;
	TRISB = 0x000F;
	TRISA = ~0x00C0;
        CNPU1 = 0x00FC;
	ANSB = 0;
	ANSA = 0;
        T3CON = 0x0031;
	IEC0bits.T3IE = 1;

}

uint16_t hour_up_change_counter = 0;
uint16_t hour_down_change_counter = 0;
uint16_t minute_up_change_counter = 0;
uint16_t minute_down_change_counter  = 0;
uint8_t hour_up_last_value = 1;
uint8_t hour_down_last_value = 1;
uint8_t minute_up_last_value = 1;
uint8_t minute_down_last_value = 1;
uint8_t toggle_last_value = 2;

uint16_t hour_up_repeat_counter = 0;
uint16_t hour_down_repeat_counter = 0;
uint16_t minute_up_repeat_counter = 0;
uint16_t minute_down_repeat_counter  = 0;

uint8_t hour_up_toggle = 0;
uint8_t hour_down_toggle = 0;
uint8_t minute_up_toggle = 0;
uint8_t minute_down_toggle  = 0;
uint8_t toggle_toggle  = 0;

uint8_t leftdigit = 0;
uint8_t leftmiddledigit = 0;
uint8_t rightmiddledigit = 0;
uint8_t rightdigit = 0;



#define DEBOUNCE_COUNTER 2
#define INITIAL_CHANGE_COUNTER 300
#define MORE_CHANGE_COUNTER 100
void ServicesPeriodic()
{
	uint8_t logic;

	logic = ((PORTA & 0x0002) == 0);
	if (logic != minute_up_last_value)
	{
		minute_up_change_counter++;
		//if (minute_up_change_counter >= DEBOUNCE_COUNTER)
		{
			// Change
			

			if (logic == 1)
			{
				minute_up_toggle = 1;
			}
		}
		minute_up_repeat_counter = 0;
                minute_up_last_value = logic;
	}
	else
	{
		minute_up_change_counter = 0;
            if (logic == 1)
            {
		++ minute_up_repeat_counter;
		if (minute_up_repeat_counter == INITIAL_CHANGE_COUNTER)
		{
			minute_up_toggle = 1;
		}

		if (minute_up_repeat_counter > (INITIAL_CHANGE_COUNTER + MORE_CHANGE_COUNTER))
		{
			minute_up_toggle = 1;
			minute_up_repeat_counter -= MORE_CHANGE_COUNTER;
		}
            }
	}

	


}

   uint8_t switch_minutes_up_pressed()
    {
	    if (minute_up_toggle)
	    {
		    minute_up_toggle = 0;
		    return(1);
	    }
	    else
	    {
		    return(0);
	    }
    }

uint8_t switch_minutes_down_pressed()
    {
        //PortA 0x0001
        return ((PORTA & 0x0001) == 0);
    }

uint8_t switch_hours_down_pressed()
    {
        //Port B 0x0002
        return ((PORTB & 0x0002) == 0);
    }

uint8_t switch_hours_up_pressed()
{
    //Port B 0x0001
    return ((PORTB & 0x0001) == 0);
}

uint8_t switch_toggle_changed()
{
    //POrt B 0x0004
     return ((PORTB & 0x0004) == 0);
}

void SetLeftDigit(uint8_t digit)
{
    leftdigit = digit;
}

void SetLeftMiddleDigit(uint8_t digit)
{
    leftmiddledigit = digit;
}

void SetRightDigit(uint8_t digit)
{
    rightdigit = digit;
}

void SetRightMiddleDigit(uint8_t digit)
{
    rightmiddledigit = digit;
}
// PIC24F16KL402 Configuration Bit Settings
uint32_t t3_counter = 0;
void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void)
{
        //Runs 800 times a second
	IFS0bits.T3IF = 0;
        TMR3 += (((uint32_t)65536) - 1250);
	++t3_counter;
        ServicesPeriodic();

        if ((t3_counter & 0x7) == 0)
        {
            next_tick = 1;
        }

        switch (t3_counter & 0x03)
        {
            case 0:
            {
                SevenSegSetDigit(0,rightdigit);
            }
            break;
           case 1:
            {
                SevenSegSetDigit(1,rightmiddledigit);
            }
            break;
           case 2:
            {
                SevenSegSetDigit(2,leftmiddledigit);
            }
            break;
            case 3:
            {
                SevenSegSetDigit(3,leftdigit);
            }
            break;

            
        }
}

// FBS
#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Flash Write Protect (General segment may be written)
#pragma config GSS0 = OFF               // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Select (Fast RC Oscillator with Postscaler and PLL (FRCDIV+PLL))
#pragma config SOSCSRC = DIG   // SOSC Source Type (Analog Mode for use with crystal)
#pragma config LPRCSEL = HP             // LPRC Power and Accuracy (High Power/High Accuracy)
#pragma config IESO = ON                // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-speed Start-up enabled))

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode (Primary oscillator disabled)
#pragma config OSCIOFNC = ON            // CLKO Pin I/O Function (Port I/O enabled (CLKO disabled))
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range (Primary Oscillator/External Clock frequency >8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Clock Switching and Fail-safe Clock Monitor Enabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32768)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = SWON            // Watchdog Timer Enable bits (WDT controlled with SWDTEN bit setting)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected (windowed WDT disabled))

// FPOR
#pragma config BOREN = BOR0             // Brown-out Reset Enable bits (Enabled in hardware; SBOREN bit disabled)
#pragma config PWRTEN = ON              // Power-up Timer Enable (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Default SCL1/SDA1 Pins for I2C1)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset at 1.8V)
#pragma config MCLRE = OFF               // MCLR Pin Enable bit (RA5 input disabled; MCLR enabled)

// FICD
#pragma config ICS = PGx3               // ICD Pin Placement Select (EMUC/EMUD share PGC3/PGD3)


