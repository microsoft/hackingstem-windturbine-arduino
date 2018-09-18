//===------------__ Hacking STEM – Windmill.X.X.X.ino – Arduino __---------===//
// For use with the "WIND TURBINE Increasing Power Through
// Design" lesson plan available from Microsoft Education Workshop at
// http://aka.ms/hackingSTEM
//
// Overview:
// Measures voltage produced by a "generator" hooked up to analog pins 0 and 1.
// The generator is just a little electic motor that makes electricity when you
// turn it by hand or by wind power!
//
// Each reading is printed to serial as "voltage,amperage" for example:
// 1.1231,0.5101
//
// This project uses an Arduino UNO microcontroller board, information at:
// https://www.arduino.cc/en/main/arduinoBoardUno
//
// Comments, contributions, suggestions, bug reports, and feature requests
// are welcome! For source code and bug reports see:
// http://github.com/[TODO github path to Hacking STEM]
//
// Copyright [year], [your name] Microsoft EDU Workshop - HackingSTEM
// MIT License terms detailed in LICENSE.md
//===----------------------------------------------------------------------===//

// Initialize variables used reading and calculating generator output
float motor = 0.0000;   // output of motor voltage
float current = 0.0000; // output of currentTime

// 'reading' is a variable we use to store readings. One confusing thing is
// that this variable is reused to read from pins 1 and 0 at different points.
float reading;

void setup() {
  Serial.begin(9600);
  // When arduino reads from analog pins, it uses a specific known internal
  // voltage reference which is equal to exactle 1100 millivolts to compare against
  analogReference(INTERNAL);
}

void loop() {
  motor = 0; // Each time the loop repeats, voltage reading is reset to 0

  // Take 100 voltage readings and keep the highest as "motor" variable
  for (int i=0;i<99;i++){
    reading = analogRead (0);
    if (reading > motor){ motor = reading;}
    delay (1);
  }
  // Ohms law: Amperage = Voltage / Resistance
  // Using ohms law, we can take a reading of voltage and then
  // divide it by our 100ohm resistor value.
  //
  // Taking a voltage read is a little messy, it entails taking the
  // value read via analogRead(1) and adjusting it by the resolution of
  // analogRead and using the known reference voltage to math out the
  // actual voltage.
  reading = analogRead (1); // Motor outputs through 100 ohm resistor to pin 1.
  // Divide by the 1024 step resolution of analogRead
  current = reading / 1024;
  // Multiple by reference voltage of 1100 millivolts (1.1 volts) to
  // get the actual voltage!
  current = current * 1100;
  // Divide the voltage by the 100 ohm resistor value and we get the amperage!
  current = current / 100;

  // Similiar to above, we're finding the voltage, only this time we're using
  // a value from a pin that doesn't have a resistor across it.
  // Take the input reading, divide by the 1024 resolution of analogRead(), and
  // then multiple by our reference voltage (1100 millivolts)
  motor = motor/1024 * 1100;

  // Print the information to SERIAL
  Serial.print (motor, 4);   // Print voltage to 4 decimal places
  Serial.print (",");        // Print a commas
  Serial.print (current, 4); // Print amperage to 4 decimal places
  Serial.print ('\n');       // Print newline character to end the line

  delay (10);  // delay 10 milliseconds before taking another reading
}
