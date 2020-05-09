#pragma once
#include <iostream>

template <typename T>
class ArrayQueue {
private:
  T* arr;
  size_t m_front;
  size_t m_back;
  size_t max_size;

public:
  ArrayQueue(size_t maximum_size) {
    max_size = maximum_size;
    arr = new T[max_size];
    m_front = 0;
    m_back = max_size - 1;
  }

  ~ArrayQueue() {
    delete[] arr;
  }

  T front() {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return arr[m_front];
  }
  
  T back() {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return arr[m_back];
  }

  void push_back(T newData) {
    if (full()) {
      throw std::out_of_range("Queue is full");
    }
    arr[++m_back %= max_size] = newData;
  }

  T pop_front() {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    T tmp = arr[m_front];
    ++m_front %= max_size;
    return tmp;
  }

  bool empty() {
    return m_front == (m_back + 1) % max_size;
  }

  bool full() {
    return m_front == (m_back + 2) % max_size;
  }
};