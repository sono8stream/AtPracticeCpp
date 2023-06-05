#include <iostream>
#include <vector>
#include <bitset>

namespace ABC {
	namespace _264 {
		using namespace std;

		class C {
		public:

			static void readArray(vector<vector<int>>& vec, int h, int w) {
				vec = vector<vector<int>>(h, vector<int>(w));
				for (int i = 0; i < h; i++) {
					for (int j = 0; j < w; j++) {
						cin >> vec[i][j];
					}
				}
			}

			static bool checkCan(int hBit, int wBit,
				const vector<vector<int>>& aArray, const vector<vector<int>>& bArray) {
				bitset<10> hBitSet(hBit);
				bitset<10> wBitSet(wBit);

				const int hTo = bArray.size();
				const int wTo = bArray[0].size();
				if (!(hBitSet.count() == hTo && wBitSet.count() == wTo)) {
					return false;
				}

				vector<vector<int>> aTmp;
				const int hFrom = aArray.size();
				const int wFrom = aArray[0].size();
				for (int i = 0; i < hFrom; i++) {
					if (hBitSet[i]) {
						aTmp.emplace_back(vector<int>());
						int hNow = aTmp.size() - 1;
						for (int j = 0; j < wFrom; j++) {
							if (wBitSet[j]) {
								aTmp[hNow].emplace_back(aArray[i][j]);
							}
						}
					}
				}

				for (int i = 0; i < hTo; i++) {
					for (int j = 0; j < wTo; j++) {
						if (bArray[i][j] != aTmp[i][j]) {
							return false;
						}
					}
				}

				return true;
			}

			static void solve() {
				int h1, w1;
				cin >> h1 >> w1;
				vector<vector<int>> aArray;
				readArray(aArray, h1, w1);

				int h2, w2;
				cin >> h2 >> w2;
				vector<vector<int>> bArray;
				readArray(bArray, h2, w2);

				int hPat = (1 << h1);
				int wPat = (1 << w1);
				for (int i = 0; i < hPat; i++) {
					for (int j = 0; j < wPat; j++) {
						if (checkCan(i, j, aArray, bArray)) {
							cout << "Yes" << endl;
							return;
						}
					}
				}

				cout << "No" << endl;
			}
		};
	}
}

int main() {
	ABC::_264::C::solve();
}
