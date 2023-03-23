#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define trigPin 4
#define echoPin 3
#define dhtPin 12
#define dhtType DHT11
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(dhtPin, dhtType); 

void setup() {
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  
  float duration, distance, speed;
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  speed = 331.4 + (0.606*temperature) + (0.0124*humidity);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2)*speed*0.0001;
  
  if (distance >= 400 || distance <= 2){
    display.setCursor(0,10);
    display.print("Out of range :(");
  }
  else {
    display.setCursor(0,10);
    display.print(String("Distance = ") + String(distance));
    display.print("cm");
  }
  delay(1000);
}
