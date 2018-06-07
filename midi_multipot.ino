#include <MIDIUSB.h>

const int buttonPin = 2;
const int sensorPin = A0;
const int p2Pin = A1;

int buttonState = 0;
int sensorValue = 0;
int sensor2Value = 0;
int sensor3Value = 0;

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  //SerialUSB.print("Channel: ");
  //SerialUSB.print(channel);
  //SerialUSB.print("Control: ");
  //SerialUSB.print(control);
  //SerialUSB.print("Value: ");
  //SerialUSB.println(value);
  MidiUSB.sendMIDI(event);
}

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  delay(100);
  if (buttonState == HIGH) {
    //SerialUSB.println("Sending note on");
    noteOn(0, 48, 64);   // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    //SerialUSB.println("Sending note off");
    noteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
    MidiUSB.flush();
    //delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }
  int newValue = 0;
  newValue = analogRead(sensorPin);
  if (newValue != sensorValue) {
    sensorValue = newValue;
    SerialUSB.println("Sending control change");
    byte byteValue = map(sensorValue, 0, 1023, 0, 255);
    controlChange(1, 16, byteValue);
    SerialUSB.print("New value:");
    SerialUSB.println(byteValue);
    SerialUSB.print("sensor: ");
    SerialUSB.println(sensorValue);
  }
  int p2Value = 0;
  p2Value = analogRead(p2Pin);
  if (p2Value != sensor2Value) {
    sensor2Value = p2Value;
    byte byteValue = map(sensor2Value, 0, 1023, 0, 255);
    controlChange(1, 10, byteValue);
    SerialUSB.print("P2 value: ");
    SerialUSB.println(byteValue);
  }
  int p3Value = 0;
  p3Value = analogRead(A2);
  if (p3Value != sensor3Value) {
    sensor3Value = p3Value;
    byte byteValue = map(sensor3Value, 0, 1023, 0, 255);
    controlChange(1, 12, byteValue);
    SerialUSB.print("P3 value: ");
    SerialUSB.println(byteValue);
  }
}
