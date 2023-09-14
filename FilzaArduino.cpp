#include "FilzaArduino.h"
enum ErrorCode {
  SUCCESS = 0,
  FILE_NOT_FOUND,
  FILE_OPEN_FAILED,
  FILE_READ_FAILED,
  FILE_WRITE_FAILED,
  // Add more error codes as needed
};

FilzaArduino::FilzaArduino(const char *path, const char *filename) {
  this->path = path;
  this->filename = filename;
}

FilzaArduino::~FilzaArduino() {
  if (this->file) {
    this->file.close();
    debugPrint("File closed.");
  }
}

bool FilzaArduino::exists() {
  return SD.exists(this->filename);
}

bool FilzaArduino::remove() {
  return SD.remove(this->filename);
}

bool FilzaArduino::open(uint8_t mode) {
  this->file = SD.open(this->filename, mode);
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
     return this->file.parseFloat();
   }
   return -1; // Return a default value or error code
}

String FilzaArduino::readString() {
   if (this->file) {
     return this->file.readStringUntil('\n');
   }
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
     return this->file.readStringUntil('\n');
   }
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
     return this->file.read(buffer, size);
   }
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

bool FilzaArduino::createDirectory(const char *path) {
  if (SD.exists(path)) {
    debugPrint("Directory already exists.");
    return false;
  }
  bool created = SD.mkdir(path);
  if (created) {
    debugPrint("Directory created successfully.");
  } else {
    debugPrint("Failed to create directory.");
  }
  return created;
}

bool FilzaArduino::removeDirectory(const char *path) {
  if (!SD.exists(path)) {
    debugPrint("Directory does not exist.");
    return false;
  }
  bool removed = SD.rmdir(path);
  if (removed) {
    debugPrint("Directory removed successfully.");
  } else {
    debugPrint("Failed to remove directory.");
  }
  return removed;
}

void FilzaArduino::listDirectory(const char *dirname, int numTabs) {
  File dir = SD.open(dirname);
  if (!dir) {
    debugPrint("Failed to open directory.");
    return;
  }
  
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // No more files
      break;
    }
    
    for (int i = 0; i < numTabs; i++) {
      Serial.print('\t');   // we'll have a nice indentation
    }
    
    // Print the name
    Serial.print(entry.name());
    
    // Recurse for directories, otherwise print the file size
    if (entry.isDirectory()) {
      Serial.println("/");
      listDirectory(entry.name(), numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    
    entry.close();
  }
  
  dir.close();
}


void FilzaArduino::changeDirectory(const char *path) {
  if (SD.exists(path)) {
    this->path = path;
    debugPrint("Changed directory successfully.");
  } else {
    debugPrint("Failed to change directory. Directory does not exist.");
  }
}

size_t FilzaArduino::getFileSize(const char *filename) {
  if (!SD.exists(filename)) {
    debugPrint("File does not exist.");
    return -1;
  }
  
  File file = SD.open(filename, FILE_READ);
  if (!file) {
    debugPrint("Failed to open file.");
    return -1;
  }
  
  size_t fileSize = file.size();
  file.close();
  
  debugPrint("File size obtained successfully.");
  
  return fileSize;
}
void FilzaArduino::listDirectory(const char *dirname, int numTabs) {
  File dir = SD.open(dirname);
  if (!dir) {
    debugPrint("Failed to open directory.");
    return;
  }
  
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // No more files
      break;
    }
    
    for (int i = 0; i < numTabs; i++) {
      Serial.print('\t');   // we'll have a nice indentation
    }
    
    // Print the name
    Serial.print(entry.name());
    
    // Recurse for directories, otherwise print the file size
    if (entry.isDirectory()) {
      Serial.println("/");
      listDirectory(entry.name(), numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    
    entry.close();
  }
  
  dir.close();
}

#include <CRC32.h>

uint32_t FilzaArduino::calculateChecksum(const char *filename) {
  if (!SD.exists(filename)) {
    debugPrint("File does not exist.");
    return 0;
  }
  
  File file = SD.open(filename, FILE_READ);
  if (!file) {
    debugPrint("Failed to open file.");
    return 0;
  }
  
  CRC32 crc;
  
  while (file.available()) {
    crc.update(file.read());
  }
  
  file.close();
  
  debugPrint("Checksum calculated successfully.");
  
  return crc.finalize();
}
String FilzaArduino::getFileType(const char *filename) {
  String file = String(filename);
  int dotIndex = file.lastIndexOf('.');
  
  if (dotIndex == -1) {
    debugPrint("Unknown file type.");
    return "unknown";
  }
  
  String extension = file.substring(dotIndex + 1);
  
  if (extension.equalsIgnoreCase("txt")) {
    debugPrint("Text file identified.");
    return "text";
  } else if (extension.equalsIgnoreCase("jpg") || extension.equalsIgnoreCase("png")) {
    debugPrint("Image file identified.");
    return "image";
  } else if (extension.equalsIgnoreCase("bin")) {
    debugPrint("Binary file identified.");
    return "binary";
  } else {
    debugPrint("Unknown file type.");
    return "unknown";
  }
}
