#include <NanitLib.h>
#include <DHT.h>

DHT dht (P5_3, DHT11);

byte redLed = P4_3;
byte greenLed = P4_4;
byte pirSensor = P5_1;
byte gasSensor = P5_2;
byte temperatureHumiditySensor = P5_3;

int gasValue;
float humidityValue;
float temperatureValue;

void setup() {
  Nanit_Base_Start();
  dht.begin();
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  gasValue = analogRead(gasSensor);
  humidityValue = dht.readHumidity();
  temperatureValue = dht.readTemperature();
  Serial.println();
  attachInterrupt(digitalPinToInterrupt(pirSensor), printValues, RISING);
}

void loop() {
  gasValue = analogRead(gasSensor);
  humidityValue = dht.readHumidity();
  temperatureValue = dht.readTemperature();

  if (gasValue <= 400 && humidityValue >= 30 && humidityValue <= 60
    && temperatureValue >= 15 && temperatureValue <= 30) {
    
    isDanger(false);

  } else {
    
    isDanger(true);

  }
}

void printValues(){
  Serial.println("Gas: " + String(gasValue));
  Serial.println("Humidity: " + String(humidityValue));
  Serial.println("Temperature: " + String(temperatureValue));
}

void isDanger(bool value){
  digitalWrite(redLed, value);
  digitalWrite(greenLed, !value);
}