#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"functions.h"
#define TABLE_SIZE 2000


BST init_tree()    /*initialize a BST*/
{
    return NULL;
}

void insertion_sort(elt s[], int n)    /*sorts an array using insertion sort*/
{
    int i,j;
    elt key;
    for (i = 1; i < n; i++)
    {
        key = strdup(s[i]);
        j = i - 1;

        while (j >= 0 && strcmp(s[j],key)>0)
        {
            s[j + 1] = strdup(s[j]);
            j = j - 1;
        }
        s[j + 1] = strdup(key);
    }
}

BST insert_word_from_main_file(BST t, elt w)    /*inserts a word from the main file to the BST*/
{
    //creates the first node in the BST
    if(t==NULL)
    {
        struct node *n = (struct node *)malloc(sizeof(struct node));
        n->word = strdup(w);
        n->synonym = NULL;
        n->i = 0;
        n->right = NULL;
        n->left = NULL;
        return n;
    }
    //stores recursively the words in the left and right nodes
    else
    {
        if(strcmp(w, t->word) > 0)
            t->right = insert_word_from_main_file(t->right, w);
        else
            t->left = insert_word_from_main_file(t->left, w);
        return t;
    }

}

BST insert_word_from_new_file(BST t, elt w)    /*inserts a word from the new file to the BST*/
{
    //creates the first node in the BST
    if(t==NULL)
    {
        struct node *n = (struct node *)malloc(sizeof(struct node));
        n->word = strdup(w);
        n->synonym = NULL;
        n->i = 0;
        n->right = NULL;
        n->left = NULL;
        return n;
    }
    //stores recursively the words in the left and right nodes
    else
    {
        if(strcmp(w, t->word) > 0)
            t->right = insert_word_from_new_file(t->right, w);
        else
            t->left = insert_word_from_new_file(t->left, w);
            t=balance_tree(t);
        return t;
    }

}


BST insert_synonym (BST t, elt w, elt syn)    /*inserts a synonym for a given word to a given node*/
{
    BST s=traverse_to_word(t,w); //iterate towards the word where the synonym belongs
    if(s->synonym == NULL)       //stores first synonym to the specified word
    {
        s->synonym = malloc(1 * sizeof(elt));
        s->synonym[0] = strdup(syn);
        s->i = 1;
        return t;
    }
    //stores synonyms to the array
    else
    {
        s->synonym = realloc(s->synonym, (s->i + 1) * sizeof(elt));
        s->synonym[s->i] = strdup(syn);
        (s->i)++;

        return t;
    }
}

int word_exist(BST t, elt w)    /*checks if a word is found in the BST*/
{
    if(t == NULL)
        return 0;
    if(strcmp(w, t->word) == 0) //word found
        return 1;
    if(strcmp(t->word, w) > 0) // words smaller that node
        return word_exist(t->left, w);
    return word_exist(t->right, w);
}

BST traverse_to_word(BST t, elt e)    /*traverse the pointer to a given word in the BST same logic as word_exist fct*/
{
    if(t == NULL)
        return NULL;
    if(strcmp(e, t->word) == 0)
        return t;
    if(strcmp(t->word, e) > 0)
    {
        return traverse_to_word(t->left, e);
    }
    return traverse_to_word(t->right, e);
}

int find_max(BST t)    /*returns the max number of synonyms in the BST*/
{
    //finds the max nb on the left side and right side and return the max
    if(t==NULL)
        return;
    int max = t->i;
    int lmax = find_max(t->left);
    int rmax = find_max(t->right);
    if (lmax > max)
        max = lmax;
    if (rmax > max)
        max = rmax;
    return max;
}

void word_with_most_synonyms(BST t, int max)    /*finds the word with the max number of synonyms*/
{
    if(t==NULL)
        return;
    if(t->i==max)
        printf("%s",t->word) ;

    word_with_most_synonyms(t->left,max);
    word_with_most_synonyms(t->right,max);
}

void print_synonyms_of_word (BST t, elt w)    /*prints all synonyms of a given word*/
{
    if(word_exist(t,w)!=1)              //check if the word exist first
    {
        printf("word not found.\n");
        return;
    }
    t=traverse_to_word(t,w);            //if found iterate towards the word
    if (t->synonym == NULL)             //if the synonym array is empty
        printf("no synonyms found\n");
    printf("The synonyms of %s are:\n",w);
    for (int j = 0; j < (t->i); j++)    //prints the synonyms
        printf("- %s\n",  t->synonym[j]);
}

int maximuim (int x, int y)    /*returns maximum*/
{
    return x > y ? x:y;
}

int height_of_tree(BST t)    /*returns height of tree*/
{
    if(t == NULL)
        return 0;
    else
        return 1 + maximuim(height_of_tree(t->left), height_of_tree(t->right));
}

BST right_rotate (BST y)    /*rotate tree towards right*/
{
    BST x = y->left;
    BST T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

BST left_rotate (BST x)    /*rotate tree towards left*/
{
    BST y = x->right;
    BST T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

BST balance_tree(BST t) /*balance the binary search tree*/
{
    if(t == NULL)
        return;
    int hl = height_of_tree(t->left);   //calculates the height of left subtree
    int hr = height_of_tree(t->right);  //calculates the height of right subtree
    if(abs(hl-hr) > 1 && hl > hr)       //checks if difference in height between the subtrees more than one and height of left > height of right
        t = right_rotate(t);
    if(abs(hl-hr) > 1 && hr > hl)       //checks if difference in height between the subtrees more than one and height of left < height of right
        t = left_rotate(t);
    balance_tree(t->left);
    balance_tree(t->right);
    return t;
}
int tree_is_Balanced(BST t)
{
    int lh;
    int rh;

    if (t == NULL)
        return 1;

    lh = height_of_tree(t->left);
    rh = height_of_tree(t->right);

    if (abs(lh - rh) <= 1 && tree_is_Balanced(t->left) && tree_is_Balanced(t->right))
        return 1;

    return 0;
}




elt new_line_removal(elt s)    /*removes \n from end of the string*/
{
    int i=0,l=0;
    while(s[i++]!='\0')
        l++;
    for(i=0; i<l; i++)
    {
        if(s[i]=='\n')
            s[i]=0;
    }
    return s;
}

FILE *open_file(char* filePath)    /*opens a file in read mode*/
{
    FILE *fp;
    fp = fopen(filePath, "r");
    if(fp == NULL)
    {
        perror("Error opening file.");
        return NULL;
    }
    return fp;
}

int check_file(elt filePath)    /*checks if a file is empty*/
{
    int size=0;
    FILE* fp = fopen(filePath,"r");
    if (fp != NULL)
    {
        fseek (fp, 0, SEEK_END);
        size = ftell(fp);

        if (size == 0)
        {
            return 0;
        }
        return 1;
    }
}

BST loading_main_file_into_bst(BST t, char* filePath)    /*loads the dictionary from the main file to the BST*/
{
    FILE *fp;
    char str[500];
    char *token;
    elt w;
    fp = open_file(filePath);   //open the file in read mode
    while(!feof(fp))            //loop through the file until end of file
    {
        fgets (str, 500, fp);
        token = strtok(str, ",-. ");    //token used to split a string using delimiters
        w = strdup(token);              //takes the word first
        token = strtok(NULL, ",-. ");   //closes the tokenization
        t = insert_word_from_main_file(t, w);          //store the word to the BST
        while(token != NULL)            //start tokenizing the synonym string
        {
            token=new_line_removal(token);
            insert_synonym(t, w, strdup(token)); //insert synonyms to the array
            token = strtok(NULL, ",-. ");        //closes the tokenization
        }
        BST temp = traverse_to_word(t,w);
        insertion_sort(temp->synonym,temp->i);  //sorts the array using insertion sort
    }
    fclose(fp); //closes the file
    return t;
}

BST loading_new_file_into_bst(BST t, char* filePath)    /*loads the dictionary from the file to the BST*/
{
    FILE *fp;
    char str[500];
    char *token;
    elt w;
    fp = open_file(filePath);   //open the file in read mode
    while(!feof(fp))            //loop through the file until end of file
    {
        fgets (str, 500, fp);
        token = strtok(str, " ");    //token used to split a string using delimiters
        w = strdup(token);              //takes the word first
        token = strtok(NULL, " ");   //closes the tokenization
        t = insert_word_from_new_file(t, w);          //store the word to the BST
        while(token != NULL)            //start tokenizing the synonym string
        {
            token=new_line_removal(token);
            insert_synonym(t, w, strdup(token)); //insert synonyms to the array
            token = strtok(NULL, " ");        //closes the tokenization
        }
    }
    fclose(fp);
    return t;
}

BST loading_temp_file_into_bst(BST t, char* filePath)    /*loads the file where synonyms were added by the user*/
{
    FILE *fp;
    char str[600];
    char *token;
    elt w;
    elt s;
    fp = open_file(filePath);
    while(!feof(fp))
    {
        fgets (str, 600, fp);
        token = strtok(str, " ");
        w = strdup(token);
        token = strtok(NULL, " ");
        if(token != NULL)
        {
            s=new_line_removal(token);
            token = strtok(NULL, " ");
        }
        if((word_exist(t, w) == 1))             //same functionality as load_file_into_BST but it checks if the word exist in the tree
            insert_synonym(t, w, s);            //then it adds the synonym, if not exist then insert the word with its synonym
        else
        {
            t = insert_word_from_new_file(t, w);
            t = insert_synonym(t, w,s);
        }
        BST temp = traverse_to_word(t,w);
        insertion_sort(temp->synonym,temp->i);
    }
    fclose(fp);
    return t;
}

elt synonyms_concatenating(int size, char *array[size], char *joint)    /*concatenates the elements of the array as one string separated with spaces*/
{
    int jlen, lens[size];
    int i, total_size = (size-1) * (jlen=strlen(joint)) + 1; // total_size equals size of string needed to be formed
    char *result, *p;


    for(i=0; i<size; ++i)
    {
        total_size += (lens[i]=strlen(array[i]));           //getting the final size of the string from the array
    }
    p = result = malloc(total_size);            //allocate the memory needed for the string
    for(i=0; i<size; ++i)
    {
        memcpy(p, array[i], lens[i]);           //copies the entries of the array to the string
        p += lens[i];
        if(i<size-1)
        {
            memcpy(p, joint, jlen);
            p += jlen;
        }
    }
    *p = '\0';
    return result;                              //returns the final string
}

elt word_and_synonyms_concatenating(BST t)    /*concatenates the word with its synonyms as one string*/
{

    if(t==NULL)
        return;
    elt s1,s2;
    s1=strdup(t->word);
    strcat(s1," ");

    for(int j=0; j<(t->i); j++)
    {
        s2=synonyms_concatenating(t->i,t->synonym," "); //concatenates the synonyms in one string
    }
    strcat(s1,s2);      //concatenates the word with its synonyms
    return s1;
}

void store_line_into_dictionary(BST t,char* filePath)    /*stores a string to the new file*/
{
    FILE *fp;
    elt s;

    fp = fopen(filePath,"a");
    if(fp == NULL)
    {
        perror("Error opening file.");
        return NULL;
    }
    s=word_and_synonyms_concatenating(t);   //takes the word/synonyms string and store it in the new file
    if(check_file("NewDictionary.txt") != 0)
        fputs("\n",fp);
    fprintf(fp,"%s",s);
    fclose(fp);
}

void store_new_dictionary(BST t,char* filePath)    /*stores the BST in the new file*/
{

    if(t==NULL)
        return;

    store_new_dictionary(t->left,filePath);
    store_line_into_dictionary(t,filePath);
    store_new_dictionary(t->right,filePath);
}

int binary_search(elt *s, int l, int r, elt syn)    /*searches for a synonym in the array using binary search*/
{
    while (r >=l)
    {
        int mid = (l + r)/ 2;
        if (strcmp(s[mid],syn)==0)
            return 1;
        if (strcmp(s[mid],syn) > 0)
            return binary_search(s,l,mid-1,syn);
        return binary_search(s,mid+1,r,syn);
    }
    return -1;
}

void print_words_of_synonym(BST t, elt s)    /*prints all the words of a given synonym*/
{
    if(t==NULL)
            return;

    if(binary_search(t->synonym,0,t->i-1,s)==1)  //if synonym found print the words of it;
        printf("%s\n",t->word);

    print_words_of_synonym(t->left,s);
    print_words_of_synonym(t->right,s);

}

void insert_synonym_into_dictionary (BST t, elt w, elt s)    /*inserts a new synonym to the dictionary*/
{
    FILE* fp = fopen("AddedSynonyms.txt","a");
    if(fp == NULL)
    {
        perror("Error opening file.");
        return NULL;
    }
    if(check_file("AddedSynonyms.txt")!=0)      //stores the word with its synonym to file AddedSynonyms.txt
        fputs("\n",fp);
    fprintf(fp,"%s %s",w,s);
    fclose(fp);

    if(word_exist(t, w) == 1)             //inserts the synonym to its word in the BST
    {
        insert_synonym(t, w, s);
    }

    else
    {
        //inserts the word and its synonym to the BST if the word not exist
        t = insert_word_from_new_file(t, w);
        t = insert_synonym(t, w,s);
    }
    BST temp = traverse_to_word(t,w);
    insertion_sort(temp->synonym,temp->i);
}

unsigned int hash(const char *key)    /*creates a hash code for a given string*/
{
    unsigned int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i)
    {
        value = value * 37 + key[i];    //generating hash code
    }
    value = value % TABLE_SIZE;         //keeping the value in range of size of the table
    return value;
}

entry_t *ht_unit(const char *key)    /*allocates memory for entry and key and assign its value*/
{

    entry_t *entry = malloc(sizeof(entry_t) * 1);
    entry->key = malloc(strlen(key) + 1);
    strcpy(entry->key, key);
    entry->next = NULL;

    return entry;
}

ht_t *ht_create()    /*creates a new hash table*/
{

    ht_t *hashtable = malloc(sizeof(ht_t) * 1);
    hashtable->entries = malloc(sizeof(entry_t*) * TABLE_SIZE);

    int i = 0;
    for (; i < TABLE_SIZE; ++i)
    {
        hashtable->entries[i] = NULL;       //sets akk entries to NULL
    }
    return hashtable;
}

void ht_set(ht_t *hashtable, const char *key)    /*stores the synonym according to its hash code in the hash table*/
{
    unsigned int slot = hash(key);
    entry_t *entry = hashtable->entries[slot];

    if (entry == NULL)                              //if the entry of this hash code empty, assign the entry to the given key
    {
        hashtable->entries[slot] = ht_unit(key);
        hashtable->entries[slot]->counter=1;
        return;
    }

    entry_t *prev;                      //creates a pointer in case of new collision
    while (entry != NULL)               //if the hash code collides with the entry
    {

        if (strcmp(entry->key, key) == 0)   //check if the keys are similar then add the counter
        {
            entry->counter++;
            return;
        }
        prev = entry;                       //if keys are different iterate through the pointer
        entry = prev->next;
    }
    prev->next = ht_unit(key);              //store key using prev pointer (linked list)
    prev->next->counter=1;                  //set the count of this key to 1
}

void ht_most(ht_t *hashtable)    /*prints the most repeated synonym in the hash table*/
{

    int max=0;
    char *s;
    for (int i = 0; i < TABLE_SIZE; ++i)    //iterates through the hash table
    {
        entry_t *entry = hashtable->entries[i];

        if (entry == NULL)      //leaves empty entries
        {
            continue;
        }

        for(;;)                //infinite loop
        {
            if(entry->counter > max)  //check for the max counter in the hash table
            {
                max=entry->counter;
                s=strdup(entry->key);
            }
            if (entry->next == NULL)
            {
                break;
            }
            entry = entry->next;
        }

    }
    printf("(%s) is the most frequent synonym with frequncy = %d\n",s,max);
}

ht_t* fill_hash_table(BST t,ht_t *table)    /*fills the hash table from the BST with all the synonyms*/
{
    if(t == NULL)
        return;
    for(int j=0; j<t->i; j++)       //loops the BST and store the synonyms in the table
    {
        ht_set(table,t->synonym[j]);
    }

    fill_hash_table(t->left,table);
    fill_hash_table(t->right,table);
    return table;
}

elt lower_case(elt s)    /*makes a string in lowercase*/
{
    for(int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
    return s;
}

int distance(char* word1,int len1,char* word2,int len2)    /*Levenshtein algorithm for editing distances between 2 strings*/
{
    /*for further explanation ask us*/
    int matrix[len1 + 1][len2 + 1];
    int i;
    for (i = 0; i <= len1; i++)
    {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++)
    {
        matrix[0][i] = i;
    }
    for (i = 1; i <= len1; i++)
    {
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++)
        {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2)
            {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else
            {
                int delete;
                int insert;
                int substitute;
                int minimum;

                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum)
                {
                    minimum = insert;
                }
                if (substitute < minimum)
                {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}

void suggestion(BST t,elt input)    /*gives all suggestions of a word if it is not found in the BST*/
{
    if(t==NULL)
        return;
    suggestion(t->left,input);
    if(distance(input,strlen(input),t->word,strlen(t->word))<=2)  //if the distance between 2 strings less than 2 suggest it to the user
        printf("did you mean: %s\n",t->word);
    suggestion(t->right,input);
}
