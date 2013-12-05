/* 
 * File:   services.h
 * Author: jabi7
 *
 * Created on November 22, 2013, 6:09 PM
 */

#ifndef SERVICES_H
#define	SERVICES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
    uint8_t switch_minutes_up_pressed();


uint8_t switch_minutes_down_pressed();


uint8_t switch_hours_down_pressed();


uint8_t switch_hours_up_pressed();


uint8_t switch_toggle_changed();


void sleep_until_next_tick();


void sleep_until_switch();


void init_hardware();
void SevenSegSetDigit(uint8_t position, uint8_t value);

void SetLeftDigit(uint8_t digit);
void SetLeftMiddleDigit(uint8_t digit);
void SetRightMiddleDigit(uint8_t digit);
void SetRightDigit(uint8_t digit);
#ifdef	__cplusplus
}
#endif

#endif	/* SERVICES_H */

