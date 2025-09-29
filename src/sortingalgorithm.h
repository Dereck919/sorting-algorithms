#include <iostream>
#include <chrono>
#include <vector>
#include "sortTracker.h"

using namespace std;
class Sort{
    public:
    void printArray(int* array, int size){
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";
        cout << endl;
    }
    void BubbleSort(int * array, int size){
        //timer start
        auto start = chrono::high_resolution_clock::now();
        for(int i = 0;i < size; i++){
            for(int j = 0; j < size-1; j++){
                if(array[j] < array[j+1]){
                    swap(array[j], array[j+1]);
                }
            }
        }
        //timer end
        auto end = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        cout << "Bubble Sort took: " << duration.count() << " nanoseconds" << endl;
    }
    void GnomeSort(int* array, int size){
    //timer start
    auto start = chrono::high_resolution_clock::now();
    int i = 0;
    while (i < size) {
        if (i == 0)
            i++;
        if (array[i] >= array[i - 1])
            i++;
        else {
            swap(array[i], array[i - 1]);
            i--;
        }
    }
    //timer end
    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Gnome Sort took: " << duration.count() << " nanoseconds" << endl;
}

void SelectionSort(int* array, int size) {
    //timer start
    auto start = chrono::high_resolution_clock::now();
   for (int i = 0; i < size - 1; i++) {
      int indexSmallest = i;
      for (int j = i + 1; j < size; j++) {
         if (array[j] < array[indexSmallest]) {
            indexSmallest = j;
         }
      }
      int temp = array[i];
      array[i] = array[indexSmallest];
      array[indexSmallest] = temp;
   }
    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Selection Sort took: " << duration.count() << " nanoseconds" << endl;
}

void InsertionSort(int* array, int size) {
    //timer start
    auto start = chrono::high_resolution_clock::now();
   for (int i = 1; i < size; i++) {
      int j = i;
      while (j > 0 && array[j] < array[j - 1]) {
         // Swap array[j] and array [j - 1]
         int temp = array[j];
         array[j] = array[j - 1];
         array[j - 1] = temp;
         j--;
      }
   }
    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Insertion Sort took: " << duration.count() << " nanoseconds" << endl;
}

//RADIX SORT BEGIN
int RadixGetLength(int value) {
   if (value == 0) {
      return 1;
   }
   int digits = 0;
   while (value != 0) {
      digits++;
      value /= 10;
   }
   return digits;
}
int RadixGetMaxLength(const int* array, int size) {
   int maxDigits = 0;
   for (int i = 0; i < size; i++) {
      int digitCount = RadixGetLength(array[i]);
      if (digitCount > maxDigits) {
         maxDigits = digitCount;
      }
   }
   return maxDigits;
}
void RadixSortFunction(int* array, int size) {
   vector<vector<int>> buckets(10);
   int copyBackIndex;
   int maxDigits = RadixGetMaxLength(array, size);
   int pow10 = 1;
   for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
      for (int i = 0; i < size; i++) {
         int num = array[i];
         int bucketIndex = (abs(num) / pow10) % 10;
         buckets[bucketIndex].push_back(num);
      }
      copyBackIndex = 0;
      for (int i = 0; i < 10; i++) {
         vector<int>& bucket = buckets[i];
         for (int j = 0; j < bucket.size(); j++) {
            array[copyBackIndex] = bucket[j];
            copyBackIndex++;
         }
         bucket.clear();
      }
      pow10 *= 10;
   }
   vector<int> negatives;
   vector<int> nonNegatives;
   for (int i = 0; i < size; i++) {
      int num = array[i];
      if (num < 0) {
         negatives.push_back(num);
      }
      else {
         nonNegatives.push_back(num);
      }
   }
}
void RadixSort(int* array, int size){
    //timer start
    auto start = chrono::high_resolution_clock::now();
    RadixSortFunction(array,size);
    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Radix Sort took: " << duration.count() << " nanoseconds" << endl;
}

//SHEL SORT BEGIN
int InsertionSortInterleaved(int* array, int size, int startIndex,
   int gap, SortTrackerShell& tracker) {
   int swapsBefore = tracker.GetSwapCount();
   for (int i = startIndex + gap; i < size; i += gap) {
      int j = i;
      while (j - gap >= startIndex &&
         tracker.IsFirstLTSecond(array, j, j - gap)) {
         tracker.Swap(array, j, j - gap);
         j -= gap;
      }
   }
   return tracker.GetSwapCount() - swapsBefore;
}
int ShellSortFunction(int* array, int size, int* gapValues, int gapValuesSize,
   SortTrackerShell& tracker) {
   int totalSwaps = 0;
   for (int g = 0; g < gapValuesSize; g++) {
      int swapsForGap = 0;
      for (int i = 0; i < gapValues[g]; i++) {
         swapsForGap += InsertionSortInterleaved(array, size, i,
            gapValues[g], tracker);
      }
      totalSwaps += swapsForGap;
   }
   return totalSwaps;
}
void ShellSort(int* array, int size) {
    //timer start
    auto start = chrono::high_resolution_clock::now();
   SortTrackerShell tracker;
   int gapValues[] = { 4, 2, 1 };
   int gapValuesLength = sizeof(gapValues) / sizeof(gapValues[0]);
   ShellSortFunction(array, size, gapValues, gapValuesLength, tracker);
    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Shell Sort took: " << duration.count() << " nanoseconds" << endl;
}
int Partition(int* array, int lowIndex, int highIndex, SortTrackerQuick& tracker) {
   int midpoint = lowIndex + (highIndex - lowIndex) / 2;
   int pivot = array[midpoint];
   bool done = false;
   while (!done) {
      while (tracker.IsLT(array[lowIndex], pivot)) {
         lowIndex++;
      }
      while (tracker.IsLT(pivot, array[highIndex])) {
         highIndex--;
      }
      if (lowIndex >= highIndex) {
         done = true;
      }
      else {
         tracker.Swap(array, lowIndex, highIndex);
         lowIndex++;
         highIndex--;
      }
   }
   return highIndex;
}
void QuicksortFunction(int* array, int lowIndex, int highIndex, SortTrackerQuick& tracker) {
   if (highIndex <= lowIndex) {
      return;
   }
   int lowEndIndex = Partition(array, lowIndex, highIndex, tracker);
   QuicksortFunction(array, lowIndex, lowEndIndex, tracker);
   QuicksortFunction(array, lowEndIndex + 1, highIndex, tracker);
}

void QuickSort(int* array, int size){
    //timer start
    auto start = chrono::high_resolution_clock::now();
    SortTrackerQuick tracker;
    QuicksortFunction(array, 0, size-1, tracker);
    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Quick Sort took: " << duration.count() << " nanoseconds" << endl;
}

//START MERGE SORT
void Merge(int* array, int leftFirst, int leftLast, int rightLast,
   SortTrackerMerge& tracker) {
   int mergedSize = rightLast - leftFirst + 1;
   int* mergedarray = new int[mergedSize];
   int mergePos = 0;
   int leftPos = leftFirst;
   int rightPos = leftLast + 1;
   while (leftPos <= leftLast && rightPos <= rightLast) {
      if (tracker.IsFirstLTESecond(array, leftPos, rightPos)) {
         mergedarray[mergePos] = array[leftPos];
         leftPos++;
      }
      else {
         mergedarray[mergePos] = array[rightPos];
         rightPos++;
      }
      mergePos++;
   }
   while (leftPos <= leftLast) {
      mergedarray[mergePos] = array[leftPos];
      leftPos++;
      mergePos++;
   }
   while (rightPos <= rightLast) {
      mergedarray[mergePos] = array[rightPos];
      rightPos++;
      mergePos++;
   }
   for (mergePos = 0; mergePos < mergedSize; mergePos++) {
      array[leftFirst + mergePos] = mergedarray[mergePos];
   }
   delete[] mergedarray;
}
void MergeSortFunction(int* array, int startIndex, int endIndex,
   SortTrackerMerge& tracker) {
   if (startIndex < endIndex) {
      int mid = (startIndex + endIndex) / 2;
      MergeSortFunction(array, startIndex, mid, tracker);
      MergeSortFunction(array, mid + 1, endIndex, tracker);
      Merge(array, startIndex, mid, endIndex, tracker);
   }
   }

void MergeSort(int* array, int size){
    //timer start
    auto start = chrono::high_resolution_clock::now();
    SortTrackerMerge tracker;
    MergeSortFunction(array, 0, size-1, tracker);
    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Merge Sort took: " << duration.count() << " nanoseconds" << endl;
}
};