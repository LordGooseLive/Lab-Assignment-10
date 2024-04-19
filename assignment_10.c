#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
typedef struct Trie
{	
    int endings;
    struct Trie * children [26];
    char letter;
} Trie;

//function prototypes
//added by student 
Trie *createTrie(); 
void insert(struct Trie *pTrie, char *word); 
int numberOfOccurances(struct Trie *pTrie, char *word); 
Trie *deallocateTrie(struct Trie *pTrie); 
int readDictionary(char *filename, char **pInWords); 

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    //traverse itteratively
    int i, j;
    int len = strlen(word);
    Trie* temp = pTrie;

    //go as far as possible
    //if letters are not there, add them
    for (i = 0; i <len; i++)
    {
        j = word[i] - 'a';
        if (temp->children[j] == NULL) //if nodes are missing
        {
            temp->children[j] = (Trie*) createTrie(); //make node
            temp->children[j]->letter = word[i]; //set letter
        }
        
        temp = temp->children[j];
    }

    //mark as present
    temp->endings ++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    //traverse word
    //check value of temp-> endings

    int len = strlen(word);
    int i, j;
    Trie* temp = pTrie;

    for (i = 0; i < len; i++)
    {
        j = word[i] - 'a';
        if (temp->children[j] == NULL)
            return 0;
        
        //else
        temp = temp->children[j];
    }

    return temp->endings;
}

// deallocate the trie structure
Trie *deallocateTrie(struct Trie *pTrie) //done
{
    //terminate on NULL call
    if (pTrie == NULL)
        return NULL;
    
    //first free all children
    for (int i = 0; i < 26; i++)
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    
    free (pTrie);
    return NULL;
}

// Initializes a trie structure
Trie *createTrie() //done
{
    Trie* pTrie = malloc( sizeof (Trie));
    pTrie->endings = 0;
    pTrie->letter = '\0';

    for (int i = 0; i < 26; i++)
        pTrie->children[i] = NULL;

    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE * source = fopen(filename, "r");
    char word [100];
    int num;

    fscanf(source, "%d", &num);

    for (int i = 0; i < num; i++)
    {
        fscanf(source, " %s", word);
        pInWords[i] = malloc(sizeof(char) * strlen(word));
        strcpy  (pInWords[i], word);
    }

    return num;
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