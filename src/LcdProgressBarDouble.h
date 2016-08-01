/*
  LcdProgressBarDouble.h - v1.0.1 - 2016-08-01

  LcdProgressBarDouble is an Arduino library for displaying a 2 progress bars in a single row in LCD display,
  which is previously initialized. This library uses LiquidCrystal library for displaying.

  Copyright (c) 2016 Wilfried Loche.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/
#ifndef LcdProgressBarDouble_h
#define LcdProgressBarDouble_h

#include "Arduino.h"
#include <LiquidCrystal.h>

/**
 * Version
 * (Major:non-compatible changes) . (Minor:backwards compatible changes) . (Patch:bugfix releases)
 * @refer http://semver.org/
 */
#define LCDPROGRESSBARDOUBLE_VERSION  "1.0.1"

/**
 * Debug mode?
 * - Uncomment to debug (verbose on Serial monitor)
 * - Comment it to avoid debug messages
 */
//#define LCDPROGRESSBAR_DEBUG true

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
    void setMinValues(unsigned long minValue1, unsigned long minValue2 = 0);
    /**
     * Set the starting value of your progress bar (0 by default)
     * @param minValue1 Starting value
     */
    void setMinValue1(unsigned long minValue);
    /**
     * Set the starting value of your progress bar (0 by default)
     * @param minValue2 Starting value
     */
    void setMinValue2(unsigned long minValue);

    /**
     * Set the finishing values of your progress bar (must be provided)
     * @param maxValue1 Finishing value
     * @param maxValue2 Finishing value
     */
    void setMaxValues(unsigned long maxValue1, unsigned long maxValue2 = 0);
    /**
     * Set the finishing value of your progress bar (mandatory)
     * @param maxValue1 Finishing value
     */
    void setMaxValue1(unsigned long maxValue);
    /**
     * Set the finishing value of your progress bar (mandatory)
     * @param maxValue2 Finishing value
     */
    void setMaxValue2(unsigned long maxValue);

    /**
     * Set the starting and finishing values of your progress bar at once
     * @param minValue1 Starting value
     * @param maxValue1 Finishing value
     */
    void setRangeValue1(unsigned long minValue1, unsigned long maxValue1);
    /**
     * Set the starting and finishing values of your progress bar at once
     * @param minValue2 Starting value
     * @param maxValue2 Finishing value
     */
    void setRangeValue2(unsigned long minValue2, unsigned long maxValue2);


    /**
     * Draw the progress bar on the LCD
     * @param value Value to draw
     */
    void draw(unsigned long value1, unsigned long value2 = 0);
    /**
     * Alias on draw() (LcdBarGraph style :))
     */
    void drawValues(unsigned long value1, unsigned long value2 = 0);

  private:
    //-- LiquidCrystal instance
    LiquidCrystal* _lcd;

    //-- Starting values
    unsigned long _minValues[2] = {0, 0};
    //-- Finishing values
    unsigned long _maxValues[2];
    //-- Computed finishing values (optimization purpose only, to avoid some repetitive maths)
    unsigned long _computedMaxValues[2];

    //-- Number of columns your LCD has (16, 8, ...)
    int _numCols = 0;
    //-- Computed number of columns (optimization purpose only, to avoid some repetitive maths)
    int _computedNumCols = 0;
    //-- Which row to display. 0 is the 1st row, 1 is the second, ...
    int _row = 0;
    //-- Which position is the progress bar: optimization purpose only; refresh LCD only on change
    byte _previousProgressPos[2] = {-1, -1};



    static byte _bars[8][8];
    static byte _intToBars[16];
};

#endif