#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>

#define BUFFER_LEN 100
#define PRINT_WHOLE_LIST -1

#define INSERT_HEAD "insert_at_beginning"
#define INSERT_END "insert_at_ending"
#define INSERT_AFTER "insert_after"
#define DELETE "delete"
#define PRINT "print"
#define PRINT_REVERSE "reverse_print"

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
	// if the new node is the new end, change ptail
	if (tmp->next == nullptr) {
		ptail = tmp;
	}
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

void insert_after(int x, int y) {
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

void delete_node(int x) {
	// find first element x
	// use two pointer to track, just make sure relation <q,p> is always correct
	Node *p = phead->next;
	Node *q = phead;
	while (p != nullptr) {
		// p points to a node
		if (p->x == x) {
			// found element x, remove it from the chain, that is relation <q,p> become <q,p.next>
			q->next = p->next;
			// delete this node
			delete p;
			// quit the loop
			break;
		}
		else {
			// element x is not found. move the pointer
			p = p->next;
			q = q->next;
		}
	}
}

void print(int n) {
	if (n == PRINT_WHOLE_LIST) {
		Node *p = phead->next;
		while (p != nullptr) {
			printf("%i ", p->x);
			p = p->next;
		}
	}
	else {
		// print element no more than n
		Node *p = phead->next;
		for (int i=0; (i<n) && (p != nullptr); ++i) { // I prefer to use size_t as that won't overflow, however that will cause i<n act error when n is negative
			// print the element
			printf("%i ", p->x);
			// move the pointer
			p = p->next;
		}
	}
	printf("\n");
}

int _reverse_print(Node *node, int n) {
	// if this node is the tail node, check if we should print the value and return
	if (node->next == nullptr) {
		if ((n==PRINT_WHOLE_LIST) || n>0) { // either we need to print the whole list, or we need to print at least one element
			printf("%i ", node->x);
			// we printed once, return print count
			return 1;
		}
		else { // we print nothing
			return 0;
		}
	}
	else { // this is not the end of the tail, so we're not sure should we print it. Instead we require a return value to judge if we have printed enough time
		// call recursively to request print next node and get the returned print times count
		int times;
		times = _reverse_print(node->next, n);
		// if print the whole list or the print count is not enough, print current value
		if ((n==PRINT_WHOLE_LIST) || (times<n)) {
			printf("%i ", node->x);
			return times+1;
		}
		else { // we have already printed enough times.
			return times;
		}
	}
}

void reverse_print(Node *node, int n) {
	// how to use recursive to make this function?
	// Why this function returns void? this can not make it recursively
	// the common method is to flip the linked list and then print it
	_reverse_print(node->next, n); // this make it to point to the first element
	printf("\n");
}


void _initialize_list() {
	// This code is required as an not-initialized pointer is always trouble-maker
	phead = new Node;
	phead->next = nullptr;
	ptail = phead;
}

void _cleanup() {
	Node *tmp = nullptr;
	while (phead != nullptr) {
		// locate to the first node need to be delete
		tmp = phead;
		phead = phead->next;
		delete tmp;
	}
	// after the loop all the node is deleted
	// and ptail is a invalid pointer so
	// we reset it to nullptr
	ptail = phead;
}




int main() {
	// this code is very important
	_initialize_list();
	// from here starts the instruction parser
	char buff[BUFFER_LEN] = "";
	int retcode = scanf("%s", buff);
	while (retcode != EOF) {
		if (strcmp(buff, INSERT_HEAD) == 0) {
			int tmp = 0;
			scanf("%i", &tmp);
			insert_at_beginning(tmp);
		}
		else if (strcmp(buff, INSERT_END) == 0) {
			int tmp = 0;
			scanf("%i", &tmp);
			insert_at_ending(tmp);
		}
		else if (strcmp(buff, INSERT_AFTER) == 0) {
			int tmp1=0, tmp2=0;
			scanf("%i %i", &tmp1, &tmp2);
			insert_after(tmp1, tmp2);
		}
		else if (strcmp(buff, DELETE) == 0) {
			int tmp = 0;
			scanf("%i", &tmp);
			delete_node(tmp);
		}
		else if (strcmp(buff, PRINT) == 0) {
			int tmp = 0;
			scanf("%i", &tmp);
			print(tmp);
		}
		else if (strcmp(buff, PRINT_REVERSE) == 0) {
			int tmp = 0;
			scanf("%i", &tmp);
			reverse_print(phead, tmp);
		}
		else {
			break;
		}
		retcode = scanf("%s", buff);
	}

	_cleanup();
	return 0;
}

