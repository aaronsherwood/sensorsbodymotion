/*
  Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
  Modified by Aaron Sherwood 2019

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.

  you need this library: https://github.com/maniacbug/RF24

*/

/**
 * Example LED Remote
 *
 * This is an example of how to use the RF24 class to control a remote
 * bank of LED's using buttons on a remote control.
 *
 * On the 'remote', connect any number of buttons or switches from
 * an arduino pin to ground.  Update 'button_pins' to reflect the
 * pins used.
 *
 * On the 'led' board, connect the same number of LED's from an
 * arduino pin to a resistor to ground.  Update 'led_pins' to reflect
 * the pins used.  Also connect a separate pin to ground and change
 * the 'role_pin'.  This tells the sketch it's running on the LED board.
 *
 * Every time the buttons change on the remote, the entire state of
 * buttons is send to the led board, which displays the state.
 */

#include <SPI.h>
#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_printf.h"

//
// Hardware configuration
//

// Set up nRF24L01 radio on HW SPI bus plus pins 7 & 8
/* 
teensy lc & 3.2 
SCK   (Clock)           13
MOSI  (Data Output)     11
MISO  (Data Input)      12

looking from top down to wireless transceiver
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
typedef enum { role_remote = 1, role_led } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Remote", "LED Board"};

// The role of the current running sketch
role_e role;

// sets the role of this unit in hardware.  Connect to GND to be the 'led' board receiver
// Leave open to be the 'remote' transmitter
const int role_pin = A4;

// Pins on the remote for buttons
const uint8_t button_pins[] = { 2 };
const uint8_t num_button_pins = sizeof(button_pins);

// Pins on the LED board for LED's
const uint8_t led_pins[] = { 3 };
const uint8_t num_led_pins = sizeof(led_pins);

// States of everything
uint8_t button_states[num_button_pins];
uint8_t led_states[num_led_pins];

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
    role = role_led;

  //
  // Print preamble
  //
  Serial.begin(115200);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted2/\n\r");
  printf("ROLE: %s\n\r", role_friendly_name[role]);

  // Setup and configure rf radio
  radio.begin();
  // Single radio pipe address for the 2 nodes to communicate.
  if ( role == role_remote )
  {
    radio.openWritingPipe(pipe);
  }
  else
  {
    radio.openReadingPipe(1, pipe);
    radio.startListening(); // listen on LED board
  }

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();

  //
  // Set up buttons / LED's
  //
  
  // Set pull-up resistors for all buttons
  if ( role == role_remote )
  {
    int i = num_button_pins;
    while (i--)
    {
      pinMode(button_pins[i], INPUT);
      digitalWrite(button_pins[i], HIGH);
    }
  }

  // Turn LED's OFF until we start getting keys
  if ( role == role_led )
  {
    int i = num_led_pins;
    while (i--)
    {
      pinMode(led_pins[i], OUTPUT);
      led_states[i] = LOW;
      digitalWrite(led_pins[i], led_states[i]);
    }
  }
}

void loop(void)
{
  if (role == role_remote)
  {
    // read all button pins and set states
    int i = num_button_pins;
    while (i--)
    {
      uint8_t state = ! digitalRead(button_pins[i]);
      if ( state != button_states[i] )
      {
        button_states[i] = state;
      }
    }

    // send states to LED board
    bool ok = radio.write( button_states, num_button_pins );
    if (ok)
      printf("Sent ok...\n\r");
    else
      printf("Send failed.\n\r");
  }

  if ( role == role_led )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( button_states, num_button_pins  );

        // in C to get size of array divide the sice of array by the size of the unit it is containing
        for (int i = 0; i < sizeof(button_states) / sizeof(uint8_t); i++) {
          // to print out ints use % d, to print out multiple separate by commas, /n/r means new line
          printf("Button %d State: %d\n\r", i, button_states[i]);
        }

        // write LEDs based on the button states
        int i = num_led_pins;
        while (i--)
        {
          led_states[i] = button_states[i];
          digitalWrite(led_pins[i], led_states[i]);
        }
      }
    }
  }
}
