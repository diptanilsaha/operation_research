// North West Corner Rule - Transportation Method.

#include <stdio.h>
#include <stdlib.h>

void print_cost_sd(int cost[100][100], int n, int m, int supply[100], int demand[100]) {
	int i, j;
	printf("\nCost Matrix\n");
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			printf("\t%d", cost[i][j]);
		}
		printf("\t%d\n", supply[i]);
	}
	for(i=0; i<m; i++) {
		printf("\t%d", demand[i]);
	}
	printf("\n");
}

void print_allo(int allo[100][100], int n, int m) {
	int i, j;
	printf("\nAllocation Matrix\n");
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			if(allo[i][j])
			printf("\t%d", allo[i][j]);
			else
			printf("\t*");
		}
		printf("\n");
	}
}

void print_sign(int sign[100][100], int n, int m) {
	int i, j;
	printf("\nSignature Matrix\n");
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			if(sign[i][j] == -1) {
				printf("\tx");
			} else {
				printf("\t%d", sign[i][j]);
			}
		}
		printf("\n");
	}
}

void nwcm(int cost[100][100], int n, int m, int supply[100], int demand[100]) {
	int sign[100][100] = {0}, allo[100][100] = {0};
	int i, j;
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			sign[i][j] = cost[i][j];
		}
	}
	int x = 0, y = 0, iter = 1;
	while(x<n && y<m) {
		system("cls");
		printf("\nIteration %d", iter);
		if(supply[x] > demand[y]) {
			allo[x][y] = demand[y];
			supply[x] = supply[x] - demand[y];
			demand[y] = 0;
			for(i=x; i<n; i++) {
				sign[i][y] = -1;
			}
			y++;
		} else if (supply[x] <= demand[y]) {
			allo[x][y] = supply[x];
			demand[y] = demand[y] - supply[x];
			supply[x] = 0;
			for(i=y; i<m; i++) {
				sign[x][i] = -1;
			}
			x++;
		}
		print_cost_sd(cost, n, m, supply, demand);
		print_allo(allo, n, m);
		print_sign(sign, n, m);
		iter++;
		getch();
	}
	int total = 0;
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			total = total + allo[i][j]*cost[i][j];
		}
	}
	printf("\nThe Transportation Path is %d", total);
}

int main() {
	int cost[100][100] = {0};
	int n, m;
	int supply[100], demand[100];

	printf("\nOrigin: ");
	scanf("%d", &n);
	printf("\nDestination: ");
	scanf("%d", &m);

	int i, j;
	printf("\nCost:\n");
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			scanf("%d", &cost[i][j]);
		}
	}
	int s, d;
	s = 0;
	printf("\nSupply: ");
	for(i=0; i<n; i++) {
		scanf("%d", &supply[i]);
		s = s + supply[i];
	}
	d = 0;
	printf("\nDemand: ");
	for(i=0; i<m; i++) {
		scanf("%d", &demand[i]);
		d = d + demand[i];
	}

	if (s != d) {
		if (s > d) {
			demand[m] = s - d;
			m++;
		} else {
			supply[n] = d - s;
			n++;
		}
		printf("\nCost was not balanced.");
	} else {
		printf("\nCost is already balanced.");
	}

	nwcm(cost, n, m, supply, demand);

	return 0;
}
