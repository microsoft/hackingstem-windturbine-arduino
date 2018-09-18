float reading;
float motor = 0.0000;
float current = 0.0000;

const String DELIMETER = ",";

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop() {
  for (int i=0;i<99;i++){
    reading = analogRead (0);
    if (reading > motor){motor = reading;}
    delay (1);
  }
  reading = analogRead (1);
  current = reading/1024;
  current = current / 100;
  current = current * 1100;
  motor = motor/1024 * 1100;
  Serial.print (motor, 4);
  Serial.print (",");
  Serial.print (current, 4);
  Serial.print ('\n');
  motor = 0;
  delay (10);
}

void readVoltage(){
  motor = 0;
  for (int i=0;i<99;i++){
    reading = analogRead (0);
    if (reading > motor){motor = reading;}
    delay (1);
  }
}

void sendDataToSerial(){
  Serial.print (motor, 4);
  Serial.print (DELIMETER);
  Serial.print (current, 4);
  Serial.print ('\n');
}

