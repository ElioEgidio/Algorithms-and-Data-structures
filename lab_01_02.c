#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



typedef struct{
    char name[5];
    float coord_x , coord_y;
}rectangle;

void swap(float* xp, float* yp);
void selectionSort(float arr[], int n);

void swap(float* xp, float* yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform Selection Sort
void selectionSort(float arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

int main() {

    //rectangle rect_list[100];
    rectangle *rect_list;
    float *array_area;
    float *array_per;
    FILE* fin;
    int i = 0, n = 5, p = 5, num_of_rect = 0;
    float x = 0, y = 0;
    int temp = 0;


    fin = fopen("../fileIn.txt", "r");
    if(fin == NULL){
        printf("error in opening file");
        return 1;
    }
    fscanf(fin,"%i", &num_of_rect);
    rect_list = malloc(num_of_rect*2*sizeof (rectangle));
    if(rect_list==NULL){
        exit(1);
    }
    array_per = calloc(num_of_rect*2,sizeof (rectangle));
    array_area = calloc(num_of_rect*2,sizeof (rectangle));


    while(fscanf(fin,"%s%f%f",rect_list[i].name, &x/*rect_list[i].coord_x*/, &y/*rect_list[i].coord_y*/) != EOF){
        rect_list[i].coord_x = x;
        rect_list[i].coord_y = y;
        i++;
    }

    for(int l = 0; l < 100 && strcmp(rect_list[l].name, "") != 0; l++){
        for(int k = l +1; k < 100 && strcmp(rect_list[k].name, "") != 0; k++){
            if(strcmp(rect_list[l].name,rect_list[k].name) == 0){
                float area = fabsf(rect_list[l].coord_x - rect_list[k].coord_x) * fabsf(rect_list[l].coord_y - rect_list[k].coord_y);
                float per = (fabsf(rect_list[l].coord_x - rect_list[k].coord_x) + fabsf(rect_list[l].coord_y - rect_list[k].coord_y)) * 2;

                array_area[temp] = area;
                array_per[temp] = per;
                temp++;
                printf("%s area = %f perimiter = %f \n", rect_list[l].name, area, per);
            }
        }
    }
    selectionSort(array_area,n);
    selectionSort(array_per,p);

    free(rect_list);
    free(array_per);
    free(array_area);

    return 0;
}
