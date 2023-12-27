// Question 1 - functions
// 
//	you are given the following missing implementation:
//	float applyF(float a, float b, ??????)
//	{
//		return f(a, b);
//	}
//	
//	1) list at least 3 different ways to replace the qustion marks (??????)
//		1. Function Pointer - float applyF1(float a, float b, float (*f)(float, float))
//		2. Function Reference - float applyF2(float a, float b, float (&f)(float, float))
//		3. Function template - float applyF3(float a, float b, const Functor& f) 
//	
//	2) replace the qustion marks in the following implementations with the solutions you listed
//
//	3) using one of those options create an add operation and a multiply operation and implement the following computation:
//		(2 * 3) + (4 * 5) + 6
//
//	you may not change the functions' implementation, only complete the signature

#include <iostream>

// Function object class with overloaded operator() for addition
class Add 
{
public:
    float operator()(float a, float b) const 
    {
        return a + b;
    }
};

// Function object class with overloaded operator() for multiplication
class Multiply 
{
public:
    float operator()(float a, float b) const {
        return a * b;
    }
};
// 1. Function Pointer
float applyF1(float a, float b, float (*f)(float, float)) 
{
    return f(a, b);
}
// 2. Function Reference
float applyF2(float a, float b, float (&f)(float, float)) 
{
    return f(a, b);
}

// 3. Function template for applyF3 with a functor
template <typename Functor>
float applyF3(float a, float b, const Functor& f) {
    return f(a, b);
}


int main(int argc, char *argv[])
{
    float fNum = 0;

    // Create instances of functors
    Add addFunctor;
    Multiply multiplyFunctor;

    // calculate fNum = (2 * 3) + (4 * 5) + 6 using applyF3
    fNum = applyF3(applyF3(applyF3(2, 3, multiplyFunctor) , applyF3(4, 5, multiplyFunctor),addFunctor) , 6,addFunctor);

    std::cout << "Result using applyF1: " << fNum << std::endl;

    return 0;
}
