#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct node1 producer;
typedef struct node2 product;

void readProducerFile(producer**head);
void readProductFile(producer*head);
void testprint(producer*head);
producer *insert(char name[], char id[], producer* t);
product* insert_product(char name[], char id[],int price, product * t);
producer*  new_producer();
product* new_product();
void destroy (producer *);
void destroyProds(product *ptr);

struct node1{
    char name[20];
    char id[20];

    producer* next;
    product* right;
};

struct node2{
   char id[20];
   char* productName;
   int price;

   product *next;
};

int main() {
    producer* head_1 = NULL;
    readProducerFile(&head_1);
    readProductFile(head_1);
    producer* test = head_1;
    destroy(head_1);
    return 0;
}

void readProducerFile(producer**head){
    FILE* fp;
    fp = fopen("../producer.txt", "r");
    producer * t;

    char name[20], id[20];

    while (fscanf(fp, "%s %s", name, id) != EOF){
        t = insert(name, id, t);
    }
    *head = t;
}

producer *insert(char name[], char id[], producer* t){
    producer* new = NULL;
    new = new_producer();

    strcpy(new->name, name);
    strcpy(new->id,id);
    new->right = NULL;

    new->next = t;
    t = new;

    return t;
}
product *insert_product(char name[], char id[],int price, product* t){
    product* new = NULL;
    new = new_product();

    new->productName = strdup(name);
    strcpy(new->id,id);
    new->price = price;

    new->next = t;
    t = new;

    return t;
}

producer* new_producer(){
    producer* node;
    node = malloc(sizeof (producer));
    if(node == NULL){
        exit(1);
    }
    return node;
}
product* new_product(){
    product* node;
    node = malloc(sizeof (product));
    if(node == NULL){
        exit(1);
    }
    return node;
}

void readProductFile(producer*head){

    FILE* fp;
    fp = fopen("../product.txt", "r");
    product * t;

    char id[20], productName[20];
    int price = 0;


    while(fscanf(fp,"%s%s%i",id, productName,&price)!=EOF){
        producer *p = head;
        printf("%s - ",id);
        while(p != NULL){
            if(strcmp(p->id, id) == 0){
             p->right = insert_product(id,productName,price,p->right);
             break;
            }
            p = p->next;
        }
    }
    printf(" END \n");
    testprint(head);
}

void testprint(producer*head){
    while(head!=NULL){
        printf("\n%s ->  ",head->name);
        while(head->right != NULL){
            printf("model: %s price: %i (-) ",head->right->id,head->right->price);

            head->right = head->right->next;
        }printf(" END \n");
        head = head->next;
    }
}
void destroy(producer *head){
    producer *tmp1a;
    product *tmp2a;

    while (head != NULL) {
        tmp1a = head;
        head = head->next;
        tmp2a = tmp1a->right;
        destroyProds(tmp2a);
        free (tmp1a);
    }
}

void destroyProds(product *ptr) {
    product *tmp2a;

    while (ptr != NULL) {
        tmp2a = ptr;
        ptr = ptr->next;
        free(tmp2a->productName);
        free(tmp2a);
    }
}
