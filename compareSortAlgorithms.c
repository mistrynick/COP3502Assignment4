// Nicholas Mistry
// ni606857

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int extraMemoryAllocated;

// Salam Alaikum TA!
// Happy Ramadan

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
  // Count Extra Memory Allocated
    int *LEFT = (int*) malloc(n1*sizeof(int));
    extraMemoryAllocated = extraMemoryAllocated + n1;
    int *RIGHT = (int*) malloc(n2*sizeof(int));
    extraMemoryAllocated = extraMemoryAllocated + n2;

    // insert info into LEFT and RIGHT tail arrays
    for (i = 0; i < n1; i++) {
      LEFT[i] = pData[l + i];
    }
    for (j = 0; j < n2; j++) {
       RIGHT[j] = pData[m + 1+ j];
    }
  // Reset back to 0 and set k equal to l
    i = 0;
    j = 0;
    k = l;
  // Begin the merge!
    while (i < n1 && j < n2) {
      if (LEFT[i] <= RIGHT[j]) { // Compare values and build the array
        pData[k] = LEFT[i]; // Build with Left
            i++;
      } else {
        pData[k] = RIGHT[j]; // build with right
        j++;
      }
      k++;
    }
// Put the remaining elements if exists
    while (i < n1) {
      pData[k] = LEFT[i];
      i++;
      k++;
    }
   
    while (j < n2) {
      pData[k] = RIGHT[j];
      j++;
      k++;
      }
      // Free the temp arrays
    free(LEFT);
    free(RIGHT);
}
void mergeSort(int pData[], int l, int r) {
  if (l < r)
    {
        // get the mid point
        int middle_point = (l+r)/2;

        // Recursively divide and merge
        mergeSort(pData, l, middle_point);
        mergeSort(pData, middle_point+1, r);


        merge(pData, l, middle_point, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
// Swap indicies until sorted essentially
void insertionSort(int *pData, int n) {
  int i, num, j;
    for (i = 1; i < n; i++) { // Iterate forwards
      num = pData[i]; // start with a num
          for(j=i-1; j>=0; j--) { // Iterate Backwards
            if(pData[j]>num) { // if the indice value is greater than number then shift
              pData[j+1] = pData[j]; // change positions
            } else {
              break;
            }
          }
          pData[j+1] = num; // switch back or if the if condition fails then set num to the index after it
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int *pData, int n) {
  int temp;
  if (n == 1) {
    return;
  }
  for (int i=0;i<n-1;++i) {
    if (pData[i] > pData[i+1]) { // if the next element is smaller then swap
      temp = pData[i];
      pData[i] = pData[i+1];
      pData[i+1] = temp;
    }
  }
  bubbleSort(pData,n-1); // Uses recursion to check each index
}


// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated

void selectionSort(int *pData, int n) {
   int i, j, MINIMUM;
    for (i = 0; i < n-1; ++i) {
      MINIMUM = i; // set minimum to i
        for (j = i+1; j < n; ++j) {
          if (pData[j] < pData[MINIMUM]) {
            MINIMUM = j; // change minimum to the new minimum if a new value was found
          }
        }
        if(MINIMUM != i) { // If there was a change in the minimum then swap
          int temp = pData[MINIMUM];
          pData[MINIMUM] = pData[i];
          pData[i] = temp;
        }
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData) {
  FILE *inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  *ppData = NULL;
  int num;

  if (inFile) {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (int *)malloc(sizeof(int) * dataSz);
    
    
    for (int i=0;i<dataSz;++i) {
      fscanf(inFile, "%d\n", &((*ppData)[i]));
    }
    
  }

  return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz) {
  int i, sz = dataSz - 100;
  printf("\tData:\n\t");
  for (i = 0; i < 100; ++i) {
    printf("%d ", pData[i]);
  }
  printf("\n\t");

  for (i = sz; i < dataSz; ++i) {
    printf("%d ", pData[i]);
  }
  printf("\n\n");
}

int main(void) {
  clock_t start, end;
  int i;
  double cpu_time_used;
  char *fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

  for (i = 0; i < 3; ++i) {
    int *pDataSrc, *pDataCopy;
    int dataSz = parseData(fileNames[i], &pDataSrc);

    if (dataSz <= 0)
      continue;

    pDataCopy = (int *)malloc(sizeof(int) * dataSz);

    printf("---------------------------\n");
    printf("Dataset Size : %d\n", dataSz);
    printf("---------------------------\n");
    
    printf("Selection Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    
    extraMemoryAllocated = 0;
    start = clock();
   
    selectionSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Insertion Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    insertionSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Bubble Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    bubbleSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Merge Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    mergeSort(pDataCopy, 0, dataSz - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    free(pDataCopy);
    free(pDataSrc);
  }
}
