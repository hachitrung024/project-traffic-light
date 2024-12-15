#include <HardwareSerial.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
WebServer server(80);

#define RXD1 0
#define TXD1 1

String json;
String input;
void parseData(){
  int field1End = input.indexOf(',');
  int field2End = input.indexOf(',', field1End + 1);

  if (field1End == -1 || field2End == -1) return;

  json = "{";
  json += "\"l1\":\"" + input.substring(0, field1End) + "\",";
  json += "\"l2\":\"" + input.substring(field1End + 1, field2End) + "\",";
  json += "\"s\":" + input.substring(field2End + 1);
  json += "}";
}
void handleRoot() { // home page
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    server.sendHeader("Location", "/admin");
    server.send(303);
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleControl(){
  if (server.hasArg("action")) {
    String action = server.arg("action");
    Serial.println("Action received: " + action);
    // Thực hiện hành động tương ứng với action
    if(action == "MODE") Serial1.print('1');
    else if(action == "SET") Serial1.print('2');
    else if(action == "OK") Serial1.print('3');
    else if(action == "RESET") Serial1.print('4');
  }
  server.send(200, "text/plain", "Action processed");
}

void setup() {
  // Setup UART
  Serial.begin(115200); // Serial Monitor
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1); // STM32 UART
  // Setup WiFi
  WiFi.begin("HYPER 5840", "hephanboaaa");
  Serial.print("Connecting...");
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
  }
  Serial.println("\nWiFi Connected\nIP: "+ WiFi.localIP().toString());
  // Web Server
  server.begin();
  server.on("/", handleRoot);
  server.on("/data", [](){parseData();server.send(200, "application/json", json);});
  server.on("/upload", HTTP_POST, []() {}, handleFileUpload);
  server.on("/admin", handleAdmin);
  server.on("/control", HTTP_POST, handleControl);

  setupLittleFS();

}

void loop() {
  // Kiểm tra nếu có dữ liệu đến từ UART1
  if (Serial1.available()){
     input = Serial1.readStringUntil('#');
    Serial.println(input);
  }
  server.handleClient();
}

void setupLittleFS(){
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount LittleFS. Formatting...");
    if (LittleFS.format()) {
      Serial.println("LittleFS formatted successfully.");
      if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS after formatting.");
        return;
      }
    } else {
      Serial.println("Failed to format LittleFS.");
      return;
    }
  }
}
void handleAdmin() {
    if (!server.authenticate("trung", "123")) {
        server.requestAuthentication();
        return;
    }
    server.send(200, "text/html",
            "<html>"
            "<body>"
            "<h1>[ADMIN] File upload</h1>"
            "<form method='POST' action='/upload' enctype='multipart/form-data'>"
            "<input type='file' name='data'>"
            "<input type='submit' value='Upload'>"
            "</form>"
            "</body>"
            "</html>");
}

void handleFileUpload() {
  HTTPUpload& upload = server.upload();
  static File file;

  if (upload.status == UPLOAD_FILE_START) {
    String filename = "/" + upload.filename; // save with the same name
    Serial.printf("Uploading: %s\n", filename.c_str());
    file = LittleFS.open(filename, "w");
    if (!file) {
      Serial.println("Failed to create file.");
      server.send(500, "text/plain", "Failed to create file.");
      return;
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (file) {
      file.write(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (file) {
      file.close();
      Serial.printf("Uploaded: %s (%u bytes)\n", upload.filename.c_str(), upload.totalSize);
      server.sendHeader("Location", "/");
      server.send(303);
    } else {
      server.send(500, "text/html",
                  "<html><body><h1>File Upload Failed</h1>"
                  "<p>Unable to save the file.</p>"
                  "<a href='/upload'>Try again</a></body></html>");
    }
  }
}


