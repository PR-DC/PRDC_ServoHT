/**
 * Sweep
 * by BARRAGAN <http://barraganstudio.com>
 * This example code is in the public domain.
 * 
 * modified 8 Nov 2013
 * by Scott Fitzgerald
 * http://www.arduino.cc/en/Tutorial/Sweep
 * 
 * modified on 27 Feb 2020
 * by Milos Petrasinovic <mpetrasinovic@pr-dc.com>
 * PR-DC, Republic of Serbia
 * info@pr-dc.com
 * 
 * --------------------
 *
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
 
#include <PRDC_ServoHT.h>

ServoHT myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(PB1);  // attaches the servo on pin PB1 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
