#include "queue.hpp"

queue_t::queue_t(size_t size)
    : size_{size} {
    array_.reset(new elem_t[size]);

    for (size_t i = 0; i < size; ++i) {
        array_[i].sequence.store(i);
        array_[i].data = 0;
    }
}

bool queue_t::enqueue(int number) {
    const auto mask = size_ - 1;
    auto pos = enqueue_pos_.load(std::memory_order_relaxed);
    elem_t* elem = nullptr;

    for (;;) {
        elem = &array_[pos & mask];
        auto seq = elem->sequence.load(std::memory_order_acquire);
        auto dif = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos);

        if (dif == 0) {
            if (enqueue_pos_.compare_exchange_weak(pos, pos + 1, std::memory_order_relaxed))
                break;
        }
        else if (dif < 0) {
            return false;
        }
        else {
            pos = enqueue_pos_.load(std::memory_order_relaxed);
        }
    }

    elem->data = number;
    elem->sequence.store(pos + 1, std::memory_order_release);

    return true;
}

int queue_t::dequeue() {
    const auto mask = size_ - 1;
    auto pos = dequeue_pos_.load(std::memory_order_relaxed);
    elem_t* elem = nullptr;

    for (;;) {
        elem = &array_[pos & mask];
        auto seq = elem->sequence.load(std::memory_order_acquire);
        auto dif = static_cast<intptr_t>(seq) - static_cast<intptr_t>(pos + 1);

        if (dif == 0) {
            if (dequeue_pos_.compare_exchange_weak(pos, pos + 1, std::memory_order_relaxed))
                break;
        }
        else if (dif < 0) {
            return 0;
        }
        else {
            pos = dequeue_pos_.load(std::memory_order_relaxed);
        }
    }

    const auto number = elem->data;
    elem->sequence.store(pos + mask + 1, std::memory_order_release);

    return number;
}