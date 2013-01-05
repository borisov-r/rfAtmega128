/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

/*
	This version of pins_arduino.h is for the Zigduino r1
	Pierce Nichols 2011 Oct 11
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            36
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 28 : -1)
#define digitalPinHasPWM(p)         ((p) == 5 ||(p) == 2 ||(p) == 4 ||(p) == 8 ||(p) == 9 ||(p) == 10 ||(p) == 11)

/*const static uint8_t SS   = 10*/
const static uint8_t MOSI = 15;
const static uint8_t MISO = 12;
const static uint8_t SCK  = 13;

const static uint8_t SDA = 17;
const static uint8_t SCL = 16;
const static uint8_t LED = 13;

const static uint8_t A0 = 28;
const static uint8_t A1 = 29;
const static uint8_t A2 = 30;
const static uint8_t A3 = 31;
const static uint8_t A4 = 32;
const static uint8_t A5 = 33;
const static uint8_t A6 = 34;
const static uint8_t A7 = 35;

// A majority of the pins are NOT PCINTs, SO BE WARNED (i.e. you cannot use them as receive pins)
// Only pins available for RECEIVE (TRANSMIT can be on any pin):
// Pins: 7, 8, 9, 10, 11, 12, 13, 20

#define digitalPinToPCICR(p)    ( (((p) >= 7) && ((p) <= 13)) || \
                                  ((p) == 15) ? (&PCICR) : ((uint8_t *)0) )

#define digitalPinToPCICRbit(p) ( ((p) == 7) ? 1 : 0 )

#define digitalPinToPCMSK(p)    ( ((((p) >= 8) && ((p) <= 13)) || ((p) == 15)) ? (&PCMSK0) : \
                                ( ((p) == 7) ? (&PCMSK1) : \
                                ((uint8_t *)0) ) )

#define digitalPinToPCMSKbit(p) ( ((p) == 7) ? 0 : \
                                ( ((p) == 8) ? 4 : \
                                ( ((p) == 9) ? 7 : \
                                ( ((p) == 10) ? 6 : \
                                ( ((p) == 11) ? 5 : \
                                ( ((p) == 12) ? 3 : \
                                ( ((p) == 13) ? 1 : \
                                ( ((p) == 15) ? 2 : \
                                0 ) ) ) ) ) )

#ifdef ARDUINO_MAIN

const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t)&DDRB,
	NOT_A_PORT,
	(uint16_t)&DDRD,
	(uint16_t)&DDRE,
	(uint16_t)&DDRF,
	(uint16_t)&DDRG,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	NOT_A_PORT,
	(uint16_t)&PORTB,
	NOT_A_PORT,
	(uint16_t)&PORTD,
	(uint16_t)&PORTE,
	(uint16_t)&PORTF,
	(uint16_t)&PORTG,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	(uint16_t)&PINC,
	(uint16_t)&PIND,
	(uint16_t)&PINE,
	(uint16_t)&PINF,
	(uint16_t)&PING,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
	NOT_A_PIN,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	// PORTLIST		
	// -------------------------------------------		
	PE	,
	PE	,
	PE	,
	PE	,
	PE	,
	PE	,
	PE	,
	PE	,
	PB	,
	PB	,
	PB	,
	PB	,
	PB	,
	PB	,
	PB	,
	PB	,
	PD	,
	PD	,
	PD	,
	PD	,
	PD	,
	PD	,
	PG	,
	PG	,
	PG	,
	PG	,
	PG	,
	PG	,
	PF	,
	PF	,
	PF	,
	PF	,
	PF	,
	PF	,
	PF	,
	PF	,
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	// PIN IN PORT		
	// -------------------------------------------		
	_BV( 0 )	,
	_BV( 1 )	,
	_BV( 2 )	,
	_BV( 3 )	,
	_BV( 4 )	,
	_BV( 5 )	,
	_BV( 6 )	,
	_BV( 7 )	,
	_BV( 4 )	,
	_BV( 7 )	,
	_BV( 6 )	,
	_BV( 5 )	,
	_BV( 3 )	,
	_BV( 1 )	,
	_BV( 0 )	,
	_BV( 2 )	,
	_BV( 0 )	,
	_BV( 1 )	,
	_BV( 2 )	,
	_BV( 3 )	,
	_BV( 4 )	,
	_BV( 7 )	,
	_BV( 0 )	,
	_BV( 1 )	,
	_BV( 2 )	,
	_BV( 3 )	,
	_BV( 4 )	,
	_BV( 5 )	,
	_BV( 0 )	,
	_BV( 1 )	,
	_BV( 2 )	,
	_BV( 3 )	,
	_BV( 4 )	,
	_BV( 5 )	,
	_BV( 6 )	,
	_BV( 7 )	,
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	// TIMERS		
	// -------------------------------------------	
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	TIMER3A	,
	TIMER3B	,
	TIMER3C ,
	NOT_ON_TIMER ,
	NOT_ON_TIMER	,
	TIMER2A ,
	TIMER1C ,
	TIMER1B ,
	TIMER1A ,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
	NOT_ON_TIMER	,
};	

#endif

#endif
