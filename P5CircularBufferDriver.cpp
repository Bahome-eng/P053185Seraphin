
// P05CircularBufferDriver.cpp -- starter code

/*  REQUIREMENTS NOTES:

    Fill in the remainder of this driver program.
    Replicate exactly the sample run provided with project's specs.
    Use a capacity of 5

*/
//CS318P05
//Bahome Seraphin

#include <iostream> 
#include <algorithm> 
#include <iterator> 
#include <vector> 
#include "circular_buffer.h" 
#include "Dog.h" 

using namespace std;

int main() {

    cout << "\n*************** <int> Circular Buffer Demo ******************\n";

    //  FINISH THIS SECTION 

    CircularBuffer<int, 5>buffer;

    cout << "\nInitial State" << endl;

    cout << buffer;

    for (int i = 0; i < 8; i++) {

        cout << "\nPushing " << i * 10 << endl;

        buffer.push_back(i * 10);

        cout << buffer;
    }

    for (int i = 3; i < 8; i++) {

        cout << "\nPopping " << i * 10 << endl;

        buffer.pop();

        cout << buffer;

    }

    cout << "\n\n*************** <string> Circular Buffer Demo ******************\n";

    //  FINISH THIS SECTION -- 

    // create a vector of words 

    // use back_insert_iterator to fill the buffer 

    vector<string> words = { "welcome","to","the","wonderful","world", "of","oz" };

    CircularBuffer<string, 5>bufferString;

    cout << "\nInitial State\n";

    cout << bufferString;

    copy(words.begin(), words.end(), back_insert_iterator<CircularBuffer<string, 5>>(bufferString));

    cout << "\nAfter using back_inserter_iterator" << endl;

    cout << bufferString;

    for (int i = 0; i < 5; i++) {

        cout << "\npopping: " << bufferString.head() << endl;

        bufferString.pop();

        cout << bufferString;

    }
    cout << "\n\n*************** <Dog> Circular Buffer Demo ******************\n";

    CircularBuffer<dog, 5> dogBuffer;

    dogBuffer.push_back(dog("Guinness", "Wheaten", 9));

    dogBuffer.push_back(dog("Grimlock", "Lab", 2));

    dogBuffer.push_back(dog("Optimus", "Bulldog", 5));

    dogBuffer.push_back(dog("Murphy", "Lab", 14));

    dogBuffer.push_back(dog("Floyd", "Beagle", 12));

    copy(dogBuffer.begin(), dogBuffer.end(), back_insert_iterator<CircularBuffer<dog, 5>>(dogBuffer));

    cout << endl << dogBuffer;

    cout << "\ndogs Full?: " << (dogBuffer.full() ? "true" : "false") << endl;

    dogBuffer.push_back(dog("Snoopy", "Beagle", 100));

    cout << endl << dogBuffer;

    dogBuffer.push_back(dog("Archie", "Brittany", 1));

    cout << endl << dogBuffer;

    dogBuffer.push_back(dog("Penny", "Beagle", 2));

    cout << endl << dogBuffer;

    for (int i = 0; i < 5; i++) {

        cout << "\nPopping:    " << dogBuffer.head();

        dogBuffer.pop();

        cout << endl << endl << dogBuffer;
    }
    //  FINISH THIS SECTION 
    cout << endl;
}







// Dog.h -- slight modification to ostream operator overload 
//CS318P05
//Bahome Seraphin

#ifndef DOG_H 
#define DOG_H 
#include <iostream> 
using namespace std;

class dog {

private:
    string name;
    string breed;
    int age;

public:

    // this is used to initialize the variables of the class 
    dog(string name = "", string breed = "", int age = 0)
        : name(name), breed(breed), age(age) {}

    string getName() const { return name; }

    string getBreed() const { return breed; }

    int getAge() const { return age; }

    void setBreed(string breed) { this->breed = breed; }

    void setAge(int age) { this->age = age; }

};

// NOTE -- THIS SHOULD BE MODIFIED SLIGHTLY 

ostream& operator<<(ostream& out, const dog& d) {

    out << "\n " << d.getName() << ", " << d.getBreed() << ", " << d.getAge();

    return out;
}
#endif 




//CS318P05
//Bahome Seraphin
#ifndef _CIRCULAR_BUFFER_H 
#define _CIRCULAR_BUFFER_H 

#include <array> 
#include <iterator> 
#include <algorithm> 
#include <iostream> 
#include <cmath> 
#include <stdexcept> 

using namespace std;

template<typename T, int cap, typename Container = std::array<T, cap> >

class CircularBuffer {

public:

    //type T will be the data type in the Container declared in the template 

    using value_type = T;

    //COMPLETE CONSTRUCTOR BELOW 

    CircularBuffer() {

        _current = 0;

        _head = 0;

        _tail = 0;

        _size = 0;

        _capacity = cap;

    };

    //COMPLETE THE FUNCTIONS BELOW USING THE FUNCTION PROTOTYPE GIVEN 

    T& head() { return c.at(_head); }

    T& tail() { return c.at(_tail); };

    T const& head() const { return c.at(_head); };

    T const& tail() const { return c.at(_head); };


    //COMPLETE THE push_back function -- circular buffer will overwrite 

    //		oldest data if buffer is full.  This function must update 

    //		appropriate instance variables 

    void push_back(T val) noexcept {

        c.at(_current) = val;

        if (_size == _capacity) {

            _head = (_head + 1) % _capacity;
        }

        _tail = _current;

        _current = (_current + 1) % _capacity;

        if (_size < _capacity) {

            _size++;

        }
    }

    void pop() {

        if (_size <= 0) {

            throw std::underflow_error("pop(): empty buffer");
        }

        // COMPLETE THE REMAINDER OF THIS FUNCTION 

        _head = (_head + 1) % _capacity;

        _size--;
    }

    // COMPLETE THE FUNCTIONS BELOW 

    int size() const noexcept { return _size; }

    int capacity() noexcept { return _capacity; }

    bool empty() const noexcept { return _size == 0; } //returns true if buffer is empty 

    bool full() const noexcept { return _size == _capacity; }  //returns true if buffer is full 

    typename Container::iterator begin() { return c.begin(); }

    typename Container::iterator end() { return c.end(); }


    // COMPLETE THE OVERLOADED << OPERATOR 

    friend std::ostream& operator<<(std::ostream& os, CircularBuffer& buf) {

        os << "Buffer Info: head: " << buf._head << ", tail: " << buf._tail << ", current: " << buf._current

            << ",capacity: " << buf._capacity << ",size: " << buf._size

            << "\nContainer: ";


        for (const auto& value : buf.c) {

            os << " " << value;
        }

        os << endl;

        return os;
    }

private:

    Container c; // will be std::array<T, cap> 

    int _head; //oldest item in buffer 

    int _tail; //newest item in buffer 

    int _size; //# of elem in buffer 

    int _current; //next write position in buffer 

    int _capacity;
};

#endif 