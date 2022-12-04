#ifndef FILEMANAGER_h
#define FILEMANAGER_h

#include <FS.h>

struct Settings {
  String DeviceId;
  String DeviceName;
  long SleepTime;
};

class FileManager {
  public:
    FileManager();

    String getBatchName();
    void saveBatchName(String batchName);
    Settings getSettings();
    void saveSettings(Settings settings);
    void createFile(String filename);
    void writeBufferToFile(uint8_t buffer[], size_t size);
    void closeFile();
    

    File getFile(String path);

  private:
  
};

#endif
