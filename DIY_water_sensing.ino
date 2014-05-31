/*
Antonio

Water Conductivity Monitor
Sketch for an Arduino gadget that measures the electrical
conductivity of water.
This example code is based on example code that is in the public domain.
*/

/* Important !!*/
int testMode = 0; // change this to 1 when you are ready to collect data

const float ArduinoVoltage = 5.00; // CHANGE THIS FOR 3.3v Arduinos
const float ArduinoResolution = ArduinoVoltage / 1024;
const float resistorValue = 10000.0; // 10K ohoms
int threshold = 3;
int inputPin = A0;
int ouputPin = A5;

// setup function
void setup()
{
  Serial.begin(9600);
  pinMode(ouputPin, OUTPUT);
  pinMode(inputPin, INPUT);
//  println("volts,ohms,microSiemens,TDS")
}

// loop function
void loop()
{
  int analogValue=0;
  int oldAnalogValue=1000;
  float returnVoltage=0.0;
  float resistance=0.0;
  double Siemens;
  float TDS=0.0;
  while(((oldAnalogValue-analogValue)>threshold) || (oldAnalogValue<50))
  {
    oldAnalogValue = analogValue;
    digitalWrite( ouputPin, HIGH );
    delay(10); // allow ringing to stop
    analogValue = analogRead( inputPin );
    digitalWrite( ouputPin, LOW );
    //Serial.print(returnVoltage);
  }
  //  Serial.print("Return voltage = ");
  returnVoltage = analogValue *ArduinoResolution;
  Serial.print(returnVoltage);
  Serial.print(",");
  //  Serial.println(" volts");
  //  Serial.print("That works out to a resistance (Ohms)of ");

  resistance = ((5.00 * resistorValue) / returnVoltage) - resistorValue;
  Serial.print(resistance);
  Serial.print(",");
//  Serial.println(" Ohms.");

//  Serial.print("Which works out to a conductivity of ");
  Siemens = 1.0/(resistance/1000000);
  Serial.print(Siemens);
  Serial.print(",");
  //  Serial.println(" microSiemens.");

  //  Serial.print("Total Dissolved Solids are on the order of ");
  TDS = 500 * (Siemens/1000);
  Serial.print(TDS);
  //  Serial.println(" PPM.");
  
  
  if(testMode==0){
    Serial.println(""); // add a new line so we can better see the incoming data
  } else {
    Serial.print("@@"); // add a separator to the reading for easy parsing
  }
  
/*
  if (returnVoltage>4.9) {
    Serial.println("Are you sure this isn't metal?");
  }
*/
  delay(1000); // wait for 1 sec before getting a new reading
}
