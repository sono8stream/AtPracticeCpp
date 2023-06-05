

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

namespace ABC {
	namespace _257 {
		using namespace std;

		bool isLast(int length, int id) {
			return id == length - 1;
		}

		class B {
		public:

			static void solve() {
				int n, k, q;
				cin >> n >> k >> q;

				int* aArray = new int[k];
				for (int i = 0; i < k; ++i) {
					cin >> aArray[i];
				}

				int* lArray = new int[q];
				for (int i = 0; i < q; ++i) {
					cin >> lArray[i];
				}

				for (int i = 0; i < q; ++i) {
					int id = lArray[i] - 1;
					if (isLast(k, id)) {
						if (aArray[id] + 1 <= n) {
							aArray[id]++;
						}
						else {
							continue;
						}
					}
					else {
						if (aArray[id] + 1 < aArray[id + 1]) {
							aArray[id]++;
						}
						else {
							continue;
						}
					}
				}

				for (int i = 0; i < k; ++i) {
					cout << aArray[i] << " ";
				}

				delete[] aArray;
				delete[] lArray;
			}
		};
	}
}

int main() {
	ABC::_257::B::solve();
}