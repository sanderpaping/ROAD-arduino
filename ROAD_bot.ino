#include <Adafruit_NeoPixel.h>
 
#define RING 6
#define TEMP A0
#define LIGHT A1

 
Adafruit_NeoPixel ring = Adafruit_NeoPixel(16, RING, NEO_GRB + NEO_KHZ800);


//Kleuren definieren
uint32_t red = ring.Color(255, 0, 0);  // red
uint32_t green = ring.Color(0, 255, 0);  // green
uint32_t blue = ring.Color(0, 0, 255);  // blue
uint32_t yellow = ring.Color(255, 255, 0);  // yellow
uint32_t magenta = ring.Color(255, 0, 255); // Magenta
uint32_t brown = ring.Color(128,0,0);


void setup() {

  //Start serial
  Serial.begin(9600);
  
  //Neopixel ring
  ring.begin();
  ring.setBrightness(255); //adjust brightness here
  ring.show(); // Initialize all pixels to 'off'

  //Temperatuur sensor
  pinMode(TEMP, INPUT);

  //Ligt sensor
  pinMode(LIGHT, INPUT);
}


//---------------------------------------------//
//-----------------MAIN LOOP------------------//
//-------------------------------------------// 
void loop() {

  readSerial();
  //getLight();
  //RainbowCycle();
  //setColor(brown);
}
 




//---------------------------------------------//
//-------------NEO PIXEL RING-----------------//
//-------------------------------------------//

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<ring.numPixels(); i++) {
      ring.setPixelColor(i, c);
      ring.show();
      delay(wait);
  }
}

//Zet de ring in een kleur die eerder in de code gedifineerd staan
void setColor(uint32_t color){

  for(int i=0; i<ring.numPixels(); i++) {
      ring.setPixelColor(i, color);
      ring.show();
    }
  
}

void chillMode(int wait){
  while (Serial.available() == 0){
    colorWipe(red, wait);
    colorWipe(green, wait);
    colorWipe(yellow, wait);
    colorWipe(magenta, wait);
  }
}

void turnOff(){
  for(int i=0; i<ring.numPixels(); i++) {
      ring.setPixelColor(i, (0,0,0));
      ring.show();
    }
}

void flicker(){
  while (Serial.available() == 0){
    setColor(red);
    delay(100);
    turnOff();
    delay(100);
  }
}

//---------------------------------------------//
//-------------SERIEEL UITLEZEN---------------//
//-------------------------------------------//

void readSerial(){
  if(Serial.available() > 0){
    String serialInput = Serial.readString();

    
    if(serialInput == "temperatuur"){
      getTemp(0);
    }else if(serialInput == "light"){
      getLight(0);
    } else if(serialInput == "chill"){
      chillMode(100);
    } else if (serialInput == "off"){
      turnOff();
    } else if (serialInput == "flikker"){
      flicker();
    }
 }
}

//---------------------------------------------//
//----------------Licht SENSOR----------------//
//-------------------------------------------//

void getLight(int wait){
  int licht = (analogRead(LIGHT));
  Serial.println(licht);
  delay(wait);

  if(licht < 990){
    setColor(red);
  } else {
    setColor(green);
  }  
}

//---------------------------------------------//
//-------------TEMPERATUUR SENSOR-------------//
//-------------------------------------------//

void getTemp(int wait){
  int temp = ((analogRead(TEMP)* 500)/1024);

  if(temp < -10) {
    temp == temp * -1;
  }
  
  Serial.println(temp);
  delay(wait);
}




 

 

 

