#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <array>
#include <vector>

namespace ABC {
	namespace _257 {
		using namespace std;



		class H {
		public:

			class Factor {
			public:
				long long numerator;
				long long denominator;
				long long cost;

				Factor() {
					numerator = 0;
					denominator = 0;
					cost = 0;
				}

				Factor(long long tmpExpected, long long tmpCost) {
					numerator = tmpExpected;
					cost = tmpCost;
				}
			};

			static void solve() {
				int n, k;
				cin >> n >> k;
				vector<int> cArray(n);
				vector<vector<int>> array(n, vector<int>(6));
				for (int i = 0; i < n; ++i) {
					cin >> cArray[i];
				}
				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < 6; ++j) {
						cin >> array[i][j];
					}
				}

				for (int i = 0; i < n; ++i) {
					
				}
			}
		};
	}
}

int main() {
	ABC::_257::H::solve();
}