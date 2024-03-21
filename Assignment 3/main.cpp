#include <iostream>
using namespace std;

template<typename itemType>
struct Node {
	itemType data;
	Node<itemType>* next = nullptr;

	// Default constructor
	Node(const itemType& item) 
		: data(item), next(nullptr) {}
};

template<typename itemType>
class Queue {
private:
	Node<itemType>* tail;
	Node<itemType>* front;
	int num_items;

public:
	// Constructor function
	Queue(Node<itemType>* tail = nullptr, Node<itemType>* front = nullptr, int num_items = 0) 
		: tail(tail), front(front), num_items(num_items) {};

	/*
	Print function -- this function prints out the contents of the queue
	*/
	void print() {
		// If the queue is empty...
		if (tail == nullptr) {
			cout << "The queue is empty." << endl;
		}
		// If the queue has exactly one node...
		else if (tail == front) {
			cout << "Queue: " << tail->data << " (1 Item)" << endl;
		}
		// The queue has more than one node.
		else {
			cout << "Queue: ";
			Node<itemType>* currentNode = tail;
			while (currentNode != front) {
				cout << currentNode->data << ", ";
				currentNode = currentNode->next;
			}
			cout << currentNode->data << " (" << num_items << " items)" << endl;
		}
	}

	/*
	Push function -- this function pushes a node to the tail of the queue
	@ arg item: Item being pushed to the tail-end of the queue.
	*/
	void push(itemType item) {
		Node<itemType>* newNode = new Node<itemType>(item);
		// If the queue is empty...
		if (tail == nullptr) {
			tail = newNode;
			front = newNode;
			++num_items;
		}
		// If the queue has exactly one item...
		else if (tail == front) {
			newNode->next = front;
			tail = newNode;
			++num_items;
		}
		// The queue has multiple nodes already.
		else {
			newNode->next = tail;
			tail = newNode;
			++num_items;
		}
		cout << "Adding item " << newNode->data << "..." << endl;
	}

	/*
	@ returns the item at the front of the queue (by-reference)
	*/
	itemType& getFront() {
		return front->data;
	}

};

int main() {
	//Variables
	Queue<int> myQueue;

	// Main program
	myQueue.print();
	
	// Push function demonstration
	cout << "Ten items will be added to the queue." << endl << endl;
	for (size_t i = 0; i < 10; ++i) {
		myQueue.push(i * 10);
		myQueue.print();
	}
	cout << endl;

	// Front function demonstration
	cout << "The item at the front of the queue is " << myQueue.getFront();

}