#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie structure
struct Trie {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;	
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *node = root;
    for( int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!node->children[index]) {
            node->children[index] = creatTrieNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct TrieNode *node = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if(!node->children[index]) {
            return 0;
        }
        node = node->children[index];
    }
    return node != NULL && node->isEndOfWOrd;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (root) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            deallocateTrie(root->children[i]);
        }
        free(root);
    }
}

// Initializes a trie structure
struct Trie *createTrie() {
     struct TrieNode *node = malloc(sizeof(struct TrieNode));
    if(node) {
        node->isEndOfWord = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL;
        }
    }
    return node;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    File *file = fopen(filename, "r");
    if (!file) {
        return 0;
    }

    int numword = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        pInWords[numWords] = strdup(line);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
