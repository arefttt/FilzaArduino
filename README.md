# FilzaArduino Library

## Overview
FilzaArduino is a robust and user-friendly library designed to simplify file operations on an SD card when using an Arduino. It provides a high-level, intuitive interface for creating, reading, and writing files, making it significantly easier to work with files on an SD card.

## Key Features
- **File Existence Verification**: Efficiently checks if a file exists on the SD card.
- **File Deletion**: Allows for the removal of a file from the SD card.
- **File Opening and Closing**: Facilitates opening a file for reading or writing, and closing it after operations are completed.
- **Data Writing**: Supports writing various data types to a file. This can be a float value, a string (line), or bytes.
- **Data Reading**: Enables reading various data types from a file. This can be a float value, a string (line), or bytes.

## Comparison with Other Libraries
While there are other SD card wrapper libraries available such as the [Arduino SD library] and [Adafruit's SD library], FilzaArduino stands out due to its user-friendly interface and additional features like checking if a file exists and removing a file. However, it's important to note that these other libraries may offer more advanced features not currently included in FilzaArduino.

## Usage Example
Here's an enhanced example of how to use the FilzaArduino library:

```cpp
#include "FilzaArduino.h"

void setup() {
  Serial.begin(9600);

  // Create a FilzaArduino object for a file named "data.aff" in the "records" directory
  FilzaArduino handler("/records", "data.aff");

  // Check if the file exists
  if (!handler.exists()) {
    Serial.println("File does not exist.");
    return;
  }

  // Write some lines to the file
  handler.writeLine("Temperature,Humidity");
  handler.writeLine("25.6,40");
  handler.writeLine("26.1,38");
  
  Serial.println("Data written to file.");
}

void loop() {
  // Nothing to do here
}
```

In this example, we first check if the file exists. If it does, we write some lines to it. This could represent sensor data like temperature and humidity readings.

## Future Enhancements
We're constantly working on improving FilzaArduino and adding new features. Here are some enhancements we're considering for future updates:
- Support for additional data types for reading and writing.
- Append mode for adding data to an existing file without overwriting it.
- Methods for moving and renaming files.
- More advanced error handling and reporting.

We value feedback from our users. If you have any suggestions or feature requests, please feel free to share them with us!
