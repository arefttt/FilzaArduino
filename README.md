# FilzaArduino Library

The FilzaArduino library is a powerful and flexible library for working with files and directories on an SD card using an Arduino. It provides a high-level, easy-to-use API for creating, reading, writing, moving, and deleting files, as well as creating, listing, and removing directories.

## Features

The FilzaArduino library includes the following features:

- File Operations: Open, close, read, write, move, rename, and delete files.
- Directory Operations: Create, list, and remove directories.
- File Information: Get the size of a file and calculate its checksum.
- Timestamps: Get and set the creation, access, and modification timestamps of files.
- Debugging: Print debug messages to the serial monitor.

## Differences from the Original SD Library

While the original SD library provides basic functionality for working with files on an SD card, the FilzaArduino library extends this functionality with additional features and improvements:

- **Error Handling**: The FilzaArduino library includes an `ErrorCode` enum for error handling. This makes it easier to identify and handle errors in your code.
- **Debugging**: The FilzaArduino library includes a `debugPrint` method for printing debug messages to the serial monitor. This can be very helpful for troubleshooting issues with your code.
- **File Checksums**: The FilzaArduino library includes a `calculateChecksum` method for calculating the checksum of a file. This can be useful for verifying the integrity of a file.
- **Timestamps**: The FilzaArduino library includes methods to get and set the creation, access, and modification timestamps of files. This can be useful for tracking when files were created or last modified.

## Example

Here's an example of how to use the FilzaArduino library:

```cpp
#include "FilzaArduino.h"

// Create a new FilzaArduino object
FilzaArduino filza("/path/to/directory", "filename.txt");

// Open the file in write mode
if (filza.open(FILE_WRITE)) {
  // Write some data to the file
  filza.writeLine("Hello, world!");
  
  // Close the file
  filza.close();
}

// Open the file in read mode
if (filza.open(FILE_READ)) {
  // Read a line from the file
  String line = filza.readLine();
  
  // Print the line to the serial monitor
  Serial.println(line);
  
  // Close the file
  filza.close();
}

// Get the creation timestamp of a file
uint32_t timestamp = filza.getTimestamp("filename.txt");

// Print the timestamp to the serial monitor
Serial.println(timestamp);

// Set the creation timestamp of a file
filza.setTimestamp("filename.txt", timestamp);
```

This example demonstrates how to create a new `FilzaArduino` object, open a file in write mode, write some data to the file, close the file, open the file in read mode, read a line from the file, print the line to the serial monitor, close the file again, get the creation timestamp of a file, print the timestamp to the serial monitor, and set the creation timestamp of a file.

## Conclusion

The FilzaArduino library is a powerful tool for working with files on an SD card using an Arduino. Whether you're building a data logger, a music player, or any other project that involves reading or writing files on an SD card, this library can make your life much easier. Give it a try today!

## Filza arduino depends list

The FilzaArduino library depends on the following libraries:

SD Library: This is a standard library included with the Arduino IDE. It provides functions for reading from and writing to SD cards.
SdFat Library: This is a more advanced library for working with SD cards. It provides additional features not found in the standard SD library, such as support for long filenames and the ability to get and set file timestamps.
AESLib Library: This library provides functions for encrypting and decrypting data using AES encryption.
