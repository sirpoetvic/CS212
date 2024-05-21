#include "MaxHeap.h"
using namespace std;
int main() {
  const int size = 5;
  int numbers[size] = { 10, 2, 5, 18, 22 };
  MaxHeap maxHeap(numbers, size); // add code to MaxHeap.h
  cout << maxHeap << endl; // output like [22, 18, 5, 2, 10]
  return 0;
}