// structs
// A demonstration of struct syntax and of using structs and functions together to implement OOP-style encapsulation
// (c) 2016, Bob Jones University
#include <stdio.h>
#include <stdbool.h>

// Declare a struct type "point2d" comprising a named pair of integers (x, y).
struct point2d {
    int x;
    int y;
};

// Establish "point2d_t" as an alias ("typedef") for the type "struct point2d"
typedef struct point2d point2d_t;

struct point2d g_p0;
struct point2d g_p1 = { 0 };
struct point2d g_p2 = { 10, 20 };
struct point2d g_p3 = { .x = 10, .y = 20 };

void print_point(struct point2d p, bool newline) {
    printf("(%d, %d)", p.x, p.y);
    if (newline) putchar('\n');
}

point2d_t add_points(point2d_t a, point2d_t b) {
    point2d_t ret = { .x = a.x + b.x, .y = a.y + b.y };
    return ret;
}

int main() {
    struct point2d my_point;    // DANGER! Uninitialized members...
    my_point.x = 100;           // Member access via the "." operator
    my_point.y = 50;

    struct point2d your_point;
    your_point = my_point;      // Assignment works (but not comparison...)
    
    print_point(my_point, false);
    printf(" == ");
    print_point(your_point, true);

    print_point(my_point, false);
    printf(" + ");
    print_point(g_p3, false);
    printf(" == ");
    print_point(add_points(my_point, g_p3), true);
}


