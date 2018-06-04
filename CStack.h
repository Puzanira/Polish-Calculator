#ifndef CSTACK_H
#define CSTACK_H

#include <cstring>
#include <cassert>

template <class T>
class CStack
{
public: 
	explicit CStack(int _bufferSize);
	~CStack();

	void Push( T a );
	T Pop();

	bool IsEmpty() const { return top == -1; }

private:
	T *buffer;
	int bufferSize;
	int top;

	void grow();
};

template <class T>
CStack<T>::CStack( int _bufferSize )
	: bufferSize( _bufferSize ),
	  top( -1 )
{
	buffer = new T[bufferSize];
}

template <class T>
CStack<T>::~CStack()
{
	delete[] buffer;
}

template <class T>
void CStack<T>::Push( T a )
{
	if ( ++top == bufferSize ) grow();
	buffer[top] = a;
}

template <class T>
T CStack<T>::Pop()
{
	assert( top != -1 );
	return buffer[top--];
}

template <class T>
void CStack<T>::grow()
{
    int new_bufferSize = bufferSize * 2;
    T *new_buffer = new T[new_bufferSize];

    for (int i = 0; i < top; i++)
    {
        new_buffer[i] = buffer[i];
    }

    delete[] buffer;
    buffer = new_buffer;
    bufferSize = new_bufferSize;

}

#endif //CSTACK_H

