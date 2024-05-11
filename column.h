#ifndef CDATAFRAME_COLUMN_H
#define CDATAFRAME_COLUMN_H

#define REALOC_SIZE 256

typedef struct{
    char *title; //title of the column
    int log_size; // logical size
    int phys_size; // physical size
    int *data;
} COLUMN;

/**
 * @brief : Create a new column
 * @param1 : Column title
 * @return : Pointer to created column
*/
COLUMN *create_column(char *title);

/**
 * @brief : Add a new value to a column
 * @param1 : Pointer to a column
 * @param2 : The value to be added
 * @return : 1 if the value is added 0 otherwise
*/
int insert_value(COLUMN *col, int value);

/**
 * @brief : Free allocated memory
 * @param : Pointer to a column
*/
void delete_column(COLUMN **col);

/**
 * @brief: Print a column content
 * @param: Pointer to a column
*/
void print_col(COLUMN *col);

/**
 * @brief: Get the number of occurrence of x in the column
 * @param1: Pointer to a column
 * @param2: Value to search
*/
int get_occurrence_col(COLUMN *col, int x);

/**
 * @brief: Get the value at the index x
 * @param1: Pointer to a column
 * @param2: Index of the value
*/
int get_val_at(COLUMN *col, int x);

/**
 * @brief: Get number of greater value than x
 * @param1: Pointer to a column
 * @param2: Number we are checking
*/
int get_nb_greater_col(COLUMN *col, int x);

/**
 * @brief: Get number of lower value than x
 * @param1: Pointer to a column
 * @param2: Number we are checking
*/
int get_nb_lower_col(COLUMN *col, int x);

#endif //CDATAFRAME_COLUMN_H