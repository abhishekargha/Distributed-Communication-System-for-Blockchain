#include <WiFi.h>

const char* ssid = "SWAN LAB";
const char* password = "swan@123";

const char* host1 = "192.168.1.24"; // IP address of Server 1
const int port1 = 5000; // Port of Server 1

const int localPort = 4095; // Local port to listen for incoming connections

WiFiClient client; // Client for Server 1
WiFiServer server(localPort); // Server to listen for any incoming connection

String lastSentMessage = ""; // Store the last sent message
unsigned long myTimerStart = 0; // Store the start time of the timer

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  if (!client.connect(host1, port1)) {
    Serial.println("Connection to Server 1 failed");
    return;
  }
  Serial.println("Connected to Server 1");

  server.begin(); // Start the server to listen for any incoming connections
  Serial.println("Server started");
}

void loop() {
  // Send data to Server 1
  if (client.connected()) {
    // Check if there's any input from the Serial Monitor
    if (Serial.available() > 0) {
      // Read the input as a string
      String message = Serial.readString();
      
      // Send the input as a message to the server
      client.print(message);

      // Store the sent message and start the timer
      lastSentMessage = message;
      myTimerStart = millis();
    }
  } else {
    Serial.println("Re-connecting to Server 1");
    if (!client.connect(host1, port1)) {
      Serial.println("Connection to Server 1 failed");
      return;
    }
    Serial.println("Connected to Server 1");
  }

  // Check if there are any new clients
  if (WiFiClient newClient = server.available()) {
    // If a new client connects, print a message and read their data
    Serial.println("New client connected");
    while (newClient.connected() && newClient.available()) {
      String line = newClient.readStringUntil('\r');
      Serial.print("Received: ");
      Serial.println(line);

      // If the received message is the same as the last sent message, stop the timer and print the elapsed time
      if (line == lastSentMessage) {
        unsigned long elapsedTime = millis() - myTimerStart;
        Serial.print("Elapsed time: ");
        Serial.print(elapsedTime);
        Serial.println(" ms");
      }
    }
  }
}
