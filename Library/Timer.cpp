#include <iostream>
#include <string>
#include <vector>
#include <time.h>

namespace ABC {
	namespace Library {
		using namespace std;

		/*
		* �^�C�}�j�����Ɏ������o�͂���
		*/
		class Timer {
		private:
			clock_t _now;
			string _name;

			Timer(string name) :_now(clock()), _name(name) {
			}

			~Timer() {
				clock_t current = clock();
#ifdef _DEBUG
				cout << _name << " = +" << (double)(current - _now) << "msec.\n" << endl;
#endif
			}
		};
	}
}