const int sensorPin = A0;
const float baselineTemp = 14.0;

void setup(){
  // Comment
  Serial.begin(9600);
  
  for(int pinNumber = 2 ; pinNumber <5 ; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop(){
  
  int sensorVal = analogRead(sensorPin);

  Serial.print("Valeur capteur: ");
  Serial.print(sensorVal);

  float  voltage = (sensorVal/1024.0) + 5.0;

  Serial.print(" , volts: ");
  Serial.print(voltage);

  Serial.print(" , degrès C: ");
  float temperature = (voltage - 5) * 100;
  Serial.print(temperature);

  if (temperature < baselineTemp){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }

  else if(temperature >= baselineTemp && temperature < baselineTemp + 1.0){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
 
  else if(temperature >= baselineTemp + 1.0 && temperature < baselineTemp + 1.5 ){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }

  else if(temperature >= baselineTemp + 1.5 ){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }

  Serial.println();
  delay(1000);

}

