#include "../include/CircularQueue.h"

template <typename T>
CircularQueue<T>::CircularQueue(int capacity)
{
	this->capacity = capacity;
	buffer = std::vector<T>(capacity);
	frontIndex = 0;
	rearIndex = 0;
	currentSize = 0;
}

template <typename T>
bool CircularQueue<T>::isEmpty() const
{
	return currentSize == 0;
}

template <typename T>
bool CircularQueue<T>::isFull() const
{
	return currentSize == capacity;
}

template <typename T>
size_t CircularQueue<T>::size() const
{
	return currentSize;
}

template <typename T>
void CircularQueue<T>::enqueue(const T& element)
{
	if (capacity > currentSize)
	{
		buffer[rearIndex] = element;
		rearIndex = ++rearIndex % capacity;
		currentSize++;
	}
}

template <typename T>
void CircularQueue<T>::dequeue()
{
	if (currentSize > 0)
	{
		frontIndex = ++frontIndex % capacity;
		currentSize--;
	}
}

template <typename T>
T& CircularQueue<T>::front()
{
	return buffer[frontIndex];
}

template <typename T>
const T& CircularQueue<T>::front() const
{
	return buffer[frontIndex];
}