#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <cmath>

#define long long long

#define READ_INT(var) int var;std::cin>>var;
#define READ_LONG(var) long var;std::cin>>var;
#define READ_DOUBLE(var) double var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;

namespace ABC {
	namespace _292 {
		const double PI = acos(-1);
		using namespace std;
		// •ûj
		// 3•ª’Tõ

		class F {
		public:

			static double validate(double shorter, double longer, double theta) {
				double edge1 = shorter / cos(theta);
				double edge2 = longer / cos(PI / 6 - theta);
				double edge = min(edge1, edge2);

				return edge;
			}

			static void solve() {
				READ_INT(a);
				READ_INT(b);

				double longer = max(a, b);
				double shorter = min(a, b);

				double bottom = 0;
				double top = PI / 6;

				double thres = 1e-10;
				while (bottom + thres < top) {
					double midLeft = (bottom * 2 + top) / 3;
					double midRight = (bottom + top * 2) / 3;

					double left = validate(shorter, longer, bottom);
					double leftCenter = validate(shorter, longer, midLeft);
					double rightCenter = validate(shorter, longer, midRight);
					double right = validate(shorter, longer, top);

					if (leftCenter <= rightCenter) {
						bottom = midLeft;
					}
					else {
						top = midRight;
					}
				}

				cout << setprecision(14) << validate(shorter, longer, bottom) << endl;
			}
		};
	}
}

int main() {
	ABC::_292::F::solve();
}