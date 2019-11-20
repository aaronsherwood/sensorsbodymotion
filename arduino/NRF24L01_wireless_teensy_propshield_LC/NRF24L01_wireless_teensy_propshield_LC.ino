/*
  Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
  Modified by Aaron Sherwood 2019

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.

  you need this library: https://github.com/maniacbug/RF24

*/

/**
   Example Propshield Remote

   This is an example of how to use the RF24 class to send
   propshield data remotely to a computer using a second teensy.

   On the 'remote', connect the propshield.

   On the 'receiver' board, connect a unused pin (14 in this case) to ground and change
   the 'role_pin'.  This tells the sketch it's running on the receiver board.

*/

#include <SPI.h>
#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_printf.h"
#include <NXPMotionSense.h>
#include <MahonyAHRS.h>
#include <Wire.h>
#include <EEPROM.h>

//
// Hardware configuration
//

// Set up nRF24L01 radio on HW SPI bus plus pins 7 & 8
/*
  teensy lc & 3.2
  SCK   (Clock)           13
  MOSI  (Data Output)     11
  MISO  (Data Input)      12

  looking from top down to wireless transceiver with attenna at top
  wiring hooks to teensy at:
  3.3V    8-CSN     11-MOSI     (not used)
  GND     7-CE      13-SCK      12-MISO
*/

RF24 radio(7, 8); // ce, csn pins

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipe = 0xF0F0F0F0E1LL;

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.
//

// The various roles supported by this sketch
typedef enum { role_remote = 1, role_receiver } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Remote", "Receiver"};

// The role of the current running sketch
role_e role;

// sets the role of this unit in hardware.  Connect to GND to be the 'led' board receiver
// Leave open to be the 'remote' transmitter
const int role_pin = 14;

// States of everything
int sensor_states[3];
const uint8_t sensors_size = sizeof(sensor_states);

// Propshield
NXPMotionSense imu;
Mahony filter;
float roll, pitch, heading;

void setup(void)
{
  //
  // Role
  //

  // set up the role pin
  pinMode(role_pin, INPUT);
  digitalWrite(role_pin, HIGH);
  delay(20); // Just to get a solid reading on the role pin

  // read the address pin, establish our role
  if ( digitalRead(role_pin) )
    role = role_remote;
  else
    role = role_receiver;

  //
  // Print preamble
  //
  Serial.begin(115200);
  printf_begin();
  printf("ROLE: %s\n\r", role_friendly_name[role]);

  // Setup and configure rf radio
  radio.begin();
  // Single radio pipe address for the 2 nodes to communicate.
  if ( role == role_remote )
  {
    radio.openWritingPipe(pipe);
    // Propshield setup
    imu.begin();
    filter.begin(60); // 60 measurements per second
  }
  else
  {
    radio.openReadingPipe(1, pipe);
    radio.startListening(); // listen on LED board
  }

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();


}

void loop(void)
{
  if (role == role_remote)
  {
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    if (imu.available()) {
      // Read the motion sensors
      imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);

      // Update the Mahony filter
      filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

      // print the heading, pitch and roll
      sensor_states[0] = filter.getRoll();
      sensor_states[1] = filter.getPitch();
      sensor_states[2] = filter.getYaw();
    }

    // send states to LED board
    bool ok = radio.write( sensor_states, sensors_size );
    if (ok)
      printf("Sent ok...\n\r");
    else
      printf("Send failed.\n\r");
  }

  if ( role == role_receiver )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( sensor_states, sensors_size  );
      }
    }
    if (Serial.available() > 0) {
      int val = Serial.read();
      Serial.print(sensor_states[0]);
      Serial.print(" ");
      Serial.print(sensor_states[1]);
      Serial.print(" ");
      Serial.println(sensor_states[2]);
    }
  }
}
