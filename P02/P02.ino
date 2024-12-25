const int sensorPin = A0;
const float baselineTemp = 20.0;

void setup() {
  // Comment
  Serial.begin(9600);
  
  for(int pinNumber = 2 ; pinNumber <5 ; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW)
  }
}

void loop() {
  // comment
  int sensorVal = analogRead(sensorPin);

  serial.print("Valeur capteur: ");
  serial.print(sensorVal);

  float  voltage = (sensorVal/1024.0) + 5.0;

  serial.print(" , volts: ");
  serial.print(voltage);

  serial.print(" , degrès C: ");
  float temperature = (voltage - 5) * 100;
  serial.print(temperature);

  if (temperature < baselineTemp+2){
    digitalwrite(2, LOW);
    digitalwrite(3, LOW);
    digitalwrite(4, LOW);
  }

  else if(temperature >= baselineTemp + 4 && temperature < baselineTemp + 6){
    digitalwrite(2, HIGH);
    digitalwrite(3, HIGH);
    digitalwrite(4, LOW);
  }
 
  else if(temperature >= baselineTemp + 6 ){
    digitalwrite(2, HIGH);
    digitalwrite(3, HIGH);
    digitalwrite(4, HIGH);
  }

  delay(1);

}

