/**
 * PRDC_ServoHT.cpp - Servo HardwareTimer based library
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
 
#include "PRDC_ServoHT.h"

static servo_t servos[MAX_SERVOS]; // static array of servo structures
uint8_t ServoCount = 0; // the total number of attached servos
uint16_t maxValue = 65535;

#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)   // minimum value in uS for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)   // maximum value in uS for this servo

// ServoHT()
// Object constructor
// --------------------
ServoHT::ServoHT(){
  if (ServoCount < MAX_SERVOS) {
    this->servoIndex = ServoCount++; // assign a servo index to this instance
    servos[this->servoIndex].ticks = DEFAULT_PULSE_WIDTH;   // store default values
  } else {
    this->servoIndex = INVALID_SERVO;  // too many servos
  }
}

// attach()
// Attach servo object to pin
// --------------------
uint8_t ServoHT::attach(int pin){
  return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t ServoHT::attach(){
  if(servos[this->servoIndex].Pin.prevAttached) {
    return this->attach(servos[this->servoIndex].Pin.nbr, this->min, this->max);
  } else {
    return false;
  }
}

uint8_t ServoHT::attach(int pin, int min, int max){
  if (this->servoIndex < MAX_SERVOS && !servos[this->servoIndex].Pin.prevAttached) {
    servos[this->servoIndex].Pin.nbr = pin;
    servos[this->servoIndex].ticks = DEFAULT_PULSE_WIDTH;
     
    TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin), PinMap_PWM);
    uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin), PinMap_PWM));
    HardwareTimer *SERVO_TIMER = new HardwareTimer(Instance);
    servos[this->servoIndex].TIM = SERVO_TIMER;
    servos[this->servoIndex].channel = channel;
    
    // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128
    this->min  = (MIN_PULSE_WIDTH - min) / 4; //resolution of min/max is 4 uS
    this->max  = (MAX_PULSE_WIDTH - max) / 4;
    servos[this->servoIndex].TIM->setMode(servos[this->servoIndex].channel, TIMER_OUTPUT_COMPARE_PWM1, servos[this->servoIndex].Pin.nbr);
    servos[this->servoIndex].TIM->setOverflow(REFRESH_INTERVAL, MICROSEC_FORMAT);
    writeMicroseconds(DEFAULT_PULSE_WIDTH);
    servos[this->servoIndex].TIM->resume();
    servos[this->servoIndex].Pin.isActive = true;
    servos[this->servoIndex].Pin.prevAttached = true;
  } else {
    servos[this->servoIndex].TIM->resumeChannel(servos[this->servoIndex].channel);
    servos[this->servoIndex].Pin.isActive = true;
  }
  return this->servoIndex;
}

// detach()
// Detach servo object from pin
// --------------------
void ServoHT::detach(){
  if(servos[this->servoIndex].Pin.prevAttached) {
    servos[this->servoIndex].TIM->pauseChannel(servos[this->servoIndex].channel);
    servos[this->servoIndex].Pin.isActive = false;
  }
}

// write()
// Write angle in degrees to servo
// --------------------
void ServoHT::write(int value){
  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
  if (value < MIN_PULSE_WIDTH) {
    if (value < 0) {
      value = 0;
    } else if (value > 180) {
      value = 180;
    }

    value = map(value, 0, 180, SERVO_MIN(), SERVO_MAX());
  }
  writeMicroseconds(value);
}

// writeMicroseconds()
// Write angle in microseconds to servo
// --------------------
void ServoHT::writeMicroseconds(int value){
  // calculate and store the values for the given channel
  uint8_t index = this->servoIndex;
  if ((index < MAX_SERVOS)) {  // ensure channel is valid
    if (value < SERVO_MIN()) {        // ensure pulse width is valid
      value = SERVO_MIN();
    } else if (value > SERVO_MAX()) {
      value = SERVO_MAX();
    }

    servos[index].ticks = value;
    uint32_t compare_value = (float)maxValue/REFRESH_INTERVAL*value;
    servos[this->servoIndex].TIM->setCaptureCompare(servos[this->servoIndex].channel, compare_value, RESOLUTION_16B_COMPARE_FORMAT);
  }
}

// read()
// Read angle in degrees from servo
// --------------------
int ServoHT::read(){ // return the value as degrees
  return map(readMicroseconds() + 1, SERVO_MIN(), SERVO_MAX(), 0, 180);
}

// readMicroseconds()
// Read angle in microseconds from servo
// --------------------
int ServoHT::readMicroseconds(){
  unsigned int pulsewidth;
  if (this->servoIndex != INVALID_SERVO) {
    pulsewidth = servos[this->servoIndex].ticks;
  } else {
    pulsewidth  = 0;
  }

  return pulsewidth;
}

// attached()
// Check if servo is attached
// --------------------
bool ServoHT::attached(){
  return servos[this->servoIndex].Pin.isActive;
}
