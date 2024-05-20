#include "column.c"
#include "cdataframe.c"

#include <time.h>
#include <stdlib.h>

void main_menu(CDATAFRAME *cdf) {
    int exit = 0;

    printf("ALL POSSIBLE ACTION:\n");
    printf("1) Print cdataframe\n");
    printf("2) Print column name\n");
    printf("3) Print number of columns\n");
    printf("4) Print number of rows\n");
    printf("5) Print col from x to y\n");
    printf("6) Print row from x to y\n");
    printf("7) Add a column\n");
    printf("8) Remove a column\n");
    printf("9) Rename a column\n");
    printf("10) Add a row \n");
    printf("11) Remove a row \n");
    printf("12) Replace a specific value\n");
    printf("13) Check if a value is in the cdf\n");
    printf("14) Get number of value greater than x\n");
    printf("15) Get number of value greater than x\n");
    printf("16) Get number of value lesser than x\n");
    printf("0) Exit the program\n\n");

    int choice;

    printf("Choose an option:");
    scanf("%d", &choice);
    fflush(stdin);

    int x, y;
    char title;
    switch (choice) {
        case 0:
            delete_cdataframe(&cdf);
            exit = 1;
            break;
        case 1:
            print_cdataframe(cdf);
            break;

        case 2:
            print_col_name(cdf);
            break;

        case 3:
            print_nb_col(cdf);
            break;

        case 4:
            print_nb_rows(cdf);
            break;

        case 5:
            printf("Start col:");
            scanf("%d", &x);
            fflush(stdin);
            printf("End col:");
            scanf("%d", &y);
            fflush(stdin);
            print_only_col(cdf, x, y);
            break;

        case 6:
            printf("Start row:");
            scanf("%d", &x);
            fflush(stdin);
            printf("End row:");
            scanf("%d", &y);
            fflush(stdin);
            print_only_rows(cdf, x, y);
            break;

        case 7:
            printf("name of the new column:");
            scanf("%s", &title);
            fflush(stdin);
            COLUMN *column = create_column(&title);
            for(int j = 0; j < cdf -> nb_rows; j++) {
                int val;

                printf("Column value %d:", j);
                scanf("%d", &val);
                fflush(stdin);
                insert_value(column, val);
            }
            add_col(cdf, column);
            break;

        case 8:
            printf("index of the column to delete:");
            scanf("%d", &x);
            fflush(stdin);
            del_col(cdf, x);
            break;

        case 9:
            printf("index of the column to rename:");
            scanf("%d", &x);
            fflush(stdin);
            printf("new name of the column:");
            scanf("%s", &title);
            fflush(stdin);
            rename_col(cdf, x, &title);
            break;

        case 10:
            int *row = malloc(sizeof(int) * cdf -> nb_rows);
            for(int j = 0; j < cdf -> nb_rows; j++) {
                int val;

                printf("row value %d:", j);
                scanf("%d", &val);
                fflush(stdin);
                row[j] = val;
            }
            add_row(cdf, row);
            free(row);
            break;

        case 11:
            printf("index of the row to delete:");
            scanf("%d", &x);
            fflush(stdin);
            del_row(cdf, x);
            break;

        case 12:
            printf("index of the column:");
            scanf("%d", &x);
            fflush(stdin);
            printf("index of the row:");
            scanf("%d", &y);
            fflush(stdin);
            int z;
            printf("new value:");
            scanf("%d", &z);
            fflush(stdin);
            edit_value(cdf, z, x, y);
            break;

        case 13:
            printf("value to check:");
            scanf("%d", &x);
            fflush(stdin);
            int is_in = is_value_in(cdf, x);
            if (is_in) printf("The value is in the cdf\n");
            else printf("The value is not in the cdf\n");
            break;

        case 14:
            printf("value to check:");
            scanf("%d", &x);
            fflush(stdin);
            int nb_occ = get_occurrence_cdf(cdf, x);
            printf("number of occurence of %d: %d\n", x, nb_occ);
            break;

        case 15:
            printf("value to check:");
            scanf("%d", &x);
            fflush(stdin);
            int nb_greater = get_nb_greater_cdf(cdf, x);
            printf("number of value greater than %d: %d\n", x, nb_greater);
            break;

        case 16:
            printf("value to check:");
            scanf("%d", &x);
            fflush(stdin);
            int nb_lower = get_nb_lower_cdf(cdf, x);
            printf("number of value greater than %d: %d\n", x, nb_lower);
            break;
    }
    printf("\n");

    if (!exit)
        main_menu(cdf);
}

//let you fill the cdataframe in dynamic mode
void dynamic_mode(CDATAFRAME *cdf, int nb_col, int nb_row) {
    dynamic_fill(cdf, nb_col, nb_row);
}

//fill cdataframe with random value
void hard_mode(CDATAFRAME *cdf, int nb_col, int nb_row) {
    int n;
    srand(time(NULL));

    char title[10];
    for(int i = 0; i < nb_col; i++) {
        printf("give a name to the column %d:", i);
        scanf("%9s", title);
        fflush(stdin);
        COLUMN *col = create_column(title);
        for(int j = 0; j < nb_row; j++) {
            n = rand() % 20;
            insert_value(col, n);
        }
        add_col(cdf, col);
        title[0] = '\0';
    }
}

int main() {
    CDATAFRAME *cdf = create_cdataframe();
    int nb_col, nb_row;
    int mode;

    printf("Choose number of column and number of rows for your c dataframe.\n");
    printf("Number of column:");
    scanf("%d", &nb_col);
    fflush(stdin);

    printf("Number of row:");
    scanf("%d", &nb_row);
    fflush(stdin);

    printf("Choose your mode (1 = Dynamic fill, 2 = Hard fill):");
    scanf("%d", &mode);
    fflush(stdin);
    if (mode == 1) {
        dynamic_mode(cdf, nb_col, nb_row);
    }
    else {
        hard_mode(cdf, nb_col, nb_row);
    }

    main_menu(cdf);

    return 0;
}
