/**
 * PRDC_ServoHT.h - Servo HardwareTimer based library
 * Author: Milos Petrasinovic <mpetrasinovic@pr-dc.com>
 * PR-DC, Republic of Serbia
 * info@pr-dc.com
 * 
 * --------------------
 * Copyright (C) 2021 PR-DC <info@pr-dc.com>
 *
 * This file is part of PRDC_ServoHT.
 *
 * PRDC_ServoHT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation, either version 3 of the 
 * License, or (at your option) any later version.
 * 
 * PRDC_ServoHT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with PRDC_ServoHT.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
 
#ifndef _PRDC_SERVOHT_H_
#define _PRDC_SERVOHT_H_
#include "Arduino.h"
#include <HardwareTimer.h>

#define Servo_VERSION           2     // software version of this library

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds

#define MAX_SERVOS  254

#define INVALID_SERVO 255

typedef struct  {
  uint8_t nbr;            // a pin number from 0 to 255
  uint8_t isActive;       // true if this channel is enabled, pin not pulsed if false
  uint8_t prevAttached;       // true if this channel is previusly attached
} ServoPin_t;

typedef struct {
  ServoPin_t Pin; 
  volatile unsigned int ticks;
  uint32_t channel;
  HardwareTimer *TIM;
} servo_t;

class ServoHT {
  public:
    ServoHT();
    uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
    uint8_t attach(int pin, int min, int max); // as above but also sets min and max values for writes.
    uint8_t attach();
    void detach();

    void write(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds
    void writeMicroseconds(int value); // Write pulse width in microseconds
    int read();                        // returns current pulse width as an angle between 0 and 180 degrees
    int readMicroseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
    bool attached();                   // return true if this servo is attached, otherwise false
  private:
    uint8_t servoIndex;               // index into the channel data for this servo
    int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH
    int8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH
};
#endif // _PRDC_SERVOHT_H_
