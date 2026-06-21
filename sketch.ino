#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE-ID"
#define BLYNK_TEMPLATE_NAME "TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR-AUTH-TOKEN"

//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <BlynkSimpleEsp32.h>

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// ---------------- PIN DEFINITIONS ----------------
#define PIR_PIN 13
#define DHT_PIN 15
#define LDR_PIN 34
#define LED_PIN 2
#define SERVO_PIN 4

// ---------------- SENSOR SETUP ----------------
#define DHTTYPE DHT22
DHT dht(DHT_PIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo fanServo;

// ---------------- VARIABLES ----------------
int motionDetected;
int lightValue;
float temperature;
float humidity;

void setup() {

  Serial.begin(115200);

  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // PIR
  pinMode(PIR_PIN, INPUT);

  // LED
  pinMode(LED_PIN, OUTPUT);

  // DHT
  dht.begin();

  // LCD
  lcd.init();
  lcd.backlight();

  // Servo
  fanServo.attach(SERVO_PIN);

  lcd.setCursor(0, 0);
  lcd.print("SMART ROOM");

  lcd.setCursor(0, 1);
  lcd.print("Initializing");

  delay(2000);
  lcd.clear();

}

void loop() {

  //Blynk.run();

  // -------- READ SENSORS --------
  motionDetected = digitalRead(PIR_PIN);

  lightValue = analogRead(LDR_PIN);

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // -------- LIGHT CONTROL --------
  // Dark room + person detected

  if (motionDetected == HIGH && lightValue > 2000) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }

  // -------- FAN CONTROL --------

  if (temperature > 32) {
    fanServo.write(180); // High speed
  }
  else if (temperature > 27) {
    fanServo.write(90); // Medium speed
  }
  else {
    fanServo.write(0); // OFF
  }

  // -------- LCD DISPLAY --------

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C ");

  lcd.print("H:");
  lcd.print(humidity);

  lcd.setCursor(0, 1);

  if (motionDetected == HIGH) {
    lcd.print("Person Detected");
  }
  else {
    lcd.print("Room Empty");
  }

  // -------- SERIAL MONITOR --------

  Serial.print("Temp: ");
  Serial.print(temperature);

  Serial.print("  Humidity: ");
  Serial.print(humidity);

  Serial.print("  Light: ");
  Serial.print(lightValue);

  Serial.print("  Motion: ");
  Serial.println(motionDetected);


  //Blynk.virtualWrite(V0, temperature);
  //Blynk.virtualWrite(V1, humidity);
  //Blynk.virtualWrite(V2, motionDetected);
  //Blynk.virtualWrite(V3, lightValue);
  //Blynk.virtualWrite(V4, fanServo.read());

  delay(1000);
}