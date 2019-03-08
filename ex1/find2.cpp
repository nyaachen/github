#include <cstdio>

// a powerful word split trick from scanf, which I had never noticed about it
// scanf format string provide %[characters] to scan all characters inside it
// and stop at the first one not inside. using ^ will get the reversed effect
#define WHOLE_WORD "%[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]"
#define WORD_SEP "%*[^abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]"

#define FILENAME "article.txt"

void to_lower(char *s) {
	// in ASCII code, A is little than a
	for (size_t i = 0; s[i] != '\0'; ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] += 'a' - 'A';
		}
	}
}
int _str_equal(char *s1, char *s2) {
	int retcode = 0;
	for (size_t i = 0; retcode == 0; ++i) {
		// update the retcode
		retcode = s1[i] - s2[i];
		if (s1[i] == '\0' || s2[i] == '\0') break;
	}
	// so this break either the end of any string is reached, or it is not equal
	// in both condition the retcode is the return value
	return retcode;
}
int str_equal(char *s1, char *s2) {
	return _str_equal(s1, s2) == 0;
}


// The code for hash function is not by me
int f(char *s) {
    int res = 0;
    for (char *c = s; *c != '\0'; ++c) {
        res = res * 26 + (*c - 'a');
        res = res % 2333;
    }
    return res;
}

// the definition of hash_table and link node
struct Node {
    char *s;
    Node *next;
};

Node *hash_table[2333] = {0};

int hash(char *s) {
    return f(s);
}

int ht_find(char *s) {
    // first calculate the hash value
    int index = hash(s);
    // find if already exist
    Node *ptr = hash_table[index];
    while (ptr != nullptr) {
        if (str_equal(s, ptr->s)) {
            // found
            return true;
        }
        else {
            // go for next node
            ptr = ptr->next;
        }
    }
    return false;
}

size_t my_strlen(char *s) {
    size_t l=0;
    for (;s[l] != '\0'; ++l);
    return l;
}
void my_strcpy(char *Dest, char *Source) {
    size_t len = my_strlen(Source);
    for (size_t l=0; l <= len; ++l) {
        Dest[l] = Source[l];
    }
}

void ht_insert(char *s) {
    // find if already exist
    if (!ht_find(s)) {
        // first calculate the hash value
        int index = hash(s);
        // add this word into the chain
        Node *tmp = new Node;
        tmp->s = new char [my_strlen(s)+1];
        my_strcpy(tmp->s, s);
        tmp->next = hash_table[index];
        hash_table[index] = tmp;
    }
}


int main() {
	// the retcode can detect EOF in fscanf
	int retcode = 1;
	char tmp[200] = "";
	FILE *fp = fopen(FILENAME, "r");
	while (retcode != EOF) {
		// read a word in
		retcode = fscanf(fp, WHOLE_WORD, tmp);
		fscanf(fp, WORD_SEP);
		// turn it to lower
		to_lower(tmp);
		// record the string into hash table
        ht_insert(tmp);
	}
	fclose(fp);
    // read the target word from stdin
	char word[200] = "";
    retcode = scanf("%s", word);
    while (retcode != EOF) {
        to_lower(word);
        if (ht_find(word)) {
            printf("True");
        }
        else {
            printf("False");
        }
        retcode = scanf("%s", word);
    }
	return 0;
}
