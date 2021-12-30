#include <iostream>
#include "LinkedListInterface.h"
#include <string>
#include <stdexcept>

using namespace std;

template<typename T>
class LL :public LinkedListInterface<T>
{
private:
	struct Node {
		Node() {
			this->value = value;//used to be data
			next = NULL;
		}
		T value;
		Node *next;
		~Node() {
		}
	};
	
	int numberOfNodes;
	Node* head; // points at the "first" object in list

public:

	LL()
	{
		head = NULL;
		numberOfNodes = 0;
	};
	~LL()
	{ 
		//void Must clean up the new stuff you've made with the constructor
		clear(); 
	};

	void print()
	{
		Node* print = head;
		for (int i = 0; i < numberOfNodes; i++) {
			cout << "Node: " << i + 1 << " and it's value: " << print->value << endl;
			print = print->next;
		}
		cout << endl;
	}

	bool dupCheck(Node* x) {//check to see whether the value of the new node is already a value of an existing node
		//cout << "Within the dupCheck function" << endl;
		//print();
		//cout << x->value << " is the value of the Node you passed in" << endl;//You should make a print list function!
		
		Node* find = head;

		while (x->value != find->value && find->next != NULL) {
			find = find->next;
		}
		if (find->value == x->value) {
			//cout << "Such a node already exists" << endl;
			return true;//just returns true if the NODE/value was already created
		}
		else {
			//cout << "No such node exists" << endl;
			return false;//if node is not there and have already iterated through each node, return false
		}
	}
	
	
	void insertHead(T value) {
		//cout << "Within the insertHead function and what we're inserting: " << value << endl;
		//print();
		Node* newNode = new Node();
		newNode->value = value;

		if (numberOfNodes == 0) {
			head = newNode; //Create a head
			head->next = NULL;
			numberOfNodes++;//increment the size by one with new insert
			return;
		}
		else if (numberOfNodes > 0) {
			if (dupCheck(newNode) == true) { 
				delete newNode;
				newNode = NULL;
				return; 
			}//may have to perform clear to reset n.
			else {
				newNode->next = head;//does this and the next line make sense?
				head = newNode;
				numberOfNodes++;
				return;
			}
		}
	}

	/*
	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	void insertTail(T value) {
		//cout << "within the insertTail function and what we're inserting: " << value << endl;
		//print();
		Node* n = head;
		Node* newNode = new Node();
		newNode->value = value; /// assigns the parameter value to the value of the new Node
		
		if (numberOfNodes == 0) {
			//print();
			head = newNode;
			newNode->next = NULL;
			numberOfNodes++;
			return;
		}
		
		if (dupCheck(newNode) == true) { 
			delete newNode;
			newNode = NULL;
			return; 
		}//may have to perform clear to reset n.
		
		while (n->next != NULL) {//the way to get to the 
			n = n->next;
		}
		if (n->next == NULL) {
			n->next = newNode;//n->next was pointing at null. Not it points to the new Node we created.
			newNode->next = NULL;//Our new node now points at NULL, as ending Nodes do
			numberOfNodes++;//When successfully adding, we must increase the size
			return;
		}
	}

	/*
	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	void insertAfter(T value, T insertionNode) {
		//want a value to equal insertion node to insert BUT don't want value to equal another value or we'll delete new node
		//cout << "Within the insertAfter function\nwhat we're inserting: " << value << " and the value under search is: "  << insertionNode << endl;
		//print();
		Node* newNode = new Node();
		newNode->value = value;
		
//		cout << "3" << endl;

		if (dupCheck(newNode) == true) {
			delete newNode;
			newNode = NULL;
			return; 
		}
		Node* n = head;
		while (n->value != insertionNode && n->next != NULL) {
			n = n->next;
		}
		
		if (n->value != insertionNode) {
			delete newNode;
			newNode = NULL;
			return;
		} 
		if (n->value == insertionNode && n->next != NULL) {
			newNode->next = n->next;
			n->next = newNode;
			numberOfNodes++;
			return;
		}
		if (n->next == NULL && n->value == insertionNode) {// i think this is unnecessary
			newNode->next = NULL;
			n->next = newNode;
			numberOfNodes++;
			return;
		}
		
	}

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	//This doesn't work when index == 0; check the boundary conditions
	void remove(T value) {
		//cout << "Within the remove function and what we're removing: " << value << endl;
		
		//print();
		if (numberOfNodes == 0) { 
			//if (numberOfNodes == 0) cout << "THere aRe No NoDEs" << endl;
			return; 
		}//in the case there are no nodes
		Node* pastilan = new Node();
		pastilan->value = value;

		if (dupCheck(pastilan) == false) { 
			delete pastilan;
			pastilan = NULL;
			return; 
		}
		else {
			delete pastilan;
			pastilan = NULL;

			Node* n = head;

			if (numberOfNodes == 1) {
				delete n;
				n = NULL;
				head = NULL;
				numberOfNodes--;
				return;
			}
			if (numberOfNodes >= 2) {
				Node* temp = n->next;

				if (n->value == value /*&& temp != NULL*/) { //When value equals first node and size is greater than 1
					delete n;
					n = NULL;
					head = temp;

					numberOfNodes--;
					return;
				}

				while (temp->value != value && temp->next != NULL) {

					n = n->next;
					temp = temp->next;
				}

				if (temp->value == value && temp->next == NULL) { //covers when temp is the last node

					delete temp;
					temp = NULL;
					numberOfNodes--;
					n->next = NULL;
					return;
				}

				if (temp->value == value && temp->next != NULL) {//covers when temp is not last node
					n->next = temp->next;
					delete temp;
					temp = NULL;
					numberOfNodes--;
					return;
				}
			}
		}

		
	}

	/*
	Remove all nodes from the list.
	*/
	void clear() {//no idea if this was done correctly
		/*
		while (head != NULL) {
			Node* temp = head;
			head = head->next;
			//temp = temp->next;
			delete temp;
			temp = NULL;
			numberOfNodes--;
		}*/
	
		while (numberOfNodes > 0) {
			remove(head->value);
		}
	}

	/*
	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	T at(int index) {
		
		if (index < 0 || index >= numberOfNodes) {
			
			throw out_of_range(" ");
		}
		else {
			Node* n = head;
			for (int i = 0; i <= index; i++) {
				if (i < index) {
					n = n->next;
				}
				else if (i == index) {
					return n->value;
				}
			}
		}

	}

	/*
	size

	Returns the number of nodes in the list.
	*/
	int size() {
		return numberOfNodes;
	}
	
};