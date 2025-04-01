#include <Servo.h>

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "Your_tempelat_ID"
#define BLYNK_TEMPLATE_NAME "Tempelate_name"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Blynk Auth Token
char auth[] = "Your_Auth_Token";

// WiFi credentials
char ssid[] = " ";
char pass[] = " ";

// Motor driver pins
const int ENA = 5;  // PWM pin for speed control
const int IN1 = 0;  // IN1 for Motor A
const int IN2 = 2;  // IN2 for Motor A

const int ENB = 4;  // PWM pin for speed control
const int IN3 = 14; // IN3 for Motor B
const int IN4 = 12; // IN4 for Motor B

// Servo pin
const int servoPin = 13;
Servo steeringServo;

// LED pins
const int indicatorLeft = 16;
const int indicatorRight = 15;
const int headlight = 3;

bool forward = 0;
bool backward = 0;
int Speed;

BLYNK_WRITE(V1) {  // Virtual pin V1 for motor speed and direction control
  Speed = param.asInt();
  
}

BLYNK_WRITE(V2) {  // Virtual pin V2 for steering control via potentiometer knob
  int angle = param.asInt();  // Read the value from the Blynk app knob
  steeringServo.write(angle);
}

// BLYNK_WRITE(V3) {  // Virtual pin V3 for left indicator
//   int state = param.asInt();
//   digitalWrite(indicatorLeft, state);
// }

// BLYNK_WRITE(V4) {  // Virtual pin V4 for right indicator
//   int state = param.asInt();
//   digitalWrite(indicatorRight, state);
// }

BLYNK_WRITE(V5) {  // Virtual pin V5 for headlight
  int state = param.asInt();
  digitalWrite(headlight, state);
}

BLYNK_WRITE(V3) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V4) {
  backward = param.asInt();
}

void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (forward == 0 && backward == 0) {
    carStop();
    Serial.println("carstop");
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Setup motor driver pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Setup servo
  steeringServo.attach(servoPin);

  // Setup LEDs
  pinMode(indicatorLeft, OUTPUT);
  pinMode(indicatorRight, OUTPUT);
  pinMode(headlight, OUTPUT);
}

void loop() {
  Blynk.run();
  smartcar();
}

void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}