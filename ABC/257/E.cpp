#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

namespace ABC {
	namespace _257 {
		using namespace std;

		class E {
		public:

			static void solve() {
				int n;
				cin >> n;

				const int costLength = 9;
				int* cArray = new int[costLength];
				int minimumId = -1;
				int minimumCost = 1e9;
				for (int i = 0; i < costLength; ++i) {
					cin >> cArray[i];
					if (minimumCost >= cArray[i]) {
						minimumCost = cArray[i];
						minimumId = i;
					}
				}

				int digits = n / minimumCost;
				int margin = n % minimumCost;

				int count = 0;
				for (int i = 0; i < digits; ++i) {
					for (int i = costLength - 1; i >= 0; --i) {
						if (cArray[i] - minimumCost <= margin) {
							cout << i + 1;
							margin -= (cArray[i] - minimumCost);
							break;
						}
					}
				}
				cout << endl;
			}
		};
	}
}

int main() {
	ABC::_257::E::solve();
}