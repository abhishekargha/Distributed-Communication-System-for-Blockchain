// It connects to a specified WiFi network and then establishes a connection to a
// server on a specified host and port. It sends messages to the server and prints 
 //the server’s responses.
// Include the WiFi library to use WiFi functions
#include <WiFi.h>

// Define the WiFi credentials
const char* ssid = "SWAN LAB"; // The SSID (name) of your WiFi network
const char* password = "swan@123"; // The password of your WiFi network

// Define the server host and port
const char* host = "192.168.1.24"; // The hostname or IP address of the server
const int port = 5005; // The port number the server is listening on

// Create a WiFiClient object
WiFiClient client;

void setup() {
  // Initialize serial communication at a baud rate of 115200
  Serial.begin(115200);

  // Connect to the WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); // Wait for 500 milliseconds
    Serial.print("."); // Print a dot every 500 milliseconds until connected
  }
  Serial.println();
  Serial.println("WiFi connected");

  // Connect to the server
  Serial.print("Connecting to server");
  if (!client.connect(host, port)) {
    Serial.println("Connection failed"); // Print an error message if the connection fails
    return;
  }
  Serial.println();
  Serial.println("Connected to server");
}

void loop() {
  // Check if the client is connected to the server
  if (client.connected()) {
    // Get a message from the user
    Serial.println("Enter a message to send to the server: ");
    while (Serial.available() == 0) {
      // Wait for user input
    }
    String message = Serial.readString(); // Read the user's message

    // Send the message to the server
    client.print(message);

    // Print the server's response
    Serial.println("Server response: ");
    while (client.available()) {
      String line = client.readStringUntil('\r'); // Read the server's response until a carriage return ('\r') is encountered
      Serial.print(line); // Print the server's response
    }
    Serial.println();
  }
  else {
    // If the client is not connected to the server, try to reconnect
    Serial.println("Re-connecting to server");
    if (!client.connect(host, port)) {
      Serial.println("Connection failed"); // Print an error message if the connection fails
      return;
    }
    Serial.println("Connected to server");
  }
}
