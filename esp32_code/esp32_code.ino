#include <WiFi.h>
#include <WebServer.h>

// --- DRIVER 1 PINS (Assume Left Side Motors) ---
const int ENA1 = 32;
const int IN1 = 33;
const int IN2 = 25;
const int IN3 = 26;
const int IN4 = 27;
const int ENB1 = 14;

// --- DRIVER 2 PINS (Assume Right Side Motors) ---
const int ENA2 = 22;
const int IN5 = 16; // RX2
const int IN6 = 17; // TX2
const int IN7 = 18;
const int IN8 = 19;
const int ENB2 = 23;

// Set the Hotspot Name and Password for this specific rover
const char* ssid = "RoverX_Team1"; 
const char* password = "password123";

WebServer server(80);

// Minimal HTML/CSS Interface for Mobile Browsers
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { text-align: center; font-family: Arial; margin-top: 50px; background-color: #121212; color: white;}
    .btn { padding: 20px 40px; font-size: 24px; margin: 10px; border-radius: 10px; border: none; cursor: pointer; color: white; background-color: #007bff;}
    .btn-stop { background-color: #dc3545; }
  </style>
</head>
<body>
  <h1>RoverX Control</h1>
  <button class="btn" onmousedown="sendCommand('forward')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('forward')" ontouchend="sendCommand('stop')">Forward</button><br>
  <button class="btn" onmousedown="sendCommand('left')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('left')" ontouchend="sendCommand('stop')">Left</button>
  <button class="btn btn-stop" onclick="sendCommand('stop')">STOP</button>
  <button class="btn" onmousedown="sendCommand('right')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('right')" ontouchend="sendCommand('stop')">Right</button><br>
  <button class="btn" onmousedown="sendCommand('backward')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('backward')" ontouchend="sendCommand('stop')">Backward</button>
  <script>
    function sendCommand(cmd) { fetch('/' + cmd); }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  // Initialize all motor control pins as outputs
  int pins[] = {ENA1, IN1, IN2, IN3, IN4, ENB1, ENA2, IN5, IN6, IN7, IN8, ENB2};
  for(int i=0; i<12; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // Set motor speed (0 to 255)
  analogWrite(ENA1, 255);
  analogWrite(ENB1, 255);
  analogWrite(ENA2, 255);
  analogWrite(ENB2, 255);

  // Broadcast the ESP32 as a Wi-Fi Hotspot
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Connect phone to Wi-Fi: "); Serial.println(ssid);
  Serial.print("Open browser to IP: "); Serial.println(IP);

  // Map URLs to Movement Functions
  server.on("/", []() { server.send(200, "text/html", htmlPage); });
  server.on("/forward", []() { moveForward(); server.send(200, "text/plain", "Forward"); });
  server.on("/backward", []() { moveBackward(); server.send(200, "text/plain", "Backward"); });
  server.on("/left", []() { turnLeft(); server.send(200, "text/plain", "Left"); });
  server.on("/right", []() { turnRight(); server.send(200, "text/plain", "Right"); });
  server.on("/stop", []() { stopMotors(); server.send(200, "text/plain", "Stop"); });

  server.begin();
}

void loop() {
  server.handleClient();
}

// --- HARDWARE MOVEMENT LOGIC ---
void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);
  digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH);
  digitalWrite(IN7, LOW); digitalWrite(IN8, HIGH);
}

void turnLeft() { // Skid steer: Left motors reverse, Right motors forward
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);
  digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);
}

void turnRight() { // Skid steer: Left motors forward, Right motors reverse
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH);
  digitalWrite(IN7, LOW); digitalWrite(IN8, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW); digitalWrite(IN8, LOW);
}