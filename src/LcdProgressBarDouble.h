/*
  LcdProgressBarDouble.h - v1.2.0 - 2018-04-26

  LcdProgressBarDouble is an Arduino library for displaying a 2 progress bars in a single row in LCD display,
  which is previously initialized. This library uses LiquidCrystal library for displaying.

  Copyright (c) 2016 Wilfried Loche.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.

  https://create.arduino.cc/projecthub/wloche/lcdprogressbardouble-707d5c
  https://github.com/wloche/LcdProgressBarDouble

> v1.0.4: DoubleBarPot.ino uses 8036 bytes and 498 bytes of RAM
> v1.0.5: DoubleBarPot.ino uses 7446 bytes and 310 bytes of RAM
> v1.1.0: Usage of PROGMEM for bars and intToBars
          DoubleBarPot.ino uses 7538 bytes and 230 bytes of RAM
> v1.2.0: Allows negative Integers
*/
#ifndef LcdProgressBarDouble_h
#define LcdProgressBarDouble_h

#include "Arduino.h"
#include <LiquidCrystal.h>
#include <avr/pgmspace.h>

/**
 * Version
 * (Major:non-compatible changes) . (Minor:backwards compatible changes) . (Patch:bugfix releases)
 * @refer http://semver.org/
 */
#define LCDPROGRESSBARDOUBLE_VERSION  "1.2.0"

/**
 * Debug mode?
 * - Uncomment to debug (verbose on Serial monitor)
 * - Comment it to avoid debug messages
 */
//#define LCDPROGRESSBAR_DEBUG

/**
 * PROGMEM usage?
 * - Comment to PREVENT using PROGMEM (EEPROM memory instead of RAM)
 */
#define LCDPROGRESSBAR_USE_PROGMEM

class LcdProgressBarDouble
{
  public:
    /**
     * Contructor
     * @param lcd     LiquidCrystal instance (must pass the pointer via prefix &, e.g. &lcd)
     * @param row     Which row to display. 0 is the 1st row, 1 is the second, ...
     * @param numCols Number of columns your LCD has (16, 8, ...)
     */
    LcdProgressBarDouble(LiquidCrystal* lcd, int row = 0, int numCols = 16);


    /**
     * Set the starting value of your progress bar (0 by default)
     * @param minValue1 Starting value
     * @param minValue2 Starting value
     */
    void setMinValues(signed long minValue1, signed long minValue2 = 0);
    /**
     * Set the starting value of your progress bar (0 by default)
     * @param minValue1 Starting value
     */
    void setMinValue1(signed long minValue);
    /**
     * Set the starting value of your progress bar (0 by default)
     * @param minValue2 Starting value
     */
    void setMinValue2(signed long minValue);

    /**
     * Set the finishing values of your progress bar (must be provided)
     * @param maxValue1 Finishing value
     * @param maxValue2 Finishing value
     */
    void setMaxValues(signed long maxValue1, signed long maxValue2 = 0);
    /**
     * Set the finishing value of your progress bar (mandatory)
     * @param maxValue1 Finishing value
     */
    void setMaxValue1(signed long maxValue);
    /**
     * Set the finishing value of your progress bar (mandatory)
     * @param maxValue2 Finishing value
     */
    void setMaxValue2(signed long maxValue);

    /**
     * Set the starting and finishing values of your progress bar at once
     * @param minValue1 Starting value
     * @param maxValue1 Finishing value
     */
    void setRangeValue1(signed long minValue1, signed long maxValue1);
    /**
     * Set the starting and finishing values of your progress bar at once
     * @param minValue2 Starting value
     * @param maxValue2 Finishing value
     */
    void setRangeValue2(signed long minValue2, signed long maxValue2);

    /**
     * Disable primary progress bar
     *
     * Semantic shortcut to setRangeValue1(0, 0)
     */
    void disableBar1();
    /**
     * Disable secondary progress bar
     *
     * Semantic shortcut to setRangeValue2(0, 0)
     */
    void disableBar2();

    /**
     * Draw the progress bar on the LCD
     * @param value Value to draw
     */
    void draw(signed long value1, signed long value2 = 0);
    /**
     * Alias on draw() (LcdBarGraph style :))
     */
    void drawValues(signed long value1, signed long value2 = 0);

  private:
    //-- LiquidCrystal instance
    LiquidCrystal* _lcd;

    //-- Starting values
    signed long _minValues[2] = {0, 0};
    //-- Finishing values
    signed long _maxValues[2];
    //-- Computed finishing values (optimization purpose only, to avoid some repetitive maths)
    signed long _computedMaxValues[2];

    //-- Number of columns your LCD has (16, 8, ...)
    int _numCols = 0;
    //-- Computed number of columns (optimization purpose only, to avoid some repetitive maths)
    int _computedNumCols = 0;
    //-- Which row to display. 0 is the 1st row, 1 is the second, ...
    int _row = 0;
    //-- Which position is the progress bar: optimization purpose only; refresh LCD only on change
    byte _previousProgressPos[2] = {0xFF, 0xFF};

#ifdef LCDPROGRESSBAR_USE_PROGMEM
    const static byte bars[];
#else
    static byte bars[8][8];
#endif

#ifdef LCDPROGRESSBAR_USE_PROGMEM
    const static byte intToBars[];
#else
    static byte intToBars[16];
#endif

};

#endif
