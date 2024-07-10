#include <WiFi.h>

const char* ssid = "5G";           // Replace with your WiFi SSID
const char* password = "qwertyfdsa";  // Replace with your WiFi password
const char* server = "192.168.252.4"; // IP address of your Flask server
const int serverPort = 5000;          // Port number of your Flask server
const char* endpoint = "/ph_sensor";  // Endpoint to send pH sensor data

const int phPin = 34; // Change this to the GPIO pin connected to the pH sensor

// Calibration constants
const float m = 3.5; // Replace with your slope constant
const float b = -1.0; // Replace with your intercept constant

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    if (attempts > 20) {
      Serial.println("Connection failed. Check your credentials or network.");
      while (true) {
        // Stay in a loop to indicate connection failure
      }
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read pH sensor value
  float phValue = readPH();
  
  // Print pH value to Serial Monitor
  Serial.print("pH value: ");
  Serial.println(phValue);

  // Send data to server
  sendData(phValue);

  delay(5000); // Adjust delay as needed for your project
}


float readPH() {
  // Read pH sensor value and convert to pH using appropriate formula
  int sensorValue = analogRead(phPin);
  float voltage = sensorValue * (5.0 / 1023.0); // Convert ADC value to voltage (assuming 10-bit ADC)
  // Assuming a linear relationship: pH = m * voltage + b
  float pHValue = m * voltage + b; // Replace m and b with your calibration constants
  return pHValue;
}

void sendData(float phValue) {
  WiFiClient client;
  if (!client.connect(server, serverPort)) {
    Serial.println("Connection failed");
    return;
  }

  // Create HTTP POST request with pH sensor data
  String postData = "ph_value=" + String(phValue);
  client.println("POST " + String(endpoint) + " HTTP/1.1");
  client.println("Host: " + String(server));
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.println("Content-Length: " + String(postData.length()));
  client.println();
  client.println(postData);

  delay(10); // Wait for the server to respond

  // Read and print the response from the server
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("Request complete");
  client.stop(); // Close connection
}
