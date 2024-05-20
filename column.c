#include <stdio.h>
#include <stdlib.h>
#include "column.h"

//create a new column with a set title
COLUMN *create_column(char *title) {
    // allocate memory to the column
    COLUMN *ptr_col = (COLUMN*) malloc(sizeof(COLUMN));

    //set parameter of the column
    ptr_col -> title = title;
    ptr_col -> log_size = 0;
    ptr_col -> phys_size = 0;
    ptr_col -> data = NULL;

    return ptr_col;
}

// insert the value given in the column
int insert_value(COLUMN *col, int value) {

    //add 256 more line to the column if all lines are taken
    if (col -> log_size == col -> phys_size) {

        int new_data_size = col->phys_size + REALOC_SIZE;
        int *new_data = (int *) realloc(col->data, new_data_size * sizeof(int));

        //if the allocation fail
        if (new_data == NULL) {
            printf("INSERT VALUE -> Allocation Failed\n");
            return 0;
        } else {
            //set new data and update physical size
            col -> data = new_data;
            col->phys_size += REALOC_SIZE;
        }
    }

    //insert the value in the column
    col -> data[col -> log_size++] = value;
    return 1;
}

void remove_value(COLUMN *col, int index) {
    // move each value up from the given index
    for (int j = index; j < col -> log_size - 1; j++) {
        col -> data[j] = col -> data[j + 1];
    }

    //set the last array to 0 because not used anymore
    col -> data[col -> log_size - 1] = 0;
    col -> log_size -= 1;
}

//delete a column
void delete_column(COLUMN **col) {
    //free memory of the data of the column
    free((*col) -> data);
    (*col) -> data = NULL;

    //free memory of the column
    free(*col);
    *col = NULL;
}


// print a column
void print_col(COLUMN *col) {
    //if column was deleted
    if (col == NULL) {
        printf("this column was deleted\n");
        return;
    }
    //if column is empty
    if(col -> data == NULL) {
        printf("this column is empty\n");
        return;
    }

    //print each value (with index and memory address) in col data
    printf("\nName: %s\n", col -> title);
    for (int i = 0; i < col -> log_size; i++) {
        int *ptr_val = &(col -> data[i]);
        printf("[%d] (%p) %d\n", i, ptr_val, col -> data[i]);
    }
}

//get occurrence of a value in a column
int get_occurrence_col(COLUMN *col, int x) {
    //if column was deleted
    if (col == NULL) {
        printf("this column was deleted\n");
        return 0;
    }

    //we go through all the data and if the val is x we add 1 to occurrence
    int occurrence = 0;
    for (int i = 0; i < col -> log_size; i++) {
        if (col -> data[i] == x) {
            occurrence += 1;
        }
    }
    return occurrence;
}

//get value at index given
int get_val_at(COLUMN *col, int x) {
    //if column was deleted
    if (col == NULL) {
        printf("this column was deleted\n");
        return 0;
    }

    //if x is greater than number of val in the column
    if (x >= col -> log_size) {
        printf("Index out of range\n");
        return 0;
    }

    return col -> data[x];
}

//get number of value greater than x
int get_nb_greater_col(COLUMN *col, int x) {
    //if column was deleted
    if (col == NULL) {
        printf("this column was deleted\n");
        return 0;
    }

    //we go through all the data and if the val is higher than
    // x we add 1 to occurrence
    int occurrence = 0;
    for (int i = 0; i < col -> log_size; i++) {
        if (col -> data[i] > x) {
            occurrence += 1;
        }
    }
    return occurrence;
}

//get number of value lower than x
int get_nb_lower_col(COLUMN *col, int x) {
    //if column was deleted
    if (col == NULL) {
        printf("this column was deleted\n");
        return 0;
    }

    //we go through all the data and if the val is lower than
    // x we add 1 to occurrence
    int occurrence = 0;
    for (int i = 0; i < col->log_size; i++) {
        if (col->data[i] < x) {
            occurrence += 1;
        }
    }
    return occurrence;
}