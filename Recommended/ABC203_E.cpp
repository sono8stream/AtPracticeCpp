#include <iostream>
#include <set>
#include <map>

namespace Recommended {
	class ABC203_E {
	public:

		class XY {
		public:

			XY() {
				X = 0;
				Y = 0;
			}

			XY(int x, int y) {
				X = x;
				Y = y;
			}

			bool operator<(const XY& xy) const {
				if (this->X < xy.X) {
					return true;
				}
				else if (this->X == xy.X) {
					return this->Y < xy.Y;
				}
				else {
					return false;
				}
			}

			bool operator==(const XY& xy) const {
				return this->X == xy.X && this->Y == xy.Y;
			}

			int X;
			int Y;
		};

		static void update(std::set<int>& res, std::map<int, int>& updater) {
			for (auto itr = updater.begin(); itr != updater.end(); ++itr) {
				if (itr->second == 1) {
					// “®‚¯‚éê‡
					res.emplace(itr->first);
				}
				else {
					// “®‚¯‚È‚¢ê‡
					res.erase(itr->first);
				}
			}
			updater.clear();
		}

		static void solve() {
			using namespace std;

			int n, m;
			cin >> n >> m;

			set<XY> xys;

			for (int i = 0; i < m; ++i) {
				int x, y;
				cin >> x >> y;
				xys.emplace(XY(x, y));
			}

			set<int> res;
			res.emplace(n);
			map<int, int> updater;

			int prevX = 0;
			for (auto itr = xys.begin(); itr != xys.end(); ++itr) {
				if (prevX != itr->X) {
					update(res, updater);
					prevX = itr->X;
				}

				if (res.find(itr->Y) == res.end()
					&& (res.find(itr->Y - 1) != res.end() || res.find(itr->Y + 1) != res.end())) {
					updater.emplace(itr->Y, 1);
				}
				if (res.find(itr->Y) != res.end()
					&& (res.find(itr->Y - 1) == res.end() && res.find(itr->Y + 1) == res.end())) {
					updater.emplace(itr->Y, -1);
				}
			}

			update(res, updater);

			cout << res.size();
		}
	};
}

int main() {
	Recommended::ABC203_E::solve();
}