#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>
#include <iomanip>

#define READ_INT(var) int var;std::cin>>var;
#define READ_DOUBLE(var) double var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;
#define long long long

namespace ABC {
	namespace _274 {
		using namespace std;
		// •ûj

		class A {
		public:

			static void solve() {
				READ_INT(a);
				READ_DOUBLE(b);

				cout << fixed << setprecision(3) << b / a << endl;
			}
		};
	}
}

int main() {
	ABC::_274::A::solve();
}