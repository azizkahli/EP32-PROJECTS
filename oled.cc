
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE,0);
  display.setCursor(35,10);
  display.print("ESP32");
  display.setCursor(25,40);
  display.print("MPU6050");
  display.display();

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(1000);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE,0);
  display.setCursor(0,0);
  display.println("Acelerometro:");
  display.print(a.acceleration.x);
  display.print(",");
  display.print(a.acceleration.y);
  display.print(",");
  display.println(a.acceleration.z);
  display.println("");

  display.println("Giroscopio:");
  display.print(g.gyro.x);
  display.print(",");
  display.print(g.gyro.y);
  display.print(",");
  display.print(g.gyro.z);
  display.display();

  delay(10);
}