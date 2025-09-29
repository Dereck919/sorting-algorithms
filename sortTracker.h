#ifndef SORTTRACKER_H
#define SORTTRACKER_H
#include <iostream>
#include <string>
class SortTrackerShell {
private:
   int comparisonCount;
   int swapCount;
public:
   SortTrackerShell() {
      comparisonCount = 0;
      swapCount = 0;
   }
   int GetComparisonCount() const {
      return comparisonCount;
   }
   int GetSwapCount() const {
      return swapCount;
   }
   bool IsFirstLTSecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] < array[index2];
   }
   bool IsFirstLTESecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] <= array[index2];
   }
   void PrintArray(const int* array, int arrayLength,
      std::ostream& output = std::cout, std::string delimiter = ", ",
      std::string prefix = "", std::string suffix = "") {
      output << prefix;
      if (arrayLength > 0) {
         output << array[0];
      }
      for (int i = 1; i < arrayLength; i++) {
         output << delimiter << array[i];
      }
      output << suffix;
   }
   void Swap(int* array, int index1, int index2) {
      swapCount++;
      int temp = array[index1];
      array[index1] = array[index2];
      array[index2] = temp;
   }
};

class SortTrackerQuick {
private:
   int comparisonCount;
   int swapCount;
public:
   SortTrackerQuick() {
      comparisonCount = 0;
      swapCount = 0;
   }
   int GetComparisonCount() const {
      return comparisonCount;
   }
   int GetSwapCount() const {
      return swapCount;
   }
   bool IsFirstLTSecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] < array[index2];
   }
   bool IsLT(int element1, int element2) {
      comparisonCount++;
      return element1 < element2;
   }
   bool IsFirstLTESecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] <= array[index2];
   }
   void PrintArray(const int* array, int arrayLength,
      std::ostream& output = std::cout, std::string delimiter = ", ",
      std::string prefix = "", std::string suffix = "") {
      // Print the prefix first
      output << prefix;
      if (arrayLength > 0) {
         output << array[0];
      }
      for (int i = 1; i < arrayLength; i++) {
         output << delimiter << array[i];
      }
      output << suffix;
   }
   void Swap(int* array, int index1, int index2) {
      swapCount++;
      int temp = array[index1];
      array[index1] = array[index2];
      array[index2] = temp;
   }
};

class SortTrackerMerge {
private:
   int comparisonCount;
   int swapCount;
public:
   SortTrackerMerge() {
      comparisonCount = 0;
      swapCount = 0;
   }
   int GetComparisonCount() const {
      return comparisonCount;
   }
   int GetSwapCount() const {
      return swapCount;
   }
   bool IsFirstLTSecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] < array[index2];
   }
   bool IsLT(int element1, int element2) {
      comparisonCount++;
      return element1 < element2;
   }
   bool IsFirstLTESecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] <= array[index2];
   }
   void PrintArray(const int* array, int arrayLength,
      std::ostream& output = std::cout, std::string delimiter = ", ",
      std::string prefix = "", std::string suffix = "") {
      output << prefix;
      if (arrayLength > 0) {
         output << array[0];
      }
      for (int i = 1; i < arrayLength; i++) {
         output << delimiter << array[i];
      }
      output << suffix;
   }
   void Swap(int* array, int index1, int index2) {
      swapCount++;
      int temp = array[index1];
      array[index1] = array[index2];
      array[index2] = temp;
   }
};
#endif