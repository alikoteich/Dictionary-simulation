#ifndef BT_H_INCLUDED
#define BT_H_INCLUDED

typedef char* elt;

typedef struct node
{
    elt word;
    elt *synonym;
    int i;
    struct node *right, *left;
}*BST;

typedef struct entry_t
{
    elt key;
    struct entry_t *next;
    int counter;
} entry_t;

typedef struct
{
    entry_t **entries;
} ht_t;

//Helper functions
int maximuim (int x, int y);
int height_of_tree(BST t);
BST right_rotate (BST y);
BST left_rotate (BST x);
int find_max(BST t);
int binary_search(elt *s, int l, int r, elt syn);
void insertion_sort(elt s[], int n);
elt lower_case(elt s);
elt new_line_removal(elt s);
elt synonyms_concatenating(int size, char *array[size], char *joint);
elt word_and_synonyms_concatenating(BST t);
int check_file(elt filePath);
FILE *open_file(char* filePath);
int tree_is_Balanced(BST t);


//BST functions
BST init_tree();
BST insert_word_from_new_file(BST t, elt w);
BST insert_word_from_main_file(BST t, elt w);
BST insert_synonym (BST t, elt w, elt syn);
int word_exist(BST t, elt w);
BST traverse_to_word(BST t, elt e);
BST balance_tree (BST t);
void print_synonyms_of_word (BST t, elt w);
void word_with_most_synonyms(BST t, int m);
void print_words_of_synonym(BST t, elt s);


//File functions
BST loading_main_file_into_bst(BST t, char* filePath);
BST loading_new_file_into_bst(BST t, char* filePath);
void store_line_into_dictionary(BST t,char* filePath);
void store_new_dictionary(BST t,char* filePath);
BST loading_temp_file_into_bst(BST t, char* filePath);
void insert_synonym_into_dictionary (BST t, elt w, elt s);

//hash table functions
unsigned int hash(const char *key);
entry_t *ht_unit(const char *key);
ht_t *ht_create();
void ht_set(ht_t *hashtable, const char *key);
void ht_most(ht_t *hashtable);
ht_t* fill_hash_table(BST t,ht_t *table);

//extra feature
int distance(char* word1,int len1,char* word2,int len2);
void suggestion(BST t,elt input);

#endif // BT_H_INCLUDED

