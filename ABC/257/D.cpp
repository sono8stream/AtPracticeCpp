#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

namespace ABC {
	namespace _257 {
		using namespace std;

		class D {
		public:

			class JumpBoard {
			public:
				long long x;
				long long y;
				long long p;

				JumpBoard() {
					x = 0;
					y = 0;
					p = 0;
				}

				JumpBoard(long long tmpX, long long tmpY, long long tmpP) {
					x = tmpX;
					y = tmpY;
					p = tmpP;
				}

				long long calcCostTo(const JumpBoard other) const {
					return abs(other.x - x) + abs(other.y - y);
				}
			};

			static void solve() {
				int n;
				cin >> n;
				JumpBoard* boardArray = new JumpBoard[n];

				for (int i = 0; i < n; ++i) {
					long long x, y, p;
					cin >> x >> y >> p;
					boardArray[i] = JumpBoard(x, y, p);
				}

				long long bottom = 0;
				long long top = 5e9;
				bool* visitedArray = new bool[n];

				while (bottom + 1 < top) {
					long long mid = (bottom + top) / 2;
					bool isOk = false;

					for (int i = 0; i < n; ++i) {
						queue<int> poses;
						poses.emplace(i);

						memset(visitedArray, false, sizeof(bool) * n);
						visitedArray[i] = true;

						int visitedCount = 1;
						while (poses.size() > 0) {
							int now = poses.front();
							poses.pop();

							for (int j = 0; j < n; ++j) {
								if (visitedArray[j]) {
									continue;
								}

								long long cost = boardArray[now].calcCostTo(boardArray[j]);
								if (boardArray[now].p * mid >= cost) {
									visitedCount++;
									poses.emplace(j);
									visitedArray[j] = true;
								}
							}
						}

						if (visitedCount == n) {
							isOk = true;
							break;
						}
					}

					if (isOk) {
						top = mid;
					}
					else {
						bottom = mid;
					}
				}

				cout << top << endl;
				delete[] boardArray;
				delete[] visitedArray;
			}
		};
	}
}

int main() {
	ABC::_257::D::solve();
}