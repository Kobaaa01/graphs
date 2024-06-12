#pragma once
#include "vector.h"
struct Queue {
    vector<int> data;
    int start, end;

    explicit Queue(int n) : data(n), start(0), end(0) {}

    void push(int x) {
        data[end++] = x;
    }

    int pop() {
        return data[start++];
    }

    bool empty() const {
        return start == end;
    }
};