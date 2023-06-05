#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

namespace ABC {
	namespace _266 {
		using namespace std;

		class A {
		public:

			static void solve() {
				string s;
				cin >> s;
				cout << s[s.size() / 2];
			}
		};
	}
}

int main() {
	ABC::_266::A::solve();
}