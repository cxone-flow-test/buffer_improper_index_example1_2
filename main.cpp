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
  // The next two are not emitted (they are valid accesses)
  // Not sure if this is due to AbsInt performing the calculation
  // or it is an edge case in the query missing them since
  // they are similar to the previous pattern.
  a[MAX - 1] = 700;
  a[(MAX + 1) - 3] = 800;

  print_array(a, MAX + 1);
  print_array_ptr(a, MAX + 1);

  b[0] = 5;
  b[1] = 6;
  b[2] = 7;
  b[3] = 8;

  print_array(b, MAX + 1);
  print_array_ptr(b, MAX + 1);
  print_array(b, MAX + 1);
  print_array_ptr(b, MAX + 1);

  free(b);
}
