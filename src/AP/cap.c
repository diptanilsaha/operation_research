/* Matrix Formation in Crew Assignment Problem */
#include <stdio.h>
#include <stdlib.h>

void print_time(float matrix[20][2], int n, int flight[20]) {
    int i;
    printf("\nFlight Number\tDeparture\tArrival");
    for(i=0; i<n; i++) {
        printf("\n%d\t%.2f\t%.2f", flight[i], matrix[i][0], matrix[i][1]);
    }
}

void print_matrix(float matrix[20][20], int n) {
    int i, j;
    printf("\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("\t%.2f", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_final_matrix(float matrix[20][20], int n, int sign_matrix[20][20]) {
    int i, j;
    printf("\nFinal Matrix");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            printf("\t%.2f", matrix[i][j]);
            if(sign_matrix[i][j]) {
                printf("*");
            }
        }
        printf("\n");
    }
}

void get_matrix(float matrix[20][20], float matrix1[20][20], float matrix2[20][20], int sign_matrix[20][20], int n) {
    int i, j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(matrix1[i][j] >= matrix2[i][j]) {
                matrix[i][j] = matrix2[i][j];
                sign_matrix[i][j]++;
            } else {
                matrix[i][j] = matrix1[i][j];
            }
        }
    }
}

int main() {
    char source[20], destination[20];
    int n;
    float dmatrix[20][2], rmatrix[20][2], layover; //depart matrix and return matrix
    int dflight[20], rflight[20];
    float matrix[20][20], matrix1[20][20], matrix2[20][20];
    printf("\nEnter Source: ");
    scanf("%s", source);
    printf("\nEnter Destination: ");
    scanf("%s", destination);
    printf("\nEnter number of flights originating: ");
    scanf("%d", &n);
    int i, j;
    printf("\n%s -> %s", source, destination);
    for(i=0; i<n; i++) {
        printf("\nFlight Number: ");
        scanf("%d", &dflight[i]);
        printf("Departure of Flight %d from %s: ", dflight[i], source);
        scanf("%f", &dmatrix[i][0]);
        printf("Arrival of Flight %d at %s: ", dflight[i], destination);
        scanf("%f", &dmatrix[i][1]);
    }
    printf("\n%s -> %s", destination, source);
    for(i=0; i<n; i++) {
        printf("\nFlight Number: ");
        scanf("%d", &rflight[i]);
        printf("Departure of Flight %d from %s: ", rflight[i], destination);
        scanf("%f", &rmatrix[i][0]);
        printf("Arrival of Flight %d at %s: ", rflight[i], source);
        scanf("%f", &rmatrix[i][1]);
    }
    printf("\nSource Flights");
    print_time(dmatrix, n, dflight);
    printf("\nReturn Flights");
    print_time(rmatrix, n, rflight);
    printf("\nEnter Layover period: ");
    scanf("%f", &layover);
    printf("\nCalculating Matrix for Crew based at %s", source);
    float diff;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            diff = rmatrix[j][0] - dmatrix[i][1];
            if(diff <= layover) {
                diff = diff + 24;
                if (diff <= layover) {
                    diff = diff + 24;
                }
            }
            matrix1[i][j] = diff;
        }
    }
    printf("\nCalculating Matrix for Crew based at %s", destination);
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            diff = dmatrix[i][0] - rmatrix[j][1];
            if(diff <= layover) {
                diff = diff + 24;
                if (diff <= layover) {
                    diff = diff + 24;
                }
            }
            matrix2[i][j] = diff;
        }
    }
    printf("\nCrew based at %s", source);
    print_matrix(matrix1, n);
    printf("\nCrew based at %s", destination);
    print_matrix(matrix2, n);
    int sign_matrix[20][20] = {0};
    get_matrix(matrix, matrix1, matrix2, sign_matrix, n);
    print_final_matrix(matrix, n, sign_matrix);
    return 0;
}
