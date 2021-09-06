// Date: 2021 April By: Shaharyar Choudhry
#include <Arduino.h>
#include <U8x8lib.h>
#define MOSFET 2 // The MOSFET driver for the water pump on digital I/O 2
#define REDLED 4 // Big red LED on digital I/O 4
#define BUTTON 6 // Push button on digital I/O 6
#define MOISTURE A1  //pin of sensor

auto display = U8X8_SSD1306_128X64_NONAME_HW_I2C(U8X8_PIN_NONE);
int moistureValue = 0;  // initializing variable
void setup() {
 Serial.begin(9600);
 display.begin();
 display.setFlipMode(1); // flipping OLED screen
 display.clearDisplay();
 display.setFont(u8x8_font_profont29_2x3_r); // set font
 pinMode(MOSFET, OUTPUT); // Sets the D2 pin (MOSFET + Pump) to output
 pinMode(REDLED, OUTPUT); // Sets the D4 pin (LED) to output
 pinMode(BUTTON, INPUT); // Sets the D6 pin (Button) to input
}
//////////function
void Graph() {
const auto value = analogRead(A1);
const byte data[] = {0, 0, highByte(value), lowByte(value)};
Serial.write(data, 4);
Serial.println(); 
}


void loop() {
 delay(200);
 Graph(); // calling graph function
 const auto receivedData = Serial.read();
 // format the data
 char buf[16];
 sprintf(buf, "%03d", receivedData);

 
moistureValue = analogRead(MOISTURE); 
 if(digitalRead(BUTTON) == HIGH) // if button is pressed turn on pump
  {
      digitalWrite(MOSFET,HIGH);
    display.print("Water!  ");
    display.setCursor(0,0);
    
  } 
else if (moistureValue >=650){ // if soil is dry turn on pump
  digitalWrite(MOSFET,HIGH);

  display.setCursor(0,0);
    display.print("water!  ");     // msg on OLED
     display.setCursor(0,5);
  }
 
  else if (moistureValue < 650){  // if soil is dry turn pump off
  digitalWrite(MOSFET,LOW);

 display.setCursor(0,0);
 display.print("no water");
 display.setFont(u8x8_font_profont29_2x3_r);
 display.setCursor(0, 0);
 
 if (!Serial.available()) {
 return;
 }
 
  if (receivedData == 255){ // if button from java is pressed turn on pump
 display.print("water!  ");
 digitalWrite(MOSFET,HIGH);
  delay(4000); // time the pump is turned on (delay controls it)
 }
 if(receivedData<=100){
 
 if(receivedData == 1){
  digitalWrite(REDLED,HIGH); 
 } 
 else if (receivedData ==0){
    digitalWrite(REDLED,LOW);
  
 }

 }
 else {
 //display.print("error");
 digitalWrite(MOSFET,LOW);
 }
  }
 }
