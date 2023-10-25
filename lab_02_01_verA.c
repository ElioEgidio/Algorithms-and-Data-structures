#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *str;
}word;

void readFile(char *, word**, int*);
void sort(word*, int num);


int main(int argc , char *argv[]) {
    word *list_of_wrd_str = NULL;
    int num = 0;
    readFile(argv[1], &list_of_wrd_str, &num);
    sort(list_of_wrd_str, num);

    for(int i = 0; i < num; i++){
        free(list_of_wrd_str[i].str);
    }
    free(list_of_wrd_str);
    return 0;
}

void readFile(char *filename, word**list, int*num){
    FILE* fp;
    int i = 0;
    word* t_list;
    fp = fopen(filename, "r");

    if(fp == NULL){
        exit(1);
    }
    fscanf(fp,"%i",&i);

    t_list = malloc(i * sizeof (word));
    if(t_list == NULL){
        exit(1);
    }
    for(int k = 0; k < i; k++){
        char t_word[100] = {""};
        fscanf(fp,"%s",t_word);
        t_list[k].str = malloc((strlen(t_word)+1)*sizeof (char));
        strcpy(t_list[k].str,t_word);
    }
    *num = i;
    fclose(fp);
    *list = t_list;
}

void sort(word*list, int num){
    char temp[100] = {""};
    for(int i=0;i<num;i++)
        for(int j=i+1;j<num;j++){
            if(strcmp(list[i].str,list[j].str)>0){
                strcpy(temp,list[i].str);
                strcpy(list[i].str,list[j].str);
                strcpy(list[j].str,temp);
            }
        }

    for(int l = 0; l < num; l++){
        printf("%s\n", list[l].str);
    }
}
