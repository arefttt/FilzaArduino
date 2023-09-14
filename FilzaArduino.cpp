#include "FilzaArduino.h"

// Enable debug mode
#define DEBUG

// Define a macro for debug printing
#ifdef DEBUG
 #define DEBUG_PRINT(x) Serial.println(x)
#else
 #define DEBUG_PRINT(x)
#endif

// Constructor
FilzaArduino::FilzaArduino(const char *path, const char *filename) : path(path), filename(filename), file(NULL) {
  DEBUG_PRINT("FileHandler object created.");
}

// Destructor
FilzaArduino::~FilzaArduino() {
  if (file) {
    file.close();
    DEBUG_PRINT("File closed.");
  }
}

// Check if the file exists
bool FilzaArduino::exists() {
  String fullPath = String(path) + "/" + String(filename);
  bool fileExists = SD.exists(fullPath.c_str());
  DEBUG_PRINT(String("File exists: ") + (fileExists ? "yes" : "no"));
  return fileExists;
}

// Remove the file
bool FilzaArduino::remove() {
  if (exists()) {
    bool removed = SD.remove(filename);
    DEBUG_PRINT(String("File removed: ") + (removed ? "yes" : "no"));
    return removed;
  }
  return false;
}

// Open the file
bool FilzaArduino::open(uint8_t mode) {
  if (file) {
    DEBUG_PRINT("Error: File is already open.");
    return false;
  }
  if (!exists()) {
    DEBUG_PRINT("Error: File does not exist.");
    return false;
  }
  String fullPath = String(path) + "/" + String(filename);
  file = SD.open(fullPath.c_str(), mode);
  if (!file) {
    DEBUG_PRINT("Error: Unable to open file.");
    return false;
  }
  DEBUG_PRINT("File opened successfully.");
  return true;
}

// Close the file
void FilzaArduino::close() {
  if (file) {
    file.close();
    file = NULL;
    DEBUG_PRINT("File closed successfully.");
  }
}

// Save a float value to the file
void FilzaArduino::save(float value) {
  if (open(FILE_WRITE)) {
    file.println(value);
    close();
    DEBUG_PRINT(String("Saved value to file: ") + value);
  }
}

// Read a float value from the file
float FilzaArduino::read() {
  float value = 0.0;
  if (open(FILE_READ)) {
    value = file.parseFloat();
    close();
    DEBUG_PRINT(String("Read value from file: ") + value);
  }
  return value;
}

// Write a line to the file
void FilzaArduino::writeLine(const String &line) {
  if (open(FILE_WRITE)) {
    file.println(line);
    close();
    DEBUG_PRINT(String("Wrote line to file: ") + line);
  }
}

// Read a line from the file
String FilzaArduino::readLine() {
  String line = "";
  if (open(FILE_READ)) {
    line = file.readStringUntil('\n');
    close();
    DEBUG_PRINT(String("Read line from file: ") + line);
  }
  return line;
}

// Write bytes to the file
void FilzaArduino::writeBytes(const uint8_t *buffer, size_t size) {
  if (open(FILE_WRITE)) {
    file.write(buffer, size);
    close();
    DEBUG_PRINT(String("Wrote bytes to file."));
  }
}

// Read bytes from the file
size_t FilzaArduino::readBytes(uint8_t *buffer, size_t size) {
  size_t bytesRead = 0;
  if (open(FILE_READ)) {
    bytesRead = file.read(buffer, size);
    close();
    DEBUG_PRINT(String("Read bytes from file."));
  }
return bytesRead;
}
