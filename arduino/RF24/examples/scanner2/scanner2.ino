/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Channel scanner
 *
 * Example to detect interference on the various channels available.
 * This is a good diagnostic tool to check whether you're picking a
 * good channel for your application.
 *
 * Inspired by cpixip.
 * See http://arduino.cc/forum/index.php/topic,54795.0.html
 */

/**
   This version tweaked a bit to give more informative stats. M. Pendrith, May 2014.
 */

#include <SPI.h>
#include "nRF24L01.h"
#include <RF24.h>
#include "RF24_printf.h"

//
// Hardware configuration
//

// Set up nRF24L01 radio on HW SPI bus plus pins 3 & 7

RF24 radio(3,7);

//
// Channel info
//

const uint8_t num_channels = 128;
uint8_t values[num_channels];

//
// Setup
//

void setup(void)
{
  //
  // Print preamble
  //

  Serial.begin(115200);
  printf_begin();
  printf("\n\rRF24/examples/scanner/\n\r");

  //
  // Setup and configure rf radio
  //

  radio.begin();
  radio.setAutoAck(false);

  // Get into standby mode
  radio.startListening();
  radio.stopListening();

  // Print out header, high then low digit
  int i = 0;
  while ( i < num_channels )
  {
    printf("%x",i>>4);
    ++i;
  }
  printf("\n\r");
  i = 0;
  while ( i < num_channels )
  {
    printf("%x",i&0xf);
    ++i;
  }
  printf("\n\r");
}

//
// Loop
//

const int num_reps = 100;

void loop(void)
{
  // Clear measurement values
  memset(values,0,sizeof(values));

  // Scan all channels num_reps times
  int rep_counter = num_reps;
  while (rep_counter--)
  {
    int i = num_channels;
    while (i--)
    {
      // Select this channel
      radio.setChannel(i);

      // Listen for a little
      radio.startListening();
      delayMicroseconds(128);
      radio.stopListening();

      // Did we get a carrier?
      if ( radio.testCarrier() ) {
	if (values[i] < 0xff)
	  ++values[i];
      }
    }
  }

  // Print out channel measurements, clamped to a single hex digit
  int i = 0;
  while ( i < num_channels )
  {
    if (values[i] < 0x10 )
      printf("%x",values[i]);
    else if (values[i] < 0xff )
      printf("X");
    else
      printf("Z");
    ++i;
  }
  printf("\n\r");
}

// vim:ai:cin:sts=2 sw=2 ft=cpp
