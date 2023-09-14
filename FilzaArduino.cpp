#include "FilzaArduino.h"

FilzaArduino::FilzaArduino(const char *path, const char *filename) {
  this->path = path;
  this->filename = filename;
  debugPrint("File object created.");
}

FilzaArduino::~FilzaArduino() {
  if (this->file) {
    this->file.close();
    debugPrint("File closed.");
  }
}

bool FilzaArduino::exists() {
  bool fileExists = SD.exists(this->filename);
  debugPrint(fileExists ? "File exists." : "File does not exist.");
  return fileExists;
}

bool FilzaArduino::remove() {
  bool fileRemoved = SD.remove(this->filename);
  debugPrint(fileRemoved ? "File removed." : "Failed to remove file.");
  return fileRemoved;
}

bool FilzaArduino::open(uint8_t mode) {
  this->file = SD.open(this->filename, mode);
  bool fileOpened = this->file;
  debugPrint(fileOpened ? "File opened." : "Failed to open file.");
  return fileOpened;
}

void FilzaArduino::close() {
  if (this->file) {
    this->file.close();
    debugPrint("File closed.");
  }
}

void FilzaArduino::save(float value) {
  if (this->file) {
    this->file.println(value);
    debugPrint("Float value saved.");
  }
}

void FilzaArduino::save(const String &value) {
  if (this->file) {
    this->file.println(value);
    debugPrint("String value saved.");
  }
}

float FilzaArduino::readFloat() {
  if (this->file) {
    float value = this->file.parseFloat();
    debugPrint("Float value read.");
    return value;
  }
  debugPrint("Failed to read float value.");
  return -1; // Return a default value or error code
}

String FilzaArduino::readString() {
  if (this->file) {
    String value = this->file.readStringUntil('\n');
    debugPrint("String value read.");
    return value;
  }
  debugPrint("Failed to read string value.");
  return String(""); // Return a default value or error code
}

void FilzaArduino::writeLine(const String &line) {
  if (this->file) {
    this->file.println(line);
    debugPrint("Line written to file.");
  }
}

String FilzaArduino::readLine() {
  if (this->file) {
    String line = this->file.readStringUntil('\n');
    debugPrint("Line read from file.");
    return line;
  }
  debugPrint("Failed to read line from file.");
  return String(""); // Return a default value or error code
}

void FilzaArduino::writeBytes(const uint8_t *buffer, size_t size) {
  if (this->file) {
    this->file.write(buffer, size);
    debugPrint("Bytes written to file.");
  }
}

size_t FilzaArduino::readBytes(uint8_t *buffer, size_t size) {
  if (this->file) {
    size_t bytesRead = this->file.read(buffer, size);
    debugPrint("Bytes read from file.");
    return bytesRead;
  }
  debugPrint("Failed to read bytes from file.");
  return -1; // Return a default value or error code
}

void FilzaArduino::appendLine(const String &line) {
   if (open(FILE_WRITE)) { // Open the file in write mode
     writeLine(line); // Write the line to the file
     close(); // Close the file
     debugPrint("Line appended to file.");
   } else {
     debugPrint("Failed to append line to file.");
   }
}

void FilzaArduino::move(const char *newPath) {
   if (!SD.exists(newPath)) { // Check if the new path exists
     File newFile = SD.open(newPath, FILE_WRITE); // Create a new file at the new path

     open(FILE_READ); // Open the current file in read mode

     // Copy the contents of the current file to the new file
     while (available()) {
       newFile.write(read());
     }

     close(); // Close the current file
     newFile.close(); // Close the new file

     remove(); // Remove the current file

     this->path = newPath; // Update the path to the new path
     debugPrint("File moved successfully.");
   } else {
     debugPrint("Failed to move file. New path already exists.");
   }
}

void FilzaArduino::rename(const char *newName) {
   const char *oldName = this->filename; // Save the old name

   this->filename = newName; // Update the filename to the new name

   move(oldName); // Move the file to the old name (which effectively renames it)
   debugPrint("File renamed successfully.");
}

void FilzaArduino::debugPrint(const char *message) {
   Serial.println(message); // Print the debug message to the serial monitor
}
