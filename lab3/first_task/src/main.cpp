#include <iostream>
#include <ctime>
#include <cmath>

constexpr size_t length1 = 12;
constexpr size_t length2 = 7;

template <typename T>
void reverseFirstHalf(T* arr, size_t length) {
  T tmp;
  size_t halfLength = length / 2 - 1;
  for (size_t i = 0; i < halfLength; i++) {
    tmp = arr[i];
    arr[i] = arr[halfLength - i];
    arr[halfLength - i] = tmp;
  }
}

template <typename T>
void printArray(T* arr, size_t length) {
  for (size_t i = 0; i < length; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  srand(time(0));
  unsigned int arr1[length1];
  unsigned char arr2[length2];

  for (size_t i = 0; i < length1; i++) {
    arr1[i] = rand() % 100;
  }

  for (size_t i = 0; i < length2; i++) {
    arr2[i] = (char) (rand() % 60 + 40);
  }

  printArray<unsigned int>(arr1, length1);
  reverseFirstHalf<unsigned int>(arr1, length1);
  printArray<unsigned int>(arr1, length1);

  printArray<unsigned char>(arr2, length2);
  reverseFirstHalf<unsigned char>(arr2, length2);
  printArray<unsigned char>(arr2, length2);
}