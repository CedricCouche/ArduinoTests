// Librairies import
#include <DHT.h>

// Variables
#define DHTPin 5
#define DHTType DHT22 

const int soilHumidityPin = A0;
int soilHumidityValue = 0;
float RelativeHumidity = 0.0;
float TempCelsius = 0.0;

// DHT-22  initialization
DHT dht(DHTPin, DHTType);

// Pin Setup
void setup () {
  
  Serial.begin(9600);
  Serial.println("Start of the program");
  Serial.println("==========================");
  Serial.println();

  // Initialization of DHT22;
  dht.begin();

  pinMode(soilHumidityPin, INPUT);

}
 
// Min Loop
void loop () {
  //delay(1000);
  
  // Getting data
  soilHumidityValue = analogRead(soilHumidityPin); // Get soil humidity sensor value
  RelativeHumidity = dht.readHumidity();     // Get Humidity value in % 
  TempCelsius = dht.readTemperature();      // Get temperature in Celsius degree

  // Check if data are received
  if (isnan(RelativeHumidity) || isnan(TempCelsius)) {
    Serial.println("No data received from DHT22, please check wiring");
    delay(2000);
    return;         // If no data are received, we wait for 2 seconds, then the loop restard
  }

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
  Serial.println();

  // Delay of 2 second, to match minimum delay reading of DHT22
  delay(2000);
}

