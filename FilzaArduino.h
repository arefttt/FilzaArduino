#ifndef FILZA_ARDUINO_H
#define FILZA_ARDUINO_H

#include <Arduino.h>
#include <SD.h>

class FilzaArduino {
public:
  FilzaArduino(const char *path, const char *filename);
  ~FilzaArduino();

  bool exists();
  bool remove();
  bool open(uint8_t mode);
  void close();
  void save(float value);
  float read();
  void writeLine(const String &line);
  String readLine();
  void writeBytes(const uint8_t *buffer, size_t size);
  size_t readBytes(uint8_t *buffer, size_t size);

private:
  const char *path;
  const char *filename;
  File file;
};

#endif
