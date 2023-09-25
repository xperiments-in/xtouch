#ifndef _XLCD_HMS_QUEUE
#define _XLCD_HMS_QUEUE

#include "types.h"
#include "FS.h"
#include "SD.h"

#define HMS_QUEUE_CAPACITY 50

unsigned long long hms_queue[HMS_QUEUE_CAPACITY];
unsigned int frontIndex;
unsigned int rearIndex;
unsigned int queueSize;

bool hms_isQueueEmpty()
{
    return queueSize == 0;
}

void hms_enqueue(unsigned long long value)
{
    if (queueSize >= HMS_QUEUE_CAPACITY)
    {
        // Si la cola está llena, no podemos agregar más elementos
        return;
    }

    hms_queue[rearIndex] = value;
    rearIndex = (rearIndex + 1) % HMS_QUEUE_CAPACITY;
    queueSize++;
}

unsigned long long hms_dequeue()
{
    if (queueSize == 0)
    {
        // Si la cola está vacía, no hay elementos para extraer
        // En este caso, retornamos un valor especial (por ejemplo, 0xFFFFFFFFFFFFFFFF) para indicar un error o un valor no válido.
        // Puedes ajustar este valor según tus necesidades.
        return 0xFFFFFFFFFFFFFFFF;
    }

    unsigned long long frontValue = hms_queue[frontIndex];
    frontIndex = (frontIndex + 1) % HMS_QUEUE_CAPACITY;
    queueSize--;
    return frontValue;
}

int xtouch_hmsdb_getValueSize(const char *fileName)
{
    File file = SD.open(fileName, "r");

    if (!file)
    {
        return -1;
    }
    String sizeString = file.readStringUntil('\n');
    return atoi(sizeString.c_str());
}

int xtouch_hmsdb_getKeyIndex(const char *fileName, const char *searchKey)
{
    // Open the file
    File file = SD.open(fileName, "r");

    if (!file)
    {
        return -1;
    }

    char lineBuffer[32]; // Adjust the buffer size based on your maximum line length
    int lineCount = 0;
    // Read the file line by line and search for the key
    while (file.available())
    {
        // Read characters into the lineBuffer until a newline or buffer full
        size_t bytesRead = file.readBytesUntil('\n', lineBuffer, sizeof(lineBuffer) - 1);
        lineBuffer[bytesRead] = '\0'; // Null-terminate the C-string

        // Check if the line starts with the searchKey
        if (strncmp(lineBuffer, searchKey, strlen(searchKey)) == 0)
        {
            file.close();
            return lineCount - 1;
        }
        lineCount++;
    }

    file.close();
    return -1;
}

void xtouch_hms_getValueByKey(const char *key)
{
    int lineKey = xtouch_hmsdb_getKeyIndex(xtouch_paths_hms_key_db, key);
    int valueSize = xtouch_hmsdb_getValueSize(xtouch_paths_hms_key_db);

    File xtouch_hms_value_file = SD.open(xtouch_paths_hms_value_db, "r");
    xtouch_hms_value_file.seek((valueSize * lineKey), SeekSet);

    char *valueBuffer = (char *)malloc(valueSize);
    xtouch_hms_value_file.readBytes(valueBuffer, valueSize);
    valueBuffer[valueSize] = '\0';
    xtouch_hms_value_file.close();
}

#endif