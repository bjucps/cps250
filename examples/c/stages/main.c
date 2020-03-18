#include <stdio.h>

#define BOOBOO 56

#define ADD(x, y) x + y
#define SQUARE(x) x * x
#define MULTIPLY(x, y) ((x) * (y))

int main()
{
  int x = BOOBOO;
  int c = getchar();
  int count = 56;

  int z = ADD(3, count);  // 3 + count

  z = SQUARE(x++);
  z = SQUARE(getchar());
  z = MULTIPLY(count + 3, x);
}
