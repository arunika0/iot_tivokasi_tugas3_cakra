#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Sensor and LCD definitions
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Adjusted I2C address to default
#define DHTPIN 27
#define DHTTYPE DHT22
#define LDR_PIN 32

DHT dht(DHTPIN, DHTTYPE);

String getLightDescription(int lux) {
  if (lux < 500) return "Dark    ";
  else if (lux < 1500) return "Medium  ";
  else if (lux < 2500) return "Bright  ";
  else return "V.Bright";
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int lightValue = analogRead(LDR_PIN);
  int lightPercent = map(lightValue, 0, 4095, 0, 100);

  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    return;
  }

  // Temperature and Humidity
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print("C ");
  lcd.print("Hum:");
  lcd.print(humidity, 0);
  lcd.print("%");

  // Light value and description
  lcd.setCursor(0, 2);
  lcd.print("Light: ");
  lcd.print(lightPercent);
  lcd.print("% ");
  
  lcd.setCursor(0, 3);
  lcd.print("Status: ");
  lcd.print(getLightDescription(lightValue));

  delay(1000);
}