#include <iostream>
#include "LinkedQueue/LinkedQueue.hpp"
#include "ArrayQueue/ArrayQueue.hpp"

void help() {
	std::cout << "h - list of commands" << std::endl;
	std::cout << "i - start testing queue with unsigned int type of data, using linked queue" << std::endl;
	std::cout << "c - start testing queue with unsigned char type of data, using array queue" << std::endl;
	std::cout << "q - quit" << std::endl;
}

void queueHelp() {
	std::cout << "h - list of commands" << std::endl;
	std::cout << "e - the queue if empty [returns 1 if true / 0 if false]" << std::endl;
	std::cout << "f - the queue if full [returns 1 if true / 0 if false]" << std::endl;
	std::cout << "1 - read the first element" << std::endl;
	std::cout << "l - read the last element" << std::endl;
	std::cout << "a [VALUE] - add element at the end" << std::endl;
	std::cout << "p - pull the element from the front" << std::endl;
	std::cout << "q - quit" << std::endl;
}

void clear() {
	while(std::cin.get() != '\n');
}

void testIntQueue() {
  unsigned int arg;
  size_t sizeOfQueue;
  std::cout << "Input size of queue" << std::endl;
  std::cin >> sizeOfQueue;
  std::cout << std::endl;
  queueHelp();
  LinkedQueue<unsigned int> queue(sizeOfQueue);
  char command;
  while (true) {
    std::cin >> command;
    switch (command) {
      case 'h':
        clear();
        queueHelp();
        break;

      case 'e':
        clear();
        std::cout << queue.empty() << std::endl << std::endl;
        break;

      case 'f':
        clear();
        std::cout << queue.full() << std::endl << std::endl;
        break;

      case '1':
        clear();
        try {
          std::cout << queue.front() << std::endl << std::endl;
        } catch (const std::out_of_range& oor) {
          std::cerr << "Out of Range: " << oor.what() << std::endl;
        }
        break;

      case 'l':
        clear();
        try {
          std::cout << queue.back() << std::endl << std::endl;
        } catch (const std::out_of_range& oor) {
          std::cerr << "Out of Range: " << oor.what() << std::endl;
        }
        break;

      case 'a':
        std::cin >> arg;
        try {
          queue.push_back(arg);
        } catch (const std::out_of_range& oor) {
          std::cerr << "Out of Range: " << oor.what() << std::endl;
        }
        clear();
        break;

      case 'p':
        clear();
        try {
          std::cout << queue.pop_front() << std::endl << std::endl;
        } catch (const std::out_of_range& oor) {
          std::cerr << "Out of Range: " << oor.what() << std::endl;
        }
        break;
      
      case 'q':
        clear();
        return;

      default:
        clear();
        std::cout << "Unknown command" << std::endl << std::endl;
    }
  }
}

void testCharQueue() {
  unsigned char arg;
  size_t sizeOfQueue;
  std::cout << "Input size of queue" << std::endl;
  std::cin >> sizeOfQueue;
  std::cout << std::endl;
  queueHelp();
  ArrayQueue<unsigned char> queue(sizeOfQueue);
  char command;
  while (true) {
    std::cin >> command;
    switch (command) {
      case 'h':
        clear();
        queueHelp();
        break;

      case 'e':
        clear();
        std::cout << queue.empty() << std::endl << std::endl;
        break;

      case 'f':
        clear();
        std::cout << queue.full() << std::endl << std::endl;
        break;

      case '1':
        clear();
        try {
          std::cout << queue.front() << std::endl << std::endl;
        } catch (const std::out_of_range& oor) {
          std::cerr << "Out of Range: " << oor.what() << std::endl;
        }
        break;

      case 'l':
        clear();
        try {
          std::cout << queue.back() << std::endl << std::endl;
        } catch (const std::out_of_range& oor) {
          std::cerr << "Out of Range: " << oor.what() << std::endl;
        }
        break;

      case 'a':
        std::cin >> arg;
        try {
          queue.push_back(arg);
        } catch (const std::out_of_range& oor) {
          std::cerr << "Out of Range: " << oor.what() << std::endl;
        }
        clear();
        break;

      case 'p':
        clear();
        try {
          std::cout << queue.pop_front() << std::endl << std::endl;
        } catch (const std::out_of_range& oor) {
          std::cerr << "Out of Range: " << oor.what() << std::endl;
        }
        break;
      
      case 'q':
        clear();
        return;

      default:
        clear();
        std::cout << "Unknown command" << std::endl << std::endl;
    }
  }
}

int main() {
  help();
  char command;
  while(true) {
    std::cin >> command;
    switch (command) {
    case 'h':
      clear();
      help();
      break;

    case 'i':
      clear();
      testIntQueue();
      break;

    case 'c':
      clear();
      testCharQueue();
      break;

    case 'q':
      return 0;

    default:
      clear();
			std::cout << "Unknown command" << std::endl;
    }
  }
}