#include <iostream>
#include "DoubleListNodeGeneric.h"

using namespace std;

template <class T>

//LinkedList Class(Single Linked List)
class DoublyLinkedListGeneric
{
	public:
		DoublyLinkedListGeneric();
		DoublyLinkedListGeneric(int maxSize);
		virtual ~DoublyLinkedListGeneric();
		void insertFront(T d);
		T removeFront();
		void insertBack(T d);
		T removeBack();
		int getPos(int pos);
		int deletePos(int pos); //delete from any position within the LinkedList
		void printList();
		T getFront(); //get the front element
		T getBack(); //get the back element
		int remove(T key);
		int removeLast(T d);
		int find(T d); //search method
		int findLast (T d);
		bool isEmpty();
		unsigned int getSize();

	private:
		DoubleListNodeGeneric<T> *front;
		DoubleListNodeGeneric<T> *back;
		unsigned int size;
};

template <class T>
DoublyLinkedListGeneric<T>::DoublyLinkedListGeneric()
{
	front = NULL;
	back = NULL;
	size = 0;
}

template <class T>
DoublyLinkedListGeneric<T>::DoublyLinkedListGeneric(int maxSize)
{
	front == NULL;
	back == NULL;
	size = maxSize;
}

template <class T>
DoublyLinkedListGeneric<T>::~DoublyLinkedListGeneric()
{
	DoubleListNodeGeneric<T> *curr = front;
	while(curr->next != NULL)
	{
		curr = curr->next;
		delete curr->prev;
	}
	delete curr;
}

template <class T>
unsigned int DoublyLinkedListGeneric<T>::getSize()
{
	return size;
}

template <class T>
void DoublyLinkedListGeneric<T>::printList()
{
	if(size == 0)
	{
		cout << "[]" << endl;
		return;
	}
	DoubleListNodeGeneric<T> *curr = front;
	cout << "[";
	while(curr->next != NULL)
	{
		cout << curr->data << ", ";
		curr = curr->next;
	}
	cout << curr->data << "]" << endl;
}

template <class T>
void DoublyLinkedListGeneric<T>::insertFront(T d)
{
	DoubleListNodeGeneric<T> *node;

	if(size == 0)
	{
		front = node;
		back = node;
	}
	else
	{
		node->next = front;
		front->prev = node;
		front = node;
	}
	size++;
}

template <class T>
T DoublyLinkedListGeneric<T>::removeFront()
{
	T temp = front->data;
	DoubleListNodeGeneric<T> *ft = front;
	front = front->next;
	ft->next = NULL;
	delete ft;
	front->prev = NULL;
	size--;
	return temp;
}

template <class T>
void DoublyLinkedListGeneric<T>::insertBack(T d)
{
	DoubleListNodeGeneric<T> *node;

	if(size == 0)
	{
		back = node;
		front = node;
	}

	else
	{
		node->next = NULL;
		node->prev = back;
		back = node;
	}
	size++;
}

template <class T>
T DoublyLinkedListGeneric<T>::removeBack()
{
	T temp = back->data;
	DoubleListNodeGeneric<T> *bk = back;
	back = back->prev;
	bk->prev = NULL;
	delete bk;
	back->next = NULL;
	size--;
	return temp;
}

//return the front numElements
template<class T>
T DoublyLinkedListGeneric<T>::getFront()
{
	return front->data;
}

template<class T>
T DoublyLinkedListGeneric<T>::getBack()
{
	return back->data;
}

//return value if it exists
template <class T>
int DoublyLinkedListGeneric<T>::find(T d) //AKA search()
{
	int idx = -1;
	DoubleListNodeGeneric<T> *curr = front;

	while(curr != NULL)
	{
		++idx;
		if(curr->data == d)
		{
			break;
		}
		else
		{
			curr = curr->next;
		}
	}

	if(curr == NULL)
	{
		idx = -1;
	}

	return idx;
}

template <class T>
int DoublyLinkedListGeneric<T>::findLast(T d)
{
    DoubleListNodeGeneric<T> *curr = back;
    int index = size;

    while(curr != nullptr)
	{
        index--;
        if(curr->data == d)
		{
            break;
        }
        else
		{
            curr = curr->prev;
        }
    }

    if(curr == NULL)
	{
        index = -1;
    }

    return index;
}

template <class T>
bool DoublyLinkedListGeneric<T>::isEmpty()
{
	return size == 0;
}

template <class T>
int DoublyLinkedListGeneric<T>::remove(T d)
{
	int pos = find(d);
	return deletePos(pos);
}

template <class T>
int DoublyLinkedListGeneric<T>::getPos(int pos)
{
	if(pos >= size || pos < 0)
	{
		cerr << "\nLinkedList index out of bounds" << endl;
		exit(1);
	}

	if(pos == 0)
	{
		return front->data;
	}

	else if(pos == size - 1)
	{
		return back->data;
	}

	DoubleListNodeGeneric<T> *curr = front;

	for (int i = 0; i < pos; ++i)
	{
		curr = curr->next;
	}

	return curr->data;
}

template <class T>
int DoublyLinkedListGeneric<T>::deletePos(int pos)
{
	if(pos == 0)
	{
		size--;
		return removeFront();
	}

	else if(pos == size-1)
	{
		size--;
		return removeBack();
	}

	else if(pos >= size || pos < 0)
	{
		cerr << "\n LinkedList index out of bounds" << endl;
		exit(0);
	}

	DoubleListNodeGeneric<T> *atPos = front;
	DoubleListNodeGeneric<T> *beforePos;
	DoubleListNodeGeneric<T> *afterPos;

	//get the atPos, beforePos, and afterPos values at the position we want
	for (int i = 0; i < pos; ++i)
	{
		atPos = atPos->next;
		beforePos = atPos->prev;
		afterPos = atPos->next;
	}

	beforePos->next = afterPos;
	afterPos->prev = beforePos;

	int temp = atPos->data;
	atPos->next = NULL;
	atPos->prev = NULL;
	delete atPos;

	return temp;
}

/*
int DoublyLinkedListGeneric::deletePos(int pos)
{
	int idx = 0;

	while(idx != pos)
	{
		prev = curr;
		curr = curr->next;
		++idx;
	}

	//when we find the correct position, update pointers
	prev->next = curr->next;
	curr->next = null;
	int temp = curr->data;
	delete curr;
	size--;

	return temp;
}
*/

/*
int DoublyLinkedListGeneric::remove(int key)
{
	//could call find() here
	//im going to search manually
	ListNodeDoubly *curr = front;
	//let's look for the value
	while(curr->data != key)
	{
		curr = curr->next;

		if(curr == NULL)
		{
			return NULL;
		}
	}

	//we found our ListNode
	//need to check if it's the front ListNode

	if(curr == front)
	{
		front = curr->next;
	}
	else
	{
		curr->prev->next = curr->next;
	}

	//let's check the back

	if(curr == back)
	{
		back = curr->prev;
	}
	else
	{
		curr->next->prev = curr->prev;
	}

	curr->next = NULL;
	curr->prev = NULL;

	size--;

	return curr;
}
*/
