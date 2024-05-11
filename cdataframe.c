#include "cdataframe.h"

#include <stdio.h>
#include <stdlib.h>


//create a cdataframe
CDATAFRAME *create_cdataframe() {
    //allocate memory for the DataFrame
    CDATAFRAME *ptr_cdf = (CDATAFRAME *) malloc(sizeof(CDATAFRAME));

    //set parameter of the DataFrame
    ptr_cdf -> nb_rows = 0;
    ptr_cdf -> nb_col = 0;
    ptr_cdf -> columns = NULL;

    return ptr_cdf;
}

int is_editable(CDATAFRAME *cdf) {
    //if cdataframe was deleted
    if(cdf == NULL) {
        printf("This cdataframe was deleted");
        return 0;
    }

    //if cdataframe is empty
    if (cdf -> columns == NULL) {
        printf("This cdataframe is empty");
        return 0;
    }
    return 1;
}


//delete a cdataframe
void delete_cdataframe(CDATAFRAME **cdf) {
    //free memory for all column in the cdataframe
    for (int i = 0; (*cdf) -> nb_col > i; i++) {
        delete_column(&(*cdf) -> columns[i]);
    }
    free((*cdf) -> columns);
    (*cdf) -> columns = NULL;

    //free memory of the cdataframe
    free(*cdf);
    *cdf = NULL;
}

//add a column to the cdataframe
int add_col(CDATAFRAME *cdf, COLUMN *col) {
    //if cdataframe is deleted
    if(cdf == NULL) {
        printf("This cdataframe was deleted");
        return 0;
    }

    //Set new allocation size for each new col
    int new_size = cdf -> nb_col + 1;
    COLUMN **new_data = (COLUMN **) realloc(cdf -> columns, new_size * sizeof(COLUMN));

    //if the allocation fail
    if (new_data == NULL) {
        printf("add_col -> Allocation Failed\n");
        return 0;
    }

    cdf -> columns = new_data;
    cdf -> columns[cdf -> nb_col++] = col;

    //we change the number nb_rows if new col have more
    // rows than the actual one with the more rows
    if (cdf -> columns[cdf -> nb_col - 1] -> log_size > cdf -> nb_rows) {
        cdf -> nb_rows = cdf -> columns[cdf -> nb_col - 1] -> log_size;
    }
    return 1;
}

int del_col(CDATAFRAME *cdf, int index) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return 0;
    }

    //delete the column at the index given
    delete_column(&cdf -> columns[index]);

    //move all column to the left
    for (int i = index + 1; i < cdf -> nb_col; i++) {
        cdf -> columns[i-1] = cdf -> columns[i];
    }

    cdf -> nb_col -= 1;
    return 1;
}

void rename_col(CDATAFRAME *cdf, int index, char *title) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    cdf -> columns[index] -> title = title;
}

// print all columns from the cdataframe
void print_cdataframe(CDATAFRAME *cdf) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    //print all column with their index
    for (int i = 0; i < cdf -> nb_rows; i++) {
        printf("[%d] ", i);
        for(int j = 0; j < cdf -> nb_col; j++) {
            int val = get_val_at(cdf -> columns[j], i);
            printf("%d  ", val);
        }
        printf("\n");
    }
}

void print_col_name(CDATAFRAME *cdf) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    for (int i = 0; i < cdf -> nb_col; i++) {
        printf("%s  ", cdf -> columns[i] -> title);
    }
    printf("\n");
}

void print_only_rows(CDATAFRAME *cdf, int x, int y) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    //print all rows between x and y
    for (int i = x; i <= y; i++) {
        printf("[%d] ", i);
        for (int j = 0; j < cdf->nb_col; j++) {
            int val = get_val_at(cdf->columns[j], i);
            printf("%d  ", val);
        }
        printf("\n");
    }
}

void print_only_col(CDATAFRAME *cdf, int x, int y) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    //print all columns between x and y
    for (int i = 0; i < cdf -> nb_rows; i++) {
        printf("[%d] ", i);
        for (int j = x; j <= y; j++) {
            int val = get_val_at(cdf->columns[j], i);
            printf("%d  ", val);
        }
        printf("\n");
    }
}

void print_nb_rows(CDATAFRAME *cdf) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    printf("NB Rows = %d\n", cdf -> nb_rows);
}

void print_nb_col(CDATAFRAME *cdf) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    printf("NB Columns = %d\n", cdf -> nb_col);
}

int is_value_in(CDATAFRAME *cdf, int val) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return -1;
    }

    int found = 0;
    int index = 0;
    while (!found && index < cdf -> nb_col) {
        int check_occurrences = get_occurrence_col(cdf -> columns[index], val);
        if (check_occurrences > 0) {
            found = 1;
        }
        index += 1;
    }
    return found;
}

void edit_value(CDATAFRAME *cdf, int val, int x, int y) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    cdf -> columns[x] -> data[y] = val;
}

int get_nb_greater_cdf(CDATAFRAME  *cdf, int val) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return 0;
    }

    int nb_greater = 0;
    for (int i = 0; i < cdf -> nb_col; i++) {
        int col_greater = get_nb_greater_col(cdf -> columns[i], val);
        nb_greater += col_greater;
    }
    return nb_greater;
}

int get_nb_lower_cdf(CDATAFRAME  *cdf, int val) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return 0;
    }

    int nb_lower = 0;
    for (int i = 0; i < cdf -> nb_col; i++) {
        int col_lower = get_nb_lower_col(cdf -> columns[i], val);
        nb_lower += col_lower;
    }
    return nb_lower;
}

int get_occurrence_cdf(CDATAFRAME  *cdf, int val) {
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return 0;
    }

    int nb_occ = 0;
    for (int i = 0; i < cdf -> nb_col; i++) {
        int col_occ = get_occurrence_col(cdf -> columns[i], val);
        nb_occ += col_occ;
    }
    return nb_occ;
}