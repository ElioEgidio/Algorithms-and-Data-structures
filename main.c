#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH   20
#define MAX_WORD_NUMBER  100
#define MAX_LINE_LENGTH  100

/* structure declaration */
typedef struct {
    char *word;
    int occurrences;
} index_t;

/* function prototypes */
void read_words(char *, index_t **, int *);
void read_text(char *, index_t [], int);
void display_index(index_t [], int);
int compare(char *, char *);

int main(int argc, char *argv[]) {
    index_t *index = NULL;
    int n;
    char filename1[20] = { "../word.txt" };
    char filename2[20] = { "../text.txt" };

    read_words(filename1, &index, &n);
    read_text(filename2, index, n);
    display_index(index, n);

    // Don't forget to free the dynamically allocated memory
    for(int l = 0; l < n;l++){
        free(index[l].word);
    }

    free(index);

    return EXIT_SUCCESS;
}

void read_words(char *name, index_t **index, int *num_ptr) {
    FILE *fp;
    int i;

    fp = fopen(name, "r");
    if (fp == NULL) {
        printf("Error opening file %s.\n", name);
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%i", &i);
    *index = (index_t*)malloc(i * sizeof(index_t));
    if (*index == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }


    for (int k = 0; k < i; k++) {
        char t_word[20] = {""};
        fscanf(fp, "%s", t_word);
        (*index)[k].word = malloc((strlen(t_word)+1)*sizeof (char));
        strcpy((*index)[k].word, t_word);
        (*index)[k].occurrences = 0;
    }

    *num_ptr = i;

    fclose(fp);
}

void read_text(char *name, index_t index[], int n) {
    char word[MAX_LINE_LENGTH+1];
    FILE *fp;

    fp = fopen(name, "r");
    if (fp == NULL) {
        printf("Error opening file %s.\n", name);
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s", word) != EOF) {
        for (int j = 0; j < n; j++) {
            if (compare(word, index[j].word) == 1) {
                index[j].occurrences++;
            }
        }
    }

    fclose(fp);
}

void display_index(index_t index[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s - %d occurrence(s)\n", index[i].word, index[i].occurrences);
    }
}

int compare(char *str1, char *str2) {
    int i;

    if (strlen(str1) != strlen(str2)) {
        return 0;
    }

    for (i = 0; i < strlen(str1); i++) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return 0;
        }
    }

    return 1;
}
