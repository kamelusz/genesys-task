#pragma once
#include <atomic>
#include <vector>
#include <memory>

class queue_t {
public:
    queue_t(size_t size);
    bool enqueue(int number);
    int dequeue();
private:
    struct elem_t {
        int data;
        std::atomic<size_t> sequence;
    };

    const size_t size_;
    std::atomic<size_t> enqueue_pos_ = ATOMIC_VAR_INIT(0);
    std::atomic<size_t> dequeue_pos_ = ATOMIC_VAR_INIT(0);
    std::unique_ptr<elem_t[]> array_;
};