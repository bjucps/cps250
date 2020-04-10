#include <stdio.h>

void printdouble(int pos, double item) {
    printf("%d - %lf\n", pos, item);
}

void printsquare(int pos, double item) {
    printf("%d - %lf\n", pos, item * item);
}

void foreach(double items[], size_t num_items, void (*action)(int pos, double item)) {
    for (int i = 0; i < num_items; ++i) {
        action(i, items[i]);
    }
}

int main()
{
    double arr[] = {15, 20, 30};

    foreach(arr, 3, printdouble);
    foreach(arr, 3, printsquare);
}