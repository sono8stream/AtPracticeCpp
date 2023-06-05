#include <iostream>

namespace ABC {
	namespace _264 {
		using namespace std;

		class B {
		public:

			static int getDistanceFromCenter(int r, int c) {
				int center = 8;
				int xDist = abs(r - center);
				int yDist = abs(c - center);

				return max(xDist, yDist);
			}

			static bool isWhite(int distance) {
				return 0 == distance % 2;
			}

			static void solve() {
				int r, c;
				cin >> r >> c;
				int distance = getDistanceFromCenter(r, c);
				if (isWhite(distance)) {
					cout << "white" << endl;
				}
				else {
					cout << "black" << endl;
				}
			}
		};
	}
}

int main() {
	ABC::_264::B::solve();
}