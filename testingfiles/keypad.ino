/*
1x4 Keypad from Adafruit.com (Unofficial Source) 
Original Source: Button
Referenced Tutorial on Arduino.com: http://arduino.cc/en/Tutorial/InputPullupSerial
Referenced: http://arduino.cc/en/Reference/pinMode
Turns on and off specified Pin or Prints to Serial Monitor when keys are press 
on a 1x4 keypad from Adafruit.com
*/

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin[] = {9,10,11,12};     // the number of the pushbutton pins
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);  
  // initialize the Serial Monitor @ 9600
  Serial.begin(9600);  
  // initialize the keypad pin(s) as an input:
  for(int x=0; x<4; x++)
  {
    pinMode(buttonPin[x], INPUT_PULLUP); 
  }
}

void loop(){
  // read the state of the keypad value:
  for(int x=0; x<4; x++)
  {
    //signifying the state of which the button is in by reading the appropriate pin #
    buttonState = digitalRead(buttonPin[x]);
    
    // check if the pushbutton on the keypad is pressed.
    // if it is, the buttonState is LOW:
  

	//button 4
    if (buttonState == LOW && buttonPin[x] == 10) {
      // turn LED on:
      Serial.println("BTN 4 ON *");
      digitalWrite(ledPin, HIGH);
    }

  	//button 3
    if (buttonState == LOW && buttonPin[x] == 9) {    
      // turn LED off:   
      Serial.println("BTN 3 OFF * ");
      digitalWrite(ledPin, LOW); 
    }

	//button 1
    if (buttonState == LOW && buttonPin[x] == 12) {    
      // turn LED off:   
      Serial.println("BTN 1 ON * ");
      digitalWrite(ledPin, HIGH); 
    }
	
	//button 2
    if (buttonState == LOW && buttonPin[x] == 11) {    
      // turn LED off:   
      Serial.println("BTN 2 OFF * ");
      digitalWrite(ledPin, LOW); 
    }

  }
  delay(100);
}
