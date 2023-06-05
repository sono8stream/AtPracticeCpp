#include <iostream>
#include <string>
#include <vector>

namespace ABC {
	namespace _264 {
		using namespace std;

		class UnionFind {
		public:
			UnionFind(int size)
				:parents(size), sizes(size, 1), ranks(size, 0) {
				for (int i = 0; i < size; i++) {
					parents[i] = i;
				}
			}

			bool isRoot(const int pos) {
				return pos == parents[pos];
			}

			int getRoot(const int pos) {
				int now = pos;
				while (!isRoot(now)) {
					now = parents[now];
				}

				parents[pos] = now;
				return now;
			}

			int getSize(const int pos) {
				return sizes[getRoot(pos)];
			}

			void unite(int x, int y) {
				int rootX = getRoot(x);
				int rootY = getRoot(y);

				if (rootX == rootY) {
					return;
				}

				if (ranks[rootX] < ranks[rootY]) {
					swap(rootX, rootY);
				}

				parents[rootY] = rootX;
				if (ranks[rootX] == ranks[rootY]) {
					ranks[rootX]++;
				}

				sizes[rootX] += sizes[rootY];
			}

		private:
			vector<int> parents, sizes, ranks;
		};

		class E {
		public:

			static void solve() {
				int n, m, e;
				cin >> n >> m >> e;
				vector<vector<int>> edges(e, vector<int>(2));
				for (int i = 0; i < e; i++) {
					int u, v;
					cin >> u >> v;
					edges[i][0] = u - 1;
					edges[i][1] = v - 1;
				}

				int q;
				cin >> q;
				vector<int> xs(q);
				for (int i = 0; i < q; i++) {
					int x;
					cin >> x;
					xs[i] = x - 1;
				}

				UnionFind uf(n + 1);// nî‘ñ⁄ÇÕî≠ìdèä
				vector<bool> areEventAffected(e, false);
				for (int i = 0; i < q; i++) {
					areEventAffected[xs[i]] = true;
				}
				for (int i = 0; i < e; i++) {
					if (!areEventAffected[i]) {
						int u = min(edges[i][0], n);
						int v = min(edges[i][1], n);
						uf.unite(u, v);
					}
				}

				vector<int> reses(q);
				for (int i = q - 1; i >= 0; i--) {
					reses[i] = uf.getSize(n) - 1;

					int u = min(edges[xs[i]][0], n);
					int v = min(edges[xs[i]][1], n);
					uf.unite(u, v);
				}

				for (int i = 0; i < q; i++) {
					cout << reses[i] << endl;
				}
			}
		};
	}
}

int main() {
	ABC::_264::E::solve();
}