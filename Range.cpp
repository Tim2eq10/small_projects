//============================================================================
// Source : Range.cpp
// Author : Poletaev Timur
// Description : 
//		Ok, I wanna write range function (like Python range)
//		To use it like this:
//			for(int x : range(n))		// x = {0,1,2,...,n-2,n-1}
//			for(int x : range(1,n))		// x = {1,...,n-1}
//			for(int x : range(1,n,2))	// x = {1,3,5,7,...}
//		Or like this:
//			for(double x : range<double>(0.0,nf,0.5))
//
//		function will return _Range object
//============================================================================
#include <iostream>
#include <vector>

//============================================================================
namespace MySTL {

template <class T = int>
class _Range {
public:
	explicit _Range() {

	}
	explicit _Range(T fin) {
		for (T el = T(); el < fin; el += 1) 
			v.push_back(el);
	}
	explicit _Range(T start, T fin) {
		for (T el = start; el < fin; el += 1) 
			v.push_back(el);
	}
	explicit _Range(T start, T fin, T step) {
		for (T el = start; el < fin; el += step)
			v.push_back(el);
	}
	auto begin() {
		return std::begin(v);
	}
	auto end() {
		return std::end(v);
	}
private:
	std::vector<T> v;
};

template <class T = int>
auto range(T fin) {
	return _Range(fin);
}
template <class T = int>
auto range(T start, T fin) {
	return _Range(start, fin);
}
template <class T = int>
auto range(T start, T fin, T step) {
	return _Range(start, fin, step);
}

}
//============================================================================
using MySTL::range;
using std::cout; using std::endl;

void int_sample() {
	cout << "Int sample" << endl << endl;

	int n = 10;
	int step = 2;
	for (auto x : range(n)) {
		cout << x << ' ';
	}
	cout << endl;
	for (auto x : range(n / 2, n)) {
		cout << x << ' ';
	}
	cout << endl;
	for (auto x : range(0, n, step)) {
		cout << x << ' ';
	}
	cout << endl << endl;
}

void double_sample() {
	cout << "Double sample" << endl << endl;

	double n = 5;
	double step = 0.2;
	for (auto x : range(n)) {
		cout << x << ' ';
	}
	cout << endl;
	for (auto x : range(n / 2, n)) {
		cout << x << ' ';
	}
	cout << endl;
	for (auto x : range(0.0, n, step)) {
		cout << x << ' ';
	}
	cout << endl << endl;
}
//============================================================================
int main()
{
	int_sample();

	double_sample();
}
//============================================================================