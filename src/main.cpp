#include <Arduino.h>
#include "IO22D08.h"
#include <TimerMs.h>

IO22D08 io22d08;
// Timer timer;
// https://github.com/GyverLibs/TimerMs
TimerMs tmr(1000, 1, 0);

void testCallback()
{
  static uint8_t idx;
  static uint8_t charIdx[4] = {0, 1, 2, 3};

  switch(idx)
  {
    case 0:
    case 1:
    case 2:
      io22d08.setCharacter(charIdx[idx], idx);
      ++idx;
      io22d08.setRelay(1);
      io22d08.resetRelay(2);
      break;
    case 3:
      io22d08.setCharacter(charIdx[idx], idx);
      idx=0;
      io22d08.resetRelay(1);
      io22d08.setRelay(2);
      break;
    default:
      break;
  }

  io22d08.updateShiftregs();

}

void setup() {
  Serial.begin(9600);
  io22d08.init();

  tmr.setPeriodMode();

  // int tickEvent = timer.every(5, testCallback);

}

void loop() {
  if (tmr.tick()) {
    testCallback();
    Serial.println("tick");
  }
}