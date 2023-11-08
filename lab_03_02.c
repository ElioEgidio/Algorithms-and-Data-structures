#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct node {
    char* name_surname;
    char* id;
    char* date_hiring;
    int salary;

    struct node *left, *right;

}employee;

void read_file(employee** head);
employee* insert(char name[], char id[], char date[], int salary,employee *temp);
employee* insertEmpty(char name[], char id[], char date[], int salary, employee *temp);
employee* new_element();
void printEmployee(employee* head, char name[],char path[]);
void printPath(employee* head, char path[]);
void freee(employee* head);


int main(){
    char name[50], path[50];
    employee * head = NULL;
    read_file(&head);
    printf("insert name_surname and a +/- string line to read in that order the list:\n");
    scanf("%s %s", name, path);
    printEmployee(head, name, path);
    freee(head);
    return 0;
}
void read_file(employee** head){
    FILE * fp;
    fp = fopen("../text.txt", "r");

    char name_surname[50];
    char id[17];
    char date_hiring[11];
    int salary = 0;

    employee *tmp = NULL;
    int flag = 0;

    while(fscanf(fp,"%s %s %s %i", name_surname, id,date_hiring, &salary) != EOF){
        if(flag == 0){
            tmp = insertEmpty(name_surname, id, date_hiring, salary,tmp);
            flag++;
        }else{
            tmp = insert(name_surname, id, date_hiring, salary,tmp);
        }
    }
    *head = tmp;

}

employee* insert(char name[], char id[], char date[], int salary, employee *temp){
    employee * new;
    new = new_element();

    new -> left = NULL;

    new->name_surname = strdup(name);
    new->id = strdup(id);
    new->date_hiring = strdup(date);
    new->salary = salary;

    new->right = temp;
    temp->left = new;
    temp = new;

    return temp;

}
employee* insertEmpty(char name[], char id[], char date[], int salary, employee *temp){
    employee * new;
    new = new_element();

    new->left = NULL;

    new->name_surname = strdup(name);
    new->id = strdup(id);
    new->date_hiring = strdup(date);
    new->salary = salary;

    new->right = NULL;

    temp = new;

    return temp;
}

employee* new_element(){
    employee* node;
    node = malloc(sizeof (employee));
    if(node == NULL){
        exit(1);
    }
    return node;
}

void freee(employee* head) {
    employee* tmp;

    while (head != NULL) {
        tmp = head;
        head = head->right;
        free(tmp->name_surname);
        free(tmp->id);
        free(tmp->date_hiring);
        free(tmp);
    }
}

void printEmployee(employee* head, char name[], char path[]){
    employee * p = head;
    while(p != NULL){
        if(strcmp(p->name_surname,name) == 0){
            printf("%s %s %s %i\n", p->name_surname, p->id,p->date_hiring,p->salary);
            printPath(p,path);
            break;
        }
        p = p->right;
    }
}

void printPath(employee* head, char path[]){
    printf("%s - ",head->name_surname);
    char name[50];
    for(int i = 0; i < strlen(path); i++){
        if(path[i] == '+'){
            if(head->right != NULL){
                head = head->right;
            }

        }
        else{
            if(head->left != NULL){
                head = head->left;
            }
        }
        printf("%s - ",head->name_surname);
    }
}
