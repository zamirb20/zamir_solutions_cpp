// Question 3 - implementation
// 
//	without using STL containers implement the following:
//	A class for a dynamic int array, let's call it "CVectorInt" that -
//  1. doubles its size automatically when its full (allocates twice the size and moves the data),
//	2. halves its size when it is half empty (allocates half of the size and moves the data)
//  3. can be told the initial capacity (num of ints) in a constructor
//  4. have a method called "reserve" - that Requests that the vector capacity be at least enough to contain n elements.
//     If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n
//  5. have a method called "capacity" - that returns the number of int elements allocated
//  6. have a method called "size" - that returns the number of elements actually inserted
//  7. have a method called "empty" - that returns true/false according to amount of actual elements in the data
//  8. have a method called "clear" - that frees all the data and resets the size
//  9. have a method called "push_back" - that adds an int elements at the end
// 10. have a method called "pop_back" - that removes an int elements at the end and return it
// 11. have a method called "remove"  - that removes an int elements at specific index
// 12. have an interface to access the data at a specific index using subscript "[]"
//
// make sure to handle edge cases such as memory issues, size issues etc.



#include <iostream>
#include <stdexcept>


class CVectorInt
{

// TODO: your code here
private:
    int* arr;
    int size_array;
    int capacity_array;
public:
    // Default constructor
    CVectorInt() : arr(nullptr), size_array(0), capacity_array(0) {}

    // Constructor with initial capacity
    CVectorInt(int initialCapacity) : arr(nullptr), size_array(0), capacity_array(initialCapacity) 
    {
        if (initialCapacity > 0) 
        {
            arr = new int[initialCapacity];
        }
    }
        // Destructor
    ~CVectorInt() 
    {
        if (arr != nullptr) 
        {
            delete[] arr;
        }
    }
    // method to allocate capacity of n element in the array
    void reserve(int n) 
    {
        if (n > capacity_array) 
        {
            // Allocate a new array with the requested capacity
            int* newArray = new int[n];

            // Copy elements to the new array
            for (int i = 0; i < size_array; ++i) 
            {
                newArray[i] = arr[i];
            }

            // Delete the old array and update the pointer and capacity
            delete[] arr;
            arr = newArray;
            capacity_array = n;
        }
    }
    // method to return the current array capacity
    int capacity()
    {
        return capacity_array;
    }
    // method to return the current array size
    int size()
    {
        return size_array;
    }
    // method to check if the array is empty 
    bool empty()
    {
        if (size_array==0)
            return true;
        else
            return false;
    }
    // / Method to clear the array, freeing all data and resetting the size
    void clear() {
        // Delete the current array
        delete[] arr;

        // Reset size and capacity
        size_array = 0;
        capacity_array = 0;

        // Set the pointer to nullptr
        arr = nullptr;
    }
    // Method to add an element to the end of the array
    void push_back(int value) 
    {
        if (size_array == capacity_array) {
            // If the array is full, resize it
            double_array();
        }
        arr[size_array++] = value;
    }
    // Method to remove the last element and return it
    int pop_back() {
        if (size_array > 0) {
            int lastElement = arr[--size_array];
            // Resizing the array if it becomes half empty
            if (capacity_array/2 > size_array)
                halves_array();
            return lastElement;
        } 
        else 
        {
            // Handle underflow (array is empty)
            std::cout << "Array is empty. Cannot pop_back.\n";
            return -1;
        }
    }
     // Method to remove element in a specofic index
    void remove(int index) 
    {
        if (index < size_array) {
            // Shift elements to the left to overwrite the element at the specified index
            for (int i = index; i < size_array - 1; ++i) 
            {
                arr[i] = arr[i + 1];
            }
            // Decrement the size
            --size_array;
        } 
        else 
        {
            // Handle index out of limits
            std::cout << "Index out of limits. Cannot remove.\n";
        }
    }
    // Overloading the  operator []
    int& operator[](int index) 
    {
        if (index < size_array) 
        {
            return arr[index];
        } 
        else 
        {
            // Handle index out of limits
            std::cout << "Index out of limits. Returning a reference to the first element.\n";
            return arr[0]; 
        }
    }
private:
    // Method to double the capacity of the array
    void double_array()
    {
        if (capacity_array == 0) 
        {
            capacity_array = 1;
        }   
        else  
        {
            capacity_array *= 2;
        }
        int* newArray = new int[capacity_array];
        // Copy elements to the new array
        for (int i = 0; i < size_array; ++i) 
        {
            newArray[i] = arr[i];
        }

        // Delete the old array and update the pointer
        delete[] arr;
        arr = newArray;   
    }
    // Method to halves the capacity of the array
    void halves_array()
    {
        if (capacity_array == 0) 
        {
            capacity_array = 1;
        }   
        else  
        {
            capacity_array /= 2;
        }
        int* newArray = new int[capacity_array];
        // Copy elements to the new array
        for (int i = 0; i < size_array; ++i) 
        {
            newArray[i] = arr[i];
        }

        // Delete the old array and update the pointer
        delete[] arr;
        arr = newArray;   
    }
};

int main(int argc, char* argv[])
{
	// some code to use the class
	try
	{
		CVectorInt v(5);

		for (int i = 0; i < 5; i++)
		{
			v.push_back(i);
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.push_back(1);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		while (!v.empty())
		{
			v.pop_back();
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.reserve(15);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		for (int i = 0; i < 15; i++)
		{
			v.push_back(i);
		}
		v[5] = 3;
		for (int i = 0; i < v.size(); i++)
		{
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
		v.clear();
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
    return 0;
}
