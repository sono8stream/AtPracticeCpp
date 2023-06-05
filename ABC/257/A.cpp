#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

namespace ABC {
	namespace _257 {
		using namespace std;

		class A {
		public:

			static void solve() {
				int n, x;
				cin >> n >> x;

				cout << (char)('A' + ((x - 1) / n)) << endl;
			}
		};
	}
}

int main() {
	ABC::_257::A::solve();
}