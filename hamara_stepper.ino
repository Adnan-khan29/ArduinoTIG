
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#define SCREEN_ADDRESS 0x3C

int Contrast=75;
const int ena = 2; //habilita o motor
const int dir = 3; //determina a direção
const int pul = 4; //executa um passo
int intervalo = 100;   //this determines the speed of motor
int a=0;
int sensorPin = A0;
   // mudanças de estado do pulso
boolean pulso = LOW; //estado do pulso

 

 void setup()
 {
  pinMode(ena, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(pul, OUTPUT);
  digitalWrite(ena, LOW); //habilita em low invertida 
  digitalWrite(dir, LOW); // low +x / high for -X
  digitalWrite(pul, HIGH);
  

    Serial.begin(9600);
    initializeScreen();

    display.clearDisplay();
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // color of text
    display.setCursor(0, 0);
  
    display.println(analogRead(sensorPin)/10);
    display.display();
   // Draw white text
   
 } 
//tring text = "Hello world";
String text = "Hello";
int lastVal = 0;
 
 void loop(){ 

  pulso = !pulso; //refer to boolean assignment above
  digitalWrite(pul, pulso); //inverts pulse signal with every loop
  delayMicroseconds(intervalo);
  readPotentioMeter();
  
//  Serial.println(val);
  

 }

 void readPotentioMeter() {
  int val = analogRead(sensorPin);
  
  int lastDigit = val % 10;
  
  val /= 10;

  if(abs(lastVal - val) > 3){
    lastVal = val;
    text = val;
    intervalo = val * 30;
    a = 0.00000132*val*val*val*val*val*val - 0.00012248*val*val*val*val*val + 0.00467472*val*val*val*val - 0.09477181*val*val*val + 1.10455417*val*val - 7.68904583*val + 36.14399997;

    //a=-0.0063*val*val*val+0.3083*val*val-5.0446*val+35.462;
    if(a>=0 && a<=36){
    printText(String(a));
    }
      
  }
 }

 String printedText = "";

 void printText(String text) {
//  Serial.println(printedText);
  if(printedText == text){}
  else {
    printedText = text;
    display.clearDisplay();
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // color of text
    display.setCursor(0, 0);
    display.println("RPM :");
    display.println(printedText);
//    Serial.println(printedText);
  
    display.display();
   //refresh the display
  }
 }

 void initializeScreen() {

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000); 
 }
