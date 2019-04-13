#include <iostream>
#include <string>
#include <cstdlib>
#include "DoublyLinkedListGenericNew.h"

using namespace std;

template <class T>
class QueueGeneric
{
public:
	QueueGeneric(); //default constructor
	//QueueGeneric(int maxSize); //overloaded constructor
	~QueueGeneric(); //destructor

	void insert(T d); //aka enqueue()
	T remove(); //aka dequeue();
	T front(); //aka peek();

	int getSize(); //return the size of the queue
	//bool isFull(); //returns true if the queue is full
	bool isEmpty(); //returns true if the queue is empty

	//int head;
	//int tail;
	int numElements;
	//int mSize;

    DoublyLinkedListGeneric<T> *LL;

	//char *myQueue;
};

template <class T>
QueueGeneric<T>::QueueGeneric()
{
	LL = new DoublyLinkedListGeneric<T>();
	numElements = 0;
	//head = 0;
	//tail = 0;
	//numElements = 0;
	//mSize = 0;
}

/*
template <class T>
QueueGeneric<T>::QueueGeneric(int maxSize)
{
	LL = new DoublyLinkedListGeneric<T>(maxSize);
	//mSize = maxSize;
	//head = 0;
	//tail = -1;
	//numElements = 0;
}
*/

template <class T>
QueueGeneric<T>::~QueueGeneric()
{
	delete LL;
}

template <class T>
void QueueGeneric<T>::insert(T d)
{
	LL->insertBack(d);
	numElements++;
}

template <class T>
T QueueGeneric<T>::remove()
{
    if(numElements == 0)
    {
        cout << "The queue is empty. Cannot remove an element. Exiting program." << endl;
        exit(1);
    }

	numElements = numElements - 1;

	T c = LL->removeFront();

	return c;
}

template <class T>
T QueueGeneric<T>::front()
{
	if(numElements == 0)
	{
		cout << "Empty queue. Nothing to return!" << endl;
		exit(1);
	}
	T frontObject = LL->getFront();
	return frontObject;
}

template <class T>
bool QueueGeneric<T>::isEmpty()
{
	return (numElements == 0);
}

template <class T>
int QueueGeneric<T>::getSize()
{
	return numElements;
}
