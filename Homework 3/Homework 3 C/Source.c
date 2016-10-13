#include <stdio.h>

int power(int, int);
int doPower(int, int, int);
int overflowPower(int, int);

int main() {
    int answer = power(2, 100000000); // overflowPower(2, 100000000);
    printf("The answer is: %d\n", answer);
}

int power(int a, int b) {
    return doPower(a, b, 1);
}

int doPower(int a, int b, int answer) {
    if (b == 0) {
        return answer;
    }
    return doPower(a, b - 1, answer * a);
}

int overflowPower(int a, int b) {
    if (b == 0) {
        return 1;
    }
    return a * overflowPower(a, b - 1);
}