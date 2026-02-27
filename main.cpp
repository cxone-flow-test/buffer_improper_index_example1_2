#include <cstdint>
#include <cwchar>
#include <iostream>
#include <string.h>

using namespace std;

#define MAX 4

void print_array(int array[], int len) {
  cout << "print_array" << endl;

  for (int x = 0; x <= len; x++) {
    cout << array[x] << endl;
  }
}

void print_array_ptr(int *array, int len) {
  cout << "print_array_ptr" << endl;

  for (int x = 0; x <= len; x++) {
    cout << array[x] << endl;
  }
}

int main(int argc, char *argv[]) {

  int a[MAX];

  int *b = (int *)malloc(sizeof(int) * MAX);

  for (int x = 0; x <= MAX; x++)
    a[x] = x;

  a[0] = 2000;
  a[MAX - 1] = 700;
  a[(MAX + 1) - 3] = 800;

  print_array(a, MAX);
  print_array_ptr(a, MAX);

  b[0] = 5;
  b[1] = 6;
  b[2] = 7;
  b[3] = 8;

  print_array(b, MAX);
  print_array_ptr(b, MAX);
  print_array(b, MAX);
  print_array_ptr(b, MAX);

  free(b);
}
