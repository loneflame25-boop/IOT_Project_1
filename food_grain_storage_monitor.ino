#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define GREEN_LED 8
#define RED_LED 9

DHT dht(DHTPIN, DHTTYPE);

float temp_low;
float temp_high;
float humidity_low;
float humidity_high;

void setup() {
  Serial.begin(9600);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  dht.begin();

  Serial.println("Food Grain Storage Monitor");

  Serial.println("Enter temperature LOW value:");
  while (Serial.available() == 0);
  temp_low = Serial.parseFloat();

  Serial.println("Enter temperature HIGH value:");
  while (Serial.available() == 0);
  temp_high = Serial.parseFloat();

  Serial.println("Enter humidity LOW value:");
  while (Serial.available() == 0);
  humidity_low = Serial.parseFloat();

  Serial.println("Enter humidity HIGH value:");
  while (Serial.available() == 0);
  humidity_high = Serial.parseFloat();

  Serial.println("Settings saved.");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error reading DHT11!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | ");

  if ((temperature >= temp_low && temperature <= temp_high) &&
      (humidity >= humidity_low && humidity <= humidity_high)) {

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    Serial.println("STATUS: SAFE");
  }
  else {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    Serial.println("STATUS: WARNING");
  }

  delay(2000);
}
