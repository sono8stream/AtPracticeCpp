#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

namespace ABC {
	namespace _266 {
		using namespace std;

		class C {
		public:

			static int getPrev(int i) {
				return (4 + i - 1) % 4;
			}

			static int getNext(int i) {
				return (i + 1) % 4;
			}

			static void solve() {
				int xs[4];
				int ys[4];
				for (int i = 0; i < 4; i++) {
					cin >> xs[i] >> ys[i];
				}

				bool ok = true;
				for (int i = 0; i < 4; i++) {
					int prevX = xs[getPrev(i)];
					int prevY = ys[getPrev(i)];
					int nextX = xs[getNext(i)];
					int nextY = ys[getNext(i)];

					int v1X = prevX - xs[i];
					int v1Y = prevY - ys[i];
					int v2X = nextX - xs[i];
					int v2Y = nextY - ys[i];

					if (v2X * v1Y - v2Y * v1X<0) {
						ok = false;
						break;
					}
				}

				if (ok) {
					cout << "Yes" << endl;
				}
				else {
					cout << "No" << endl;
				}
			}
		};
	}
}

int main() {
	ABC::_266::C::solve();
}