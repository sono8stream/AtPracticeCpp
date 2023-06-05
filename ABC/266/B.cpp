#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

namespace ABC {
	namespace _266 {
		using namespace std;

		class B {
		public:

			static void solve() {
				long long n;
				cin >> n;
				long long divisor = 998244353;
				if (n < 0) {
					long long mod = n % divisor;
					cout << (divisor + mod) % divisor;
				}
				else {
					cout << n % divisor;
				}
			}
		};
	}
}

int main() {
	ABC::_266::B::solve();
}