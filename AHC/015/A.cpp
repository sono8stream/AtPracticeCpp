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
#include <random>

#define long long long

#define READ_INT(var) int var;std::cin>>var;
#define READ_LONG(var) long var;std::cin>>var;
#define READ_DOUBLE(var) double var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;

namespace AHC {
	namespace _015 {
		using namespace std;
		// ���j
		// �܂��̓����_���Ɏ擾
		// ��茻���_�̃|�C���g�������Ȃ���ɓ�����
		// 10����x��܂Ń����_���ɃV�~�����[�V�������Ă݂ėǂ����ȕ����Ɉړ�

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

		class A {
		public:

			static const int row = 10;
			static const int col = 10;
			static const int all = 100;

			enum Dire{
				F,
				R,
				B,
				L
			};

			static int toLine(int r, int c) {
				return r * col + c;
			}

			static void simulate(Dire d, const vector<vector<int>>& current, vector<vector<int>>& next) {

				next = vector<vector<int>>(current.size(), vector<int>(current[0].size(), 0));
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < col; j++) {
						next[i][j] = current[i][j];
					}
				}

				switch (d) {
				case F:
					for (int j = 0; j < col; j++) {
						for (int i = 0; i < row; i++) {
							// ���݂���Ȃ��Ɉړ�������
							if (next[i][j] > 0) {
								int val = current[i][j];
								next[i][j] = 0;
								int to = i;
								while (to > 0 && next[to - 1][j] == 0) {
									to--;
								}
								next[to][j] = val;
							}
						}
					}
					break;
				case R:
					for (int i = 0; i < row; i++) {
						for (int j = col-1; j >=0; j--) {
							// ���݂���Ȃ�E�Ɉړ�������
							if (next[i][j] > 0) {
								int val = next[i][j];
								next[i][j] = 0;
								int to = j;
								while (to + 1 < col && next[i][to + 1] == 0) {
									to++;
								}
								next[i][to] = val;
							}
						}
					}
					break;
				case B:
					for (int j = 0; j < col; j++) {
						for (int i = row-1; i >=0; i--) {
							// ���݂���Ȃ牺�Ɉړ�������
							if (next[i][j] > 0) {
								int val = next[i][j];
								next[i][j] = 0;
								int to = i;
								while (to + 1 < row && next[to + 1][j] == 0) {
									to++;
								}
								next[to][j] = val;
							}
						}
					}
					break;
				case L:
					for (int i = 0; i < row; i++) {
						for (int j = 0; j < col; j++) {
							// ���݂���Ȃ獶�Ɉړ�������
							if (next[i][j] > 0) {
								int val = next[i][j];
								next[i][j] = 0;
								int to = j;
								while (to > 0 && next[i][to - 1] == 0) {
									to--;
								}
								next[i][to] = val;
							}
						}
					}
					break;
				}
			}

			static int evaluate(const vector<vector<int>>& current) {
				UnionFind uf(all);
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < col; j++) {
						if (i + 1 < row && current[i][j] == current[i + 1][j]) {
							uf.unite(i * col + j, (i + 1) * col + j);
						}
						if (i - 1 >= 0 && current[i][j] == current[i - 1][j]) {
							uf.unite(i * col + j, (i - 1) * col + j);
						}
						if (j + 1 < col && current[i][j] == current[i][j + 1]) {
							uf.unite(i * col + j, i * col + j + 1);
						}
						if (j - 1 >= 0 && current[i][j] == current[i][j - 1]) {
							uf.unite(i * col + j, i * col + j - 1);
						}
					}
				}

				int res = 0;
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < col; j++) {
						int line = toLine(i, j);
						if (uf.getRoot(line) == line && current[i][j] > 0) {
							res += uf.getSize(line) * uf.getSize(line);
						}
					}
				}

				return res;
			}

			static void getPos(vector<vector<int>>& current, int num, int& r, int& c) {
				r = 0;
				c = -1;
				int now = 0;
				while (now < num) {
					c++;
					if (c == col) {
						r++;
						c = 0;
					}
					while (current[r][c] > 0) {
						c++;
						if (c == col) {
							r++;
							c = 0;
						}
					}
					now++;
				}
			}

			static void decideMoveOnce(vector<vector<int>>& current) {
				// ���ꂼ��̃X�R�A���v�Z���A���傫�ȕ���I��
				vector<vector<int>> maxNext;
				int maxScore = 0;

				// ��
				vector<vector<int>> forwardNext;
				simulate(Dire::F, current, forwardNext);
				int forwardScore = evaluate(forwardNext);

				if (maxScore < forwardScore) {
					maxScore = forwardScore;
					maxNext = forwardNext;
				}

				// ��
				vector<vector<int>> backNext;
				simulate(Dire::B, current, backNext);
				int backScore = evaluate(backNext);

				if (maxScore < backScore) {
					maxScore = backScore;
					maxNext = backNext;
				}

				// �E
				vector<vector<int>> rightNext;
				simulate(Dire::R, current, rightNext);
				int rightScore = evaluate(rightNext);

				if (maxScore < rightScore) {
					maxScore = rightScore;
					maxNext = rightNext;
				}

				// ��
				vector<vector<int>> leftNext;
				simulate(Dire::L, current, leftNext);
				int leftScore = evaluate(leftNext);

				if (maxScore < leftScore) {
					maxScore = leftScore;
					maxNext = leftNext;
				}

				current = maxNext;
			}

			static void decideMove(vector<vector<int>>& current, char& maxMove, int putCount,vector<int>& pats) {
				// ������������
				random_device rnd;
				mt19937 mt(rnd());

				int simulationCount = min(10, all - putCount - 1);
				vector<int> simulationPoses;
				for (int i = 0; i < simulationCount; i++) {
					uniform_int_distribution<> rand(0, all - putCount - i - 2);
					simulationPoses.emplace_back(rand(mt) + 1);
				}

				// ���ꂼ��̃X�R�A���v�Z���A���傫�ȕ���I��
				vector<vector<int>> maxNext;
				int maxScore = 0;

				// ��
				vector<vector<int>> forwardNext;
				simulate(Dire::F, current, forwardNext);
				for (int i = 0; i < simulationCount; i++) {
					// ���W�`�F�b�N
					int r, c;
					getPos(forwardNext, simulationPoses[i], r, c);

					forwardNext[r][c] = pats[i];
					decideMoveOnce(forwardNext);
				}
				int forwardScore = evaluate(forwardNext);

				if (maxScore < forwardScore) {
					maxScore = forwardScore;
					maxMove = 'F';
				}

				// ��
				vector<vector<int>> backNext;
				simulate(Dire::B, current, backNext);
				for (int i = 0; i < simulationCount; i++) {
					// ���W�`�F�b�N
					int r, c;
					getPos(backNext, simulationPoses[i], r, c);

					backNext[r][c] = pats[i];
					decideMoveOnce(backNext);
				}
				int backScore = evaluate(backNext);

				if (maxScore < backScore) {
					maxScore = backScore;
					maxMove = 'B';
				}

				// �E
				vector<vector<int>> rightNext;
				simulate(Dire::R, current, rightNext);
				for (int i = 0; i < simulationCount; i++) {
					// ���W�`�F�b�N
					int r, c;
					getPos(rightNext, simulationPoses[i], r, c);

					rightNext[r][c] = pats[i];
					decideMoveOnce(rightNext);
				}
				int rightScore = evaluate(rightNext);

				if (maxScore < rightScore) {
					maxScore = rightScore;
					maxMove = 'R';
				}

				// ��
				vector<vector<int>> leftNext;
				simulate(Dire::L, current, leftNext);
				for (int i = 0; i < simulationCount; i++) {
					// ���W�`�F�b�N
					int r, c;
					getPos(leftNext, simulationPoses[i], r, c);

					leftNext[r][c] = pats[i];
					decideMoveOnce(leftNext);
				}
				int leftScore = evaluate(leftNext);

				if (maxScore < leftScore) {
					maxScore = leftScore;
					maxMove = 'L';
				}

				if (maxMove == 'F') {
					simulate(Dire::F, current, maxNext);
				}
				if (maxMove == 'B') {
					simulate(Dire::B, current, maxNext);
				}
				if (maxMove == 'R') {
					simulate(Dire::R, current, maxNext);
				}
				if (maxMove == 'L') {
					simulate(Dire::L, current, maxNext);
				}

				current = maxNext;
			}

			static void solve() {
				READ_INT_ARRAY(pats, all);

				vector<vector<int>> blocks(row, vector<int>(col, 0));

				for (int i = 0; i < all; i++) {
					// �z�u�����ʒu���擾
					READ_INT(n);

					// ���W�`�F�b�N
					int r, c;
					getPos(blocks, n, r, c);

					blocks[r][c] = pats[i];

					char moveDire;
					decideMove(blocks, moveDire, i, pats);

					WRITE_LINE(moveDire);
				}
			}
		};
	}
}

int main() {
	AHC::_015::A::solve();
}