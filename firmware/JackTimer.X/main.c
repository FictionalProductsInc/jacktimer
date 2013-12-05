/* 
 * File:   main.c
 * Author: jabi7
 *
 * Created on November 15, 2013, 7:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "services.h"
/*
 * 
 */

void display_time(void);
void add_10ms_to_time(void);
typedef enum {

	STATE_SLEEP,
	STATE_SETUP,
	STATE_COUNT_UP,
	STATE_COUNT_UP_PAUSE,
	STATE_SET_COUNTDOWN,
	STATE_COUNT_DOWN,
	STATE_COUNT_DOWN_PAUSE,
	STATE_BUZZING,
}timer_state_t;

timer_state_t timer_state = STATE_SETUP;


int8_t sec_100ths = 0;
int8_t sec_10ths = 0;
int8_t sec_1s = 0;
int8_t sec_10s = 0;
int8_t hours_1s = 0;
int8_t minutes_1s = 0;
int8_t hours_10s = 0;
int8_t minutes_10s = 0;
int32_t jacksvariable = 0;

int main(int argc, char** argv) {


    init_hardware();

    while(1)
    {
	  add_10ms_to_time();
	  display_time(); 
	  sleep_until_next_tick();
	  
    }

    return (EXIT_SUCCESS);
}

void Every10Ms()
{
	switch(timer_state)
	{
		case STATE_SLEEP:
		{
			//TODO

		}
		break;
		case STATE_SETUP:
		{
			//TODO
			
		}
		break;
		case STATE_COUNT_UP:
		{
			add_10ms_to_time();
			if (switch_toggle_changed())
			{
				timer_state = STATE_COUNT_UP_PAUSE;
			}
		}
		break;
		case STATE_COUNT_UP_PAUSE:
		{
			//TODO
			
		}
		break;
		case STATE_SET_COUNTDOWN:
		{
			
			//TODO
		}
		break;
		case STATE_COUNT_DOWN:
		{
			
			//TODO
		}
		break;
		
		case STATE_COUNT_DOWN_PAUSE:
		{

			//TODO
		}
		break;

		case STATE_BUZZING:
		{

			//TODO
		}
		break;

		default:
		{

			//TODO
		}
		break;
	}

}

void add_10ms_to_time()
{
	if (hours_10s == 9 && hours_1s == 9 && minutes_10s == 5 && minutes_1s == 9 && sec_10s == 5 && sec_1s == 9  && sec_10ths == 9 && sec_100ths == 9)
	{
		// This number is 99:59:59.99 and is the biggest number
		// we can have.  So we will not increment.
		return;
	}


	sec_100ths = sec_100ths + 1;
	if (sec_100ths == 10)
	{
		sec_100ths = 0;
		sec_10ths = sec_10ths + 1;

		if (sec_10ths == 10)
		{
			sec_10ths = 0;
			sec_1s = sec_1s + 1;
			if (sec_1s == 10)
			{
				sec_1s = 0;
				sec_10s = sec_10s + 1;

				if(sec_10s == 6)
				{
					sec_10s = 0;
					minutes_1s = minutes_1s + 1;
					if (minutes_1s == 10)
					{
						minutes_1s = 0;
						minutes_10s = minutes_10s + 1;

						if (minutes_10s == 6)
						{
							minutes_10s = 0;
							hours_1s = hours_1s + 1;
							if (hours_1s == 10)
							{
								hours_10s = hours_10s + 1;
								hours_1s = 0; 
							}
						}
					}
				}
			}
		}

	}
}



void display_time()
{

	if (hours_10s != 0  || hours_1s != 0 )
	{
		// THere are hours.  Display hours and minutes.  Do not display seconds or 10ths/100ths of seconds
		SetLeftDigit(hours_10s);
		SetLeftMiddleDigit(hours_1s);
		SetRightMiddleDigit(minutes_10s);
		SetRightDigit(minutes_1s);
	}
	else if (minutes_1s != 0 || minutes_10s != 0)
	{
		// THere are minutes.  DIsplay minutes and seconds.  Do not display hours or 10ths/ 10ths of seconds
		SetLeftDigit(minutes_10s);
		SetLeftMiddleDigit(minutes_1s);
		SetRightMiddleDigit(sec_10s);
		SetRightDigit(sec_1s);
	}
	else
	{
		// Display seconds and 100ths of a second
		SetLeftDigit(sec_10s);
		SetLeftMiddleDigit(sec_1s);
		SetRightMiddleDigit(sec_10ths);
		SetRightDigit(sec_100ths);
	}
}
