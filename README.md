# ParkingArduino
## Innovation week project

### Overview
ParkingArduino is the physical component of our Parkit application. 
Parkit is a concept that allows a user to check the amount of available 
parkings in the Malls and shopping centres nearby.
This is achieved through the means of sensors that determine if a Parking spot is vacant or occupied.

### Hardware
- Ultra Sonic Sensors - Measures distance.
- Arduino Mega - Used its 5V power output (Beneficially we would use a dedicated 5V power supply to the sensors).
- DOIT ESP32 DEV KIT - Microprocessor with bluetooth and WiFi capabilities.
- Bread board - Power up all the sensors
- Standard project jumper cables.

### Software and Libraries
- Arduino IDE - Program the microprocessor.
- Library <WiFi.h> - Connect the WiFi module to the WiFi available.
- Library <FirebaseESP32.h> - Upload the parking spot status to Firebase

### Concept
We used ultra sonic sensors to measure the distance from the floor upwards. A car would cover the sensor when pulling into a parking lot. If the distance measured by the sensor is less than the set threshold, a parking spot is ocupied, otherwise vacant. 

The status of the parking is determined by microprocessor and then uploaded to the Firebase database. Parkit, the app, constantly observe changes in the database and will update the parking spot gridview accordingly. 
