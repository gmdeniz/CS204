#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <time.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "gdeniz_Gozen_MiracDeniz_hw7_HW7DynIntQueue.h"

using namespace std;

int total_box_count, fill_counter = 0, pack_counter = 0;
HW7DynIntQueue FillingQueue, PackagingQueue;
mutex mutex_fill, mutex_pack, mutex_cout;

int random_range(const int& min, const int& max) {
	// Summary: Randomly picks a value between min and max (both inclusive)
	// Returns: the selected value
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void producer(int min_production, int max_production) {
	int queue_size;

	for (int i = 1; i <= total_box_count; i++) {
		
		this_thread::sleep_for(chrono::seconds(random_range(min_production, max_production))); // thread sleeps for an amount between min and max to simulate production process
		
		mutex_fill.lock();	// fill mutex is locked to allow only one worker to modify the queue
		FillingQueue.enqueue(i);
		queue_size = FillingQueue.getCurrentSize();
		mutex_fill.unlock();

		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // time at end of production (queueing)
		struct tm* ptm = new struct tm;
		localtime_s(ptm, &tt);

		mutex_cout.lock();	// cout mutex is locked to display production info
		cout << "Producer has enqueued a new box " << i << " to filling queue (filling queue size is " << queue_size << "): " << put_time(ptm, "%X") << endl;
		mutex_cout.unlock();

		delete ptm;
	}
}

void filler(int fillerNo, int min_filling_time, int max_filling_time) {
	int box;
	int queue_size;

	while (fill_counter < total_box_count) { // fillers work until global total reaches specified amount

		mutex_fill.lock();
		if (!FillingQueue.isEmpty()) {		 // filler works when queue is not empty

			FillingQueue.dequeue(box);		 // filler gets the box from filling queue
			queue_size = FillingQueue.getCurrentSize();
			fill_counter++;
			mutex_fill.unlock();

			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // time at the start of filling process
			struct tm* ptm = new struct tm;
			localtime_s(ptm, &tt);

			mutex_cout.lock();		// cout mutex locked to display fill-start info
			cout << "Filler " << fillerNo << " started filling the box " << box << " (filling queue size is " << queue_size << "): " << put_time(ptm, "%X") << endl;
			mutex_cout.unlock();

			this_thread::sleep_for(chrono::seconds(random_range(min_filling_time, max_filling_time))); // thread sleeps for an amount between min and max to simulate filling process
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now());					       // time at the end of filling process
			localtime_s(ptm, &tt);

			mutex_cout.lock();      // cout mutex locked to display fill-end info
			cout << "Filler " << fillerNo << " finished filling the box " << box << ": " << put_time(ptm, "%X") << endl;
			mutex_cout.unlock();

			mutex_pack.lock();		// pack mutex is locked to allow only one filler to modify the pack queue (enqueues)
			PackagingQueue.enqueue(box);
			queue_size = PackagingQueue.getCurrentSize();
			mutex_pack.unlock();

			tt = chrono::system_clock::to_time_t(chrono::system_clock::now());	// time at the adding of box to pack queue
			localtime_s(ptm, &tt);

			mutex_cout.lock();		// cout mutex locked to display pack-add info
			cout << "Filler " << fillerNo << " put box " << box << " into packaging queue (packaging queue size is " << queue_size << "): " << put_time(ptm, "%X") << endl;
			mutex_cout.unlock();

			delete ptm;
		}

		else {
			mutex_fill.unlock();
		}
	}
}

void packager(int packagerNo, int min_packaging_time, int max_packaging_time) {
	int packBox;
	int queue_size;

	while (pack_counter < total_box_count) {	// packagers work until global total reaches specified amount

		mutex_pack.lock();
		if (!PackagingQueue.isEmpty()) {		// packager works when queue is not empty

			PackagingQueue.dequeue(packBox);	// packager gets the box from packing queue
			queue_size = PackagingQueue.getCurrentSize();
			pack_counter++;
			mutex_pack.unlock();

			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());  // time at the start of packaging process
			struct tm* ptm = new struct tm;
			localtime_s(ptm, &tt);

			mutex_cout.lock();	// cout mutex locked to display packaging-start info
			cout << "Packager " << packagerNo << " started packaging the box " << packBox << " (packaging queue size is " << queue_size << "): " << put_time(ptm, "%X") << endl;
			mutex_cout.unlock();

			this_thread::sleep_for(chrono::seconds(random_range(min_packaging_time, max_packaging_time)));	// thread sleeps for an amount between min and max to simulate packaging process
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now());								// time at the end of packaging process
			localtime_s(ptm, &tt);
			
			mutex_cout.lock();	// cout mutex locked to display packaging-end info
			cout << "Packager " << packagerNo << " finished packaging the box " << packBox << ": " << put_time(ptm, "%X") << endl;
			mutex_cout.unlock();

			delete ptm;
		}
		else {
			mutex_pack.unlock();
		}
	}
}


int main() {

	int min_production, max_production, min_filling_time, max_filling_time, min_packaging_time, max_packaging_time;

	// getting required inputs for the production line simulation

	cout << "Please enter the total number of items: ";
	cin >> total_box_count;

	cout << "Please enter the min-max waiting time range of producer:" << endl;
	cout << "Min: ";
	cin >> min_production;
	cout << "Max: ";
	cin >> max_production;

	cout << "Please enter the min-max waiting time range of filler workers:" << endl;
	cout << "Min: ";
	cin >> min_filling_time;
	cout << "Max: ";
	cin >> max_filling_time;

	cout << "Please enter the min-max waiting time range of packager workers:" << endl;
	cout << "Min: ";
	cin >> min_packaging_time;
	cout << "Max: ";
	cin >> max_packaging_time;

	thread thr0(producer, min_production, max_production);					  // each thread represents each worker by working concurrently
	thread thr1(filler, 1, min_filling_time, max_filling_time);
	thread thr2(filler, 2, min_filling_time, max_filling_time);
	thread thr3(packager, 1, min_packaging_time, max_packaging_time);
	thread thr4(packager, 2, min_packaging_time, max_packaging_time);

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // time at the moment of simulation start
	struct tm* ptm = new struct tm;
	localtime_s(ptm, &tt);
	cout << "Simulation starts " << put_time(ptm, "%X") << endl;

	thr0.join();		// worker threads are bound to main thread
	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now());	// time at the moment of simulation end
	localtime_s(ptm, &tt);
	cout << "End of the simulation ends: " << put_time(ptm, "%X") << endl;

	delete ptm;
	return 0;
}