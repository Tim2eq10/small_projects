//============================================================================
// Source : RomalNums.cpp
// Author : Timur Poletaev
// Created : 06.11.2022
// Description : 
//		The Romans didn't understand negative numbers
//		And notations for big number are hard to use in console
//		I converts numbers in segment [1...10000)
//		And converts 5000 -> MMMMM
//============================================================================
#include <iostream> 
#include <string>
#include <map>
#include <vector>
//============================================================================
namespace Numerals {

using Romal = std::string;
using Arabian = int;

const inline std::vector<char> Romal_symb {
	'M',
	'D',
	'C',
	'L',
	'X',
	'V',
	'I'
};
const inline std::map<char, int> Romal_symbcost {
	{'M',1000},
	{'D',500},
	{'C',100},
	{'L',50},
	{'X',10},
	{'V',5},
	{'I',1}
};
Romal toRomal(Arabian _Num) {
	if (_Num > 9999) throw std::invalid_argument("Too large num");
	if (_Num < 1) throw std::invalid_argument("Too less num");

	Romal res;

	if (_Num > 999) {
		for (int i = 0; i < _Num / 1000; i++)
			res += 'M';
		_Num %= 1000;
	}

	for (int i = 0; i < 7; i += 2) {
		int base = (int)pow(10, 3 - i / 2);
		if (_Num > base - 1) {
			if (_Num / base <= 3)
			{
				for (int j = 0; j < _Num / base; j++)
					res += Romal_symb[i];
			}
			else if (4 <= _Num / base && _Num / base <= 8)
			{
				for (int j = 0; j < 5 - _Num / base; j++)
					res += Romal_symb[i];
				res += Romal_symb[i - 1];
				for (int j = 0; j < _Num / base - 5; j++)
					res += Romal_symb[i];
			}
			else
			{
				res += Romal_symb[i];
				res += Romal_symb[i - 2];
			}
			_Num %= base;
		}
	}

	return res;
}
Arabian toArabian(Romal _Num) {
	int res = 0;
	Romal::iterator begin = _Num.begin();
	Romal::iterator end = _Num.end();
	Romal::iterator pos;
	while (begin != end) {
		for (int i = 0; i < 7; i++) {
			auto found_it = std::find(begin, end, Romal_symb[i]);
			if (found_it != end) {
				pos = found_it;
				break;
			}
		}
			
		for (; begin != pos; begin++)
			res -= Romal_symbcost.at(*begin);
		for (; *begin == *pos && begin != end; begin++)
			res += Romal_symbcost.at(*begin);
	}
	return res;
}

} // namespace Numerals
//============================================================================
void sample_two_hundreds_romals() {
	using std::cout; using std::endl;
	for (int arabic_num = 1; arabic_num <= 200; arabic_num++) {
		cout << arabic_num << ':' << Numerals::toRomal(arabic_num) << endl;
	}
}

int main() {
	sample_two_hundreds_romals();
}
//============================================================================
