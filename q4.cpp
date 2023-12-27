//Question 4 - pointers

// There is a memory leak in the code below, where is it?, what class/solution can you use to fix it while ensuring that the object will be deleted only once and only when it's not used by any consumer
// Task: Modify the code to address the issues above. Please explain the changes you made and how they solve the memory allocation/deletion issue  

// Do not remove any function or change threads dispatching order - you can(and should) change the functions body/signature

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>

struct Payload {
    Payload(uint64_t id_) :
        id(id_),
        veryLargeVector(1000 * 1000)
    {}

    uint64_t id;
    std::vector<int> veryLargeVector;
};

void operation1(Payload* payload) {
    std::cout << "Performing operation1 on payload " << payload->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));
    std::cout << "Operation1 Performed" << std::endl;
}

void operation2(Payload* payload) {
    std::cout << "Performing operation2 on payload " << payload->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));
    std::cout << "Operation2 Performed" << std::endl;
}

void dispatcher_thread(Payload* payload) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread wt1(&operation1, payload);
    std::thread wt2(&operation2, payload);

    wt1.join();
    wt2.join();

    // The threads have finished using the payload, safe to delete it
    delete payload;
}

int main(int argc, char** argv)
{
    std::cout << "Calling dispatcher thread" << std::endl;

    Payload* payload = new Payload(1);

    std::thread t(&dispatcher_thread, payload);
    t.join();

    std::cout << "Press enter to exit" << std::endl;
    getchar(); // Note: getchar() is used for simplicity, consider using a better way to wait for user input

    return 0;
}
