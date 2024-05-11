#include "column.c"
#include "cdataframe.c"

#include <time.h>
#include <stdlib.h>

int main() {
    COLUMN *col1 = create_column("col1");
    COLUMN *col2 = create_column("col2");
    COLUMN *col3 = create_column("col3");

    int n;
    srand(time(NULL));

    for(int i = 0; i < 6; i++) {
        n = rand() % 10;
        insert_value(col1, n);
    }
    for(int i = 0; i < 6; i++) {
        n = rand() % 10;
        insert_value(col2, n);
    }
    for(int i = 0; i < 6; i++) {
        n = rand() % 10;
        insert_value(col3, n);
    }

    CDATAFRAME *cdf = create_cdataframe();
    add_col(cdf, col1);
    add_col(cdf, col2);
    add_col(cdf, col3);

    print_col_name(cdf);
    print_cdataframe(cdf);
    print_nb_col(cdf);
    print_nb_rows(cdf);

    printf("%d\n", get_nb_greater_cdf(cdf, 3));
    printf("%d\n", get_nb_lower_cdf(cdf, 3));
    printf("%d\n", get_occurrence_cdf(cdf, 3));

    return 0;
}
