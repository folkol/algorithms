#include "algorithms.h"

/*
  function quicksort(array, left, right)
 
      // If the list has 2 or more items
      if left < right
 
          // See "Choice of pivot" section below for possible choices
          choose any pivotIndex such that left ≤ pivotIndex ≤ right
 
          // Get lists of bigger and smaller items and final position of pivot
          pivotNewIndex := partition(array, left, right, pivotIndex)
 
          // Recursively sort elements smaller than the pivot
          quicksort(array, left, pivotNewIndex - 1)
 
          // Recursively sort elements at least as big as the pivot
          quicksort(array, pivotNewIndex + 1, right)
*/

int* elements;
int num_elements = 0;

void read_input();
void quicksort(int* elements, int num_elements);
void recursive_quicksort(int* elements, int left, int right);
void swap(int* a, int* b);
int partition(int* elements, int left, int right, int pivot_index);
void print_result(uint64_t ela);

void read_input() {
  int buffer_size = 1024;
  elements = (int*) malloc(buffer_size * sizeof(int));

  int i;
  while(scanf("%d", &i) == 1) {
    if(num_elements > (buffer_size - 1)) {
      buffer_size *= 2;
      elements = realloc(elements, buffer_size * sizeof(int));
    }
    elements[num_elements++] = i;
  }
  printf("Read %d elements into the elements array.\n", num_elements);
}

void quicksort(int* elements, int num_elements) {
  printf("Sorting elements.\n");
  recursive_quicksort(elements, 0, num_elements - 1);
}

void recursive_quicksort(int* elements, int left, int right) {
  //  fprintf(stderr, "recursive_quicksort(elements=%p, left=%d, right=%d)\n", elements, left, right);
  if(left < right) {
    int pivot = (left + right) / 2;
    pivot = partition(elements, left, right, pivot);
    recursive_quicksort(elements, left, pivot - 1);
    recursive_quicksort(elements, pivot + 1, right);
  }
}

// Swap elements pointed at by argument pointers
void swap(int* a, int* b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

// Partition the elements so that the ones left of the (new) pivot_index
// is smaller than the one on the pivot_index, and all elements to the right
// of the pivot_index is equal to or larger than the pivot
// Return the new pivot index
int partition(int* elements, int left, int right, int pivot_index) {
  int pivot_value = elements[pivot_index];
  // Move the pivot element to the end of the array temporatily, so get it out of the way
  swap(elements + pivot_index, elements + right);
  // store_index is the new pivot_index, start with it at left, and move as we find smaller items
  int store_index = left;
  // Inspect all elements, if we find one smaller than the pivot, we swap it with the temporary pivot
  // and move the temporary pivot forward one step.
  // This say, if all elements are bigger than the pivot it will be at the left, and if all elements 
  // are larger it will eventually end up at the end of the element partition
  for(int c = left; c < right; c++) {
    if(elements[c] < pivot_value) {
      swap(elements + c, elements + store_index);
      store_index++;
    }
  }
  // Move the pivot element back to the new pivot position and return the new pivot index
  swap(elements + store_index, elements + right);
  return store_index;
}

void print_result(uint64_t elapsed_time) {
  printf("Sorted list in %llu nanoseconds:\n", elapsed_time);
  for(int c = 0; c < num_elements; c++) {
    printf("%d ", elements[c]);
  }
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(int argc, char** argv) {
  read_input();

  uint64_t elapsed;
  if(argc > 1) {
    fprintf(stderr, "Sorting array using standard library qsort");
    GetPIDTimeInNanoseconds();
    qsort (elements, num_elements, sizeof(int), compare);
    elapsed = GetPIDTimeInNanoseconds();
  } else {
    fprintf(stderr, "Sorting array using folkol quicksort");
    GetPIDTimeInNanoseconds();
    quicksort(elements, num_elements);
    elapsed = GetPIDTimeInNanoseconds();
  }

  print_result(elapsed);

  free(elements);
  elements = 0;
}

