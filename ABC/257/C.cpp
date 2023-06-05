

#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

namespace ABC {
	namespace _257 {
		using namespace std;

		class C {
		public:

			static void solve() {
				int n;
				cin >> n;

				string s;
				cin >> s;
				bool* isAdultArray = new bool[n];
				for (int i = 0; i < n; ++i) {
					isAdultArray[i] = s[i] == '1';
				}

				int* wArray = new int[n];
				for (int i = 0; i < n; ++i) {
					cin >> wArray[i];
				}

				vector<int> children;
				vector<int> adults;

				for (int i = 0; i < n; ++i) {
					if (isAdultArray[i]) {
						adults.emplace_back(wArray[i]);
					}
					else {
						children.emplace_back(wArray[i]);
					}
				}

				sort(adults.begin(), adults.end());
				sort(children.begin(), children.end());
				sort(wArray, wArray + n);

				int childCount = 0;
				int adultCount = 0;
				int res = 0;

				for (int i = 0; i < n; ++i) {
					while (childCount < children.size() && children[childCount] < wArray[i]) {
						++childCount;
					}
					while (adultCount < adults.size() && adults[adultCount] < wArray[i]) {
						++adultCount;
					}

					res = max(res, childCount + (int)(adults.size() - adultCount));
				}

				{
					while (childCount < children.size() && children[childCount] < wArray[n - 1] + 1) {
						++childCount;
					}
					while (adultCount < adults.size() && adults[adultCount] < wArray[n - 1] + 1) {
						++adultCount;
					}

					res = max(res, childCount + (int)(adults.size() - adultCount));
				}

				cout << res << endl;

				delete[] wArray;
			}
		};
	}
}

int main() {
	ABC::_257::C::solve();
}