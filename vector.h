#pragma once
template<typename T>
class vector {
private:
    T* data;
    size_t capacity;
    size_t size_;

public:
    // default constructor
    vector() : data(nullptr), capacity(0), size_(0) {}

    // constructor with initial size and value
    vector(size_t initial_size, const T& value = T()) : capacity(initial_size), size_(initial_size) {
        data = new T[initial_size];
        std::fill(data, data + initial_size, value);
    }

    // initializer list constructor
    vector(std::initializer_list<T> init) : capacity(init.size()), size_(init.size()) {
        data = new T[size_];
        std::copy(init.begin(), init.end(), data);
    }

    // move constructor
    vector(vector&& other) noexcept : data(other.data), capacity(other.capacity), size_(other.size_) {
        other.data = nullptr;
        other.capacity = 0;
        other.size_ = 0;
    }

    // copy assignment operator
    vector& operator=(const vector& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size_ = other.size_;
            data = new T[capacity];
            std::copy(other.data, other.data + size_, data);
        }
        return *this;
    }

    // destructor
    ~vector() {
        delete[] data;
    }

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        std::copy(data, data + size_, new_data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    void push_back(const T& value) {
        if (size_ == capacity) {
            resize((capacity == 0) ? 1 : capacity * 2);
        }
        data[size_++] = value;
    }

    // access elements
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    size_t size() const {
        return size_;
    }

    // iterator support for loops
    T* begin() {
        return data;
    }

    T* end() {
        return data + size_;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + size_;
    }

    // is vector empty
    bool empty() const {
        return size_ == 0;
    }
};