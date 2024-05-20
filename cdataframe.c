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

// Add all column given in parameter to the cdf
void hard_fill(CDATAFRAME *cdf, COLUMN **columns, int nb_col) {
    for (int i = 0; i < nb_col; i++) {
        add_col(cdf, columns[i]);
    }
}

// Interactive way to fill the cdf
void dynamic_fill(CDATAFRAME *cdf, int nb_col, int nb_rows) {
    for(int i = 0; i < nb_col; i++) {
        char title;
        printf("give a name to the column %d:", i);
        scanf("%s", &title);
        fflush(stdin);
        COLUMN *column = create_column(&title);
        for(int j = 0; j < nb_rows; j++) {
            int val;

            printf("Column %d value %d:", i, j);
            scanf("%d", &val);
            fflush(stdin);
            insert_value(column, val);
        }
        add_col(cdf, column);
    }
}

// Add a column to the cdataframe
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

    // we change the number nb_rows if new col have more
    // rows than the actual one with the more rows
    if (cdf -> columns[cdf -> nb_col - 1] -> log_size > cdf -> nb_rows) {
        cdf -> nb_rows = cdf -> columns[cdf -> nb_col - 1] -> log_size;
    }
    return 1;
}

// Delete a column at the index given
int del_col(CDATAFRAME *cdf, int index) {
    //check if cdf is empty or deleted
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

// Add a given row to the cdf
int add_row(CDATAFRAME  *cdf, int *row) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return 0;
    }

    // for each column, we insert the value at the right pos in row array
    for (int i = 0; i < cdf -> nb_col; i++) {
        insert_value(cdf -> columns[i], row[i]);
    }
    cdf -> nb_rows += 1;
    return 1;
}

// Remove a row at the index given
int del_row(CDATAFRAME *cdf, int index) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return 0;
    }

    //for each column, we move all value one index higher
    for (int i = 0; i < cdf -> nb_col; i++) {
        remove_value(cdf -> columns[i], index);
    }
    cdf -> nb_rows -= 1;
    return 1;
}

// rename the column at the index given
void rename_col(CDATAFRAME *cdf, int index, char *title) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    cdf -> columns[index] -> title = title;
}

// print all columns from the cdataframe
void print_cdataframe(CDATAFRAME *cdf) {
    //check if cdf is empty or deleted
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

// Print name of all column
void print_col_name(CDATAFRAME *cdf) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    //print each column name
    for (int i = 0; i < cdf -> nb_col; i++) {
        printf("%s  ", cdf -> columns[i] -> title);
    }
    printf("\n");
}

// Print all rows between x and y (included)
void print_only_rows(CDATAFRAME *cdf, int x, int y) {
    //check if cdf is empty or deleted
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

// print all col between x and y (included)
void print_only_col(CDATAFRAME *cdf, int x, int y) {
    //check if cdf is empty or deleted
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

// Print number of row in the cdf
void print_nb_rows(CDATAFRAME *cdf) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    printf("NB Rows = %d\n", cdf -> nb_rows);
}

// Print number of column in the cdf
void print_nb_col(CDATAFRAME *cdf) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    printf("NB Columns = %d\n", cdf -> nb_col);
}

// Check if a value is in the cdf
int is_value_in(CDATAFRAME *cdf, int val) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return -1;
    }

    int found = 0;
    int index = 0;
    // search in all column if the value is there
    // and stop when it founds the value in one of the column
    // or stop when searched through all column
    while (!found && index < cdf -> nb_col) {
        int check_occurrences = get_occurrence_col(cdf -> columns[index], val);
        if (check_occurrences > 0) {
            found = 1;
        }
        index += 1;
    }
    return found;
}

// Edit the value at the pos (x, y) in the cdf
void edit_value(CDATAFRAME *cdf, int val, int x, int y) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return;
    }

    //check if x and y coord are in the table range
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cdf -> columns[x] -> data[y] = val;
}

// Return number of value greater than val in the cdf
int get_nb_greater_cdf(CDATAFRAME  *cdf, int val) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return 0;
    }

    int nb_greater = 0;
    // check number of value greater than val in each column in cdf
    // and add them to nb_greater
    for (int i = 0; i < cdf -> nb_col; i++) {
        int col_greater = get_nb_greater_col(cdf -> columns[i], val);
        nb_greater += col_greater;
    }
    return nb_greater;
}

// Return number of value lower than val in the cdf
int get_nb_lower_cdf(CDATAFRAME  *cdf, int val) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return 0;
    }

    int nb_lower = 0;
    // check number of value lower than val in each column in cdf
    // and add them to nb_lower
    for (int i = 0; i < cdf -> nb_col; i++) {
        int col_lower = get_nb_lower_col(cdf -> columns[i], val);
        nb_lower += col_lower;
    }
    return nb_lower;
}

// Return number of occurrence of val in the cdf
int get_occurrence_cdf(CDATAFRAME  *cdf, int val) {
    //check if cdf is empty or deleted
    int check_editable = is_editable(cdf);
    if (!check_editable) {
        return 0;
    }

    int nb_occ = 0;
    // check occurrence of val in each column in cdf
    // and add them to nb_occ
    for (int i = 0; i < cdf -> nb_col; i++) {
        int col_occ = get_occurrence_col(cdf -> columns[i], val);
        nb_occ += col_occ;
    }
    return nb_occ;
}