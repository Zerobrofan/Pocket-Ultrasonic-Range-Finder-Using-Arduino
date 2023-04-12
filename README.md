https://user-images.githubusercontent.com/100843256/227296053-ed8bd5e9-2792-4283-a651-34ced3cb44b8.mp4

---

The **PURF** is small, hand-sized Arduino project that measures the distance between itself and a still object using ultrasonic sound waves.

The device is powered with a Polymer Li-Ion Single Cell Battery 3.7V, 220mAh which allows for up to 9 hours of battery life.

This project taught me C++, Arduino programming and IoT development.

See the demo video here: https://youtu.be/C64T1HQPC4I

## ⚙ Technologies used:
- C/C++
- Arduino IDE

## ⚡ Components:

- Arduino Nano
- Double Layer 7x5 Perfboard
- HC-SR04 Ultrasonic Sensor
- DHT11 Temperature and Humidity Sensor
- 0.96" OLED 4pin LCD Display
- Polymer Li-Ion Single Cell Battery 3.7V, 220mAh
- DC-DC Boost Converter 0.9V ~ 5V
- Lithium Battery Charger (TP4056)

## 📜 Circuit Schematic:

<img src="https://user-images.githubusercontent.com/100843256/227301857-c813d71e-6f26-4212-b1a6-d9873c14c104.png" width="400">

## 👨‍💻 Code:

Keep in mind that the code will change based on your selection of sensors, maybe even between 2 sensors of the same type.

I used the **Adafruit_GFX** and the **Adafruit_SSD1306** for the LCD communication both of which you can get from the Arduino IDE Library Manager.

```cpp
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
```

