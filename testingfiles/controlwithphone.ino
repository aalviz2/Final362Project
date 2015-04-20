#include <SoftwareSerial.h> 
char inchar; // Will hold the incoming character from the GSM shield
SoftwareSerial SIM900(7, 8);

/**************Initialize Tricolor Anode LED**************/
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;
int currRGB[] = {0,0,0};
#define COMMON_ANODE

void setup()
{
  Serial.begin(19200);
  // set up the digital pins to control
  setupLED();

  // wake up the GSM shield
  SIM900power(); 
  SIM900.begin(19200);
  delay(20000);  // give time to log on to network.
  SIM900.print("AT+CMGF=1\r");  // set SMS mode to text
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
  // blurt out contents of new SMS upon receipt to the GSM shield's serial out
  delay(100);
  Serial.println("Ready...");
}

void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(7000);
}

void sendSMS()
{
  SIM900.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(100);
  SIM900.println("AT + CMGS = \"+18474213979\"");                                     // recipient's mobile number, in international format
  delay(100);
  SIM900.println("Alex is sending me a message to send you a message!");        // message to send
  delay(100);
  SIM900.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900.println();
  delay(5000);                                     // give module time to send SMS
  SIM900power();                                   // turn off module
}

void loop() 
{
  //If a character comes in from the cellular module...
  if(SIM900.available() >0)
  {
    inchar=SIM900.read();
    //Serial.print(inchar);
    if (inchar=='#')
    {
      delay(10);

      inchar=SIM900.read(); 
      if (inchar=='a')
      {
        delay(10);
        inchar=SIM900.read();
        if (inchar=='0')
        {
          sendSMS();
        } 
        else if (inchar=='1')
        {
          setColor(0,0,0);
        }
          SIM900.println("AT+CMGD=1,4"); // delete all SMS
      }
    }
  }
}//end loop

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  currRGB[0] = red;
  currRGB[1] = green;
  currRGB[2] = blue;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void setupLED(){
  // initialize the ANNODE pins as an output
  pinMode(redPin, OUTPUT);    
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
