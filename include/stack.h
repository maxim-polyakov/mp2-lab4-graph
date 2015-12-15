#pragma once
#include "list.h"
using namespace std;


template <class Type>
class Stack
{
private:
	List<Type> *list;
	
	
public:
	Stack();
	Stack(int n);
	Stack(const Stack &s);
	
	
	bool IsFull()const;
	bool IsEmpty()const;

	Type Put();								//взять и удалить верхний элемент
	void Push(Type element);					//добавить элемент
	Type Peek() const;						//посмотреть верхний элемент без удаления


};

template <class Type>
Stack<Type>::Stack()
{
	list = new List<Type>();
}

template <class Type>
Stack<Type>::Stack(const Stack<Type> &s)
{
	this->list = new List<Type>(*(s.list));
}



template<class Type>
bool Stack<Type>::IsEmpty() const {
	return list->getFirst() == 0;
}

template<class Type>
bool Stack<Type>::IsFull()const {
	Node<Type> *tmp;
	try{
		tmp = new Node<Type>;
	}
	catch (...){
		return 1;
	}
	delete tmp;
	return 0;
}

template <class Type>
void Stack<Type>::Push(Type element) {
	if (this->IsFull()) {
		throw ("Стэк переполнен!");
	}
	list->InsertFirst(element);
}

template <class Type>
Type Stack<Type>::Put() {
	if (this->IsEmpty()) {
		throw ("Стэк пуст!");
	}
	Type result = list->getFirst()->key;
	list->erase(result);
	return result;
}

template <class Type>
Type Stack<Type>::Peek() const {
	if (this->IsEmpty()) {
		throw ("Стэк пуст!");
	}
	return list->getFirst()->key;
}



