/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013
 *
 * Same as counter.cpp, but using a mutex lock to
 * access the counter.
 *
 */

#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
using namespace std;

const unsigned int NTHREADS = 20;
const int ITERS = 10000000;

mutex counter_mutex;

int counter;

void increment()
{
	lock_guard<mutex> lock(counter_mutex);
	for(int i=0; i<ITERS; i++)
		counter++;
	// mutex is released by lock_guard destructor
	// at the end of function scope
}

void decrement()
{
	lock_guard<mutex> lock(counter_mutex);
	for(int i=0; i<ITERS; i++)
		counter--;
	// mutex is released by lock_guard destructor
	// at the end of function scope
}

int main(int argc, char* argv[])
{
	cout << "The counter is " << counter << endl;

	thread *threads = new thread[NTHREADS];

	for(unsigned int i=0; i<NTHREADS; i++)
		if(i%2==0)
			threads[i] = thread(increment);
		else
			threads[i] = thread(decrement);

	for(unsigned int i=0; i<NTHREADS; i++)
		threads[i].join();

	cout << "The counter is " << counter << endl;

	return 0;
}
