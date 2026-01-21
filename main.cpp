#include <cstdint>
#include <cwchar>
#include <iostream>
#include <string.h>

using namespace std;

#define MAX 4

void print_array(int array[], int len) {
  cout << "print_array" << endl;

  for (int x = 0; x < len; x++) {
    cout << array[x] << endl;
  }
}

void print_array_ptr(int *array, int len) {
  cout << "print_array_ptr" << endl;

  for (int x = 0; x < len; x++) {
    cout << array[x] << endl;
  }
}

int main(int argc, char *argv[]) {

  int a[MAX];

  int *b = (int *)malloc(sizeof(int) * MAX);

  for (int x = 0; x < MAX; x++)
    a[x] = x;

  a[0] = 2000;
  // The query misses this as a FN.  MAX is one
  // element beyond the end of the array since indexing starts at 0.
  a[MAX] = 400;
  // This TP result is emitted.
  a[MAX + 1] = 500;
  // The next two are not emitted (they are valid accesses)
  // Not sure if this is due to AbsInt performing the calculation
  // or it is an edge case in the query missing them since
  // they are similar to the previous pattern.
  a[MAX - 1] = 700;
  a[(MAX + 1) - 3] = 800;
  // This TP result is emitted.
  a[6] = 600;

  cout << "a[0]: " << a[0] << endl;
  // This should have been a TP, not reported as a FN
  cout << "a[MAX]: " << a[MAX] << endl;
  // This TP result is emitted.
  cout << "a[6]: " << a[6] << endl;

  // This one shouldn't be reported because the implementation
  // accounts for 0 index.
  print_array(a, MAX);

  // This is a FN since the logic would go 1 element beyond
  // the end.
  print_array(a, MAX + 1);

  // Next two are same as previous, just a variation in how
  // the memory is accessed.
  print_array_ptr(a, MAX);
  print_array_ptr(a, MAX + 1);

  // No reports here, as expected
  b[0] = 5;
  b[1] = 6;
  b[2] = 7;
  b[3] = 8;

  // These are also missed.
  print_array(b, MAX);
  print_array(b, MAX + 1);
  print_array_ptr(b, MAX);
  print_array_ptr(b, MAX + 1);

  // FN result here, likely because this is dynamically
  // allocated.
  b[4] = 900;

  // These are also missed.
  print_array(b, MAX);
  print_array(b, MAX + 1);
  print_array_ptr(b, MAX);
  print_array_ptr(b, MAX + 1);

  free(b);
}
