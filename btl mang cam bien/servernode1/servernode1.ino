#include <WiFi.h>
#include <WiFiServer.h>
#include <Wire.h>

const char* ssid = "a";
const char* password = "012345678";
WiFiServer server(80); 

const int ledPin = 2; // Chân kết nối đèn LED 
const int led1Pin = 0;
const int led2Pin = 17;

int motionData = 0; // Biến lưu trữ giá trị cảm biến chuyển động

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  // Kết nối đến mạng Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(" ");
  Serial.println("Connected to Wi-Fi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Bắt đầu lắng nghe kết nối

  Serial.println("Server is waiting for connections...");
}

void loop() {
  // Kiểm tra kết nối từ Client
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client connected");

    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println("Received: " + request);

        // Phân tích dữ liệu từ Client (URL có thể được sử dụng để xác định chuyển động)
        if (request.indexOf("/motion?value=1") != -1) {
          motionData = 1; // Có chuyển động
          digitalWrite(ledPin, HIGH); // Bật đèn LED
        } else if (request.indexOf("/motion?value=0") != -1) {
          motionData = 0; // Không có chuyển động
          digitalWrite(ledPin, LOW); // Tắt đèn LED
        }


        if (request.indexOf("/motion1value=1") != -1) {
          motionData = 1; // Có chuyển động
          digitalWrite(led1Pin, HIGH); // Bật đèn LED
        } else if (request.indexOf("/motion1value=0") != -1) {
          motionData = 0; // Không có chuyển động
          digitalWrite(led1Pin, LOW); // Tắt đèn LED
        }


        if (request.indexOf("/motion2value=1") != -1) {
          motionData = 1; // Có chuyển động
          digitalWrite(led2Pin, HIGH); // Bật đèn LED
        } else if (request.indexOf("/motion2value=0") != -1) {
          motionData = 0; // Không có chuyển động
          digitalWrite(led2Pin, LOW); // Tắt đèn LED
        }
        

        client.stop(); // Đóng kết nối sau khi xử lý dữ liệu
      }
    }

    Serial.println("Client disconnected");
  }
}
