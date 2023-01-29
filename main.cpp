// sam206 - vector - accessing elements using Iterators
//
// https://en.cppreference.com/w/cpp/container/vector

#include <iostream>
#include <vector>
//#include <algorithm>
using namespace std;

/**
 *  Iterator
 *  An Iterator is an object that we can use to point at a position in a vector.
 *  Iterators can be used to move along through the elements in an array by
 *  incrementing the iterator.  We can call methods from the vector class to get
 *  an iterator to a vector's elements.
 *
 * This sample shows:
 * - iterating over elements of vector using Iterator
 * - declaring iterator variable/object using "auto"
 * - using vector functions that depend on iterators
 * - using the Algorithms Library <algorithm> to process vector
 *      functions:  all_of(), none_of(), find(), find_if()
 *                  use of lambdas, use of predicates
 */

// function prototype
void display(const vector<int> &);  // parameter is a reference to a vector (pass-by-reference)
// the "const" means that the parameter references a constant vector - meaning that,
// the reference can not be used to modify the contents of the vector.
void populate_vector( vector<int>& );

int main()
{
    cout << "sam206 - vector - using Iterators" << endl;

    // Create a vector called "ages_vector" to store the ages of students in a class.
    // The "ages_vector" is an object that is of type "vector of int".

    vector<int> ages_vector;  // declare an object that is a vector of int - initially empty

    populate_vector(ages_vector);

    display(ages_vector);

    // Let's say we want to use an iterator to iterate across (move across) each
    // element in the vector and print out each element.
    // We use the function begin(), to get an iterator that initially points
    // to the beginning of the vector.

    // We store the iterator in a variable of type Iterator (called "iter")
    // Defining the types for iterator can be complex, but luckily, C++ allows
    // us to use the "auto" keyword, which declares the right type for the iterator variable.
    // "auto" deduces the right type from the return type of function begin().

    auto iter = ages_vector.begin();

// https://en.cppreference.com/w/cpp/container/vector/begin

    // Now we have an iterator that points at the first element in the vector.
    // Let's use the iterator to access the element and output it.

    cout << "Dereferencing the Iterator to get first element in vector, value = " << *iter << endl;

    // The star "*" is the "dereference" operator, as it gets the thing that the iterator is referring to.
    // The Iterator points at the first element, so *iter, gets the element that the iterator points at.

    // An Iterator can be incremented - so that it moves forward to point at the next element of the vector.
    iter++; // move from pointing at current element to pointing at next element

    cout << "Increment by one (iter++;) Dereferencing the Iterator to get value = " << *iter << endl;

    // Now that we know how an iterator operates, let us use it
    // to iterate over all the elements in the vector.
    // In our for loop, we will initialize an iterator to point at the first element.
    // Each time, we check that our iterator (iter) is not equal to the end iterator.
    // We get the end iterator position by calling end().
    // Note that the iterator is considered at the end when it points
    // just beyond the last element.

    cout << "Output vector elements using for loop and iterator : ";
    for (auto iter = ages_vector.begin(); iter != ages_vector.end(); ++iter){
        cout << *iter << ", " ;  // dereference iterator to get the element
    }
    cout << endl;



    // Below we use cbegin() and cend() [since C++ 14] which gives us iterators that
    // point to "constant" elements.
    // This helps us to avoid accidental modification of the vector elements.
    // We should really always use them, unless we want to update the element
    // that an iterator points to.

    // Use the count() function from <algorithm> library to count elements in vector
    // Let's count the number of ages in the vector that are = 18
    int age = 21;

    // the count() function requires us to pass in two iterators :
    // an iterator pointing at the beginning of where we want to search in the vector, and
    // an iterator pointing at then end of where we want to search in the vector.
    // https://cplusplus.com/reference/algorithm/count/

    int num_items = count(ages_vector.cbegin(), ages_vector.cend(), age);  // counts all matches (=18) from beginning to end of vector
    cout << "Count of students aged " << age << " = " << num_items << endl;

    // use the count_if() function from <algorithm> library
    // and a lambda expression to count student ages that are under 18
    // The predicate here is  a UnaryPredicate - as it takes one parameter only (i)
    // and returns a boolean value (true or false)
    // https://cplusplus.com/reference/algorithm/

    int count_under18 = count_if(ages_vector.begin(), ages_vector.end(), [] (int i) { return i < 18; } );
    cout << "Count of students aged under 18 = " << count_under18 << '\n';

    // remove the last element in a vector
    if( !ages_vector.empty() )
    {
        ages_vector.pop_back();   // removes the last element from a vector
    }

    // We use the member function erase() to remove either :
    // - an element at a position specified by an iterator or
    // - a range of elements specified by two iterators (start and end of range)
    // This operation is usually expensive (unless removing only the end element(s))
    //

    cout << "Vector content before erasing the third element" << endl;
    display(ages_vector);
    ages_vector.erase( ages_vector.begin() + 2 );  // removes the third element in the vector
    cout << "Vector content AFTER erasing the third element" << endl;
    display(ages_vector);


    cout << "Re-populating vector:";
    populate_vector(ages_vector);
    display(ages_vector);

    // Iterate through the elements of a vector
    // Test each element and remove the element if it is even
    // Important: when an element is removed, the vector is restructured
    //            and the current iterator becomes invalid.  (Invalidated)
    // So, to continue iterating over the remaining elements we need a new
    // iterator.  Conveniently, the function erase() returns a new iterator that
    // points to the element directly after the one that was removed. So, we
    // use this iterator to continue in our for loop.
    //
    cout << "Iterating over vector to remove even elements" << endl;
    for (std::vector<int>::iterator iter = ages_vector.begin(); iter != ages_vector.end();)
    {
        if (*iter % 2 == 0)
            iter = ages_vector.erase(iter);
        else
            ++iter;
    }
    cout << "After removal of even elements vector contains : " ;
    display(ages_vector);

    cout << "Re-populating vector:";
    populate_vector(ages_vector);
    display(ages_vector);

    ////// Processing vectors using functions from the          //////
    ////// Algorithms Library <algorithm> and lambda functions  //////

    // Check that "all of" the student ages are greater than 16.
    // Every element in the range (begin -> end) is tested using the
    // lambda predicate "i>16".
    // all_of() returns true if all of the ages are > 16.
    //
    if ( all_of( ages_vector.cbegin(), ages_vector.cend(), [](int i){ return i > 16; } ) )
        cout << "all_of() : All values in ages_vector are greater than 16\n";
    else
        cout << "all_of() : One or more values are not greater than 16" << endl;

    // Use case : check to see if it is true that none of the students are under 17
    if ( none_of(ages_vector.cbegin(), ages_vector.cend(), [](int i){ return i < 17; }) )
        cout << "none_of() : None of the values in vector are less than 17\n";
    else
        cout << "none_of() : One or more values are less than 17" << endl;

    // The <algorithm> find() function searches for a value in the vector, and
    // returns an iterator.
    // If the element was not found, the iterator will be equal to the end() iterator
    // If found, the iterator will be pointing at the first matching element.
    //
    cout << "Using find() to find value 17 in the vector." << endl;
    auto result_iter1 = find( begin(ages_vector), end(ages_vector), 17 ); // call find() to find 17

    // did we find the element searched for ?
    // i.e. did the iterator run past the end of the vector or not ?
    if(  result_iter1 != end(ages_vector))
        cout << "Found at least one value 17\n";
    else
        cout << "NO value 17 in vector " << endl;

    // Searching for the first even number in a vector.
    // First define a lambda ( a function that will test each element to see if it is even)
    // (is_even is a pointer to a function - we will discuss later)
    auto is_even = [](int i){ return i%2 == 0; };   // define a lambda function and store in variable

    auto result_iter2 = find_if( begin(ages_vector), end(ages_vector), is_even ); // call find_if() to find elements that satisfy the is_even lambda

    (result_iter2 != end(ages_vector))? cout << " found one value that satisfied the is_even lambda expression \n" : cout << "NO even values found" << endl;

    // Vectors can be compared using relational operators:  ==, !=, <, >, <=, >=
    // https://cplusplus.com/reference/vector/vector/operators/
    // In C++ these operators (e.g. ==) are OVERLOADED so that they work
    // correctly for vectors.  They compare the contents of two arrays.

    vector<int> lottoDraw { 02,10,13,22,35,47 }; // initialization list
    vector<int> myNumbers { 02,10,13,22,35,47 };

    if( lottoDraw == myNumbers)
        cout << "Horray, I have won the lotto" << endl;
    else
    cout << "No luck today" << endl;

    cout << "Program finished - goodbye." << endl;
}

/**
 * Display the elements in a vector of integers.
 * @param vector_ref is a reference to a 'constant vector of int'
 * - a reference is an alias - another name for the vector 'ages_vector' in this case.
 */
void display(const vector<int>& vector_ref)
{
    for (int i=0; i<vector_ref.size(); i++)
    {
        if (i != 0) {
            cout << ",";
        }
        cout << vector_ref.at(i);
    }
    cout << endl;
}

void populate_vector( vector<int>& vect){
        vect.clear();  // clear vector of any previous values
        vect.push_back(18);
        vect.push_back(17);
        vect.push_back(21);
        vect.push_back(18);
        vect.push_back(21);
}