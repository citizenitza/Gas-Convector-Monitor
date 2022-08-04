
#include "WiFi.h"
#include "EEPROM.h"
#include <ESP32Encoder.h>

#define DEBOUNCE_TIME  50 // the debounce time in millisecond, increase this time if it still chatters
#define POSITION_ADDRESS 0x10
#define FALSE 0
#define TRUE 1

ESP32Encoder encoder;

// LED on GPIO2
int ledPin = 2;
int ledPin2 = 4;
int VsupPin = 2;
int EncoderInputA = 36;
int EncoderInputB = 39;
unsigned long encoder2lastToggled;
bool encoder2Paused = false;

//button debounce
int lastSteadyState = LOW;       // the previous steady state from the input pin
int lastFlickerableState = LOW;  // the previous flickerable state from the input pin
int currentState;                // the current reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

void setup() {
  Timer_Init();
  Serial.begin(115200);
  // Set LED as output
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(VsupPin, OUTPUT);
  pinMode(EncoderInputA, INPUT);
  pinMode(EncoderInputB, INPUT);
  digitalWrite(VsupPin, HIGH);

   pinMode(27, INPUT_PULLUP);

  
  // Serial monitor setup
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Wifi Ok");

   EEPROM.read(0x00);
    //ESP32Encoder::useInternalWeakPullResistors=DOWN;
  // Enable the weak pull up resistors
  ESP32Encoder::useInternalWeakPullResistors=UP;

  // use pin 19 and 18 for the first encoder
  encoder.attachHalfQuad(EncoderInputA, EncoderInputB);
    
  // set starting count value after attaching
  //encoder.setCount(37);

  // clear the encoder's raw count and set the tracked count to zero
  encoder.clearCount();
 Serial.println("Encoder Start = " + String((int32_t)encoder.getCount()));
  // set the lastToggle
 ///encoder2lastToggled = millis();
}

void loop() {


  if(CheckTimerState(10)){ // Task 10ms

  }
  if(CheckTimerState(20)){ // Task 20ms

  }
  if(CheckTimerState(50)){ // Task 50ms

  }
  if(CheckTimerState(100)){ // Task 100ms

  }
  if(CheckTimerState(200)){ // Task 200ms
    Serial.println( String((int32_t)encoder.getCount()));
  }
  if(CheckTimerState(500)){ // Task 500ms

  }
  if(CheckTimerState(1000)){ // Task 1s

  }
  if(CheckTimerState(5000)){ // Task 2s

  }
  if(CheckTimerState(10000)){ // Task 10s

  }
  //check button
  CheckBtnState();
}

void CheckBtnState(){
    currentState = digitalRead(27);
  if (currentState != lastFlickerableState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = currentState;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if(lastSteadyState == HIGH && currentState == LOW){
      Serial.println("The button is pressed");
      SetPointZero();
    }else if(lastSteadyState == LOW && currentState == HIGH){
      Serial.println("The button is released");
    }

    // save the the last steady state
    lastSteadyState = currentState;
  }
}

void SetPointZero(){
  encoder.setCount(0);
  EEPROM.write(POSITION_ADDRESS, 0);
}
