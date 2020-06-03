#include <iostream>
#include "String.hpp"
#include "StringID.hpp"
#include "StringD.hpp"

void clear() {
	while(std::cin.get() != '\n');
}

// 0 - String
// 1 - StringID
// 2 - StringD

int main() {
  system("clear");
  int countOfTestingClasses = 0;
  std::cout << "Hey, user! Nice to meet you here, let's begin testing String classes."
    << std::endl << "At first, input how many objects we will test: " << std::endl;
  std::cin >> countOfTestingClasses;
  clear();
  if (countOfTestingClasses < 1) {
    std::cout << "Not enough to test. Bye." << std::endl;
    return 0;
  }
  String ** strs = new String *[countOfTestingClasses];
  int types[countOfTestingClasses];
  for (size_t i = 0; i < countOfTestingClasses; i++) {
    strs[i] = nullptr;
    types[i] = -1;
  }

  char command, arg, arg2;
  std::string value;
  bool isRunning = true;
  while (isRunning) {
    std::cout << "Choose command: " << std::endl
      << "1 - Set default value" << std::endl
      << "2 - Test methods" << std::endl
      << "3 - Quit" << std::endl;
    std::cin >> command;
    clear();

    switch (command) {



      case '1':
        std::cout << "Which element you want to add? [input index]" << std::endl;
        std::cin.get(arg);
        clear();
        if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
          std::cout << "Incorrect argument" << std::endl;
          break;
        }
        if (strs[arg] != nullptr) {
          delete strs[arg];
        }
        std::cout << "Which class you want to create? [1 - String / 2 - StringID / 3 - StringD]" << std::endl;
        std::cin.get(arg2);
        clear();
        std::cout << "Input initial value" << std::endl;
        std::cin >> value;
        clear();
        switch (arg2) {
          case '1':
            strs[arg] = new String(value.c_str());
            types[arg] = 0;
            break;

          case '2':
            strs[arg] = new StringID(value.c_str());
            types[arg] = 1;
            break;

          case '3':
            strs[arg] = new StringD(value.c_str());
            types[arg] = 2;
            break;

          default:
            std::cout << "Incorrect argument" << std::endl;
        }
        break;



      case '2':
        std::cout << "1 - Output element" << std::endl
          << "2 - Test String class" << std::endl
          << "3 - Test StringID class" << std::endl
          << "4 - Test StringD class" << std::endl;
        std::cin.get(arg);
        clear();
        switch (arg) {
          case '1':
            std::cout << "Which element you want to output? [input index]" << std::endl;
            std::cin.get(arg);
            clear();
            if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
              std::cout << "Incorrect argument" << std::endl;
              break;
            }
            if (strs[arg] == nullptr) {
              std::cout << arg << " element is missing" << std::endl;
              break;
            }
            std::cout << *strs[arg] << std::endl;
            break;

          case '2':
            std::cout << "1 - print count of calls copy constructor" << std::endl
              << "2 - assign value of one element to another" << std::endl
              << "3 - print length of string" << std::endl;
            std::cin.get(arg);
            clear();
            switch (arg) {
              case '1':
                std::cout << "Count of calls of which element you want to output? [input index]" << std::endl;
                std::cin.get(arg);
                clear();
                if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg] == nullptr) {
                  std::cout << arg << " element is missing" << std::endl;
                  break;
                }
                std::cout << strs[arg]->getCountOfCallCopy() << std::endl;
                break;

              case '2':
                std::cout << "Value of which element you want to change? [input index]" << std::endl;
                std::cin.get(arg);
                clear();
                if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg] == nullptr) {
                  std::cout << arg << " element is missing" << std::endl;
                  break;
                }
                std::cout << "Value of which element you want to assign? [input index]" << std::endl;
                std::cin.get(arg2);
                clear();
                if ((int) arg2 - 48 > countOfTestingClasses || (int) arg2 - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg2] == nullptr) {
                  std::cout << arg2 << " element is missing" << std::endl;
                  break;
                }
                std::cout << arg << " element was = " << *strs[arg] << "\tassigned to " << arg2 << " element = " << *strs[arg2] << std::endl;
                *strs[arg] = *strs[arg2];
                std::cout << arg << " element now = " << *strs[arg] << std::endl;
                break;

              case '3':
                std::cout << "Length of which element you want to output? [input index]" << std::endl;
                std::cin.get(arg);
                clear();
                if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg] == nullptr) {
                  std::cout << arg << " element is missing" << std::endl;
                  break;
                }
                std::cout << strs[arg]->length() << std::endl;
                break;

              default:
                std::cout << "Incorrect argument" << std::endl;
            }
            break;



          case '3':
            std::cout << "1 - print count of calls copy constructor" << std::endl
              << "2 - assign value of one element to another" << std::endl
              << "3 - print length of string" << std::endl
              << "4 - upcase every letter in string" << std::endl
              << "5 - concat two strings" << std::endl;
            std::cin.get(arg);
            clear();
            switch (arg) {
              case '1':
                std::cout << "Count of calls of which element you want to output? [input index]" << std::endl;
                std::cin.get(arg);
                clear();
                if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg] == nullptr) {
                  std::cout << arg << " element is missing" << std::endl;
                  break;
                }
                if (types[arg] != 1) {
                  std::cout << "Incompatible type of element. Here you can test only StringID" << std::endl;
                  break;
                }
                std::cout << strs[arg]->getCountOfCallCopy() << std::endl;
                break;

              case '2':
                std::cout << "Value of which element you want to change? [input index]" << std::endl;
                std::cin.get(arg);
                clear();
                if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg] == nullptr) {
                  std::cout << arg << " element is missing" << std::endl;
                  break;
                }
                if (types[arg] != 1) {
                  std::cout << "Incompatible type of element. Here you can test only StringID" << std::endl;
                  break;
                }
                std::cout << "Value of which element you want to assign? [input index]" << std::endl;
                std::cin.get(arg2);
                clear();
                if ((int) arg2 - 48 > countOfTestingClasses || (int) arg2 - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg2] == nullptr) {
                  std::cout << arg2 << " element is missing" << std::endl;
                  break;
                }
                if (types[arg2] != 1) {
                  std::cout << "Incompatible type of element. Here you can test only StringID" << std::endl;
                  break;
                }
                std::cout << arg << " element was = " << *strs[arg] << "\tassigned to " << arg2 << " element = " << *strs[arg2] << std::endl;
                *strs[arg] = *strs[arg2];
                std::cout << arg << " element now = " << *strs[arg] << std::endl;
                break;

              case '3':
                std::cout << "Length of which element you want to output? [input index]" << std::endl;
                std::cin.get(arg);
                clear();
                if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg] == nullptr) {
                  std::cout << arg << " element is missing" << std::endl;
                  break;
                }
                if (types[arg] != 1) {
                  std::cout << "Incompatible type of element. Here you can test only StringID" << std::endl;
                  break;
                }
                std::cout << strs[arg]->length() << std::endl;
                break;

              case '4':
                {
                  std::cout << "Which string you want to upcase? [input index]" << std::endl;
                  std::cin.get(arg);
                  clear();
                  if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                    std::cout << "Incorrect argument" << std::endl;
                    break;
                  }
                  if (strs[arg] == nullptr) {
                    std::cout << arg << " element is missing" << std::endl;
                    break;
                  }
                  if (types[arg] != 1) {
                    std::cout << "Incompatible type of element. Here you can test only StringID" << std::endl;
                    break;
                  }
                  StringID * s = (StringID *) strs[arg];
                  std::cout << "Was: " << *s << std::endl;
                  s->upcase();
                  std::cout << "Now: " << *s << std::endl;
                }
                break;

              case '5':
                {
                  std::cout << "Choose the first string (in that string will keep result of concat) [input index]" << std::endl;
                  std::cin.get(arg);
                  clear();
                  if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                    std::cout << "Incorrect argument" << std::endl;
                    break;
                  }
                  if (strs[arg] == nullptr) {
                    std::cout << arg << " element is missing" << std::endl;
                    break;
                  }
                  if (types[arg] != 1) {
                    std::cout << "Incompatible type of element. Here you can test only StringID" << std::endl;
                    break;
                  }
                  StringID * s1 = (StringID *) strs[arg];
                  std::cout << "Choose the second string [input index]" << std::endl;
                  std::cin.get(arg);
                  clear();
                  if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                    std::cout << "Incorrect argument" << std::endl;
                    break;
                  }
                  if (strs[arg] == nullptr) {
                    std::cout << arg << " element is missing" << std::endl;
                    break;
                  }
                  if (types[arg] != 1) {
                    std::cout << "Incompatible type of element. Here you can test only StringID" << std::endl;
                    break;
                  }
                  StringID * s2 = (StringID *) strs[arg];
                  std::cout << "Was: string1 = " << *s1 << ", string2 = " << *s2 << std::endl;
                  *s1 = *s1 + *s2;
                  std::cout << "Now: string1 = " << *s1 << std::endl;
                }
                break;

              default:
                std::cout << "Incorrect argument" << std::endl;
            }
            break;



          case '4':
            std::cout << "1 - print count of calls copy constructor" << std::endl
              << "2 - assign value of one element to another" << std::endl
              << "3 - print length of string" << std::endl
              << "4 - count the sum of two numbers" << std::endl
              << "5 - know is number is positive" << std::endl;
            std::cin.get(arg);
            clear();
            switch (arg) {
              case '1':
                std::cout << "Count of calls of which element you want to output? [input index]" << std::endl;
                std::cin.get(arg);
                clear();
                if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg] == nullptr) {
                  std::cout << arg << " element is missing" << std::endl;
                  break;
                }
                if (types[arg] != 2) {
                  std::cout << "Incompatible type of element. Here you can test only StringD" << std::endl;
                  break;
                }
                std::cout << strs[arg]->getCountOfCallCopy() << std::endl;
                break;

              case '2':
                std::cout << "Value of which element you want to change? [input index]" << std::endl;
                std::cin.get(arg);
                clear();
                if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg] == nullptr) {
                  std::cout << arg << " element is missing" << std::endl;
                  break;
                }
                if (types[arg] != 2) {
                  std::cout << "Incompatible type of element. Here you can test only StringD" << std::endl;
                  break;
                }
                std::cout << "Value of which element you want to assign? [input index]" << std::endl;
                std::cin.get(arg2);
                clear();
                if ((int) arg2 - 48 > countOfTestingClasses || (int) arg2 - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg2] == nullptr) {
                  std::cout << arg2 << " element is missing" << std::endl;
                  break;
                }
                if (types[arg2] != 2) {
                  std::cout << "Incompatible type of element. Here you can test only StringD" << std::endl;
                  break;
                }
                std::cout << arg << " element was = " << *strs[arg] << "\tassigned to " << arg2 << " element = " << *strs[arg2] << std::endl;
                *strs[arg] = *strs[arg2];
                std::cout << arg << " element now = " << *strs[arg] << std::endl;
                break;

              case '3':
                std::cout << "Length of which element you want to output? [input index]" << std::endl;
                std::cin.get(arg);
                clear();
                if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                  std::cout << "Incorrect argument" << std::endl;
                  break;
                }
                if (strs[arg] == nullptr) {
                  std::cout << arg << " element is missing" << std::endl;
                  break;
                }
                if (types[arg] != 2) {
                  std::cout << "Incompatible type of element. Here you can test only StringD" << std::endl;
                  break;
                }
                std::cout << strs[arg]->length() << std::endl;
                break;

              case '4':
                {
                  std::cout << "Choose the first element (in that element will keep result of sum) [input index]" << std::endl;
                  std::cin.get(arg);
                  clear();
                  if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                    std::cout << "Incorrect argument" << std::endl;
                    break;
                  }
                  if (strs[arg] == nullptr) {
                    std::cout << arg << " element is missing" << std::endl;
                    break;
                  }
                  if (types[arg] != 2) {
                    std::cout << "Incompatible type of element. Here you can test only StringD" << std::endl;
                    break;
                  }
                  StringD * s1 = (StringD *) strs[arg];
                  std::cout << "Choose the second element [input index]" << std::endl;
                  std::cin.get(arg);
                  clear();
                  if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                    std::cout << "Incorrect argument" << std::endl;
                    break;
                  }
                  if (strs[arg] == nullptr) {
                    std::cout << arg << " element is missing" << std::endl;
                    break;
                  }
                  if (types[arg] != 2) {
                    std::cout << "Incompatible type of element. Here you can test only StringD" << std::endl;
                    break;
                  }
                  StringD * s2 = (StringD *) strs[arg];
                  std::cout << "Was: string1 = " << *s1 << ", string2 = " << *s2 << std::endl;
                  *s1 = *s1 + *s2;
                  std::cout << "Now: string1 = " << *s1 << std::endl;
                }
                break;

              case '5':
                {
                  std::cout << "Which element you want to check? [input index]" << std::endl;
                  std::cin.get(arg);
                  clear();
                  if ((int) arg - 48 >= countOfTestingClasses || (int) arg - 48 < 0) {
                    std::cout << "Incorrect argument" << std::endl;
                    break;
                  }
                  if (strs[arg] == nullptr) {
                    std::cout << arg << " element is missing" << std::endl;
                    break;
                  }
                  if (types[arg] != 2) {
                    std::cout << "Incompatible type of element. Here you can test only StringD" << std::endl;
                    break;
                  }
                  StringD * s = (StringD *) strs[arg];
                  std::cout << (s->isPositive() ? "Positive" : "Negative") << std::endl;
                }
                break;

              default:
                std::cout << "Incorrect argument" << std::endl;
            }
            break;

          default:
            std::cout << "Incorrect argument" << std::endl;
        }
        break;


        
      case '3':
        isRunning = false;
        break;
      default:
        clear();
        std::cout << "Incorrect argument" << std::endl;
    }
  }

  delete[] strs;
}