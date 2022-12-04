#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"
#define TABLE_SIZE 2000

int main()
{

    BST tree = init_tree();
    ht_t *table= ht_create();
    int choice;
    char w[20], s[20];
    if(check_file("NewDictionary.txt")==0)
    {
        tree = loading_main_file_into_bst(tree,"WordsSynonyms.txt");
        store_new_dictionary(tree,"NewDictionary.txt");
    }
    else
    {
        tree = loading_new_file_into_bst(tree,"NewDictionary.txt");
        if(check_file("AddedSynonyms.txt")!=0)
            tree = loading_temp_file_into_bst(tree,"AddedSynonyms.txt");
    }

    printf("\n                             Welcome to our dictionary\n----------------------------------------------------------------------------------------------\n");
    printf("1. Enter a word to search for\n2. Enter a word to print its synonyms\n3. Insert a synonym to the dictionary\n4. Find the word with the highest number of synonyms\n5. Find the words of a synonym\n6. Find the most repeated word as a synonym in the dictionary\n7. check if the tree is balanced\n8. View search history\n9. exit\n");

    while(1)
    {

        printf("----------------------------------------------------------------------------------------------\nChoose an option: ");
        char input[20];
        scanf("%s",&input);
        choice = atoi(input);
        switch(choice)
        {
        case 1:
            printf("\nEnter a word: ");
            scanf("%s",w);
            FILE* fp = fopen("history.txt","a");
            if(check_file("history.txt")!=0)
                fputs("\n",fp);
            fprintf(fp,"%s",w);
            fclose(fp);
            if(word_exist(tree,lower_case(w))==1)
            {
                printf("%s exist in the dictionary.\n");
                printf("Do you want to print its synonyms [Y/N]? ");
                char c;
                scanf(" %c",&c);
                if(c == 'Y'|| c == 'y')
                    print_synonyms_of_word(tree,lower_case(w));
                else
                    continue;
            }

            else
            {
                printf("%s does not exist in the dictionary.\n\n");
                suggestion(tree,w);
                printf("\n");
            }
            break;

        case 2:
            printf("\nEnter a word: ");
            scanf("%s",w);
            print_synonyms_of_word(tree,lower_case(w));
            break;

        case 3:
            printf("\nEnter the word then its synonym to store in the dictionary: \nword: ");
            scanf("%s",w);
            printf("synonym: ");
            scanf("%s",s);
            insert_synonym_into_dictionary(tree,lower_case(w),lower_case(s));
            break;

        case 4:
            printf("\nThe word with most synonyms is ");
            word_with_most_synonyms(tree,find_max(tree));
            printf(" with %d synonyms.\n",find_max(tree));
            break;

        case 5:
            printf("\nEnter a synonym: ");
            scanf("%s",s);
            printf("The words of %s are: \n",s);
            print_words_of_synonym(tree,tolower(s));
            break;

        case 6:
            table=fill_hash_table(tree,table);
            ht_most(table);
            break;

        case 7:
            if(tree_is_Balanced(tree) == 1)
                printf("The tree is balanced\n");
            else
                printf("The tree is not balanced\n");
            break;

        case 8:
            printf("\nSearch history: \n");
            fp=fopen("history.txt","r");
            while(!feof(fp))
            {
                fscanf(fp,"%s",w);
                printf("%s\n",w);
            }
            break;

        }
        if(choice == 9)
        {
            printf("\nbye!!\n ");
            break;
        }
    }



    return 0;
}
