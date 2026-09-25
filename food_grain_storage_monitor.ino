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

  Serial.println("================================");
  Serial.println(" Food Grain Storage Monitor");
  Serial.println("================================");

  Serial.println("Select Grain:");
  Serial.println("1. Rice");
  Serial.println("2. Maize");
  Serial.println("3. Wheat");
  Serial.println("4. Custom");
  Serial.println("Enter your choice:");

  while (Serial.available() == 0);

  int choice = Serial.parseInt();

  if (choice == 1) {
    // Rice
    temp_low = 20;
    temp_high = 30;
    humidity_low = 50;
    humidity_high = 70;

    Serial.println("Grain selected: Rice");
  }

  else if (choice == 2) {
    // Maize
    temp_low = 15;
    temp_high = 25;
    humidity_low = 50;
    humidity_high = 60;

    Serial.println("Grain selected: Maize");
  }

  else if (choice == 3) {
    // Wheat
    temp_low = 15;
    temp_high = 25;
    humidity_low = 50;
    humidity_high = 65;

    Serial.println("Grain selected: Wheat");
  }

  else if (choice == 4) {
    Serial.println("Custom Settings");

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

    Serial.println("Custom settings saved.");
  }

  else {
    Serial.println("Invalid choice!");
    Serial.println("Restart the Arduino and try again.");

    while (true);
  }

  Serial.println("--------------------------------");
  Serial.print("Temperature Range: ");
  Serial.print(temp_low);
  Serial.print(" - ");
  Serial.print(temp_high);
  Serial.println(" C");

  Serial.print("Humidity Range: ");
  Serial.print(humidity_low);
  Serial.print(" - ");
  Serial.print(humidity_high);
  Serial.println(" %");

  Serial.println("--------------------------------");
  Serial.println("Monitoring started...");
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
