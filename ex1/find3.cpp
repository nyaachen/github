#include <cstdio>

// a powerful word split trick from scanf, which I had never noticed about it
// scanf format string provide %[characters] to scan all characters inside it
// and stop at the first one not inside. using ^ will get the reversed effect
#define WHOLE_WORD "%[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]"
#define WORD_SEP "%*[^abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ]"

#define FILENAME "article.txt"

#define PRIME1 2333
#define PRIME2 2237
#define PRIME3 1951

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
int f(char *s, int prime) {
    int res = 0;
    for (char *c = s; *c != '\0'; ++c) {
        res = res * 26 + (*c - 'a');
        res = res % prime;
    }
    return res;
}

// the definition of Bloom Hash Table
bool hash_table1[PRIME1] = {false};
bool hash_table2[PRIME2] = {false};
bool hash_table3[PRIME3] = {false};



int bf_find(char *s) {
    // first calculate the hash value
    int index1 = f(s,PRIME1);
	int index2 = f(s,PRIME2);
	int index3 = f(s,PRIME3);
    // find if already exist
    if (
		hash_table1[index1] &&
		hash_table2[index2] &&
		hash_table3[index3]) {
        return true;
    }
    else {
		return false;
    }
}

void bf_insert(char *s) {
	// first calculate the hash value
    int index1 = f(s,PRIME1);
	int index2 = f(s,PRIME2);
	int index3 = f(s,PRIME3);
	hash_table1[index1] = true;
	hash_table2[index2] = true;
	hash_table3[index3] = true;
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
        bf_insert(tmp);
	}
	fclose(fp);
    // read the target word from stdin
	char word[200] = "";
    retcode = scanf("%s", word);
    while (retcode != EOF) {
        to_lower(word);
        if (bf_find(word)) {
            printf("True");
        }
        else {
            printf("False");
        }
        retcode = scanf("%s", word);
    }
	return 0;
}
