//
// Created by Michael Poliakov on 6/16/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KEY_SIZE 52
#define WORDS_ARRAY_SIZE 100
#define MAX_STR_LEN 50

/* Function Declarations */
char encrypt(unsigned char key[KEY_SIZE], char ch);
int read_words(char* words[], int size, int max_str_len);
void encrypt_words(char* words[], int num_words, unsigned char key[KEY_SIZE]);
void release_memory(char* words[], int num_words);
void print_words(char* words[], int num_words);


/* Implementation */
void print_words(char* words[], int num_words)
{
    int i;
    for ( i = 0; i < num_words; i++) {
        printf("%s\n", words[i]);
    }
}

int main()
{
    unsigned char key[KEY_SIZE] = {

            '>', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '~', 'S', 'D',
            'F', 'G', '*', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', '+', 'M',
            'm','b','n','v','z','c','@','q','r','u','i','e','r',
            't','o','p','w','$','j','g','d','%','s','f','h','k'
    };
    int num_words =0, i;
    char* words[WORDS_ARRAY_SIZE];

    for ( i = 0; i < WORDS_ARRAY_SIZE; i++) {
        words[i] = NULL;
    }

    num_words = read_words(words, WORDS_ARRAY_SIZE, MAX_STR_LEN);
    if (num_words == -1)
    {
        printf("Failed to read words.\n");
        return 0;
    }

    encrypt_words(words, num_words, key);
    print_words(words, num_words);
    release_memory(words, num_words);
    return 0;
}

char encrypt(unsigned char key[KEY_SIZE], char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return (char) key[(int)(ch - 'A')];
    else
        return (char) key[(int)(ch - 'a' + ('Z' - 'A' + 1))];
}

int read_words(char* words[], int size, int max_str_len)
{
    char* one_word = (char*) malloc(sizeof(char) * max_str_len + 1);
    if (one_word == NULL) return -1;
    int i = 0;
    while(i < size)
    {
        if(scanf("%s", one_word) == EOF) break;
        int n = (int) strlen(one_word) + 1;
        words[i] = (char*) malloc(sizeof(char) * n);
        if (words[i] == NULL)
        {
            free(one_word);
            release_memory(words, i);
            return -1;
        }
        strcpy(words[i], one_word);
        i++;
    }
    free(one_word);
    return i;
}

void encrypt_words(char* words[], int num_words, unsigned char key[KEY_SIZE])
{
    for (int word = 0; word < num_words; word++)
    {
        char* ch = words[word];
        while (*ch != '\0')
        {
            *ch = encrypt(key, *ch);
            ch++;
        }
        //for (char* ch_prime = words[word]; *ch_prime != '\0'; ch_prime++)
           // *ch_prime = encrypt(key, *ch_prime);
    }
}

void release_memory(char* words[], int num_words)
{
    while (num_words)
        free(words[--num_words]);
}