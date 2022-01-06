/**
 * test_ServoHT.ino - Test Servo HardwareTimer library
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

// Library
// --------------------
// Servo HardwareTimer
// Author: PRDC
#include <PRDC_ServoHT.h>

// Define variables
// --------------------
uint16_t SERVO_PIN = PB1; // data out
ServoHT servo; // Servo motor instances
int width = 0;   // servo position in ms

// setup function
// --------------------
void setup(){
  servo.attach(SERVO_PIN);
}

// loop function
// --------------------
void loop(){ 
  // scan from 0 to 180 degrees
  for(width = 500; width < 2500; width = width+10){                                  
    servo.writeMicroseconds(width);               
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(width = 2500; width > 500; width = width-10){                                
    servo.writeMicroseconds(width);           
    delay(15);       
  } 
} 
