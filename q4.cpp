//Question 4 - pointers

// There is a memory leak in the code below, where is it?, what class/solution can you use to fix it while ensuring that the object will be deleted only once and only when it's not used by any consumer
// Task: Modify the code to address the issues above. Please explain the changes you made and how they solve the memory allocation/deletion issue  
// Answer:
// The memory leak is because in the code we allocate memory for payload object and we don't releas it when we finished to use this object,
// and also we have an issue with wt1.detach() and wt2.detach() because this method means that the main thread has no control over the state of the secondary threads.
// For the first issue, I added a Delete operation when the payload object finish his working, 
// For the secounand issue, I replaced detached() method with join method that make the program to wait until the threads will be finished. 
// Do not remove any function or change threads dispatching order - you can(and should) change the functions body/signature

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>

struct Payload 
{
    Payload(uint64_t id_) :
        id(id_),
        veryLargeVector(1000 * 1000)
    {}

    uint64_t id;
    std::vector<int> veryLargeVector;
};

void operation1(Payload* payload) 
{
    std::cout << "Performing operation1 on payload " << payload->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));
    std::cout << "Operation1 Performed" << std::endl;
}

void operation2(Payload* payload) 
{
    std::cout << "Performing operation2 on payload " << payload->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));
    std::cout << "Operation2 Performed" << std::endl;
}

void dispatcher_thread(Payload* payload) 
{
    // Payload* payload = new Payload(1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread wt1(&operation1, payload);
    std::thread wt2(&operation2, payload);

	// //Waiting for wt1 & wt2 to finish is not allowed, dispacher_thread should exit after creating wt1 and wt2
	// wt1.detach();
	// wt2.detach();
    //Waiting for wt1 & wt2 to finish
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
