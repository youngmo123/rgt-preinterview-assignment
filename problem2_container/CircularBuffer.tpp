#ifndef CIRCULAR_BUFFER_TPP
#define CIRCULAR_BUFFER_TPP

#include "CircularBuffer.h"

template<typename T>
CircularBuffer<T>::CircularBuffer(size_t capacity) 
    : buffer_(std::make_unique<T[]>(capacity)), 
      capacity_(capacity), 
      size_(0), 
      head_(0), 
      tail_(0) {
    if (capacity == 0) {
        throw std::invalid_argument("Capacity must be greater than 0");
    }
}

template<typename T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer& other)
    : buffer_(std::make_unique<T[]>(other.capacity_)),
      capacity_(other.capacity_),
      size_(other.size_),
      head_(other.head_),
      tail_(other.tail_) {
    
    for (size_t i = 0; i < capacity_; ++i) {
        buffer_[i] = other.buffer_[i];
    }
}

template<typename T>
CircularBuffer<T>& CircularBuffer<T>::operator=(const CircularBuffer& other) {
    if (this != &other) {
        buffer_ = std::make_unique<T[]>(other.capacity_);
        capacity_ = other.capacity_;
        size_ = other.size_;
        head_ = other.head_;
        tail_ = other.tail_;
        
        for (size_t i = 0; i < capacity_; ++i) {
            buffer_[i] = other.buffer_[i];
        }
    }
    return *this;
}

template<typename T>
void CircularBuffer<T>::push_back(const T& item) {
    buffer_[head_] = item;
    head_ = (head_ + 1) % capacity_;
    
    if (size_ < capacity_) {
        ++size_;
    } else {
        // 버퍼가 가득 찬 경우, tail도 이동
        tail_ = (tail_ + 1) % capacity_;
    }
}

template<typename T>
void CircularBuffer<T>::pop_front() {
    if (empty()) {
        throw std::runtime_error("Cannot pop from empty buffer");
    }
    
    tail_ = (tail_ + 1) % capacity_;
    --size_;
}

template<typename T>
T& CircularBuffer<T>::front() {
    if (empty()) {
        throw std::runtime_error("Buffer is empty");
    }
    return buffer_[tail_];
}

template<typename T>
const T& CircularBuffer<T>::front() const {
    if (empty()) {
        throw std::runtime_error("Buffer is empty");
    }
    return buffer_[tail_];
}

template<typename T>
T& CircularBuffer<T>::back() {
    if (empty()) {
        throw std::runtime_error("Buffer is empty");
    }
    size_t back_index = (head_ == 0) ? capacity_ - 1 : head_ - 1;
    return buffer_[back_index];
}

template<typename T>
const T& CircularBuffer<T>::back() const {
    if (empty()) {
        throw std::runtime_error("Buffer is empty");
    }
    size_t back_index = (head_ == 0) ? capacity_ - 1 : head_ - 1;
    return buffer_[back_index];
}

template<typename T>
typename CircularBuffer<T>::iterator CircularBuffer<T>::begin() {
    return iterator(this, tail_, size_);
}

template<typename T>
typename CircularBuffer<T>::iterator CircularBuffer<T>::end() {
    return iterator(this, tail_, 0);
}

template<typename T>
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::begin() const {
    return const_iterator(this, tail_, size_);
}

template<typename T>
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::end() const {
    return const_iterator(this, tail_, 0);
}

template<typename T>
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::cbegin() const {
    return const_iterator(this, tail_, size_);
}

template<typename T>
typename CircularBuffer<T>::const_iterator CircularBuffer<T>::cend() const {
    return const_iterator(this, tail_, 0);
}

#endif // CIRCULAR_BUFFER_TPP
