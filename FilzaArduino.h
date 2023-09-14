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
  void save(float value); // Save a float value
  void save(const String &value); // Save a string value
  float readFloat(); // Read a float value
  String readString(); // Read a string value
  void writeLine(const String &line);
  String readLine();
  void writeBytes(const uint8_t *buffer, size_t size);
  size_t readBytes(uint8_t *buffer, size_t size);
  void appendLine(const String &line); // New method for appending a line to the file
  void move(const char *newPath); // New method for moving the file
  void rename(const char *newName); // New method for renaming the file

private:
  const char *path;
  const char *filename;
  File file;

  void debugPrint(const char *message);
};

#endif
