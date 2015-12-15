#pragma once
#include <iostream>
using namespace std;

template <class Type>
class Node
{
public:
	Type key;
	Node *pNext;

};

template <class Type>
class List {
private:
	Node<Type>* pFirst;

	Node<Type>* SearchPrev(Type key, Node<Type> *&point);
	void erase(Node<Type> *elem);
public:
	List();
	List(const List &list);
	void Print();
	Node<Type>* Search(Type key);
	void erase(Type key);
	void InsertFirst(Type key);
	void InsertLast(Type key);
	void InsertBefore(Type key, Node<Type> *elem);
	void InsertAfter(Type key, Node<Type> *elem);
	Node<Type>* getFirst();
};

template <class Type>
List<Type>::List()
{
	pFirst = 0;
}

template <class Type>
List<Type>::List(const List<Type> &list)
{
	pFirst = 0;
	Node<Type>* tmp = list.pFirst;
	while (tmp != 0){
		InsertLast(tmp->key);
		tmp = tmp->pNext;
	}
}

template <class Type>
void List<Type>::Print()
{
	if (pFirst == 0) {
		cout << "Нет памяти" << endl;
		return;
	}

	Node<Type> *tmp = pFirst;
	while (tmp != 0)	{
		cout << tmp->key << " ";
		tmp = tmp->pNext;
	}
	cout << std::endl;
}

template <class Type>
Node<Type>* List<Type>::Search(Type key)
{
	if (pFirst == 0) throw "Список пуст";

	Node<Type> *tmp = pFirst;
	while ((tmp != 0) && (tmp->key != key))
		tmp = tmp->pNext;

	if ((tmp == 0) || (tmp->key != key)) return 0;

	return tmp;
}

template <class Type>
Node<Type>* List<Type>::SearchPrev(Type key, Node<Type> *&elem)
{
	if (pFirst == 0) return 0;

	Node<Type> *pPrev = 0;
	elem = pFirst;
	while ((elem != 0) && (elem->key != key)) {
		pPrev = elem;
		elem = elem->pNext;
	}
	if ((elem == 0) || (elem->key != key)) {
		elem = 0;
		pPrev = 0;
		return 0;
	}

	return pPrev;
}

template <class Type>
void List<Type>::erase(Node<Type> *elem)
{
	Node<Type> *point = pFirst;
	Node<Type> *pPrev = 0;
	while ((point != 0) && (point != elem)) {
		pPrev = point;
		point = point->pNext;
	}
	if (point != elem) return;

	if (pPrev == 0) {
		pFirst = pFirst->pNext;
		delete point;
		return;
	}
	pPrev->pNext = point->pNext;
	delete point;
	return;
}

template <class Type>
void List<Type>::erase(Type key)
{
	if (!pFirst) throw "Список пуст";
	Node<Type> *point;
	Node<Type> *pPrev = SearchPrev(key, point);
	if ((pPrev == 0) && (pFirst->key != key))
		throw "Элемент не найден";
	if (pPrev == 0) {
		pFirst = pFirst->pNext;
		delete point;
		return;
	}
	pPrev->pNext = point->pNext;
	delete point;
	return;
}

template <class Type>
void List<Type>::InsertFirst(Type key)
{
	Node<Type> *tmp = new Node<Type>();
	tmp->key = key;
	tmp->pNext = pFirst;
	pFirst = tmp;
}

template <class Type>
void List<Type>::InsertLast(Type key)
{
	Node<Type> *tmp = pFirst;
	if (!pFirst) {
		InsertFirst(key);
		return;
	}
	while (tmp->pNext != 0)
		tmp = tmp->pNext;
	tmp->pNext = new Node<Type>;
	tmp = tmp->pNext;
	tmp->key = key;
	tmp->pNext = 0;
}

template <class Type>
void List<Type>::InsertBefore(Type key, Node<Type> *elem)
{
	if (!pFirst) throw "Список пуст";
	Node<Type> *point;
	Node<Type> *pPrev = searchPrev(key, point);
	if ((pPrev == 0) && (pFirst->key != key))
		throw "Не установлен ключ вставки";

	elem->pNext = point;
	if (pPrev == 0)	{
		pFirst = elem;
		return;
	}
	pPrev->pNext = elem;
}

template <class Type>
void List<Type>::InsertAfter(Type key, Node<Type> *elem)
{
	if (!pFirst) throw "Список пуст";
	Node<Type> *point = search(key);
	if (point == 0)
		throw "Не установлен ключ вставки";
	elem->pNext = point->pNext;
	point->pNext = elem;
}

template <class Type>
Node<Type>* List<Type>::getFirst()
{
	return pFirst;
}
