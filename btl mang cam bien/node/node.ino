#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// Thông tin mạng Wi-Fi
const char* ssid = "a";
const char* password = "012345678";

// Địa chỉ IP và cổng của ESP32 Server
const char* serverIP = "192.168.220.17"; 
const int serverPort = 80; 

WiFiClient client;

const int motionSensorPin = 13;

void setup() {
  Serial.begin(115200);

  // Kết nối đến mạng Wi-Fi99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int motionData = digitalRead(motionSensorPin);

  // Gửi giá trị cảm biến chuyển động đến ESP32 Server
  if (sendMotionData(motionData)) {
    Serial.println("Motion data sent to server");
  } else {
    Serial.println("Failed to send motion data");
  }

  delay(500); 
}

bool sendMotionData(int data) {
  if (client.connect(serverIP, serverPort)) {
    // Gửi dữ liệu cảm biến chuyển động đến ESP32 Server
    String url = "/motion?value=" + String(data);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + serverIP + "\r\n" +
                 "Connection: close\r\n\r\n");
    delay(10);

    // Đọc phản hồi từ ESP32 Server (nếu có)
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    client.stop(); // Đóng kết nối sau khi gửi dữ liệu
    return true;
  } else {
    Serial.println("Failed to connect to server");
    return false;
  }
}
