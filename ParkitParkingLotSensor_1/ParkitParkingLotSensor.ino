#include <NewPing.h>

// ---------------------------------------------------------------------------
// Example NewPing library sketch that pings 3 sensors 20 times a second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define SONAR_NUM 5      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonarGroundLevel[SONAR_NUM] = {   // Sensor object array.
  NewPing(31, 30, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(33, 32, MAX_DISTANCE), 
  NewPing(35, 34, MAX_DISTANCE),
  NewPing(37, 36, MAX_DISTANCE),
  NewPing(39, 38, MAX_DISTANCE)
};

NewPing sonarFirstLevel[SONAR_NUM] = {   // Sensor object array.
  NewPing(40, 41, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(42, 43, MAX_DISTANCE), 
  NewPing(44, 45, MAX_DISTANCE),
  NewPing(46, 47, MAX_DISTANCE),
  NewPing(48, 49, MAX_DISTANCE)
};

int groundLevelParkingSpacesStates[SONAR_NUM] = {
  0,0,0,0,0
};

int firstLevelParkingSpacesStates[SONAR_NUM] = {
  0,0,0,0,0
};

int groundLevelDistance[SONAR_NUM] = {
  0,0,0,0,0
};

int firstLevelDistance[SONAR_NUM] = {
  0,0,0,0,0
};

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() { 
  Serial.println("Ground Level");
  Serial.println("------------------------------------------------------------------");
  populateCurrentGroundLevelDistanceData();
  constructGroundLevelData();
  Serial.println("------------------------------------------------------------------");
  Serial.println("First Level");
  Serial.println("------------------------------------------------------------------");
  populateCurrentFirstLevelDistanceData();
  constructFirstLevelData();
  delay(4000);
  Serial.println();
  Serial.println();
}

void constructGroundLevelData() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (groundLevelDistance[i] <= 5) {
      printCurrentGroundLevel(i);
      groundLevelParkingSpacesStates[i] = 0;
    } else {
      groundLevelParkingSpacesStates[i] = 1;
      printCurrentGroundLevel(i);
    }

    Serial.print("Parking G");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(groundLevelParkingSpacesStates[i]);
  }
}

void constructFirstLevelData() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (firstLevelDistance[i] <= 5) {
      printCurrentFirstLevel(i);
      firstLevelParkingSpacesStates[i] = 0;
    } else {
      firstLevelParkingSpacesStates[i] = 1;
      printCurrentFirstLevel(i);
    }

    Serial.print("Parking F");
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(firstLevelParkingSpacesStates[i]);
  }
}

void printCurrentGroundLevel(int i) {
  Serial.print("**current: ");
  Serial.print(groundLevelDistance[i]);
  Serial.println("cm**");
}

void printCurrentFirstLevel(int i) {
  Serial.print("**current: ");
  Serial.print(firstLevelDistance[i]);
  Serial.println("cm**");
}

void populateCurrentGroundLevelDistanceData() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    groundLevelDistance[i] = sonarGroundLevel[i].ping_cm();
    delay(20);
  }
}

void populateCurrentFirstLevelDistanceData() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    firstLevelDistance[i] = sonarFirstLevel[i].ping_cm();
    delay(20);
  }
}
