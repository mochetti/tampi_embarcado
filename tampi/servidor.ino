

void startAP() { // Start a Wi-Fi access point
  WiFi.mode(WIFI_AP);
  bool result = WiFi.softAP(ssid, password);             // Start the access point
  if (result == true) {
    Serial.print("Access Point \"");
    Serial.print(ssid);
    Serial.println("\" started\r\n");
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
    Serial.println("Connecting");
    while (WiFi.softAPgetStationNum() < 1) {  // Wait for the Wi-Fi to connect
      delay(250);
      Serial.print('.');
      buzina(500, 8);
    }
    Serial.println("\r\n");
    Serial.println("Station connected to ESP8266 AP");
    buzina(500, 8);
    buzina(700, 8);
    buzina(650, 8);
  }
  else {
    Serial.println("AP falhou!");
  }
}

// evento webSocket como servidor
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("EVENTO WS: Connected from %d.%d.%d.%d url: %s\n", ip[0], ip[1], ip[2], ip[3], payload);
        // avisa o cliente
        webSocket.sendTXT(num, "welcome");
      }
      break;
    case WStype_TEXT:                     // if new text data is received
      Serial.printf("EVENTO WS: get Text: %s\n", payload);

      if (payload[0] == 'a') acoes(payload);
      else if (payload[0] == 'm') movimento(payload);
      else if(payload[0] == 'b') buzzer(payload);
      else if (payload[0] == 's') testeBuzzer(payload);

      break;
  }
}

void startWebSocket() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
}

//void startMDNS() { // Start the mDNS responder
//  MDNS.begin(mdnsName);                        // start the multicast domain name server
//  Serial.print("mDNS responder started: http://");
//  Serial.print(mdnsName);
//  Serial.println(".local");
//}

//void startServer() { // Start a HTTP server with a file read handler and an upload handler
//  server.on("/edit.html",  HTTP_POST, []() {  // If a POST request is sent to the /edit.html address,
//    server.send(200, "text/plain", "");
//  });                       // go to 'handleFileUpload'
//
//  //  server.onNotFound(handleNotFound);          // if someone requests any other file or page, go to function 'handleNotFound'
//  // and check if the file exists
//
//  server.begin();                             // start the HTTP server
//  Serial.println("HTTP server started.");
//}

//bool handleFileRead(String path) { // send the right file to the client (if it exists)
//  Serial.println("handleFileRead: " + path);
//  if (path.endsWith("/")) path += "index.html";          // If a folder is requested, send the index file
//  String contentType = getContentType(path);             // Get the MIME type
//  String pathWithGz = path + ".gz";
//  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) { // If the file exists, either as a compressed archive, or normal
//    if (SPIFFS.exists(pathWithGz))                         // If there's a compressed version available
//      path += ".gz";                                         // Use the compressed verion
//    File file = SPIFFS.open(path, "r");                    // Open the file
//    size_t sent = server.streamFile(file, contentType);    // Send it to the client
//    file.close();                                          // Close the file again
//    Serial.println(String("\tSent file: ") + path);
//    return true;
//  }
//  Serial.println(String("\tFile Not Found: ") + path);   // If the file doesn't exist, return false
//  return false;
//}

//void handleFileUpload(){ // upload a new file to the SPIFFS
//  HTTPUpload& upload = server.upload();
//  String path;
//  if(upload.status == UPLOAD_FILE_START){
//    path = upload.filename;
//    if(!path.startsWith("/")) path = "/"+path;
//    if(!path.endsWith(".gz")) {                          // The file server always prefers a compressed version of a file
//      String pathWithGz = path+".gz";                    // So if an uploaded file is not compressed, the existing compressed
//      if(SPIFFS.exists(pathWithGz))                      // version of that file must be deleted (if it exists)
//         SPIFFS.remove(pathWithGz);
//    }
//    Serial.print("handleFileUpload Name: "); Serial.println(path);
//    fsUploadFile = SPIFFS.open(path, "w");            // Open the file for writing in SPIFFS (create if it doesn't exist)
//    path = String();
//  } else if(upload.status == UPLOAD_FILE_WRITE){
//    if(fsUploadFile)
//      fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
//  } else if(upload.status == UPLOAD_FILE_END){
//    if(fsUploadFile) {                                    // If the file was successfully created
//      fsUploadFile.close();                               // Close the file again
//      Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
//      server.sendHeader("Location","/success.html");      // Redirect the client to the success page
//      server.send(303);
//    } else {
//      server.send(500, "text/plain", "500: couldn't create file");
//    }
//  }
//}

//void handleNotFound(){ // if the requested file or page doesn't exist, return a 404 not found error
//  if(!handleFileRead(server.uri())){          // check if the file exists in the flash memory (SPIFFS), if so, send it
//    server.send(404, "text/plain", "404: File Not Found");
//  }
//}

//void startSPIFFS() { // Start the SPIFFS and list all contents
//  SPIFFS.begin();                             // Start the SPI Flash File System (SPIFFS)
//  Serial.println("SPIFFS started. Contents:");
//  {
//    Dir dir = SPIFFS.openDir("/");
//    while (dir.next()) {                      // List the file system contents
//      String fileName = dir.fileName();
//      size_t fileSize = dir.fileSize();
//      Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
//    }
//    Serial.printf("\n");
//  }
//}

void startSTA() { // se conecta numa rede wifi

  //  WiFi.softAP(ssid, password);             // Start the access point
  //  Serial.print("Access Point \"");
  //  Serial.print(ssid);
  //  Serial.println("\" started\r\n");
  //
  //  Serial.println("Connecting");
  //  while (WiFi.softAPgetStationNum() < 1) {  // Wait for the Wi-Fi to connect
  //    delay(250);
  //    Serial.print('.');
  //  }
  //  Serial.println("\r\n");
  //  Serial.println("Station connected to ESP8266 AP");
}

// evento webSocket como cliente
//void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
//
//  switch(type) {
//    case WStype_DISCONNECTED:
//      USE_SERIAL.printf("[WSc] Disconnected!\n");
//      break;
//    case WStype_CONNECTED: {
//      USE_SERIAL.printf("[WSc] Connected to url: %s\n", payload);
//
//      // send message to server when Connected
//      webSocket.sendTXT("Connected");
//    }
//      break;
//    case WStype_TEXT:
//      USE_SERIAL.printf("[WSc] get text: %s\n", payload);
//
//      // send message to server
//      // webSocket.sendTXT("message here");
//      break;
//    case WStype_BIN:
//      USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
//      hexdump(payload, length);
//
//      // send data to server
//      // webSocket.sendBIN(payload, length);
//      break;
//        case WStype_PING:
//            // pong will be send automatically
//            USE_SERIAL.printf("[WSc] get ping\n");
//            break;
//        case WStype_PONG:
//            // answer to a ping we send
//            USE_SERIAL.printf("[WSc] get pong\n");
//            break;
//    }
//
//}
