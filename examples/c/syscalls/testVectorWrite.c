#include <stdio.h>

int values[N][N] = { { 0 } };

int main() {
  unsigned int j,k;

  /* fill the values matrix */
  for (j=0; j < N; ++j) {
    for (k=0; k < N; ++k) {
      values[j][k] = j*N+k;
    }
  }

  for (j=0; j < N; ++j) {
    for (k=0; k < N; ++k) {
      printf("%u ", values[j][k]);
    }
    puts("");
  }

  return 0;
}

