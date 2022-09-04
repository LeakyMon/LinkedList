#pragma once
#include <string>
#include <iostream>	
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

template <typename T>

class LinkedList {

public:

	struct Node {

		T data;
		T value;
		Node* next;
		Node* prev;
		

	};



	//PART 1 
	
	//Ways to add information to container
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	//A way to get some information about the container
	unsigned int NodeCount() const;
	//Ways to see data in the container
	void PrintForward() const;
	void PrintReverse() const;
	LinkedList();
	~LinkedList();
	

	//PART 2

	const Node* Head() const;
	Node* Head();

	const Node* Tail() const;
	Node* Tail();

	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);

	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);

	const Node* Find(const T& data) const;
	Node* Find(const T& data);

	void FindAll(vector<Node*>& outData, const T& value) const;

	LinkedList(const LinkedList<T>& list);

	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	void Clear();

	//PART 3

	const Node* Iterate(const T &data, int option) const;
	Node* Iterate(const T& data, int option);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);
	bool operator==(const LinkedList<T>&rhs);
	

	//PART 4

	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	bool RemoveHead();
	const Node* Delete(const Node* node) const;
	Node* Delete(const Node* node);
	bool RemoveTail();

	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	bool isNode();

	


private:

	Node* head;
	Node* tail;
	unsigned int count;

};




//----------BIG 3-----------//



//Constructor
template<typename T>
LinkedList<T>::LinkedList() {


	head = nullptr; //setting the first and end datas of the lst to null, and the number = 0
	tail = nullptr;
	count = 0;

}

//Copy Constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {



	count = 0;
	head = nullptr;
	tail = nullptr;



	for (unsigned int i = 0; i < list.count; i++) {

		const Node* temp = list.GetNode(i);

		AddTail(temp->data);

	}


}

//Assignment Operator
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	//If statements to find the larger container
	if (head != nullptr) {

		while (head->next != nullptr) {

			Node* temp = head->next;
			delete head;
			head = temp;

		}
		delete tail;

	}

	else {

		head = nullptr;
		tail = nullptr;
		count = 0;

	}

	if (count >= rhs.count) { //First is larger

		count = 0;

		for (unsigned int i = 0; i < rhs.count; i++) {

			const Node* temp = rhs.GetNode(i);

			AddTail(temp->data);
		}
	}
	else if (count <= rhs.count) { //Second is larger

		count = 0;

		for (unsigned int i = 0; i < rhs.count; i++) {

			const Node* temp = rhs.GetNode(i);

			AddTail(temp->data);

		}

	}
	return *this;
}





template<typename T>
void LinkedList<T>::AddHead(const T& data) {

	if (head != nullptr) { //Checks if list is empty
		Node* addHead = new Node;
		addHead->data = data;
		Node* tempNode = head; //Temporary node to hold value of current head
		head = addHead;
		head->next = tempNode; //Set the new heads next value to tempNode
		tempNode->prev = head; //Sets the tempNode previous value to the new head
		head->prev = nullptr;

	}
	else { //If list is empty

		Node* addHead = new Node;
		addHead->data = data; //Creating the first node of the list
		head = addHead;
		tail = addHead;
		addHead->next = nullptr;
		addHead->prev = nullptr;
	}
	count++; //Increase count each time function is called
}

template<typename T>
void LinkedList<T>::AddTail(const T& data) {


	if (tail != nullptr) {

		Node* addTail = new Node; //Same concept as head, but must find end of list
		addTail->data = data;
		Node* tempNode = tail;
		tail = addTail;
		tail->prev = tempNode;
		tempNode->next = tail;
		tail->next = nullptr;

	}
	else {

		Node* addTail = new Node; //Same concept as head, but must find end of list
		addTail->data = data;

		head = addTail;
		tail = addTail;

		addTail->next = nullptr;
		addTail->prev = nullptr;

	}
	count++;
}


template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {

	for (unsigned int i = 1; i <= count; i++) {

		//string tempBuffer = data[count - i]; //Set the temporary buffer equal to the data pushed through at i, then call the AddHead function with the tempBuffer parameter
		AddHead(data[count - i]);

	}


}
template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {

	for (unsigned int i = 0; i < count; i++) {

		//string tempBuffer = data[count - i];  //Set the temporary buffer equal to the data pushed through at i, then call the AddTail function with the tempBuffer parameter
		AddTail(data[i]);

	}

}





template<typename T>
void LinkedList<T>::PrintReverse() const {


	Node* Iterator = head;


	while (Iterator->next != nullptr) { //Find the tail first

		Iterator = Iterator->next;

	}

	while (Iterator != nullptr) { //Go from the tail backwards until the tail = nullptr

		cout << Iterator->data << endl;
		Iterator = Iterator->prev;

	}

}

template<typename T>
unsigned int LinkedList<T>::NodeCount() const {

	return count;

}

//PART 2


template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
	Node* temp = head;
	//Node* match;

	for (unsigned int i = 0; i < count; i++) {


		if (temp->data == data) { //if the data is equal return the temporary node


			return temp;

		}

		else if (temp->data != data) { //Iterate until temp->data = match->data

			temp = temp->next;

		}
	}
	return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {

	Node* temp = head;


	for (unsigned int i = 0; i < count; i++) {


		//match->data = data;

		if (temp->data == data) { //if the data is equal return the temporary node


			return temp;

		}

		else if (temp->data != data) { //Iterate until temp->data = match->data

			temp = temp->next;

		}
	}
	return nullptr;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {


	if (head != nullptr) {

		Node* temp = head;

		while (temp != nullptr) {

			//Node* match;


			if (temp->data == value) { //If the temporary node is equal to the value passed by reference, store it in outData vector

				outData.push_back(temp);
				temp = temp->next;

			}
			else {

				temp = temp->next;

			}
		}

	}



}


template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {

	if (index > count || index < 0) {
		throw out_of_range("Index too big");
	}
	else {

		Node* temp = head;
		if (index > 0 && index < count) {

			for (unsigned int i = 0; i < index; i++) {

				temp = temp->next;

			}

			return temp;
		}

		else if (index == 0) {

			//Node* temp = head;

			return temp;

		}

		else if (index == count) {

			Node* temp = tail;
			return temp;


		}

		else {

			return temp;

		}

	}

}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {


	if (index > count || index < 0) {
		throw out_of_range("Index too big");
	}
	else {

		Node* temp = head;
		if (index > 0 && index < count) {

			for (unsigned int i = 0; i < index; i++) {

				temp = temp->next;

			}

			return temp;
		}

		else if (index == 0) {

			//Node* temp = head;

			return temp;

		}

		else if (index == count) {

			Node* temp = tail;
			return temp;


		}

		else {

			return temp;

		}

	}

}


template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {

	Node* temp = GetNode(index);

	return temp->data;


}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index) {

	Node* temp = GetNode(index);

	return temp->data;

}
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
	return this->head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
	return this->head;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
	return this->tail;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
	return this->tail;
}



template <typename T>
void LinkedList<T>::Clear() {

	Node* temp = head;
	Node* buff;
	while (temp != nullptr) {
		buff = temp->next;
		delete temp;
		temp = buff;
	}
	head = nullptr;
	tail = nullptr;
	count = 0;




}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {

	Node* temp = head;

	for (unsigned int i = 0; i < count; i++) {

		if (temp->data == node->prev->data) { //If the temporary node is equal to the value passed by reference, store it in outData vector


			Node* newNode = new Node;
			newNode->data = data;

			newNode->next = node;
			newNode->prev = node->prev;
			node->prev->next = newNode;

			break;

		}
		else {

			temp = temp->next;

		}
	}

}



template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {

	Node* temp = head;

	for (unsigned int i = 0; i < count; i++) {

		if (temp->data == node->data) { //If the temporary node is equal to the value passed by reference, store it in outData vector

			Node* newNode = new Node;
			newNode->data = data;

			newNode->next = node->next;
			newNode->prev = node;
			node->next->prev = newNode;
			node->next = newNode;

			break;
		}
		else {

			temp = temp->next;

		}
	}

}


template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {


	Node* temp = GetNode(index);

	if (temp->data == head->data) {
		AddHead(data);
	}

	else if (temp->data == tail->data) {
		AddTail(data);
	}

	else if (temp->data != tail->data && temp->data != head->data) {

		Node* newNode = new Node;
		newNode->data = data;

		newNode->next = temp;
		newNode->prev = temp->prev;
		temp->prev->next = newNode;
		temp->prev = newNode;

		count++;


	}

}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) {

	if (count != rhs.count) {

		return false;

	}
	else if (count == rhs.count) {

		for (unsigned int i = 0; i < count; i++) {


			Node* temp = GetNode(i);
			const Node* rhsTemp = rhs.GetNode(i);

			if (temp->data != rhsTemp->data) {

				return false;

			}
			else {

				continue;

			}

		}



	}

	return true;
}

//PART 3


template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Iterate(const T& data, int option) const
{
	Node* temp = head;
	if (option == 1) {

		while (temp != nullptr) { //Traverse through list and print data located at the iterator, until it reaches end aka = nullptr

			if (temp->data == data) { //if the data is equal return the temporary node

				while (temp != nullptr) {
					cout << temp->data << endl;
					temp = temp->next;
				}
			}

			else if (temp->data != data) { //Iterate until temp->data = match->data

				temp = temp->next;

			}

			//cout << Iterator->data << endl;
			//Iterator = Iterator->next;
		}
		return temp;
	}
	else if (option == 2) {

		Node* temp = tail;

		while (temp != nullptr) { //Traverse through list and print data located at the iterator, until it reaches end aka = nullptr

			if (temp->data == data) { //if the data is equal return the temporary node

				while (temp != nullptr) {

					cout << temp->data << endl;
					temp = temp->prev;
				}
			}

			else if (temp->data != data) { //Iterate until temp->data = match->data

				temp = temp->prev;

			}

			//cout << Iterator->data << endl;
			//Iterator = Iterator->next;
		}


		return temp;

	}
	return temp;

}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Iterate(const T& data, int option)
{

	Node* temp = head;
	if (option == 1) { //Option decides to either go from head or tail



		while (temp != nullptr) { //Traverse through list and print data located at the iterator, until it reaches end aka = nullptr

			if (temp->data == data) { //if the data is equal return the temporary node

				cout << temp->data << endl;
				temp = temp->next;

			}

			else if (temp->data != data) { //Iterate until temp->data = match->data

				temp = temp->next;

			}

			//cout << Iterator->data << endl;
			//Iterator = Iterator->next;
		}

		return temp;

	}
	else if (option == 2) {

		Node* temp = tail;

		while (temp != nullptr) { //Traverse through list and print data located at the iterator, until it reaches end aka = nullptr

			if (temp->data == data) { //if the data is equal return the temporary node

				cout << temp->data << endl;
				temp = temp->prev;

			}

			else if (temp->data != data) { //Iterate until temp->data = match->data

				temp = temp->prev;

			}

			//cout << Iterator->data << endl;
			//Iterator = Iterator->next;
		}


		return temp;

	}
	return temp;
}


template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
	const Node* temp = node;

	//Find(temp->data);
	Iterate(temp->data, 1);

}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	const Node* temp = node;
	Iterate(temp->data, 2);


}



template<typename T>
bool LinkedList<T>::RemoveHead()
{

	Node* temp = head;

	if (isNode() == true && count == 1) { //If there is only one node 

		delete head;
		head = nullptr;
		tail = nullptr;
		count--;
		return true;


	}

	if (isNode() == false) { //If there are no nodes;


		return false;

	}

	else if (isNode() == true && count > 1) { //If there is more than 1 node

		Node* temp = head->next;
		delete head;
		temp->prev = nullptr;
		head = temp;

		count--;
		return true;


	}
	else {

		return false;
	}

}

template<typename T>
bool LinkedList<T>::RemoveTail()
{
	Node* temp = tail;

	if (isNode() == true && count == 1) { //If there is only one node 

		delete tail;
		head = nullptr;
		tail = nullptr;
		count--;
		return true;


	}


	else if (isNode() == true && count > 1) { //If there is more than one node

		Node* temp = tail->prev;
		delete tail;
		temp->next = nullptr;
		tail = temp;

		count--;
		return true;


	}

	else {

		return false;

	}
}


template<typename T>
unsigned int LinkedList<T>::Remove(const T& data)
{
	unsigned int numRemovals = 0;
	unsigned int index = 0;
	Node* Iterator = head;


	while (Iterator != nullptr) {
		//Traverse through list and print data located at the iterator, until it reaches end aka = nullptr

		if (Iterator->data == data) { //if the data is equal return the temporary node

			Iterator = Iterator->next;
			RemoveAt(index);
			numRemovals++;

		}

		else if (Iterator->data != data) { //Iterate until temp->data the data passed in

			Iterator = Iterator->next;
			index++;
		}

	}
	return numRemovals;
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
	Node* temp = head;

	if (isNode() == true && count < index) { //If there is at least 1 node, but the index is too large.

		return false;

	}
	else if (isNode() == true && count > index) { //If there is a node and the index is in range

		while (temp != nullptr) {

			if (temp->data == GetNode(index)->data) { //If temp = the node at the index


				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				count--;
				return true;



			}

			else {

				temp = temp->next; //iterate


			}

		}


	}

	return false;
}

template<typename T>
bool LinkedList<T>::isNode() //Function to call to see if there are nodes
{

	if (count > 0) {

		return true;

	}
	else if (count == 0) {

		return false;

	}


}



//Destructor
template<typename T>
LinkedList<T>::~LinkedList() { //Iteratre through and delete all nodes, stack overflow reference
	Clear();
	//delete tail;




}


template<typename T>
void LinkedList<T>::PrintForward() const {

	Node* Iterator = head;

	while (Iterator != nullptr) { //Traverse through list and print data located at the iterator, until it reaches end aka = nullptr


		cout << Iterator->data << endl;
		Iterator = Iterator->next;
	}

}

