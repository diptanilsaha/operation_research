/*
Assignment Problem
Optimality using Hungarian Method implemented.
However, Multiple Solution Assignment Problem will not work.
*/

#include <stdio.h>
#include <stdlib.h>

void print_matrix(int matrix[20][20], int n) {
    printf("\n\n");
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("\t%d", matrix[i][j]);
        }
        printf("\n");
    }
}

int matrix_input(int matrix[20][20]) {
    int n;
    scanf("%d", &n);
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    return n;
}

void zero_count(int matrix[20][20], int row_col[2][20], int n) {
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(!matrix[i][j])
            row_col[0][i]++;
        }
    }
    for(j=0; j<n; j++) {
        for(i=0; i<n; i++) {
            if(!matrix[i][j])
            row_col[1][j]++;
        }
    }
}

int all_array_zero(int row_col[2][20], int n) {
    int i;
    for(i=0; i<n; i++) {
        if(row_col[0][i]) {
            return 0;
        }
        if(row_col[1][i]) {
            return 0;
        }
    }
    return 1;
}

void get_max_row_col(int row_col[2][20], int n, int result[2]) {
    int max_row = row_col[0][0], row_index = 0;
    int max_col = row_col[1][0], col_index = 0;
    int i;
    for(i=0; i<n; i++) {
        if(max_row < row_col[0][i]) {
            max_row = row_col[0][i];
            row_index = i;
        }
    }
    for(i=0; i<n; i++) {
        if(max_col < row_col[1][i]) {
            max_col = row_col[1][i];
            col_index = i;
        }
    }
    if(max_row >= max_col) {
        result[0] = 0;
        result[1] = row_index;
    } else {
        result[0] = 1;
        result[1] = col_index;
    }
}

void init_matrix_zero(int matrix[20][20], int n) {
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            matrix[i][j] = 0;
        }
    }
}

void hungarian_method(int matrix[20][20], int n) {
    int row_col[2][20] = {0}, i, j;
    int optimal = 0, sign_matrix[20][20] = {0};
    int result[2], min_value;
    while(1) {
        zero_count(matrix, row_col, n);
        init_matrix_zero(sign_matrix, n);
        optimal = 0;
        while(!all_array_zero(row_col, n)) {
            get_max_row_col(row_col, n, result);
            row_col[result[0]][result[1]] = 0;
            if(!result[0]) {
                for(i=0; i<n; i++) {
                    sign_matrix[result[1]][i]++;
                    if(!matrix[result[1]][i]) {
                        row_col[1][i]--;
                    }
                }
            } else {
                for(i=0; i<n; i++) {
                    sign_matrix[i][result[1]]++;
                    if(!matrix[i][result[1]]) {
                        row_col[0][i]--;
                    }
                }
            }
            optimal++;
        }
        if (optimal >= n) {
            printf("\nOptimized Matrix\n---------\n");
            print_matrix(matrix, n);
            break;
        }
        min_value = 99999;
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                if(!sign_matrix[i][j] && min_value > matrix[i][j]) {
                    min_value = matrix[i][j];
                }
            }
        }
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                if(sign_matrix[i][j] == 2) {
                    matrix[i][j] = matrix[i][j] + min_value;
                }
                if (!sign_matrix[i][j]) {
                    matrix[i][j] = matrix[i][j] - min_value;
                }
            }
        }
    }
}


int main() {
    int matrix[20][20], rows;
    rows = matrix_input(matrix);
    hungarian_method(matrix, rows);
    return 0;
}
