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
	@ returns size of the Queue (the number of items in it)
	*/
	int size() {
		return num_items;
	}

	/*
	@ returns true if the Queue is empty and false otherwise
	*/
	bool empty() {
		if (tail == nullptr) {
			return true;
		}
		return false;
	}

	/*
	Print function -- this function prints out the contents of the queue
	*/
	void print() {
		// If the queue is empty...
		if (empty()) {
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
			cout << currentNode->data << " (" << size() << " items)" << endl;
		}
	}

	/*
	Push function -- this function pushes a node to the tail of the queue
	@ arg item: Item being pushed to the tail-end of the queue.
	*/
	void push(itemType item) {
		Node<itemType>* newNode = new Node<itemType>(item);
		// If the queue is empty...
		if (empty()) {
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
	}

	/*
	@ returns the item at the front of the queue (by-reference)
	*/
	itemType& getFront() {
		return front->data;
	}

	/*
	Removes the node at the front of the queue.
	*/
	void pop() {
		// If the Queue is empty...
		if (empty()) {
			cout << "Queue empty -- No items to remove." << endl;
		}
		// If there is exactly one item in the Queue...
		else if (tail == front) {
			delete tail;
			tail = nullptr;
			front = nullptr;
			--num_items;
		}
		else {
		// There are multiple items in the Queue 
			Node<itemType>* currentNode = tail;
			while (currentNode->next != front) {
				currentNode = currentNode->next;
			}
			delete front;
			front = currentNode;
			--num_items;
		}
	}

	/*
	Removes item at the front of the Queue and appends it to the back of the Queue
	*/
	void move_to_rear() {
		itemType temp = getFront();
		pop();
		push(temp);
	}

	/*
	Recursively searches the queue to find the last instance of a given value
	@ param target: By-reference itemType. This is the value we're looking for the last instance of.
	@ param pos: integer. We'll want to enter it size() - 1 when we originally call it. 
	@ return position of the last instance of the target value.
	*/
	itemType reverse_linear_search(itemType target, int pos) {
		Node<itemType>* currentNode = tail;
		int index = 0;

		while (index < pos) {
			currentNode = currentNode->next;
			++index;
		}

		// If the whole Queue has been searched to no avail
		if (pos < 0)
			return -1;
		// If the target is found...
		if (target == currentNode->data)
			return pos;
		// If the target hasn't been found but the search isn't over...
		else
			return reverse_linear_search(target, pos-1);
	}
};

int main() {
	//Variables
	Queue<int> myQueue;
	Queue<int> tempQueue;

	// Main program
	myQueue.print();
	cout << endl;
	
	// Push function demonstration
	cout << "Ten items will be added to the queue." << endl;
	for (size_t i = 0; i < 10; ++i) {
		myQueue.push(i * 10);
		cout << "Adding item " << i * 10 << "..." << endl;
		myQueue.print();
	}
	cout << endl;

	// Front function demonstration
	cout << "The item at the front of the queue is " << myQueue.getFront() << endl << endl;

	// Pop function demonstration
	cout << "The frontmost item will be removed from the queue ten times." << endl;
	for (size_t i = 0; i < 11; ++i) {
		if (!myQueue.empty()) {
			cout << "Removing " << myQueue.getFront() << "..." << endl;
		}
		myQueue.pop();
		myQueue.print();
	}
	cout << endl;
	cout << "empty() and size() were both implemented and used in the code of the other functions." << endl << endl;

	// Push function demonstration
	cout << "Adding ten items to the queue." << endl;
	for (size_t i = 0; i < 10; ++i) {
		myQueue.push(i % 3);
	}
	cout << endl;

	// Display with only primitive functions
	
	cout << "Printing Queue using only primitive functions (result is inverted)..." << endl;

		// Print Queue
		cout << "Queue: ";
		for (size_t i = myQueue.size(); i > 1; --i) {
			cout << myQueue.getFront() << ", ";
			tempQueue.push(myQueue.getFront());
			myQueue.pop();
		}
		cout << myQueue.getFront() << endl;
		tempQueue.push(myQueue.getFront());
		myQueue.pop();

		// Refill original Queue
		for (size_t i = tempQueue.size(); i > 1; --i) {
			myQueue.push(tempQueue.getFront());
			tempQueue.pop();
		}
		myQueue.push(tempQueue.getFront());
		tempQueue.pop();

	// demonstrate move_to_rear() function
	cout << endl << "Performing move_to_rear() function..." << endl;
	myQueue.move_to_rear();
	myQueue.print();

	// demonstrate reverse_linear_search() function
	cout << "Demonstrating recursive search function." << endl;
	cout << "The last instance of the value 2 is at index " << myQueue.reverse_linear_search(2, myQueue.size() - 1) << endl << endl;
}