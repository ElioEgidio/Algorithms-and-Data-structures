#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//refer to 2D arrays page: 18

void malloc2d(char ***, int *num, char *);
void sort(char**list, int num);

int main(int argc, char *argv[]) {
    char **mat;
    int num = 0;

    malloc2d(&mat,&num, argv[1]);
    sort(mat, num);
    return 0;
}
//triple pointer!! o.o
void malloc2d(char ***list, int *num, char *filename){
    FILE* fp;
    int i = 0;
    char **t_list;
    fp = fopen(filename, "r");
    fscanf(fp, "%i", &i);

    t_list = malloc(i * sizeof (char *));
    if(t_list == NULL){
        exit(1);
    }
    for(int k = 0; k<i;k++){
        char t_word[100] = {""};
        fscanf(fp, "%s", t_word);
        t_list[k] = malloc((strlen(t_word)+1)*sizeof (char));
        strcpy(t_list[k], t_word);
        if(t_list[k] == NULL){
            exit(1);
        }
    }
    *num = i;
    *list = t_list;
}
void sort(char**list, int num){
    char *temp;
    for(int i=0;i<num;i++)
        for(int j=i+1;j<num;j++){
            if(strcmp(list[i],list[j])>0){
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }

    for(int l = 0; l < num; l++){
        printf("%s\n", list[l]);
    }
}
