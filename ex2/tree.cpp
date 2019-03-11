#include <cstdio>
#include <cstring>

#define INSERT "insert_at_root"
#define INSERT_AFTER "insert_after"
#define PRINT "print"
#define DELETE "delete"
#define BUFFER_LEN 200

// Struct Tree is implemented as a two dimension tree.
// That is,the left child is its brother and the right child is its first(one of) children
// And it performs like a normal tree
// This will bring some complex on deleting nodes but in all it acts like a chain

struct TNode {
    int x;
    TNode *brother;
    TNode *first_children;
};

TNode *Tree_root = nullptr;

// This function replace the root of the tree
void insert_at_root(int x) {
    // make the new
    TNode *tmp = new TNode;
    tmp->x = x;
    tmp->brother = nullptr;
    tmp->first_children = nullptr;
    if (Tree_root == nullptr) {
        // The previous tree is empty
        Tree_root = tmp;
    }
    else {
        // The previous tree become one of its children
        tmp->first_children = Tree_root;
        Tree_root = tmp;
    }
}

// print the tree on specific dim, implemented as recursive function
void _print(TNode *node, int n) {
    if (n == -1 || n > 0) {
        // print this node
        printf("%i ", node->x);
        // print each of its children
        for (
                TNode *tmp = node->first_children; // visit its first children
                tmp != nullptr; // it has more children
                tmp = tmp->brother) {
            _print(tmp, n==-1?-1:n-1); // if n==-1 we keep using -1
        }
    }
}

void print(TNode *node, int n) {
    _print(node,n);
    printf("\n");
}

// This stack is used to visit a tree
struct _stack {
    TNode *ptr; // element
    _stack *next; // implemented as chain
};
// push stack
void _push(_stack *&stack, TNode *node) {
    _stack *tmp = new _stack;
    tmp->ptr = node;
    tmp->next = stack;
    stack = tmp;
}
// pop stack
TNode *_pop(_stack *&stack) {
    TNode *tmp = stack->ptr; // element
    _stack *t = stack;
    stack = stack->next;
    delete t; // avoid memory leak
    return tmp;
}
// destroy stack
void _destroy(_stack *&stack) {
    _stack *t = nullptr;
    while (stack != nullptr) {
        t = stack;
        stack = stack->next;
        delete t;
    }
}
// code of stack end here

// find x if exist, then add y as one of its children, or
// to be specificly, the last children
void insert_after(int x, int y) {
    // in order to insert, we first find the element x
    // This require us to use stack
    TNode *ptr = Tree_root;
    _stack *stack = nullptr;
    while (true) {
        if (ptr != nullptr) {
            // push ptr into stack so later we can visit its brother
            _push(stack, ptr);
            // visit element
            if (ptr->x == x) {
                // we find x successful
                TNode *tmp = new TNode;
                tmp->x = y;
                tmp->brother = nullptr;
                tmp->first_children = nullptr;
                // lets insert y after it;
                if (ptr->first_children == nullptr) {
                    ptr->first_children = tmp;
                }
                else {
                    // we insert y as its last children so we find the tail of the chain
                    for (
                            TNode *p = ptr->first_children;
                            p != nullptr;
                            p = p->brother) {
                        if (p->brother == nullptr) {
                            p->brother = tmp;
                            break;
                        }
                    }
                }
                // the insert has done and we have no need of continue to search
                break;
            }
            // let ptr be the first children of it so we prepare to visit it in the next loop
            ptr = ptr->first_children;
        }
        else {
            // trace back to last point and we prepare to visit its brother in the next loop
            if (stack != nullptr) {
                ptr = _pop(stack);
                ptr = ptr->brother;
            }
            else {
                // this tree is fully visited
                break;
            }
        }
    }
    _destroy(stack);
}
// 感想：第一次把数据结构书上（这个是从TAOCP看的，那本书上只有伪码）看到的算法写进代码，边回忆思路边写，一次就写对了
// 数据结构不愧是真正的编程核心内容
// 为什么TAOCP的这个算法是正确的：
// 1 在进入的任何时刻，ptr都是stack中上一个元素的左孩子
// 2 在回溯的任何时候，ptr都会变成stack中被弹出元素的右孩子
// 3 ptr不为nullptr时，ptr就指向一颗完整的树
// 因此，通过改造这个算法应该能跟踪ptr的父节点
void delete_node(int x) {
    // in order to delete, we find the element x
    // and also keep tracking of its father(who save its pointer)
    TNode *ptr = Tree_root;
    TNode *father = nullptr;
    _stack *stack = nullptr;
    while (true) {
        if (ptr != nullptr) {
            // push ptr into stack so later we can visit its brother
            _push(stack, ptr);
            // visit element
            if (ptr->x == x) {
                // check if it has no children
                if (ptr->first_children == nullptr) {
                    if (father->first_children == ptr) {
                        father->first_children = ptr->brother;
                        delete ptr;
                    }
                    else {
                        father->brother = ptr->brother;
                        delete ptr;
                    }
                }
                // the insert has done and we have no need of continue to search
                break;
            }
            // let ptr be the first children of it so we prepare to visit it in the next loop, remember to change its father
            ptr = ptr->first_children;
            father = stack->ptr;
        }
        else {
            // trace back to last point and we prepare to visit its brother in the next loop
            if (stack != nullptr) {
                father = _pop(stack);
                ptr = father->brother;
            }
            else {
                // this tree is fully visited
                break;
            }
        }
    }
    _destroy(stack);
}




int main() {
    char buff[BUFFER_LEN] = "";
	int retcode = scanf("%s", buff);
	while (retcode != EOF) {
		if (strcmp(buff, INSERT) == 0) {
			int tmp = 0;
			scanf("%i", &tmp);
			insert_at_root(tmp);
		}
		else if (strcmp(buff, INSERT_AFTER) == 0) {
            int tmp1=0, tmp2=0;
            scanf("%i %i", &tmp1, &tmp2);
            insert_after(tmp1, tmp2);
		}
		else if (strcmp(buff, PRINT) == 0) {
            int tmp = 0;
            scanf("%i", &tmp);
            print(Tree_root, tmp);
		}
		else if (strcmp(buff, DELETE) == 0) {
			int tmp = 0;
			scanf("%i", &tmp);
			delete_node(tmp);
		}
		else {
			break;
		}
		retcode = scanf("%s", buff);
	}

    return  0;
}


// Reference :
// TAOCP Vol.1 Chap 2 Tree
