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

int main() {
	// read the target word from stdin
	char word[200] = "";
	scanf("%s", word);
	to_lower(word);
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
		// compare to provided string
		if (str_equal(word, tmp)) {
			printf("True");
			fclose(fp);
			return 0;
		}
		else {
			;
		}
	}
	fclose(fp);
	printf("False");
	return 0;
}
