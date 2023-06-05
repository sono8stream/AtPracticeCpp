#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

namespace ABC {
	namespace _264 {
		using namespace std;

		class A {
		public:

			static void solve() {
				int l, r;
				cin >> l >> r;
				int top = l - 1;
				int length = r - l + 1;
				string str("atcoder");
				cout << str.substr(top, length) << endl;
			}
		};
	}
}

int main() {
	ABC::_264::A::solve();
}