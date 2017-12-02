#include "queue.hpp"
#include "utils.hpp"
#include <random>
#include <thread>
#include <chrono>
#include <iomanip>
#include <map>
#include <Windows.h> // _mm_pause()

namespace {
queue_t queue{1024};
std::map<int, entry_t> result;

void on_produce(int limit) {
    const auto from = 1;
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dis{from, limit};

    for (auto i = from; i <= limit; ++i) {
        const auto number = dis(gen);
        while (!queue.enqueue(number))
            _mm_pause();
    }
}

void on_consume(int until) {
    namespace chrono =  std::chrono;

    const auto width = get_digits(until);
    auto on_print = [width](int value, const entry_t &elem) {
        std::cout << "sequence: " << std::setw(width) << elem.sequence;
        std::cout << ", value: " << std::setw(width) << value;
        std::cout << ", generated in: " << std::setw(5) << elem.time << " microseconds\n";
    }; // lambda on_print

    int dequeued = 0;
    int sequence = 0;
    chrono::high_resolution_clock clock;
    auto generation_op = clock.now();

    // start dequeuing
    do {
        const auto value = queue.dequeue();
        if (!value) continue;

        ++dequeued;
        auto it = result.emplace(std::make_pair(value, entry_t{}));
        if (!it.second) continue;

        ++sequence;
        const auto current_time = clock.now();
        const auto op_duration = current_time - generation_op;
        const auto op_ms = chrono::duration_cast<chrono::microseconds>(op_duration);
        generation_op = current_time;

        auto& elem = it.first->second;
        elem.sequence = sequence;
        elem.time = op_ms.count();

        on_print(value, elem);
    } while (dequeued < until);
}
} // namespace

int main(int argc, char** argv) {
    const auto limit = get_limit(argc, argv);
    if (!limit) return 0;

    std::thread consumer{on_consume, limit};
    std::thread producer{on_produce, limit};

    producer.join();
    consumer.join();

    const auto count = result.size();
    if (!count) return 0;

    size_t generation_duration = 0;
    for (const auto& entry : result)
        generation_duration += entry.second.time;
    const auto avg = generation_duration / count;

    std::cout << "average generation: " << avg << " microseconds" << std::endl;

    return 0;
}