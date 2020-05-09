#pragma once
#include <iostream>

template <typename T>
class LinkedQueue {
private:
  struct Node {
		T data;
		Node *prev;
	};
  size_t m_size;
  size_t max_size;
  Node* m_front;
  Node* m_back;

public:
  LinkedQueue(size_t maximum_size = -1) {
    m_size = 0;
    m_front = nullptr;
    m_back = nullptr;
    max_size = maximum_size;
  }

  ~LinkedQueue() {
    Node* tmp = m_front;
    while (m_front != nullptr) {
      m_front = m_front->prev;
      delete tmp;
      tmp = m_front;
    }
  }

  T front() {
    if (m_size == 0) {
      throw std::out_of_range("Queue is empty");
    }
    return m_front->data;
  }
  
  T back() {
    if (m_size == 0) {
      throw std::out_of_range("Queue is empty");
    }
    return m_back->data;
  }

  void push_back(T newData) {
    if (m_size == max_size) {
      throw std::out_of_range("Queue is full");
    }
    Node* tmp = new Node;
    tmp->prev = nullptr;
    tmp->data = newData;
    if (m_front == nullptr) {
      m_front = m_back = tmp;
    } else {
      m_back->prev = tmp;
      m_back = m_back->prev;
    }
    m_size++;
  }

  T pop_front() {
    if (m_size == 0) {
      throw std::out_of_range("Queue is empty");
    }
    T tmp = m_front->data;
    Node* prev = m_front->prev;
    
    delete m_front;
    m_front = prev;
    m_size--;

    return tmp;
  }

  bool empty() {
    return m_size == 0;
  }

  bool full() {
    return m_size == max_size;
  }
};