//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

constexpr size_t ITERATIONS = 1000 * 1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

size_t gSum = 0;
std::mutex gSumMutex;  // Mutex to protect gSum

void operation1(size_t arg) {
    std::cout << "Performing operation1" << std::endl;
    for (size_t i = 0; i < ITERATIONS; i++) {
        gSumMutex.lock();  // Lock the mutex
        gSum += (arg + i);
        gSumMutex.unlock();  // Unlock the mutex explicitly
    }
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate some heavy work
    std::cout << "Operation1 Performed" << std::endl;
}

void operation2(size_t arg) {
    std::cout << "Performing operation2" << std::endl;
    for (size_t i = 0; i < ITERATIONS; i++) {
        gSumMutex.lock();  // Lock the mutex
        gSum += (arg * i);
        gSumMutex.unlock();  // Unlock the mutex explicitly
    }
    std::this_thread::sleep_for(std::chrono::seconds(10)); // Simulate some heavy work
    std::cout << "Operation2 Performed" << std::endl;
}

int main(int argc, char** argv) {
    auto start = std::chrono::steady_clock::now();

    // Create two threads to execute operation1 and operation2 concurrently
    std::thread thread1(operation1, OP1_PARAM);
    std::thread thread2(operation2, OP2_PARAM);

    // Wait for both threads to finish
    thread1.join();
    thread2.join();

    auto end = std::chrono::steady_clock::now();

    std::cout << "Total execution duration in milliseconds: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    std::cout << "Result:  " << gSum << ", " << (gSum == EXPECTED_SUM ? "success" : "failure!") << std::endl;
    std::cout << "Press enter to exit" << std::endl;
    getchar();
    return 0;
}
