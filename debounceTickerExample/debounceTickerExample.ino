/********************************************************* 
 *  debounceTickerExample
 *  Greg Nordstrom
 *  August, 2019
 *  
 *  Description: This code shows how to use the Ticker
 *  library to automatically update the pushbutton switch 
 *  state being managed by code in the Bounce2 library.
 *  The pushbutton's state is displayed on a serial 
 *  monitor (9600N81).
 *  
 *  This example expects a N.O. pushbutton to be connected
 *  between NodeMCU pin D1 and ground, and uses the
 *  NodeMCU's internal pull-up.
 *  
 *  NB: The main loop() code doesn't nothing--all the
 *  work is done in the updatePBStatus call-back function
 *  which is invoked periodically by the pbTimer object,
 *  and the debouncer object maintains the switch state.
 *********************************************************/
#include "debounceTickerExample.h"
#include <Bounce2.h>    // to debounce pushbuttons
#include <Ticker.h>     // to make Bounce2 work

// create a Ticker object to periodically check the
// the state of a debounced pushbutton
Ticker pbTimer;

// create a Bounce object to debounce a pushbutton switch
Bounce debouncer = Bounce();

// global millisecond tick counter
unsigned long currentMillis = millis();

// state counters
int pressedCount, releasedCount;

void updatePBStatus() {
  // this function is called every 8 milliseconds
  // to update the state of the pushbutton debouncer
  // (adjust the time according to PB characteristics)
  debouncer.update();

  if(debouncer.fell()) {
    Serial.print("Pressed  [");
    Serial.print(++pressedCount);
    Serial.println("]");
  }
  else if(debouncer.rose()) {
    Serial.print("Released [");
    Serial.print(++releasedCount);
    Serial.println("]");
    Serial.println();
  }
}

void clearScreen(void) {
  // clear the screen (only works with
  // terminal emulators like PuTTY)
  Serial.write(27);
  Serial.print("[2J");
  Serial.write(27);
  Serial.print("[H");
}

void setup() {
  Serial.begin(9600);

  // configure pushbutton I/O pin
  pinMode(PB_PIN, INPUT_PULLUP);

  // attach a debouncer to each pushbutton and set debounce interval
  debouncer.attach(PB_PIN);
  debouncer.interval(DEBOUNCE_INTERVAL);
  
  // Create a timer to periodically call the updatePBStatus routine
  pbTimer.attach_ms(PB_UPDATE_TIME, updatePBStatus);

  // initialize counters
  pressedCount = 0;
  releasedCount = 0;

  // make sure random NodeMCU "stuff" is cleared away
  delay(100);
  clearScreen();
}

void loop() {
  debouncer.update();
  
  if(debouncer.fell()){
    Serial.println("Fell");
  } else {
    Serial.println("Up");
  }
  
}
