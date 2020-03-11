#include <NewPing.h>

// ---------------------------------------------------------------------------
// Example NewPing library sketch that pings 3 sensors 20 times a second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define SONAR_NUM 5      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonarFirstLevel[SONAR_NUM] = {   // Sensor object array.
  NewPing(31, 30, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(33, 32, MAX_DISTANCE), 
  NewPing(35, 34, MAX_DISTANCE),
  NewPing(37, 36, MAX_DISTANCE),
  NewPing(39, 38, MAX_DISTANCE)
};

NewPing sonarSecondLevel[SONAR_NUM] = {   // Sensor object array.
  NewPing(40, 41, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(42, 43, MAX_DISTANCE), 
  NewPing(44, 45, MAX_DISTANCE),
  NewPing(46, 47, MAX_DISTANCE),
  NewPing(48, 49, MAX_DISTANCE)
};

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() { 
  Serial.println();
  Serial.println("                    First Level");
  Serial.println("//////////////////////////////////////////////////");
  
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i+1);
    Serial.print(" = ");
    Serial.print(sonarFirstLevel[i].ping_cm());
    Serial.print("cm ");
    Serial.print("    ");
    
  }
  Serial.println();
  Serial.println();
  Serial.println("                    Second Level");
  Serial.println("//////////////////////////////////////////////////");
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i+1);
    Serial.print(" = ");
    Serial.print(sonarSecondLevel[i].ping_cm());
    Serial.print("cm ");
    Serial.print("    ");
  }
  delay(2000);
  Serial.println();
  Serial.println();
}
