// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
 private:
    T* massiv;
    int maxLength;
    int start;
    int stop;
    int c;
 public:
    TPQueue();
        ~TPQueue();
        void push(const T&);
        T pop();
        T get() const;
        bool isEmpty() const;
        bool isFull() const;
    };

template<typename T>
TPQueue<T>::TPQueue() : maxLength(100),
start(0), stop(0), c(0) {
    massiv = new T[maxLength + 1];
}

template<typename T>
TPQueue<T>::~TPQueue() {
  delete [] massiv;
}

template<typename T>
void TPQueue<T>::push(const T & item) {
  assert(c < maxLength);

  if (stop != 0) {
      for (int i = stop - 1; i > -1; --i) {
          if (massiv[i].prior >= item.prior) {
              massiv[i + 1] = item;
              continue;
          }

          if (massiv[i].prior < item.prior) {
              massiv[i + 1] = massiv[i];
              if (i == 0)
                massiv[i] = item;

              continue;
          }
      }
  } else {
      massiv[start] = item;
  }

  c++;
  stop++;
}

template<typename T>
T TPQueue<T>::pop() {
  assert(c > 0);
  T item = massiv[start++];
  c--;
  if (start > maxLength)
      start -= maxLength + 1;
  return item;
}

template<typename T>
T TPQueue<T>::get() const {
  assert(c > 0);
  return massiv[start];
}

template<typename T>
bool TPQueue<T>::isEmpty() const {
  return c == 0;
}

template<typename T>
bool TPQueue<T>::isFull() const {
  return c == maxLength;
}

struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
