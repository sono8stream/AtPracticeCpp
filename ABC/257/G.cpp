#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <vector>

namespace ABC {
	namespace _257 {
		using namespace std;



		class G {
		public:

			static void zAlgorithm(string s, int* res) {
				for (int i = 0; i < s.size(); ++i) {
					res[i] = 0;
				}
				res[0] = s.size();

				int currentPos = 1;
				int sameLength = 0;
				while( currentPos < s.size()) {
					while (currentPos + sameLength < s.size() 
						&& s[sameLength] == s[currentPos + sameLength]) {
						sameLength++;
					}
					res[currentPos] = sameLength;

					// 1•¶Žš‚àˆê’v‚µ‚Ä‚¢‚È‚¢ê‡‚Í‘ÅØ‚è
					if (sameLength == 0) {
						currentPos++;
						continue;
					}

					int reuseLength = 1;
					while (reuseLength < sameLength && reuseLength + res[reuseLength] < sameLength) {
						res[currentPos + reuseLength] = res[reuseLength];
						reuseLength++;
					}

					currentPos += reuseLength;
					sameLength -= reuseLength;
				}
			}

			static void solve() {
				string s, t;
				cin >> s >> t;

				string total = s + "X" + t;
				int* matches = new int[total.size()];
				zAlgorithm(total, matches);

				int* dp = new int[t.size()];
				for (int i = 0; i < t.size(); ++i) {
					dp[i] = (int)-1;
				}

				int uncheckedPos = 0;
				for (int i = 0; i < t.size(); ++i) {
					int prev = i == 0 ? 0 : dp[i - 1];
					if (prev == -1) {
						break;
					}

					int matchLength = matches[s.size() + 1 + i];
					if (matchLength > 0) {
						for (int k = uncheckedPos; k < i + matchLength; k++) {
							dp[k] = prev + 1;
						}

						if (uncheckedPos < i + matchLength) {
							uncheckedPos = i + matchLength;
						}
					}
				}

				cout << dp[t.size() - 1] << endl;

				delete[] matches;
				delete[] dp;
			}
		};
	}
}

int main() {
	ABC::_257::G::solve();
}