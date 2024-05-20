#ifndef CDATAFRAME_CDATAFRAME_H
#define CDATAFRAME_CDATAFRAME_H

#include "column.h"

typedef struct{
    COLUMN **columns; //a list of columns
    int nb_rows; //number of rows in the cdataframe
    int nb_col; //number of col in the cdataframe
} CDATAFRAME;

/**
 * @brief : Create a new cdf
 * @return : Pointer to created cdf
*/
CDATAFRAME *create_cdataframe();

/**
 * @brief : Check if the cdf was deleted/is empty
 * @param : Pointer to a cdf
 * @return : 1 if u can edit, 0 otherwise
*/
int is_editable(CDATAFRAME *cdf);

/**
 * @brief : Add all column given in parameter to the cdf
 * @param1 : Pointer to the cdf
 * @param2 : Pointer to an array of column
 * @param3: number of column in the array
*/
void hard_fill(CDATAFRAME  *cdf, COLUMN  **columns, int nb_col);

/**
 * @brief : interactive way to fill the cdf
 * @param1 : Pointer to the cdf
 * @param2 : number of column
 * @param3 : number of rows
*/
void dynamic_fill(CDATAFRAME  *cdf, int nb_col, int nb_rows);

/**
 * @brief : Add a column to the cdf
 * @param1 : Pointer to the cdf
 * @param2 : Pointer to a column
 * @return : 1 if successful, 0 otherwise
*/
int add_col(CDATAFRAME *cdf, COLUMN *col);

/**
 * @brief : Delete a column at the index given
 * @param1 : Pointer to the cdf
 * @param2 : index of the column that need to be deleted
 * @return : 1 if successful, 0 otherwise
*/
int del_col(CDATAFRAME *cdf, int index); // no check rn for index being in the dataframe

/**
 * @brief : Rename the column at the index given
 * @param1 : Pointer to the cdf
 * @param2 : index of the column
 * @param3 : new name
*/
void rename_col(CDATAFRAME *cdf, int index, char *title); // no check rn for index being in the dataframe

/**
 * @brief : Add a given row to the cdf
 * @param1 : Pointer to the cdf
 * @param2 :  row to add as an int array
 * @param3 : new name
*/
int add_row(CDATAFRAME *cdf, int *row); // no check rn for index being in the dataframe

/**
 * @brief : Remove a row at the index given
 * @param1 : Pointer to the cdf
 * @param2 :  index of the row to remove
 * @param3 : new name
*/
int del_row(CDATAFRAME *cdf, int index); // no check rn for index being in the dataframe

/**
 * @brief : Delete the cdf
 * @param : Pointer to the cdf
*/
void delete_cdataframe(CDATAFRAME **cdf);

/**
 * @brief : Print all the cdf
 * @param : Pointer to the cdf
*/
void print_cdataframe(CDATAFRAME *cdf);

/**
 * @brief : Print all rows between x and y (included)
 * @param1 : Pointer to the cdf
 * @param2 : start row index
 * @param3 : end row index
*/
void print_only_rows(CDATAFRAME *cdf, int x, int y); // no check rn for x and y being in the dataframe

/**
 * @brief : Print all col between x and y (included)
 * @param1 : Pointer to the cdf
 * @param2 : start col index
 * @param3 : end col index
*/
void print_only_col(CDATAFRAME *cdf, int x, int y); // no check rn for x and y being in the dataframe

/**
 * @brief : Print number of row in the cdf
 * @param : Pointer to the cdf
*/
void print_nb_rows(CDATAFRAME *cdf);

/**
 * @brief : Print number of column in the cdf
 * @param : Pointer to the cdf
*/
void print_nb_col(CDATAFRAME *cdf);

/**
 * @brief : Print name of all column
 * @param : Pointer to the cdf
*/
void print_col_name(CDATAFRAME *cdf);

/**
 * @brief : Check if a value is in the cdf
 * @param1 : Pointer to the cdf
 * @param2 : value we are checking
*/
int is_value_in(CDATAFRAME *cdf, int val);

/**
 * @brief : Edit the value at the pos (x, y) in the cdf
 * @param1 : Pointer to the cdf
 * @param2 : col index
 * @param3 : row index
*/
void edit_value(CDATAFRAME *cdf, int val, int x, int y); // no check rn for x and y being in the dataframe

/**
 * @brief : Return number of value greater than val in the cdf
 * @param1 : Pointer to the cdf
 * @param2 : value we are checking
*/
int get_nb_greater_cdf(CDATAFRAME  *cdf, int val);

/**
 * @brief : Return number of value lower than val in the cdf
 * @param1 : Pointer to the cdf
 * @param2 : value we are checking
*/
int get_nb_lower_cdf(CDATAFRAME  *cdf, int val);

/**
 * @brief : Return number of occurrence of val in the cdf
 * @param1 : Pointer to the cdf
 * @param2 : value we are checking
*/
int get_occurrence_cdf(CDATAFRAME  *cdf, int val);


#endif //CDATAFRAME_CDATAFRAME_H
