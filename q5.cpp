// Question 5
//
//	we want to implement a logic class named MyBool to use in our logic
//	we would like to be able to use the logical and (&&) with instances of this class 
//  i.e. to be able to write in the form of myBool1 && myBool2
//	we have also implemented some function using this class
//	"notNull" checks if a pointer is null and return a corresponding MyBool
//  "greaterThanZero" checks if an int pointer points to a positive int and return a corresponding MyBool
//
//	1. Implement this addition in the MyBool class 
// -answer: See inside the class the operator overloading
//  2. Did it compile successfully?
//  -answer: Yes, It is
//	3. Did it run successfully? 
// - answer: Yes, It is. Since we check before increment the value if the pointer is not null.                                   
//	4. Explain the result, explain what happened and why
//  answer - In the main function we created 2 pointer for type int , a and b.
//  we also created a variable val and initilize it to 5. than a initialized to Null 
//  and b initilized to the address of val.
// The first if check if the pointer is not null and if the value is positive.
// The second and the third if check the same things using the two functions.
// The function "MyBool notNull(int* intPtr)" return object of MyBool and the value of m_val depends if the intPtr is null or not 
// The function "MyBool greaterThanZero(int* intPtr)" return object of MyBool ant the value of m_val depends if the intPtr is positive or not 

// useful links:
// https://en.cppreference.com/w/cpp/language/operators
// https://cplusplus.com/doc/tutorial/operators/
// https://isocpp.org/wiki/faq/operator-overloading
 
#include <iostream>

class MyBool
{
public:
	MyBool(bool b) : m_val(b) {};

	//TODO: Your code here
    //The solution for task number 1 (implement an operator overloading for "&&"")
    bool operator&&(const MyBool& other) const
    {
        return m_val && other.m_val;
    }

	
private:
	bool m_val;
};

MyBool notNull(int* intPtr)
{
	return intPtr != nullptr;
}

MyBool greaterThanZero(int* intPtr)
{
	return *intPtr > 0;
}

int main(int argc, char* argv[])
{
	int* a = nullptr;
	int val = 5;
	int* b = &val;

	
	// the long way to check
	if (a != nullptr && *a > 0)
	{
		++*a;
		std::cout << "*a is " << *a << std::endl;
	}

	// using our functions
	if (notNull(b) && greaterThanZero(b))
	{
		++*b;
		std::cout << "*b is " << *b << std::endl;
	}

	// using our functions again
	if (notNull(a) && greaterThanZero(a))
	{
		++*a;
		std::cout << "*a is " << *a << std::endl;
	}

	return 0;
}
