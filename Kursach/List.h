#ifndef list_H
#define list_H

using namespace std;

#include <iostream>
#include <exception>

template<typename T>
class List
{
public:
	List();
	~List();

	void pop_front(); // First list element removal
	void pop_back(); //Last list element removal
	void push_back(T data); // New list element at the end
	void push_front(T data); // New list element ar the beggining
	void insert(T value, int index); // New list element at certain position
	void clear(); // Full list clearance, also used in destructor
	void removeAt(int index); // Remove certain list element
	unsigned int GetSize() // Get current list size
	{
		return Size;
	}
	T& operator[] (const int index); // Get certain list element
	void print_to_console(); // Print all list elements to console with \n
	void set(T value, int index); // Set new certain list element value
	bool isEmpty(); // Check if List is empty
	bool contains(T search);


	int find_last(List<T>& search); // Compare 2 lists. Get first element (bigger list, not in ()) index where match starts, or get -1 if there is no match. 
private:


	template<typename T>
	class Node
	{
	public:
		Node* pNext; // next element pointer
		Node* pPrevious; // previous element pointer
		T data;

		Node(T data = T(), Node* pNext = nullptr, Node* pPrevious = nullptr) // by default, next and previous pointers are nullptr
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrevious = pPrevious;
		}
	};
	int Size; // contains current Size of the lsit
	Node<T>* head; // A node used to contain head of the list
	Node<T>* tail; // A node used to contain tail of the list. Can be the same node as head
};


template<typename T>
List<T>::List()// constructor, used for list creation
{
	Size = 0; // when just created, list size is always 0
	head = nullptr;// by default, next and previous pointers are nullptr
	tail = nullptr;
}


template<typename T>
List<T>::~List() // destructor, used for list removal
{
	clear();
}


template<typename T>
void List<T>::pop_front()
{
	if (Size == 0)
		throw exception("List is empty, pop_front() didn't work");
	Node<T>* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}


template<typename T>
void List<T>::pop_back()
{
	if (Size == 0)
		throw exception("List is empty, pop_back() didn't work");
	removeAt(Size - 1);
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
		tail = head;
	}
	else
	{
		Node<T>* temp = new Node<T>(data);
		temp->pNext = nullptr;
		temp->pPrevious = tail;
		tail->pNext = temp;
		tail = temp;
	}
	Size++;
}


template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
	if (Size == 1)
		tail = head;
}


template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
		push_front(data);
	else
	{
		if (index < 0)
			throw exception("Index (insert(data, index)) is negative");
		if (index > Size)
			throw exception("Index (insert(data, index)) is bigger than list size + 1");
		Node<T>* previous = this->head;
		Node<T>* nex = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
			nex = nex->pNext;
		}
		Node<T>* addNode = new Node<T>(data, previous->pNext);
		previous->pNext = addNode;

		nex = nex->pNext;
		nex->pPrevious = previous;
		if (index != Size)
		{
			previous = previous->pNext;
			nex = nex->pNext;
			nex->pPrevious = previous;
		}
		else
			tail = nex;

		Size++;
	}
}


template<typename T>
void List<T>::clear()
{
	while (Size)
		pop_front();
}


template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
		pop_front();
	else
	{
		if (index < 0)
			throw exception("Index (removeAt(index)) is negative");
		if (index >= Size)
			throw exception("Index (removeAt(index)) is bigger than list size");
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->pNext;
		Node<T>* toDelete = previous->pNext;
		if (index != Size - 1)
		{
			Node<T>* nex = toDelete->pNext;
			nex->pPrevious = previous;
		}
		else
			tail = previous;
		previous->pNext = toDelete->pNext;
		delete toDelete;
		Size--;
	}
}


template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
			return current->data;
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void List<T>::print_to_console()
{
	Node<T>* current = this->head;
	if (Size == 0)
		cout << "List is empty";
	else
		while (current != nullptr)
		{
			cout << current->data << endl;
			current = current->pNext;
		}
}

template<typename T>
void List<T>::set(T data, int index)
{
	if (index < 0)
		throw exception("Index (set(data, index)) is negative");
	if (index >= Size)
		throw exception("Index (set(data, index)) is bigger than list size");
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
			break;
		current = current->pNext;
		counter++;
	}

	current->data = data;

}

template<typename T>
bool List<T>::isEmpty()
{
	if (Size == 0)
		return true;
	else
		return false;
}

template<typename T>
bool List<T>::contains(T search)
{
	Node<T>* temp = head;
	for (unsigned int i = 0; i < GetSize(); ++i)
		if (temp->data == search)
			return true;
	return false;
}

template<typename T>
int List<T>::find_last(List<T>& search)
{
	if (Size == 0)
		throw exception("Main list contains 0 items, findlast() didn't work");
	if (search.GetSize() > Size)
		throw exception("Included list is bigger than main one, findlast() didn't work");
	if (search.GetSize() == 0)
		throw exception("Included list contains 0 items, findlast() didn't work");
	Node<T>* field = this->tail;
	int steps = 0;
	bool match = false;
	for (int i = Size - 1; i >= 0; i--)
	{
		if (field->data == search[search.GetSize() - 1])
		{
			steps = 0;
			for (int j = search.GetSize() - 2; j >= 0; j--)
			{
				steps++;
				field = field->pPrevious;
				if (field->data != search[j])
				{
					match = false;
					for (int k = 0; k < steps; k++)
						field = field->pNext;
					steps = 0;
					break;
				}
				if (j == 0)
					match = true;
			}
			if ((match == true) || (search.GetSize() == 1))
			{
				return (i - steps);
			}
		}
		field = field->pPrevious;
	}
	return -1;
}

#endif list_H