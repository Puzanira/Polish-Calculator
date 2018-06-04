#ifndef CQUEUE_H
#define CQUEUE_H

#include <assert.h>
 
// очередь с динамическим зацикленным буфером

template <class T>
class CQueue {
public:

    explicit CQueue( int size = 20 );

    ~CQueue() { delete[] buffer; }
 
    // Добавление элемента в конец очереди.
    void Push( T data );
    // Извлечение элемента. Если очередь пуста, assert.
    T Pop();
    // Пуста ли очередь.
    bool IsEmpty() const { return head == tail; }

private:

    void grow();
    T *buffer;
    int bufferSize;
    int head;
    int tail;
};

template <class T>
CQueue<T>::CQueue( int size) : 
    bufferSize(size),
    head(0),
    tail(0) 
{
    buffer = new T[bufferSize];
}

template <class T>
void CQueue<T>::grow()
{
    int new_bufferSize = bufferSize * 2;
    T *new_buffer = new T[new_bufferSize];
    int new_tail = 0;
    
    if (head > tail) 
    {
        for (int i = head; i < bufferSize; i++)
        {
            new_buffer[new_tail++] = buffer[i];
        }
        for (int i = 0; i < tail; i++)
        {
            new_buffer[new_tail++] = buffer[i];
        }
    }
    else
    {
        for (int i = head; i < tail; i++)
        {
            new_buffer[new_tail++] = buffer[i];
        }
    }
    delete[] buffer;
    buffer = new_buffer;
    bufferSize = new_bufferSize;
    head = 0;
    tail = new_tail;

}

template <class T>
void CQueue<T>::Push( T data )
{
    if ( (tail + 1) % bufferSize == head)
    {
        grow();
    }
    buffer[tail] = data;
    tail = (tail + 1) % bufferSize;
}

template <class T>
T CQueue<T>::Pop()
{
    assert( head != tail );
    T data = buffer[head];
    head = (head + 1) % bufferSize;
 
    return data;
}

#endif //CQUEUE_H

