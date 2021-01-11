#include "funcoes.h"

// Configura o ESP como ponto de acesso
void startAP() {
  WiFi.mode(WIFI_AP);
  bool result = WiFi.softAP(ssid, password);             // Start the access point
  if (result == true) {

    // Callback quando alguém se conecta
    stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&conexaoCliente);
    // Callback quando alguém se desconecta
    stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&desconexaoCliente);
    Serial.print(ssid);
    Serial.println(" iniciado !\r\n");
    Serial.print("IP address = ");
    Serial.println(WiFi.softAPIP());
    Serial.println("Esperando conexões...");
  }
  else {
    Serial.println("AP falhou!");
  }
}

// Callback quando alguém se conecta no ESP
void conexaoCliente(const WiFiEventSoftAPModeStationConnected& evt) {
  Serial.print("Cliente entrou: ");
  Serial.println(macToString(evt.mac));
}
// Callback quando alguém se desconecta do ESP
void desconexaoCliente(const WiFiEventSoftAPModeStationDisconnected& evt) {
  Serial.print("Cliente caiu: ");
  Serial.println(macToString(evt.mac));
}
// Retorna uma String com o valor do mac address
String macToString(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}

void startWS() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
  //  heartbeat (intervalo de ping, pong máximo, tentativas antes de desconectar)
  webSocket.enableHeartbeat(1000, 500, 3);
}

// evento webSocket como servidor
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("WS DESCONECTADO - [%u]\n", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("WS CONECTADO - IP: %d.%d.%d.%d url: %s\n", ip[0], ip[1], ip[2], ip[3], payload);
      // avisa o cliente
      webSocket.sendTXT(num, "oi");
    }
      break;
    case WStype_ERROR:
      Serial.printf("WS ERRO: %s\n", payload);
    case WStype_TEXT:
      Serial.printf("WS TEXT0: %s\n", payload);

      // Define o tipo de cliente
      if(payload[0] == 'c') {
        // Define como PC
        if(payload[1] == 'p') {
          for(int i=0; i<5; i++) {
            if(pc[i] == -1) pc[i] = num;
            break;
            }
          }
        // Define como app
        else if(payload[1] == 'a') {
          for(int i=0; i<5; i++) {
            if(app[i] == -1) app[i] = num;
            break;
            }
          }
          webSocket.sendTXT(num, "e");
        }

        // Comando para atualizar os sensores
        else if(payload[0] == 's') {
          leituraSensores();
          for(int i=0; i<30; i++) Serial.print(sensores[i]);
          Serial.println();
          webSocket.sendTXT(num, sensores, 30);
        }

        // Comando direto para os motores
        else if(payload[0] == 'm') {
          char velE[4], velD[4];
          int pos = 1, index = 0;;
          // Lê até encontrar uma vírgula
          while(payload[pos] != 44) {
            velE[index] = payload[pos];
            pos++;
            index++;
          }
            pos++;
            index = 0;
          // Lê até encontrar um ponto e vírgula
          while(payload[pos] != 59) {
            velD[index] = payload[pos];
            pos++;
            index++;
         }


         int velEsq = atoi(velE);
         int velDir = atoi(velD);
         Serial.print(velEsq);
         Serial.print("   ");
         Serial.println(velDir);

//         motor(velEsq, velDir);

         webSocket.sendTXT(num, "e");
        }

        // Andar uma distância específica
        else if(payload[0] == 'a') {
          char dist[4];
          int pos = 1;
          // Lê até encontrar um ponto e vírgula
          while(payload[pos] != 59) {
            dist[pos-1] = payload[pos];
            pos++;
          }
          int distFinal = atoi(dist);
          int distAtual = 0;
          while(distAtual < distFinal) {
            motor(0, 0);
          }
          
          Serial.println("andando");
          delay(3000);
          Serial.println("já deu");
          webSocket.sendTXT(num, "e");
        }

        // Andar uma distância específica
        else if(payload[0] == 'g') {
          Serial.println("girando");
          delay(5500);
          Serial.println("já deu");
          webSocket.sendTXT(num, "e");
        }

//      if (payload[0] == 'a') acoes(payload);
//      else if (payload[0] == 'm') movimento(payload);
//      else if(payload[0] == 'b') buzzer(payload);
//      else if (payload[0] == 's') testeBuzzer(payload);

      break;
  }
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
