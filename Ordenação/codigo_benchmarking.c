#include <time.h>

int main(void) {
  clock_t start_time = clock();

  // code or function to benchmark

  double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
  printf("Done in %f seconds\n", elapsed_time);
}