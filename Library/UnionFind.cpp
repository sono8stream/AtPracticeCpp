#include <iostream>
#include <string>
#include <vector>

namespace ABC {
	namespace Library {
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
	}
}