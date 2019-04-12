//ListNode.h
//Created on: Mar 5, 2019

#include <iostream>

using namespace std;

template <class T>

class DoubleListNodeGeneric
{
	public:
		DoubleListNodeGeneric();
		DoubleListNodeGeneric(T d); //overloaded constructor
		~DoubleListNodeGeneric();

		T data;
		DoubleListNodeGeneric<T> *next;
		DoubleListNodeGeneric<T> *prev;
};

template<class T>
DoubleListNodeGeneric<T>::DoubleListNodeGeneric()
{
	//default constructor

	data = NULL;
	next = NULL;
	prev = NULL;
}

template <class T>
DoubleListNodeGeneric<T>::DoubleListNodeGeneric(T d)
{
	data = d;
	next = NULL; //null ptr
	prev = NULL; //null ptr
}

template <class T>
DoubleListNodeGeneric<T>::~DoubleListNodeGeneric()
{
	next = NULL;
	prev = NULL;
}
