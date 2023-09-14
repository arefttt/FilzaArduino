#ifndef FILZA_ARDUINO_H
#define FILZA_ARDUINO_H

#include <SD.h>
#include <CRC32.h>
#include <SdFat.h>

enum ErrorCode {
  SUCCESS = 0,
  FILE_NOT_FOUND,
  FILE_OPEN_FAILED,
  FILE_READ_FAILED,
  FILE_WRITE_FAILED,
};

class FilzaArduino {
public:
  FilzaArduino(const char *path, const char *filename);
  ~FilzaArduino();
  
  bool exists();
  bool remove();
  bool open(uint8_t mode);
  void close();
  
  void save(float value);
  void save(const String &value);
  
  float readFloat();
  String readString();
  
  void writeLine(const String &line);
  String readLine();
  
  void writeBytes(const uint8_t *buffer, size_t size);
  size_t readBytes(uint8_t *buffer, size_t size);
  
  void appendLine(const String &line);
  
  void move(const char *newPath);
  void rename(const char *newName);
  
  bool createDirectory(const char *path);
  bool removeDirectory(const char *path);
  
  void listDirectory(const char *dirname, int numTabs = 0);
  
  void changeDirectory(const char *path);
  
  size_t getFileSize(const char *filename);
  
  uint32_t calculateChecksum(const char *filename);
  
  String getFileType(const char *filename);


  uint32_t getTimestamp(const char *filename);
  void setTimestamp(const char *filename, uint32_t timestamp);

private:
  File file;
  const char *path;
  const char *filename;
  
  void debugPrint(const char *message);
};

#endif // FILZA_ARDUINO_H
