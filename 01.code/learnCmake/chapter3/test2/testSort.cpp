#include <stdio.h>
#include "sort.h"

int main() {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(arr)/sizeof(arr[0]);
  
  bubbleSort(arr, n);
  
  printf("Sorted array: \n");
  for (int i=0; i<n; i++)
    printf("%d ", arr[i]);

  return 0;
}