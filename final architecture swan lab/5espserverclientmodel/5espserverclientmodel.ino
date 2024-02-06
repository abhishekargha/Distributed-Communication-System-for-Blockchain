// include the wifi library to use wifi functions
#include <WiFi.h>

//define the wifi credentials
const char* ssid = "SWAN LAB"; // the ssid (name) of your wifi network
const char* password = "swan@123"; //the password of your wifi network

// define the server host and port for the first server (from where we recieve messages)
const char* host1 = "192.168.1.24"; // the hostname of IP address of the second server 
const int port1 = 5005; // the port number the seconf server is listening on

// define the server host and port for the second server (to where we send messages)
const char* host2 = "192.168.1.25"; // the hostname or IP address of the second server
const int port2 = 5006; // the port number the second server is listening to

// create two wificlient objects
WiFiClient client1; // client to connect to the first server 
WiFiClient client2; // client to connect to the server 

void setup() {
 // initialize serial communication at a baud rate of 115200
  Serial.begin(115200);

 // connect to the wifi network 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); // wait for 500 milliseconds
  }

  // connect to the first server 
  if (!client1.connect(host1, port1)) {
    return; // if the connection fails , exit the function
  }

  // connect to the second server
  if (!client2.connect(host2, port2)) {
    return; // if the connection fails, exit the function
  }
}


void loop() {
 // check if the first client is connected to the first server
  if (client1.connected()) {
   // if there are available bytes to read from the server 
    while (client1.available()) {
     // read a line from the first server 
      String line = client1.readStringUntil('\r');
     // send the line to the second server
      client2.print(line);
    }
  }
  else {
   // if the first client is not connected to the first server , try to reconnect
    if (!client1.connect(host1, port1)) {
      return; // if the connection fails, exit the function
    }
  }
  // check if the second client is connected to the second server 
  if (!client2.connected()) {
   // if the second client is not connected to the second server , try to reconnect
    if (!client2.connect(host2, port2)) {
      return; // if the connection fails, exit the function
    }
  }
}
