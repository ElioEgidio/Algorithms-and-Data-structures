#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>


typedef struct node_s{
    char* word;
    int count;
    struct node_s* fr;
}node;

void read_file(node* head);
node* push(node*head,char word[]);
node* new_elements();
void tolow(char word[]);
void printList( node* head);


int main() {
    node* head = NULL;

    read_file(head);
    return 0;
}


//correct version
void read_file(node *head){
    FILE * fp;
    node* p;
    int start = 1;
    char cur[10];
    fp = fopen("../text.txt", "r");

    while(fscanf(fp,"%s", cur) != EOF){
        if(start == 1){
            tolow(cur);
            head = push(head, cur);
            start = 0;
        }else{
            p = head;
            int found = 0;
            while(p != NULL){
                tolow(cur);
                if(strcmp(cur,p->word) == 0){
                    found = 1;
                    p->count++;
                    break;
                }
                    p = p->fr;
            }
            if(!found){
                head = push(head,cur);
            }
        }
    }
    printList(head);

    while (head != NULL) {
        node* temp = head;
        head = head->fr;
        free(temp);
    }
}

node* new_elements(){
    node* node;
    node = malloc(sizeof (node));
    if(node == NULL){
        exit(1);
    }
    return node;
}
node* push(node* head,char word[]){
    node* new;
    new = new_elements();

    new->word = strdup(word);
    new->count = 1;
    new->fr = head;
    head = new;

    return head;
}


void tolow(char word[]){
    for(int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
}

void printList( node* head) {
     node* current = head;
    while (current != NULL) {
        printf("%s - %i -> ", current->word, current->count);
        current = current->fr;
    }
    printf("NULL\n");
}
