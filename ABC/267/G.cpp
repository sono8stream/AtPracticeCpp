#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>

#define READ_INT(var) int var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;
#define long long long

namespace ABC {
	namespace _267 {
		using namespace std;
		// •ûj
		// ‘å‚«‚¢‡‚É•À‚×AŒÂ”‚ÅDP

        class CaseCalculator
        {

        private:
            long mask;
            vector<long> allPermutations;
            vector<long> allInverses;

        public:

            long multi(long left, long right)
            {
                long val = left % mask;
                val *= right % mask;
                val %= mask;
                return val;
            }

            void getAllPermutations(long n, vector<long>& vec)
            {
                vec = vector<long>(n + 1, 1);
                for (int i = 1; i <= n; i++)
                {
                    vec[i] = multi(vec[i - 1], i);
                }
            }

            void getAllInverses(long n, vector<long>& vec)
            {
                vector<long> inverses(n + 1, 0);
                inverses[1] = 1;
                vec = vector<long>(n + 1, 1);
                for (int i = 2; i <= n; i++)
                {
                    inverses[i] = mask - inverses[mask % i] * (mask / i) % mask;
                    vec[i] = multi(vec[i - 1], inverses[i]);
                }
            }

            CaseCalculator(long mask, long permutationCnt)
                :mask(mask)
            {
                getAllPermutations(permutationCnt, allPermutations);
                getAllInverses(permutationCnt, allInverses);
            }

            long getCombination(long n, long m)
            {
                if (n < m) {
                    return 0;
                }

                if (n - m < m) {
                    m = n - m;
                }
                return multi(multi(allPermutations[n], allInverses[n - m]), allInverses[m]);
            }

            long getPermutation(long n, long m)
            {
                if (n < m) {
                    return 0;
                }

                return multi(allPermutations[n], allInverses[n - m]);
            }
        };

		class G {
		public:

			static void solve() {
				READ_INT(n);
				READ_INT(k);
				READ_INT_ARRAY(arr, n);
				sort(arr.begin(), arr.end());

				vector<int> blocks;
				int now = 0;
				for (int i = 0; i < n; i++) {
					if (now == arr[i]) {
						blocks[blocks.size() - 1]++;
					}
					else {
						blocks.emplace_back(1);
						now = arr[i];
					}
				}

				int putCount = blocks[0];
                int mask = 998244353;
                CaseCalculator calculator(mask, n);
                vector<vector<long>> dp(blocks.size(), vector<long>(n, 0));
                dp[0][0] = 1;
                long allPerm = calculator.getPermutation(blocks[0], blocks[0]);
				for (int i = 1; i < blocks.size(); i++) {
                    for (int j = 0; j < n; j++) {
                        if (dp[i - 1][j] == 0) {
                            continue;
                        }

                        int puttableCount = putCount - j;
                        int maxCount = min(puttableCount, blocks[i]);
                        for (int l = 0; l <= maxCount; l++) {
                            long uncountableCount = j + l + 1;
                            long combination = calculator.multi(
                                calculator.getCombination(puttableCount, l),
                                calculator.getCombination(uncountableCount - 1 + blocks[i] - l, uncountableCount - 1));
                            dp[i][j + l] += calculator.multi(dp[i - 1][j], combination);
                            dp[i][j + l] %= mask;
                        }
                    }
                    putCount += blocks[i];
                    allPerm = calculator.multi(allPerm, calculator.getPermutation(blocks[i], blocks[i]));
				}

                WRITE_LINE(calculator.multi(dp[blocks.size() - 1][k], allPerm));
			}
		};
	}
}

int main() {
	ABC::_267::G::solve();
}