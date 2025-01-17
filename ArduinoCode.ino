#include <Servo.h>
// Pin definitio
const int enaA = 5; // Motor A PWM
const int enB = 6; // Motor B PWM
const int in1 = 8; // Motor A direction
const int in2 = 9;
const int in3 = 10; // Motor B direction
const int in4 = 11;
const int LeftIR = A0; // Left IR sensor
const int RightIR = A1; // Right IR sensor
const int moisture = A2; // Moisture sensor
const int pump = 12; // Pump motor
const int servoPin = 4; // Servo motor
const int trigPin = 3; // Ultrasonic trigger pin
const int echoPin = 2; // Ultrasonic echo pin
Servo servoMotor;
// Variables for timing
unsigned long previousMillis = 0;
const unsigned long interval = 10000; // 10 seconds
void setup() {
// Set motor pins as output
pinMode(enaA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
// Set sensor and pump pins
pinMode(LeftIR, INPUT);
pinMode(RightIR, INPUT);
pinMode(moisture, INPUT);
pinMode(pump, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
// Attach and initialize servo motor
servoMotor.attach(servoPin);
servoMotor.write(0); // Arm up position
// Stop motors and pump initially
digitalWrite(pump, LOW);
stopMotors();
Serial.begin(9600); // For debugging
}
void loop() {
// Check for obstacle
if (detectObstacle()) {
stopMotors();
Serial.println("Obstacle detected! Stopping motors.");
return; // Skip the rest of the loop if obstacle detected
}
// Line following logic
int leftIRValue = analogRead(LeftIR);
int rightIRValue = analogRead(RightIR);
if (leftIRValue < 500 && rightIRValue < 500) {
// Both sensors on the black line
moveForward();
} else if (leftIRValue < 500) {
// Left sensor on the black line
turnLeft();
} else if (rightIRValue < 500) {
// Right sensor on the black line
turnRight();
} else {
// Both sensors off the black line
stopMotors();
}
// Moisture check logic
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
previousMillis = currentMillis;
// Stop motors
stopMotors();
// Lower the servo arm
Serial.println("Lowering servo arm to check moisture...");
servoMotor.write(90); // Arm down position
delay(1000); // Wait for servo to move
int moistureValue = analogRead(moisture);
Serial.print("Moisture Value: ");
Serial.println(moistureValue);
if (moistureValue < 987) { // Adjust threshold as needed
Serial.println("Moisture not detected! Starting pump...");
digitalWrite(pump, HIGH);
delay(3000); // Run pump for 3 seconds
digitalWrite(pump, LOW);
} else {
Serial.println("Moisture detected.");
}
// Raise the servo arm
Serial.println("Raising servo arm...");
servoMotor.write(0); // Arm up position
delay(1000); // Wait for servo to move
}
}
// Function to detect obstacle
bool detectObstacle() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
long duration = pulseIn(echoPin, HIGH);
float distance = duration * 0.034 / 2; // Calculate distance in 
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");
if (distance > 0 && distance <= 15) { // Adjust threshold as needed (15 cm ≈ 6 inches)
return true; // Obstacle detected
}
return false; // No obstacle
}
// Function to move forward
void moveForward() {
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enaA, 200); // Adjust speed as needed
analogWrite(enB, 200);
}
// Function to turn left
void turnLeft() {
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enaA, 150); // Adjust speed as needed
analogWrite(enB, 150);
}
// Function to turn right
void turnRight() {
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enaA, 150); // Adjust speed as needed
analogWrite(enB, 150);
}
// Function to stop motors
void stopMotors() {
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
analogWrite(enaA, 0);
analogWrite(enB, 0);
}
