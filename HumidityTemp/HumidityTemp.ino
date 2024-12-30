// Librairies import
#include <DHT.h>

// Variables
#define DHTPin 5
#define DHTType DHT22 
#define relayHeater 3
#define relayFan 4
#define relayWaterPump 6
#define relayLight 7

const int soilHumidityPin = A0;
int soilHumidityValue = 0;
float RelativeHumidity = 0.0;
float TempCelsius = 0.0;
int light_sensor = A3; 


// DHT-22  initialization
DHT dht(DHTPin, DHTType);

// Pin Setup
void setup () {
  
  Serial.begin(9600);
  Serial.println();
  Serial.println("==========================");
  Serial.println("Start of the program");
  Serial.println("Version 03 ");
  Serial.println("==========================");
  Serial.println();

  // Initialization of DHT22;
  dht.begin();

  pinMode(soilHumidityPin, INPUT);

  // Relay Pin setup
  digitalWrite(relayHeater, HIGH); // Relay config : Normally Closed
  digitalWrite(relayFan, HIGH);    // Relay config : Normally Closed
  digitalWrite(relayWaterPump, HIGH); // Relay config : Normally Closed
  digitalWrite(relayLight, HIGH); // Relay config : Normally OPEN
  pinMode(relayHeater, OUTPUT);
  pinMode(relayFan, OUTPUT);
  pinMode(relayWaterPump, OUTPUT);
  pinMode(relayLight, OUTPUT);

}
 
// Min Loop
void loop () {

  // Getting data
  soilHumidityValue = analogRead(soilHumidityPin); // Get soil humidity sensor value
  int raw_lightValue = analogRead(light_sensor); // Get light sensor value
  RelativeHumidity = dht.readHumidity();     // Get Humidity value in % 
  TempCelsius = dht.readTemperature();      // Get temperature in Celsius degree
  

  // Check if data are received
  if (isnan(RelativeHumidity) || isnan(TempCelsius)) {
    Serial.println("No data received from DHT22, please check wiring");
    delay(2000);
    return;         // If no data are received, we wait for 2 seconds, then the loop restard
  }

  // Map of  light value
  int lightValue = map(raw_lightValue, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100

  // Conversion to felt temperature
  float feltTempCelsius = dht.computeHeatIndex(TempCelsius, RelativeHumidity, false); // Le "false" est là pour dire qu'on travaille en °C, et non en °F
  
  // Soil humidity values
  //soilHumidityValue = constraint(soilHumidityValue, 0, 1023); // Keep values within a range
  soilHumidityValue = map(soilHumidityValue, 0, 1023, 100, 0); // Mapping of values


  // Display of values
  Serial.print("Relative Humidity = "); Serial.print(RelativeHumidity); Serial.println(" %");
  Serial.print("Temperature = "); Serial.print(TempCelsius); Serial.println(" °C");
  Serial.print("Felt temperature = "); Serial.print(feltTempCelsius); Serial.println(" °C");
  Serial.print("Soil humidity = "); Serial.print(soilHumidityValue); Serial.println(" %");
  Serial.print("Light = "); Serial.print(lightValue); Serial.println(" %");
  Serial.println();

  // Relay action
  if (TempCelsius < 15.0) {
    Serial.print("Action on Heater : Start");  
    digitalWrite(relayHeater, HIGH);
    delay(2000);
    digitalWrite(relayHeater, LOW);
    delay(2000);
    } 
    else {Serial.print("Action on Heater : Not required");};

  if (RelativeHumidity < 40.0) {
    Serial.print("Action on Fan : Start");  
    digitalWrite(relayFan, HIGH);
    delay(2000);
    digitalWrite(relayFan, LOW);
    delay(2000);
    } 
    else {Serial.print("Action on Fan : Not required");};

   if (soilHumidityValue < 40.0) {
    Serial.print("Action on Water Pump : Start");  
    digitalWrite(relayWaterPump, HIGH);
    delay(2000);
    digitalWrite(relayWaterPump, LOW);
    delay(2000);
    } 
    else {Serial.print("Action on WaterPump : Not required");};

   if (lightValue > 50) {
    Serial.print("Action on Light : switch off light");  
    digitalWrite(relayLight, HIGH);
    delay(2000);
    digitalWrite(relayLight, LOW);
    delay(2000);
    } 
    else {Serial.print("Action on Light : keep light on");};


  // Delay of 2 second, to match minimum delay reading of DHT22
  delay(2000);
  Serial.print("End of Process");
  Serial.println();
}