/**
 * Controlling a servo position using a potentiometer (variable resistor)
 * by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>
 * 
 * modified on 8 Nov 2013
 * by Scott Fitzgerald
 * http://www.arduino.cc/en/Tutorial/Knob
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

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(PB1);  // attaches the servo on pin PB1 to the servo object
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}