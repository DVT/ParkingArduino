#include <WiFi.h>

const char* ssid = "DVT-JHB";
const char* pass = "BullHornBitesOnce";

const char* host = "data.sparkfun.com";

const char* streamId   = "....................";
const char* privateKey = "....................";

int value = 0;

//WiFiClient client;

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
//  delay(5000);
//    ++value;
//
//    Serial.print("connecting to ");
//    Serial.println(host);
//
//    // Use WiFiClient class to create TCP connections
//    WiFiClient client;
//    const int httpPort = 80;
//    if (!client.connect(host, httpPort)) {
//        Serial.println("connection failed");
//        return;
//    }
//
//    // We now create a URI for the request
//    String url = "/input/";
//    url += streamId;
//    url += "?private_key=";
//    url += privateKey;
//    url += "&value=";
//    url += value;
//
//    Serial.print("Requesting URL: ");
//    Serial.println(url);
//
//    // This will send the request to the server
//    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//                 "Host: " + host + "\r\n" +
//                 "Connection: close\r\n\r\n");
//    unsigned long timeout = millis();
//    while (client.available() == 0) {
//        if (millis() - timeout > 5000) {
//            Serial.println(">>> Client Timeout !");
//            client.stop();
//            return;
//        }
//    }
//
//    // Read all the lines of the reply from server and print them to Serial
//    while(client.available()) {
//        String line = client.readStringUntil('\r');
//        Serial.print(line);
//    }
//
//    Serial.println();
//    Serial.println("closing connection");

  
}
