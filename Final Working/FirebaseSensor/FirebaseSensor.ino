#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "DVT-JHB"   //"VodafoneMobileWiFi-467D"
#define WIFI_PASSWORD "BullHornBitesOnce"   //"voIK3ik3"
#define FIREBASE_HOST "parkit-6cd47.firebaseio.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "dBxRigeLzfQULWmjHg65heoGsXe7Rp7tuC5dIhSx"

//Define FirebaseESP32 data object
FirebaseData firebaseData;

FirebaseJson json;

const int triggerPinParkingG0 = 13;
const int echoPinParkingG0 = 12;

const int triggerPinParkingG1 = 33;
const int echoPinParkingG1 = 32;

const int triggerPinParkingG2 = 26;
const int echoPinParkingG2 = 25;

const int triggerPinParkingG3 = 27;
const int echoPinParkingG3 = 14;

const int triggerPinParkingG4 = 13;
const int echoPinParkingG4 = 12;

const int triggerPinParkingF0 = 15;
const int echoPinParkingF0 = 0;

const int triggerPinParkingF1 = 4;
const int echoPinParkingF1 = 2;

const int triggerPinParkingF2 = 18;
const int echoPinParkingF2 = 5;

const int triggerPinParkingF3 = 21;
const int echoPinParkingF3 = 19;

const int triggerPinParkingF4 = 23;
const int echoPinParkingF4 = 22;

int duration = 0;
int distance = 0;
int readDataTime = 50;
int updateDatabaseTime = 3000;

String path = "Error";
int state = 0;

String dbGroundLevelPaths [5] = {
  "/Parking/Level0/L0:P1:N",
  "/Parking/Level0/L0:P2:N",
  "/Parking/Level0/L0:P3:N",
  "/Parking/Level0/L0:P4:N",
  "/Parking/Level0/L0:P5:D"
  };

String dbFirstLevelPaths [5] = {
  "/Parking/Level1/L1:P1:N",
  "/Parking/Level1/L1:P2:F",
  "/Parking/Level1/L1:P3:N",
  "/Parking/Level1/L1:P4:N",
  "/Parking/Level1/L1:P5:N"
};

const int sensorsPerLevel = 5;

int groundLevelParkingDistances[sensorsPerLevel]  = {
  0,0,0,0,0
};

int firstLevelParkingDistances[sensorsPerLevel]  = {
  0,0,0,0,0
};

int groundLevelParkingStates[sensorsPerLevel] = {
  0,0,0,0,0
};

int firstLevelParkingStates [sensorsPerLevel] = {
  0,0,0,0,0
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(triggerPinParkingG0, OUTPUT);
  pinMode(echoPinParkingG0, INPUT);
  pinMode(triggerPinParkingG1, OUTPUT);
  pinMode(echoPinParkingG1, INPUT);

  pinMode(triggerPinParkingG2, OUTPUT);
  pinMode(echoPinParkingG2, INPUT);
  pinMode(triggerPinParkingG3, OUTPUT);
  pinMode(echoPinParkingG3, INPUT);

  pinMode(triggerPinParkingF0, OUTPUT);
  pinMode(echoPinParkingF0, INPUT);
  pinMode(triggerPinParkingF1, OUTPUT);
  pinMode(echoPinParkingF1, INPUT);

  pinMode(triggerPinParkingF2, OUTPUT);
  pinMode(echoPinParkingF2, INPUT);
  pinMode(triggerPinParkingF3, OUTPUT);
  pinMode(echoPinParkingF3, INPUT);

  pinMode(triggerPinParkingF4, OUTPUT);
  pinMode(echoPinParkingF4, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print("G0: ");
//  Serial.print(readDistanceFromUSensor(triggerPinParkingG0, echoPinParkingG0));
//  Serial.println("cm");
//  Serial.println();
  Serial.print("G0: ");
  Serial.print(readDistanceFromUSensor(triggerPinParkingG0, echoPinParkingG0));
  groundLevelParkingDistances[0] = readDistanceFromUSensor(triggerPinParkingG0, echoPinParkingG0);
  delay(readDataTime);
  Serial.print("   G1:");
  Serial.print(readDistanceFromUSensor(triggerPinParkingG1, echoPinParkingG1));
  groundLevelParkingDistances[1] = readDistanceFromUSensor(triggerPinParkingG1, echoPinParkingG1);
  delay(readDataTime);
  Serial.print("   G2:");
  Serial.print(readDistanceFromUSensor(triggerPinParkingG2, echoPinParkingG2));
  groundLevelParkingDistances[2] = readDistanceFromUSensor(triggerPinParkingG2, echoPinParkingG2);
  delay(readDataTime);
  Serial.print("   G3:");
  Serial.print(readDistanceFromUSensor(triggerPinParkingG3, echoPinParkingG3));
  groundLevelParkingDistances[3] = readDistanceFromUSensor(triggerPinParkingG3, echoPinParkingG3);
  delay(readDataTime);
  Serial.print("   F1:");
  Serial.print(readDistanceFromUSensor(triggerPinParkingF0, echoPinParkingF0));
  firstLevelParkingDistances[0] = readDistanceFromUSensor(triggerPinParkingF0, echoPinParkingF0);
  delay(readDataTime);
  Serial.print("   F2:");
  Serial.print(readDistanceFromUSensor(triggerPinParkingF1, echoPinParkingF1));
  firstLevelParkingDistances[0] = readDistanceFromUSensor(triggerPinParkingF1, echoPinParkingF1);
  delay(readDataTime);
  Serial.print("   F3:");
  Serial.print(readDistanceFromUSensor(triggerPinParkingF2, echoPinParkingF2));
  firstLevelParkingDistances[0] = readDistanceFromUSensor(triggerPinParkingF2, echoPinParkingF2);
  delay(readDataTime);
  Serial.print("   F4:");
  Serial.print(readDistanceFromUSensor(triggerPinParkingF3, echoPinParkingF3));
  firstLevelParkingDistances[0] = readDistanceFromUSensor(triggerPinParkingF3, echoPinParkingF3);
  delay(readDataTime);
  Serial.print("   F5:");
  Serial.print(readDistanceFromUSensor(triggerPinParkingF4, echoPinParkingF4));
  firstLevelParkingDistances[0] = readDistanceFromUSensor(triggerPinParkingF4, echoPinParkingF4);
  delay(readDataTime);
  Serial.println("cm");

  //Calculate parking states
  for (uint8_t i = 0; i < sensorsPerLevel; i++) {
    if (groundLevelParkingDistances[i] < 5) {
      groundLevelParkingStates[i] = 0;
    } else {
      groundLevelParkingStates[i] = 1;
    }

    if (firstLevelParkingDistances[i] < 5) {
      firstLevelParkingStates[i] = 0;
    } else {
      firstLevelParkingStates[i] = 1;
    }
  }
  
  //Write States Array to Firebase
  for (uint8_t i = 0; i < sensorsPerLevel; i++) {
    Serial.print("GroundLevel: ");
    Serial.println(groundLevelParkingStates[i]);
    Serial.print("FirstLevel: ");
    Serial.println(firstLevelParkingStates[i]);
    path = dbGroundLevelPaths[i];
    state = groundLevelParkingStates[i];
    if (Firebase.setDouble(firebaseData, path, state)) {
      Serial.println("PASSED TO PATH:");
      Serial.println(path);
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
    path = dbFirstLevelPaths[i];
    state = firstLevelParkingStates[i];
    if (Firebase.setDouble(firebaseData, path, state)) {
      Serial.println("PASSED TO PATH:");
      Serial.println(path);
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }
}

float readDistanceFromUSensor(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  delayMicroseconds(10);
  
  distance = ((duration / 2) / 29.1);
  return distance;
}
