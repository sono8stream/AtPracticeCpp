#include <iostream>
#include <string>

namespace ABC {
	namespace _264 {
		using namespace std;

		class D {
		public:

			static void solve() {
				string str;
				cin >> str;

				string groundtruth = "atcoder";
				int length = groundtruth.size();
				int cost = 0;
				for (int i = 0; i < length; i++) {
					int pos = str.find(groundtruth[i]);
					while (pos > i) {
						char tmp = str[pos - 1];
						str[pos - 1] = str[pos];
						str[pos] = tmp;
						pos--;
						cost++;
					}
					if (pos > i) {
						cost += pos - i;
					}
				}

				cout << cost << endl;
			}
		};
	}
}

int main() {
	ABC::_264::D::solve();
}