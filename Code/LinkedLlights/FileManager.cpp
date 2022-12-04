#include <FS.h>
#include "filemanager.h"

File currentFile;

FileManager::FileManager() {
  SPIFFS.begin();
}

String FileManager::getBatchName() {
  String batchName = "";
  
  if (SPIFFS.exists("batch.current")) {
    File file = SPIFFS.open("batch.current", "r");

    batchName = file.readString();
    
    file.close();
  }
  
  return batchName;
}

void FileManager::saveBatchName(String batchName) {
  if (SPIFFS.exists("batch.current")) {
    SPIFFS.remove("batch.current");
  }
  
  File file = SPIFFS.open("batch.current", "w");
  file.print(batchName);
  file.close();
}

Settings FileManager::getSettings() {
  Settings settings;

  settings.DeviceId = "asdasd";
  settings.DeviceName = "Mollll";
  settings.SleepTime = 30 * 60000000 / 30;
  
  return settings;
}

void FileManager::saveSettings(Settings settings) {
  
}

void FileManager::createFile(String filename) {
  currentFile = SPIFFS.open(filename, "w");
}

void FileManager::writeBufferToFile(uint8_t buffer[], size_t size) {
  currentFile.write(buffer, size);
}

void FileManager::closeFile() {
  currentFile.close();
}

File FileManager::getFile(String path) {
  return SPIFFS.open(path.c_str(), "r");
}
