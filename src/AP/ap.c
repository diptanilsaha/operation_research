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

int matrix_input(int matrix[20][20], int maximize) {
    int n;
    printf("\nNumber of rows: ");
    scanf("%d", &n);
    int i, j;
    printf("\nMaze:\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            scanf("%d", &matrix[i][j]);
            if(matrix[i][j] == -1) {
                if(maximize) {
                    matrix[i][j] = -99999;
                } else {
                    matrix[i][j] = 99999;
                }
            }
        }
    }
    return n;
}

void convert_max_to_min(int matrix[20][20], int n) {
    int i, j, max_value = matrix[0][0];
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(max_value < matrix[i][j]) {
                max_value = matrix[i][j];
            }
        }
    }
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            matrix[i][j] = max_value - matrix[i][j];
        }
    }
}

void row_minimize(int matrix[20][20], int n) {
    int i, j, min;
    for(i=0; i<n; i++) {
        min = 9999;
        for(j=0; j<n; j++) {
            if(min > matrix[i][j]) {
                min = matrix[i][j];
            }
        }
        for(j=0; j<n; j++) {
            matrix[i][j] = matrix[i][j] - min;
        }
    }
}

void col_minimize(int matrix[20][20], int n) {
    int i, j, min;
    for(j=0; j<n; j++) {
        min = 9999;
        for(i=0; i<n; i++) {
            if(min > matrix[i][j]) {
                min = matrix[i][j];
            }
        }
        for(i=0; i<n; i++) {
            matrix[i][j] = matrix[i][j] - min;
        }
    }
}

void copy_matrix(int original[20][20], int duplicate[20][20], int n) {
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            duplicate[i][j] = original[i][j];
        }
    }
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

void get_min_row_col(int row_col[2][20], int n, int result[3]) {
    int min_row = 99999, row_index = 0;
    int min_col = 99999, col_index = 0;
    int i;
    for(i=0; i<n; i++) {
        if((min_row > row_col[0][i])) {
            if(!row_col[0][i])
            continue;
            min_row = row_col[0][i];
            row_index = i;
        }
    }
    for(i=0; i<n; i++) {
        if((min_col > row_col[1][i])) {
            if(!row_col[1][i])
            continue;
            min_col = row_col[1][i];
            col_index = i;
        }
    }
    if(min_row <= min_col) {
        result[0] = 0;
        result[1] = row_index;
        result[2] = min_row;
    } else {
        result[0] = 1;
        result[1] = col_index;
        result[2] = min_col;
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
    printf("\nFinding Optimality: ");
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
                    if(!matrix[result[1]][i] && sign_matrix[result[1]][i] < 2) {
                        row_col[1][i]--;
                    }
                }
            } else {
                for(i=0; i<n; i++) {
                    sign_matrix[i][result[1]]++;
                    if(!matrix[i][result[1]] && sign_matrix[i][result[1]] < 2) {
                        row_col[0][i]--;
                    }
                }
            }
            optimal++;
            printf("\nLine %d is drawn", optimal);
            printf("\nSignature Matrix:\n");
            print_matrix(sign_matrix, n);
            getchar();
        }
        if (optimal >= n) {
            // printf("\nOptimized Matrix\n---------\n");
            // print_matrix(matrix, n);
            printf("\nOptimality attained.");
            break;
        }
        printf("\nMatrix is not optimzed.");
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
        printf("\nMatrix reduced.");
        print_matrix(matrix, n);
        printf("\nGoing for another iteration");
        getchar();
    }
}

void assignment_problem(int matrix[20][20], int n, int solution[20]) {
    int result[3], count = 0;
    int row_col[2][20], sign_matrix[20][20] = {0}, i, zero_index;
    zero_count(matrix, row_col, n);
    while(!all_array_zero(row_col, n)) {
        get_min_row_col(row_col, n, result);
        printf("\n");
        for(i=0; i<n; i++) {
            printf("\t%d", row_col[0][i]);
        }
        printf("\n");
        for(i=0; i<n; i++) {
            printf("\t%d", row_col[1][i]);
        }
        if(!result[0]) {
            for(i=0; i<n; i++) {
                if(!sign_matrix[result[1]][i] && !matrix[result[1]][i]) {
                    zero_index = i;
                    solution[result[1]] = i;
                    break;
                }
            }
            for(i=0; i<n; i++) {
                sign_matrix[i][zero_index]++;
                if(!matrix[i][zero_index] && sign_matrix[i][zero_index] < 2) {
                    row_col[0][i]--;
                }
            }
            if(result[2] > 1) {
                for(i=0; i<n; i++) {
                    sign_matrix[result[1]][i]++;
                    if(!matrix[result[1]][i] && sign_matrix[result[1]][i] < 2) {
                        row_col[1][i]--;
                    }
                }
                row_col[0][result[1]] = 0;
            }
            row_col[1][zero_index] = 0;
        } else {
            for(i=0; i<n; i++) {
                if(!sign_matrix[i][result[1]] && !matrix[i][result[1]]) {
                    zero_index = i;
                    solution[i] = result[1];
                    break;
                }
            }
            for(i=0; i<n; i++) {
                sign_matrix[zero_index][i]++;
                if(!matrix[zero_index][i] && sign_matrix[zero_index][i] < 2) {
                    row_col[1][i]--;
                }
            }
            if(result[2] > 1) {
                for(i=0; i<n; i++) {
                    sign_matrix[i][result[1]]++;
                    if(!matrix[i][result[1]] && sign_matrix[i][result[1]] < 2) {
                        row_col[0][i]--;
                    }
                }
                row_col[1][result[1]] = 0;
            }
            row_col[0][zero_index] = 0;
        }
        count++;
        printf("\nSolutions found: %d", count);
        print_matrix(sign_matrix, n);
        getchar();
    }
}


int main() {
    int matrix[20][20], rows, solution[20], working_matrix[20][20];
    int maximize = 0, i, cost = 0;
    printf("\nMaximization? (0/1): ");
    scanf("%d", &maximize);
    rows = matrix_input(working_matrix, maximize);
    copy_matrix(working_matrix, matrix, rows);
    if(maximize) {
        convert_max_to_min(matrix, rows);
        printf("\nMatrix converted from Maximization to Minimization\n");
        print_matrix(matrix, rows);
        getchar();
    }
    row_minimize(matrix, rows);
    col_minimize(matrix, rows);
    printf("\nRow and Column Reduced Matrix\n");
    print_matrix(matrix, rows);
    getchar();
    hungarian_method(matrix, rows);
    assignment_problem(matrix, rows, solution);
    printf("\nWorker\tJob\tCost");
    printf("\n------\t---\t----");
    for(i=0; i<rows; i++) {
        printf("\n%d\t%d\t%d", i+1, solution[i] + 1, working_matrix[i][solution[i]]);
        cost = cost + working_matrix[i][solution[i]];
    }
    printf("\nTotal Cost = %d", cost);
    return 0;
}
