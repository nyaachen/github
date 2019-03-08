#include <iostream>

// this is actually a double end deque
// There is no list pointer parameter in the function, which indicates
// a global variable to storage the pointer


struct Node {
	int x;
	Node *next;
};

// The initialize of the list is in main() as an module
Node *phead = nullptr;
Node *ptail = nullptr;

void insert_at_beginning(int x) {
	// init the new node and copy data
	Node *tmp = new Node;
	tmp->x = x;
	// make this node to point to the old beginning
	tmp->next = phead->next;
	// make head node to point to the new beginning
	phead->next = tmp;
}

void insert_at_ending(int x) {
	// init the new node and copy data
	Node *tmp = new Node;
	tmp->x = x;
	tmp->next = nullptr;
	// make tail node to point to the new tail
	ptail->next = tmp;
	// make tail pointer to point to the new tail
	ptail = tmp;
}

voidd insert_after(int x, int y) {
	// first find element x
	Node *p = phead->next;
	while (p != nullptr) {
		// p points to a node
		if (p->x == x) {
			// found element x, insert after it

			// make new node and copy data
			Node *tmp = new Node;
			tmp->x = y;
			// add node into the chail
			tmp->next = p->next;
			p->next = tmp;
			// if the new node is the new end, change ptail
			if (tmp->next == nullptr) {
				ptail = tmp;
			}
			// the function is done and no need to continue the loop
			break;
		}
		else {
			// x is not found, turn to next node
			p = p->next;
		}
	}
}

void delete_node(int x);
