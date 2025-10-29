#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <memory>
#include <iterator>
#include <stdexcept>

template<typename T>
class CircularBuffer {
private:
    std::unique_ptr<T[]> buffer_;
    size_t capacity_;
    size_t size_;
    size_t head_;  // 다음에 데이터를 추가할 위치
    size_t tail_;  // 가장 오래된 데이터의 위치

public:
    // Forward Iterator 클래스
    class iterator {
    private:
        const CircularBuffer* buffer_;
        size_t index_;
        size_t count_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(const CircularBuffer* buf, size_t idx, size_t cnt) 
            : buffer_(buf), index_(idx), count_(cnt) {}

        reference operator*() {
            return buffer_->buffer_[index_];
        }

        pointer operator->() {
            return &buffer_->buffer_[index_];
        }

        iterator& operator++() {
            if (count_ > 0) {
                index_ = (index_ + 1) % buffer_->capacity_;
                --count_;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return buffer_ == other.buffer_ && count_ == other.count_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    // Const Iterator 클래스
    class const_iterator {
    private:
        const CircularBuffer* buffer_;
        size_t index_;
        size_t count_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator(const CircularBuffer* buf, size_t idx, size_t cnt) 
            : buffer_(buf), index_(idx), count_(cnt) {}

        reference operator*() const {
            return buffer_->buffer_[index_];
        }

        pointer operator->() const {
            return &buffer_->buffer_[index_];
        }

        const_iterator& operator++() {
            if (count_ > 0) {
                index_ = (index_ + 1) % buffer_->capacity_;
                --count_;
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const const_iterator& other) const {
            return buffer_ == other.buffer_ && count_ == other.count_;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
    };

    // 생성자
    explicit CircularBuffer(size_t capacity);

    // 복사 생성자
    CircularBuffer(const CircularBuffer& other);

    // 대입 연산자
    CircularBuffer& operator=(const CircularBuffer& other);

    // 소멸자
    ~CircularBuffer() = default;

    // 용량 및 크기 관련 메서드
    size_t capacity() const { return capacity_; }
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    // 데이터 추가/제거 메서드
    void push_back(const T& item);
    void pop_front();

    // 데이터 접근 메서드
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    // 반복자 메서드
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
};

#include "CircularBuffer.tpp"

#endif // CIRCULAR_BUFFER_H
