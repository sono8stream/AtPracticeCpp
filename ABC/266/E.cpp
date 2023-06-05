#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

#define READ_INT(var) int var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;
#define long long long

namespace ABC {
	namespace _266 {
		using namespace std;

		class E {
		public:

			static const int diePat = 6;

			static double getExpectValue(const vector<double>& array) {
				double sum = 0;
				for (int i = 0; i < diePat; i++) {
					sum += array[i];
				}

				return sum;
			}

			static void solve() {
				READ_INT(n);

				vector<vector<double>> res(n, vector<double>(diePat, 0));
				for (int i = 0; i < diePat; i++) {
					res[n - 1][i] = (i + 1.0) / diePat;
				}
				for (int i = n - 2; i >= 0; i--) {
					double expectVal = getExpectValue(res[i + 1]);
					for (int j = 0; j < diePat; j++) {
						res[i][j] = max((j + 1.0) / diePat, expectVal / diePat);
					}
				}

				WRITE_LINE(getExpectValue(res[0]));
			}
		};
	}
}

int main() {
	ABC::_266::E::solve();
}