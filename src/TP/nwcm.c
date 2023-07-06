// North West Corner Rule - Transportation Problem

#include <stdlib.h>
#include <stdio.h>

typedef struct list{
	int x, y, value;
	struct list *next;
}Node;

void print(int a[100][100], int origin, int destination) {
	int i, j;
	printf("\n");
	for(i=0; i<origin; i++) {
		for(j=0; j<destination; j++) {
			printf("\t%d", a[i][j]);
		}
		printf("\n");
	}
}

Node* createNode() {
	Node *node = (Node*)malloc(sizeof(Node));
	node->next = NULL;
	return node;
}


int main() {
	int n[100][100]; // matrix
	int c[100], r[100]; // capacity, requirements
	int o=0, d=0; // origin and destination
	printf("\nEnter number of origins: ");
	scanf("%d", &o);
	printf("\nEnter number of destination: ");
	scanf("%d", &d);
	printf("\nEnter Matrix values:\n");
	int i, j;
	for(i=0; i<o; i++) {
		for(j=0; j<d; j++) {
			scanf("%d", &n[i][j]);
		}
	}
    int t_c = 0, t_r = 0; // total capacity and total requirement init 0
	printf("\nEnter Capacity: ");
	for(i=0; i<o; i++) {
		scanf("%d", &c[i]);
        t_c = t_c + c[i];
	}
	printf("\nEnter Requirements: ");
	for(i=0; i<d; i++) {
		scanf("%d", &r[i]);
        t_r = t_r + r[i];
	}
    // unstable
    if (t_c > t_r) {
        printf("Unstable Matrix: Capacity greater than Requirement");
        for(i=0; i<o; i++) {
            n[i][d] = 0;
        }
        r[d] = t_c - t_r;
        d++;
    } else if (t_c < t_r) {
        printf("Unstable Matrix: Requirement greater than Capacity");
        for(i=0; i<d; i++) {
            n[o][i] = 0;
        }
        c[o] = t_r - t_c;
        o++;
    }
	int x=0,y=0; //origin and destination coordinates
	Node *head = NULL;
	Node *last = NULL;
	while(x<o && y<d) {
		if(c[x] < r[y]) {
			Node *node = createNode(); //creating node
			node->value = c[x]; //adding a value
			node->x = x; //adding the coordinates of the value
			node->y = y;
			r[y] = r[y] - c[x];
			x++;
			if(last) {
				last->next = node;
				last = last->next;
			} else {
				last = node;
				head = last;
			}
		} else if(c[x] > r[y]) {
			Node *node = createNode();
			node->value = r[y];
			node->x = x;
			node->y = y;
			c[x] = c[x] - r[y];
			y++;
			if(last) {
				last->next = node;
				last = last->next;
			} else {
				last = node;
				head = last;
			}
		} else {
			Node *node = createNode();
			node->value = r[y];
			node->x = x;
			node->y = y;
            x++;
            y++;
			if(last) {
				last->next = node;
				last = last->next;
			} else {
				last = node;
				head = last;
			}
		}
	}
	Node *tmp = head;
	int sum = 0, p = 0;
	while(tmp->next) {
		p = tmp->value * n[tmp->x][tmp->y];
		sum = sum + p;
		tmp = tmp->next;
	}
	if(tmp->next == NULL) {
		p = tmp->value * n[tmp->x][tmp->y];
		sum = sum + p;
	}
	printf("\nThe total is %d.", sum);
	return 0;
}
