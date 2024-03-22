#pragma once
using namespace std;
#include <iostream>
#include <vector>
#include <random>

// Structures and classes

template <typename itemType>
struct DataNode {
	itemType data;
	DataNode* next;

	DataNode(const itemType& data, DataNode* next = nullptr) :
		data(data), next(next) {}
};

template<typename itemType>
struct Node {
	itemType data;
	Node<itemType>* next = nullptr;

	// Default constructor
	Node(const itemType& item)
		: data(item), next(nullptr) {}
};

// Note: This class is imported from assignment 2, but it is my own work. Additionally, I added my own .at() function so that the list insertionSort function would be easilier to implement.
template <typename itemType>
class Single_Linked_List {
private:
	DataNode<itemType>* head;
	DataNode<itemType>* tail;
	size_t num_items;

public:

	Single_Linked_List(DataNode<itemType>* head = nullptr, DataNode<itemType>* tail = nullptr, size_t num_items = 0) :
		head(head), tail(tail), num_items(num_items) {}

	/*
		Pushes new data to the front of the list, which is held in a DataNode
		@ param constant itemType-by-reference "item" is the new data we're pushing to the front of the list
	*/
	void push_front(const itemType& item) {
		// Special case: Is the list empty?
		if (head == nullptr) {
			head = new DataNode<itemType>(item);
			tail = head;
		}
		// Special case: Is there exactly one item in the list?
		else if (head->next == nullptr) {
			DataNode<itemType>* newNode = new DataNode<itemType>(item);
			newNode->next = head;
			tail = head;
			head = newNode;
		}
		// Main case: The list already has multiple items
		else {
			DataNode<itemType>* newNode = new DataNode<itemType>(item);
			newNode->next = head;
			head = newNode;
		}
		++num_items;
	}

	/*
		Pushes new data to the back  of the list, which is held in a DataNode
		@ param constant itemType-by-reference "item" is the new data we're pushing to the back of the list
	*/
	void push_back(const itemType& item) {
		// Special case: Is the list empty?
		if (head == nullptr) {
			push_front(item);
		}
		// Main case: The list already has one or more items
		else {
			DataNode<itemType>* newNode = new DataNode<itemType>(item);
			tail->next = newNode;
			tail = newNode;
			++num_items;
		}
	}

	/*
		Removes the first item from the list
	*/
	void pop_front() {
		// Special case: Is the list empty?
		if (head == nullptr) {
			return;
		}
		// Special case: Is there exactly one item in the list?
		else if (head->next == nullptr) {
			DataNode<itemType>* markedNode = head;
			head = nullptr;
			tail = nullptr;
			delete markedNode;
			--num_items;
		}
		// Main case: There is more than one item in the list
		else {
			DataNode<itemType>* markedNode = head;
			head = head->next;
			delete markedNode;
			--num_items;
		}
	}

	/*
		Removes the last item from the list
	*/
	void pop_back() {
		// Special case: Is the list empty?
		if (tail == nullptr) {
			pop_front();
		}
		// Special case: Is there exactly one item in the list?
		else if (head->next == nullptr) {
			pop_front();
		}
		// Main case: There is more than one item in the list
		else {
			DataNode<itemType>* markedNode = tail;
			DataNode<itemType>* currentNode = head;
			while (currentNode->next != tail) {
				currentNode = currentNode->next;
			}
			tail = currentNode;
			tail->next = nullptr;
			delete markedNode;
			--num_items;
		}

	}

	/*
		Prints out contents of the list from first to last or "list empty" if it is empty.
	*/
	void print_list() {
		if (head != nullptr) {
			DataNode<itemType>* currentNode = head;
			while (currentNode != nullptr) {
				cout << currentNode->data << " ";
				currentNode = currentNode->next;
			}
			cout << endl;
		}
		else {
			cout << "List empty" << endl;
		}
	}

	/*
		@ returns By-reference itemType from the front of the list (head).
	*/
	itemType& front() {
		return head->data;
	}

	/*
		@ returns By-reference itemType from the back of the list (tail).
	*/
	itemType& back() {
		return tail->data;
	}

	/*
		@ returns True if the list is empty, false otherwise
	*/
	bool empty() {
		return (head == nullptr);
	}

	/*
		Inserts new item BEFORE item at a certain index into the list
		@ param index (size_t): Index that the new item will be at once it is inserted
		@ param item (constant by-reference itemType): New item being inserted
	*/
	void insert(size_t index, const itemType& item) {
		// Special case: Is the list empty? Or, is the new item being inserted at the beginning?
		if (empty() || index <= 0) {
			push_front(item);
		}
		// Main case: New item is not being inserted at the beginning.
		else {
			// Iterate through the list until index is found or end is reached
			DataNode<itemType>* currentNode = head;
			size_t i = 0;
			while (currentNode != nullptr && i < index - 1) {
				currentNode = currentNode->next;
				++i;
			}

			// If i is about to reach its index
			if (i == index - 1) {
				// If the index is at the very end
				if (currentNode->next == nullptr) {
					push_back(item);
				}
				// If the index wasn't at the very end
				else {
					DataNode<itemType>* newNode = new DataNode<itemType>(item);
					newNode->next = currentNode->next;
					currentNode->next = newNode;
					++num_items;
				}
			}
			// If index was beyond the end of the list
			else if (currentNode == nullptr) {
				push_back(item);
			}
		}
	}

	/*
		Removes item at a given index from the list. Returns false if that index is beyond the list's range.
		@ param index (size_t): Index of item to be removed
		@ returns booleon value. True if removal was successful. False if there were no items to remove or if the index given was out of range.
	*/
	bool remove(size_t index) {
		// Special case: Is the list empty?
		if (empty()) {
			return false;
		}
		// Special case: Are we removing the element from the front of the list?
		else if (index == 0) {
			pop_front();
			return true;
		}
		else {
			DataNode<itemType>* currentNode = head;
			size_t i = 0;
			while (currentNode->next != nullptr && i < index - 1) {
				currentNode = currentNode->next;
				++i;
			}

			if (currentNode->next == nullptr) {
				return false;
			}

			if (i <= index - 1) {
				if (currentNode->next->next != nullptr) {
					DataNode<itemType>* markedNode = currentNode->next;
					currentNode->next = markedNode->next;
					delete markedNode;
					--num_items;
					return true;
				}
				else {
					pop_back();
					return true;
				}
			}
		}
	}

	/*
		Returns num_items in list (size_t)
	*/
	size_t size() {
		return num_items;
	}

	/*
		Returns the index of the first instance of a given value in the linked list
		@ param item (constant by-reference itemType): The data we are searching for in the linked list
		@ returns size_t of the index of the querry. If the item isn't in the list anywhere, the function simply returns the size of the list.
	*/
	size_t find(const itemType& item) {
		size_t i = 0;
		DataNode<itemType>* currentNode = head;

		// Special case: Is the list empty?
		if (empty()) {
			return num_items;
		}
		// Special case: Is the very first node the item being searched for?
		else if (head->data == item) {
			return 0;
		}
		else {
			while (i < num_items && currentNode->data != item) {
				++i;
				currentNode = currentNode->next;
			}

			// If item not found
			if (i >= num_items) {
				return num_items;
			}

			// If item found
			if (currentNode->data == item) {
				return i;
			}
		}
	}

	/*
	Returns a reference to the nth node of the list
	@ param n: Index we are searching for
	@ returns reference to DataNode at index n of the list, or the head if that index is out of range.
	*/
	DataNode<itemType>& at(int n) {
		if (n == 0) {
			return *head;
		}
		else if (n == size() - 1) {
			return *tail;
		}
		else if (n > 0 && n < size() - 1) {
			DataNode<itemType>* currentNode = head->next;
			int index = 1;
			while (index != n) {
				++index;
				currentNode = currentNode->next;
			}
			return *currentNode;
		}
		else {
			return *head;
		}
	}
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
			return reverse_linear_search(target, pos - 1);
	}
};

// Functions


// I wanted to "properly" define this function in the .cpp file, but its use of templates severely complicated that.
/*
Finds the index of the last index of a target value in a vector.
@ param v: By-reference vector of template type. This is the vector we are reverse-linear-searching.
@ param target: Template type. This is the value we are looking for.
@ param pos: integer. This represents the index we are searching for target at with each call.
@ returns index of the last instance of the target, or -1 if the target is absent.
*/
template <typename itemType>
int vRLS(vector<itemType>& v, itemType target, int pos) {
	if (pos < 0) {
		return -1;
	}

	if (target == v[pos]) {
		return pos;
	}
	else {
		return vRLS(v, target, pos - 1);
	}
};

/*
Sorts a singly linked list into ascending order
@ param list: By-reference Single_Linked_List of integer type. This list will be sorted by the function.
*/
void insertion_sort(Single_Linked_List<int>& list);