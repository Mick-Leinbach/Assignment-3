#include "assignment_3.h"

int main() {
	//Variables
	Queue<int> myQueue;
	Queue<int> tempQueue;
	vector<int> myVector;
	Single_Linked_List<int> myList;

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
		myQueue.push(i * 3);
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

	// demonstrate recursive linear search function
	
		cout << endl << "Performing recursive reverse linear search function." << endl;

		// Create vector
		cout << "Creating vector..." << endl;
		for (size_t i = 1; i < 9; ++i) {
			myVector.push_back(i % 4);
		}

		// Print out vector
		for (size_t i = 0; i < myVector.size(); ++i) {
			cout << myVector.at(i) << " ";
		}
		cout << endl;

		// Demonstrate vRLS()
		cout << "The last instace of the number 0 is at index " << vRLS(myVector, 0, myVector.size() - 1) << endl;
		cout << "The last instace of the number 1 is at index " << vRLS(myVector, 1, myVector.size() - 1) << endl;
		cout << "The last instace of the number 2 is at index " << vRLS(myVector, 2, myVector.size() - 1) << endl;
		cout << "The last instace of the number 3 is at index " << vRLS(myVector, 3, myVector.size() - 1) << endl;
		cout << "The last instace of the number 4 is at index " << vRLS(myVector, 4, myVector.size() - 1) << endl;
		cout << endl;

	// Demonstrate linked list insertion sort

		// Create linked list
		cout << "Creating linked list..." << endl;
		for (size_t i = 1; i < 9; ++i) {
			myList.push_back(i % 4);
		}

		// Print out linked list
		myList.print_list();

		// Sort list
		cout << "Sorting list..." << endl;
		insertion_sort(myList);
		myList.print_list();
}