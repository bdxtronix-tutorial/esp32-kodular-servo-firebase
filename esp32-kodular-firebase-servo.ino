#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Servo.h>

// Your WiFi credentials
#define WIFI_SSID "Nama WiFI Anda"
#define WIFI_PASSWORD "Password WiFi Anda"

// Your Firebase project credentials
#define FIREBASE_HOST "URL Firebase Anda"
#define FIREBASE_AUTH "Database Secret Anda"
FirebaseData firebaseData;

Servo servoMotor;

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  // Attach the servo motor to pin 13
  static const int servoPin = 13;
  servoMotor.attach(servoPin);
  }

void loop() {
  // Read the gyroscope x-axis data from Firebase
  if (Firebase.getFloat(firebaseData, "gyroscopeX")) {
    float gyroX = firebaseData.floatData();
    
    // Decide servo position based on gyroscope data
    int servoAngle;
    if (gyroX < 0) {  // Phone pusing ke kiri
      servoAngle = 0; // Servo pusing ke kiri
    } else {         // Phone pusing ke kanan
      servoAngle = 180; // Servo pusing ke kanan
    }

    // Move the servo
    servoMotor.write(servoAngle);
  } else {
    Serial.println(firebaseData.errorReason());
  }
  delay(100); // Adjust delay mengikut kesesuaian
}
