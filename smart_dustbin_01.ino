#include <Servo.h> // Includes the Servo library

Servo servo;
int trig = 5;      // Pin for triggering the ultrasonic sensor
int echo = 6;      // Pin for receiving the echo signal
int servoPin = 9;  // Pin to control the servo motor
int buzzerPin = 7; // Pin to control the buzzer
long Duration, Distance, Average;
long aver[3];      // Array to store distance readings for averaging

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzerPin, OUTPUT); // Sets the buzzer pin as an output
  servo.write(0);           // Initializes with the lid closed
  delay(100);
  servo.detach();           // Detaches servo to save power and avoid jitter
}

void measure() {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig, LOW);
  Duration = pulseIn(echo, HIGH);  // Measures the time taken by the echo
  Distance = (Duration / 2) / 29.1; // Converts time to distance in centimeters
}

void loop() {
  for (int i = 0; i <= 2; i++) {
    measure();
    aver[i] = Distance;      // Store each reading for averaging
    delay(10);
  }
  
  Distance = (aver[0] + aver[1] + aver[2]) / 3; // Calculate average distance

  if (Distance <= 20) {
    servo.attach(servoPin);
    digitalWrite(buzzerPin, HIGH); // Turns the buzzer ON when the lid is about to open
    servo.write(0);           // Opens the lid
    delay(3500);              // Keeps the lid open for 3.5 seconds
    servo.write(180);           // Closes the lid
    delay(1500);
    digitalWrite(buzzerPin, LOW);  // Turns the buzzer OFF after the lid is closed
    servo.detach();           // Detach to save power
  }
}