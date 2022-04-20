#include <ESP8266WiFi.h>
#include <WiFiClient.h>
const int d_0 = D2; // make d_0 assigned to pin D2 - TRIG
const int d_1 = D1;
int sensor_val = 0; // variable to store the value coming from the sensor\
const char* ssid = "AndroidAP";
const char* password = "poppy123";
//ESP8266WebServer server(80);
WiFiClient client;
void setup() {
// Start Comm
Serial.begin(9600);
Serial.setTimeout(2000);
delay(1000);
// Wait for serial to initialize.

//while(!Serial) { }
delay(1000);
Serial.println("I'm awake.");
delay(1000);
WiFi.begin(ssid, password);
Serial.print("Connecting...");
// Wait for connection
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.print("\nConnected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
delay(1000);
pinMode(d_0, OUTPUT);
pinMode(d_1, INPUT);
digitalWrite(d_0, LOW);
}
void loop() {
// Initiate Pulsing of Sensor
digitalWrite(d_0, LOW); // Set Low 2us
delay(2);
digitalWrite(d_0, HIGH); // Set High 10us
delay(10);
digitalWrite(d_0, LOW); // Make low again
int distance = pulseIn(d_1, HIGH, 26000); // Read pulse time from D1
distance = distance/58; // Convert to distance
Serial.print(distance); // Display
Serial.println(" cm");
//int d_read = digitalRead(d_1);
//Serial.print(d_read);
//Serial.println(" logic");
Serial.println("\nStarting connection to server...");
if (client.connect("192.168.43.198", 80)) {
Serial.println("Connected to server!");
client.print("GET /file3/receive1.php?"); // This
client.print("water="); // This


client.print(distance); // And this is what we did in the testing section above. We are making a GET request just like we would from our browser but now with live data from the sensor
client.println(" HTTP/1.1"); // Part of the GET request
client.println("Host: 192.168.20.5"); // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here
client.println("Connection: close"); // Part of the GET request telling the server that we are over transmitting the message
client.println(); // Empty line
client.println(); // Empty line
client.stop(); // Closing connection to server
Serial.print("water = ");
Serial.println(distance);
}
else {
// if the esp doesnt connect to the web server
Serial.println("--> connection failed\n");
}
delay(50);
delay(50);
Serial.println("Going into deep sleep for 10 seconds");
ESP.deepSleep(10e6); // 20e6 is 20 microseconds
}
