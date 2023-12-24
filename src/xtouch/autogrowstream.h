#ifndef XtouchAutoGrowBufferStream_h
#define XtouchAutoGrowBufferStream_h

#include <Arduino.h>
#include <Stream.h>

// XtouchAutoGrowBufferStream class definition
class XtouchAutoGrowBufferStream : public Stream
{
private:
   uint16_t _len;        // Current length of data in the buffer
   uint16_t buffer_size; // Size of the buffer
   char* _buffer;        // Buffer pointer

public:
  // Constructor
  XtouchAutoGrowBufferStream();

  // Destructor
  ~XtouchAutoGrowBufferStream() {
    free(this->_buffer); // Free dynamically allocated memory
  }

  // Conversion operators
  operator const uint8_t *() const { return NULL; }
  operator const char *() const { return (const char*)NULL; }

  // Get the current length of data in the buffer
  const uint16_t current_length() const { return _len; }

  // Stream-related methods
  bool listen() { return true; }
  void end() {}
  bool isListening() { return true; }
  int peek();

  // Stream virtual methods
  virtual size_t write(uint8_t byte);
  virtual int read();
  virtual int available();
  virtual void flush();

  // Get the buffer pointer
  const char* get_buffer() const { return _buffer; }
  bool includes(const char* target);

  // Get the buffer as a null-terminated string
  const char* get_string() const { 
    // Null terminate
    _buffer[_len] = '\0';
    return _buffer;
  }

  using Print::write; // Allow write methods from the Print class
};

#endif
