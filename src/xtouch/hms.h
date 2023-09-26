#ifndef _XLCD_HMS_QUEUE
#define _XLCD_HMS_QUEUE

#include "types.h"

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

#endif