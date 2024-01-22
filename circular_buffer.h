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

	T& head() { return c.at(_head);}

	T& tail() { return c.at(_tail);};

	T const& head() const { return c.at(_head);};

	T const& tail() const { return c.at(_head);};


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