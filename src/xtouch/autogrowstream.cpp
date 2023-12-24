#include "autogrowstream.h"
#include <Arduino.h>

#define BUFFER_INCREMENTS 128

// Constructor for XtouchAutoGrowBufferStream
XtouchAutoGrowBufferStream::XtouchAutoGrowBufferStream()
{
    this->_len = 0;
    this->_buffer = (char*)malloc(BUFFER_INCREMENTS); // Allocate initial buffer
}


bool XtouchAutoGrowBufferStream::includes(const char* target) {
  return strstr(this->_buffer, target) != nullptr;
}

// Write a byte to the buffer
size_t XtouchAutoGrowBufferStream::write(uint8_t byte) {
    // Check if there is enough space in the buffer
    if (this->_len + 1 > this->buffer_size) {
        // If not enough space, grow the buffer
        auto tmp = (char*)realloc(this->_buffer, this->buffer_size + BUFFER_INCREMENTS);

        // Check if the buffer growing operation was successful
        if (tmp == NULL) {
            // Print an error message if buffer growth fails due to memory error
            Serial.println("Failed to grow buffer");
            return 0; // Indicate failure to write
        }

        // Update the buffer pointer and size after successful growth
        this->_buffer = tmp;
        this->buffer_size += BUFFER_INCREMENTS;
    }

    // Write the byte to the buffer at the current position
    this->_buffer[this->_len] = byte;

    // Increment the buffer length to reflect the added byte
    this->_len++;

    // Return the number of bytes written (always 1 in this case)
    return 1;
}

// Flush the buffer, resetting its length and potentially shrinking it
void XtouchAutoGrowBufferStream::flush() {
  this->_len=0;
  // Shrink the buffer
  this->_buffer = (char*)realloc(this->_buffer, BUFFER_INCREMENTS);
  this->buffer_size = BUFFER_INCREMENTS;
}

// Dummy read method (not implemented)
int XtouchAutoGrowBufferStream::read() {
  return 0;
}

// Dummy peek method (not implemented)
int XtouchAutoGrowBufferStream::peek() {
  return 0;
}

// Dummy available method (always returns 1)
int XtouchAutoGrowBufferStream::available() {
  return 1;
}
