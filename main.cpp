// MinGW-4.8.1
// GCC version: 4.6.3
// options -O3 -std=c++11

// timings at the end of the file

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

template<typename RandomAccessIterator, typename Order>
 void mergesort(RandomAccessIterator first, RandomAccessIterator last, Order order)
{
  if (last - first > 1)
  {
    RandomAccessIterator middle = first + (last - first) / 2;
    mergesort(first, middle, order);
    mergesort(middle, last, order);
    std::inplace_merge(first, middle, last, order);
  }
}
 
template<typename RandomAccessIterator>
 void mergesort(RandomAccessIterator first, RandomAccessIterator last)
{
  mergesort(first, last, std::less<typename std::iterator_traits<RandomAccessIterator>::value_type>());
}

vector<int> funqsort(vector<int> v)
{
  if (v.size() > 1)
  {
    int pivot = v[0];
	vector<int> lesser;
	vector<int> greater;
	std::copy_if(v.begin()+1, v.end(), std::back_inserter(lesser), std::bind2nd(std::less<int>(), pivot));
	std::copy_if(v.begin()+1, v.end(), std::back_inserter(greater), std::not1(std::bind2nd(std::less<int>(), pivot)));
	vector<int> result;
	vector<int> fql = funqsort(lesser);
	vector<int> fqg = funqsort(greater);
	std::copy(fql.begin(), fql.end(), std::back_inserter(result));
	result.push_back(pivot);
	std::copy(fqg.begin(), fqg.end(), std::back_inserter(result));
	return result;
  } else {
	  return v;
  }
}
 
int main(int argc, char **argv)
{
	vector<int> data20k = vector<int>(20000);
	for (int i = 0; i < 20000; ++i) {
		data20k[i] = rand();
	}
	vector<int> data200k = vector<int>(200000);
	for (int i = 0; i < 200000; ++i) {
		data200k[i] = rand();
	}	
	vector<int> data500k = vector<int>(500000);
	for (int i = 0; i < 500000; ++i) {
		data500k[i] = rand();
	}
	vector<int> data1m = vector<int>(1000000);
	for (int i = 0; i < 1000000; ++i) {
		data1m[i] = rand();
	}	
	vector<int> data2m = vector<int>(2000000);
	for (int i = 0; i < 2000000; ++i) {
		data2m[i] = rand();
	}
	
	long grand_total = 0;

	double total_time = 0.0;
	for (int j = 0; j < 50; ++j) {
		vector<int> data(data20k);
		auto start = std::chrono::high_resolution_clock::now();
		sort(data.begin(), data.end());
		grand_total += data[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Standard built-in sort" << "- data size: 20k iterations: 50 time: " <<  total_time / (1000.0 * 50.0) << "ms" << endl;

	total_time = 0.0;
	for (int j = 0; j < 20; ++j) {
		vector<int> data(data500k);
		auto start = std::chrono::high_resolution_clock::now();
		sort(data.begin(), data.end());
		grand_total += data[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Standard built-in sort" << "- data size: 500k iterations: 20 time: " <<  total_time / (1000.0 * 20.0) << "ms" << endl;

	total_time = 0.0;
	for (int j = 0; j < 20; ++j) {
		vector<int> data(data1m);
		auto start = std::chrono::high_resolution_clock::now();
		sort(data.begin(), data.end());
		grand_total += data[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Standard built-in sort" << "- data size: 1m iterations: 20 time: " <<  total_time / (1000.0 * 20.0) << "ms" << endl;
	
	total_time = 0.0;
	for (int j = 0; j < 10; ++j) {
		vector<int> data(data2m);
		auto start = std::chrono::high_resolution_clock::now();
		sort(data.begin(), data.end());
		grand_total += data[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Standard built-in sort" << "- data size: 2m iterations: 10 time: " <<  total_time / (1000.0 * 10.0) << "ms" << endl;
	
	total_time = 0.0;
	for (int j = 0; j < 50; ++j) {
		vector<int> data(data20k);
		auto start = std::chrono::high_resolution_clock::now();
		mergesort(data.begin(), data.end());
		grand_total += data[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Merge sort" << "- data size: 20k iterations: 50 time: " <<  total_time / (1000.0 * 50.0) << "ms" << endl;

	total_time = 0.0;
	for (int j = 0; j < 20; ++j) {
		vector<int> data(data500k);
		auto start = std::chrono::high_resolution_clock::now();
		mergesort(data.begin(), data.end());
		grand_total += data[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Merge sort" << "- data size: 500k iterations: 20 time: " <<  total_time / (1000.0 * 20.0) << "ms" << endl;

	total_time = 0.0;
	for (int j = 0; j < 20; ++j) {
		vector<int> data(data1m);
		auto start = std::chrono::high_resolution_clock::now();
		mergesort(data.begin(), data.end());
		grand_total += data[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Merge sort" << "- data size: 1m iterations: 20 time: " <<  total_time / (1000.0 * 20.0) << "ms" << endl;
	
	total_time = 0.0;
	for (int j = 0; j < 10; ++j) {
		vector<int> data(data2m);
		auto start = std::chrono::high_resolution_clock::now();
		mergesort(data.begin(), data.end());
		grand_total += data[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Merge sort" << "- data size: 2m iterations: 10 time: " <<  total_time / (1000.0 * 10.0) << "ms" << endl;
	
	total_time = 0.0;
	for (int j = 0; j < 50; ++j) {
		vector<int> data(data20k);
		auto start = std::chrono::high_resolution_clock::now();
		vector<int> res = funqsort(data);
		grand_total += res[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Functional Quick sort" << "- data size: 20k iterations: 50 time: " <<  total_time / (1000.0 * 50.0) << "ms" << endl;

	total_time = 0.0;
	for (int j = 0; j < 20; ++j) {
		vector<int> data(data500k);
		auto start = std::chrono::high_resolution_clock::now();
		vector<int> res = funqsort(data);
		grand_total += res[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Functional Quick sort" << "- data size: 500k iterations: 20 time: " <<  total_time / (1000.0 * 20.0) << "ms" << endl;

	total_time = 0.0;
	for (int j = 0; j < 20; ++j) {
		vector<int> data(data1m);
		auto start = std::chrono::high_resolution_clock::now();
		vector<int> res = funqsort(data);
		grand_total += res[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Functional Quick sort" << "- data size: 1m iterations: 20 time: " <<  total_time / (1000.0 * 20.0) << "ms" << endl;
	
	total_time = 0.0;
	for (int j = 0; j < 10; ++j) {
		vector<int> data(data2m);
		auto start = std::chrono::high_resolution_clock::now();
		vector<int> res = funqsort(data);
		grand_total += res[0];
		auto finish = std::chrono::high_resolution_clock::now();
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		total_time += microseconds.count();
	}

	std::cout << "Functional Quick sort" << "- data size: 2m iterations: 10 time: " <<  total_time / (1000.0 * 10.0) << "ms" << endl;
	
	std::cout << "The grand total is :) " << grand_total << endl;
	
	return 0;
}

// timings
/********************************************************************
Standard built-in sort- data size: 20k iterations: 50 time: 1.02006ms  
Standard built-in sort- data size: 500k iterations: 20 time: 29.1017ms 
Standard built-in sort- data size: 1m iterations: 20 time: 58.4534ms   
Standard built-in sort- data size: 2m iterations: 10 time: 117.107ms   
Merge sort- data size: 20k iterations: 50 time: 6.8604ms               
Merge sort- data size: 500k iterations: 20 time: 173.36ms              
Merge sort- data size: 1m iterations: 20 time: 355.57ms                
Merge sort- data size: 2m iterations: 10 time: 748.843ms               
Functional Quick sort- data size: 20k iterations: 50 time: 44.5025ms   
Functional Quick sort- data size: 500k iterations: 20 time: 1626.74ms  
Functional Quick sort- data size: 1m iterations: 20 time: 3751.86ms    
Functional Quick sort- data size: 2m iterations: 10 time: 8881.91ms    
The grand total is :) 150                                              
********************************************************************/