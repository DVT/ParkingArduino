#include <WiFi.h>

const char* ssid = "DVT-JHB";
const char* pass = "BullHornBitesOnce";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to Wifi...");
  }

  Serial.println("Connected to Network");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
