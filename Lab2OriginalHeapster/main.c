#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "HeapManager.h"
#include "Test.h"

void standardDeviation();

int main() {
    standardDeviation();
    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();
    //customTestCase1(); // Use size 32
    customTestCase1Coalescing(); // Use size 32
    customTestCase2(); // Use size 48
}

void standardDeviation() {
    int n;

    printf("Please enter the number of integers you want to enter: ");
    scanf("%d", &n);
    printf("Allocating enough space for %d integers...\n", n);

    my_initialize_heap(n * sizeof(int) + BLOCK_SIZE);

    int *data = my_alloc(n * sizeof(int));;

    for (int i = 0; i < n; i++) {
        if ((i + 1) % 10 == 1 && (i + 1) % 100 != 11) {
            printf("Please enter your %dst number: ", i + 1);
        }
        else if ((i + 1) % 10 == 2 && (i + 1) % 100 != 12) {
            printf("Please enter your %dnd number: ", i + 1);
        }
        else if ((i + 1) % 10 == 3 && (i + 1) % 100 != 13) {
            printf("Please enter your %drd number: ", i + 1);
        }
        else {
            printf("Please enter your %dth number: ", i + 1);
        }
        int temp;
        scanf("%d", &temp);
        data[i] = temp;
    }

    double mu = 0;
    for (int i = 0; i < n; i++) {
        mu += data[i];
    }

    mu = mu / n;

    double variance = 0;

    for (int i = 0; i < n; i++) {
        variance += pow(data[i] - mu, 2);
    }

    double standardDeviation = sqrt(variance / n);

    printf("The standard deviation of the numbers you entered is: %f\n", standardDeviation);
    printf("\n");
}