#include "assignment_3.h"

/*
Sorts a singly linked list into ascending order
@ param list: By-reference Single_Linked_List of integer type. This list will be sorted by the function.
*/
void insertion_sort(Single_Linked_List<int>& list) {
	int i, j, key;
	bool insertionNeeded = false;

	for (j = 1; j < list.size(); ++j) {
		key = list.at(j).data;
		insertionNeeded = false;

		for (i = j - 1; i >= 0; --i) {
			if (key < list.at(i).data) {
				list.at(i + 1).data = list.at(i).data;
				insertionNeeded = true;
			}
			else {
				break;
			}
		}

		if (insertionNeeded) {
			list.at(i + 1).data = key;
		}
	}
}