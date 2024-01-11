#include <WiFiManager.h>
#include <ArduinoOTA.h>
#include <WS2812FX.h>
#include <ESP8266httpUpdate.h>
#include "Timer.h"
#include "pitches.h"
#include "songs.h"
#include "filemanager.h"

#define LED_COUNT 150
#define LED_PIN 14
#define EFFECT_DURATION 3000
#define INPUT_PIN 13
#define BUZZER_PIN 12

#define FIRMWARE_VERSION 3

WiFiManager wifiManager;
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
ESP8266WebServer server(80);
FileManager fileManager;
Song song = JingleBells(BUZZER_PIN);

void checkForUpdates(int firmwareVersionToCheck) {
  ESPhttpUpdate.rebootOnUpdate(false);
  WiFiClient client;

  String updateUrl = "http://williamb.net:80/LightsFirmwareV" + String(firmwareVersionToCheck + 1) + ".bin";
  Serial.print("Checking for update from ");
  Serial.println(updateUrl);

  t_httpUpdate_return ret = ESPhttpUpdate.update(client, updateUrl);
  if (ret == HTTP_UPDATE_OK){
      Serial.println("HTTP_UPDATE_OK. Reboot");
      delay(1000); // Wait a second and restart
      ESP.restart();
  } else {
    Serial.print("HTTP_UPDATE Result = ");
    Serial.println(ret);
  }
}

void configureOTA() {
  // Make sure the flash size matches. For ESP8266 12F it should be 4MB.
  ArduinoOTA.setHostname("linkedlights");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {
      // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}

void connectToWifi() {
  wifiManager.autoConnect("linkedlights");
}

void handleFileUpload(){ // upload a new file to the SPIFFS
  HTTPUpload& upload = server.upload();
  if(upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    if(!filename.startsWith("/")) filename = "/"+filename;
    Serial.print("handleFileUpload Name: "); Serial.println(filename);
    fileManager.createFile(filename);
  } else if(upload.status == UPLOAD_FILE_WRITE){
    fileManager.writeBufferToFile(upload.buf, upload.currentSize);
  } else if(upload.status == UPLOAD_FILE_END){
    fileManager.closeFile();
    server.send(200);
  } else {
    server.send(500, "text/plain", "500: couldn't create file");
  }
}

void handleRequest() {
  String path = server.uri();

  String dataType = "text/plain";
  bool mustProcess = false;
  if(path.endsWith("/")) path += "index.html";

  if(path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if(path.endsWith(".htm"))  dataType = "text/html";
  else if(path.endsWith(".html")) dataType = "text/html";
  else if(path.endsWith(".css"))  dataType = "text/css";
  else if(path.endsWith(".js"))   dataType = "application/javascript";
  else if(path.endsWith(".png"))  dataType = "image/png";
  else if(path.endsWith(".gif"))  dataType = "image/gif";
  else if(path.endsWith(".jpg"))  dataType = "image/jpeg";
  else if(path.endsWith(".ico"))  dataType = "image/x-icon";
  else if(path.endsWith(".xml"))  dataType = "text/xml";
  else if(path.endsWith(".pdf"))  dataType = "application/pdf";
  else if(path.endsWith(".zip"))  dataType = "application/zip";

  File dataFile = fileManager.getFile(path);
  if (!dataFile) {
    Serial.print(path); Serial.println(" not found");
    server.send(404, "text/plain", "not found");
    return;
  }

  if (mustProcess) {
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.sendHeader("Content-Type", dataType, true);
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, dataType, "");
  
    while(dataFile.available()) {
      String line = dataFile.readStringUntil('\n');
      
//      line.replace("{{{Tilt}}}", String(tilt));
//      line.replace("{{{Temp}}}", String(temp));
//      line.replace("{{{ID}}}", deviceId);
//      line.replace("{{{voltage}}}", String(voltage));
      
      server.sendContent(line);
    }
    
    server.sendContent("");
    dataFile.close();
  } else {
    server.streamFile(dataFile, dataType);
  }
}

Song getSong(String songName) {
  songName.toLowerCase();

  if (songName == "jinglebells") { return JingleBells(BUZZER_PIN); }
  else if (songName == "wewishyouamerrychristmas") { return WeWishYouAMerryChristmas(BUZZER_PIN); }
  else if (songName == "santaclauseiscomingtotown") { return SantaClauseIsComingToTown(BUZZER_PIN); }
  else if (songName == "canonind") { return CanonInD(BUZZER_PIN); }
  else if (songName == "supermariobrothers") { return SuperMarioBrothers(BUZZER_PIN); }
  else if (songName == "silentnight") { return SilentNight(BUZZER_PIN); }
  else if (songName == "gameofthrones") { return GameOfThrones(BUZZER_PIN); }
  else if (songName == "asabranca") { return AsaBranca(BUZZER_PIN); }
  else if (songName == "babyelephantwalk") { return BabyElephantWalk(BUZZER_PIN); }
  else if (songName == "brahmslullaby") { return BrahmsLullaby(BUZZER_PIN); }
  else if (songName == "starwarscantina") { return StarWarsCantina(BUZZER_PIN); }
  else if (songName == "furelise") { return FurElise(BUZZER_PIN); }
  else if (songName == "greenhill") { return GreenHill(BUZZER_PIN); }
  else if (songName == "greensleeves") { return GreenSleeves(BUZZER_PIN); }
  else if (songName == "happybirthday") { return HappyBirthday(BUZZER_PIN); }
  else if (songName == "imperialmarch") { return ImperialMarch(BUZZER_PIN); }
  else if (songName == "jigglypuffssong") { return JigglypuffsSong(BUZZER_PIN); }
  else if (songName == "keyboardcat") { return KeyboardCat(BUZZER_PIN); }
  else if (songName == "miichanneltheme") { return MiiChannelTheme(BUZZER_PIN); }
  else if (songName == "minueting") { return MinuetInG(BUZZER_PIN); }
  else if (songName == "nevergonnagiveyouup") { return NeverGonnaGiveYouUp(BUZZER_PIN); }
}

void configureUrlRoutes() {
  server.on("/api/data", HTTP_GET, []() {
    String meow = "meow";
    String result = "{\"batchname\": \"" + meow + "\"}";
    server.send(200, "text/json", result);
  });

  server.on("/api/resetwifi", HTTP_GET, []() {
    wifiManager.resetSettings();
    server.send(200, "text/json", "OK");
  });

  server.on("/api/upload", HTTP_GET, []() {
    server.send(200, "text/html", "<form method=\"post\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"name\"><input class=\"button\" type=\"submit\" value=\"Upload\"></form>");
  });

  server.on("/api/play", HTTP_GET,
  []() {
    server.send(200);
    song = getSong(server.arg("song"));
    song.play();
  });

  server.on("/api/upload", HTTP_POST,
    [](){ server.send(200); },
    handleFileUpload);
  
  server.onNotFound(handleRequest);
}

void setup() {
  Serial.begin(115200);

  pinMode(INPUT_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);

  //ws2812fx.init();
  //ws2812fx.setBrightness(50);
  //ws2812fx.setSpeed(EFFECT_DURATION);
  //ws2812fx.setColor(GREEN);
  //ws2812fx.setMode(FX_MODE_CHASE_RAINBOW_WHITE);

  connectToWifi();
  configureOTA();
  checkForUpdates(FIRMWARE_VERSION);
  configureUrlRoutes();
  server.begin();
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();
  
  song.processSong();
}
