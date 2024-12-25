const int greenLEDPin = 9;
const int redLEDPin = 10;
const int blueLEDPin = 11;

const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup(){
  // Comment
  Serial.begin(9600);
  
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop(){
  
  // Les valeurs brutes ont une valeur entre 0 et 1023
  redSensorValue = analogRead(redSensorPin);
  delay(5);
  greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  blueSensorValue = analogRead(blueSensorPin);
  delay(5);

  Serial.print("Valeur brutes \t rouge: ");
  Serial.print(redSensorValue);
  Serial.print("\t vert: ");
  Serial.print(greenSensorValue);
  Serial.print("\t bleu: ");
  Serial.print(blueSensorValue);

  // Les valeurs recalculées doivent avoir une valeur entre 0 et 254
  redValue = redSensorValue / 4;
  greenValue = greenSensorValue / 4;
  blueValue = blueSensorValue / 4;

  // Définition manuelle
  //redValue = 0;
  //greenValue = 253;
  //blueValue = 0;

  Serial.print(" | Valeurs recalculées \t rouge: ");
  Serial.print(redValue);
  Serial.print("\t vert: ");
  Serial.print(greenValue);
  Serial.print("\t bleu: ");
  Serial.print(blueValue);

  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);

  Serial.println();
  delay(1000);

}

