#include <iostream>
#include <unordered_set>
#include <set>
#include <unordered_map>
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

#define READ_ARRAY_TO(var,length) for(int i=0;i<length;i++){std::cin>>var[i];}

#define WRITE_LINE(x) std::cout<<x<<std::endl;

namespace ABC {
	namespace _332 {
		using namespace std;
		// ���j
		// ���c���ꂼ��ŏ���̑S�T�����s��

		class D {
		public:
			static const int H_MAX = 5;
			static const int W_MAX = 5;
			static const int W_PATTERN = 120;// 5!

			D() {
			}

			int getManipulationCount(int pattern[], int size) {
				int count = 0;
				for (int i = 0; i < size; i++) {
					for (int j = i + 1; j < size; j++) {
						if (pattern[i] > pattern[j]) {
							count++;
						}
					}
				}
				return count;
			}

			void solve() {
				int patternH[H_MAX];
				for (int i = 0; i < H_MAX; i++) {
					patternH[i] = i;
				}
				int patternW[W_MAX];
				for (int i = 0; i < W_MAX; i++) {
					patternW[i] = i;
				}

				// h�sw��̃T�C�Y�����
				READ_INT(h);
				READ_INT(w);

				// 2�̔z��𓾂�B
				int arrayA[H_MAX][W_MAX];
				int arrayB[H_MAX][W_MAX];
				for (int i = 0; i < h; i++) {
					for (int j = 0; j < w; j++) {
						READ_INT(val);
						arrayA[i][j] = val;
					}
				}
				for (int i = 0; i < h; i++) {
					for (int j = 0; j < w; j++) {
						READ_INT(val);
						arrayB[i][j] = val;
					}
				}

				// ���O��W�����ɓ���ւ����Ƃ��Ɋe�s����v���邩�ǂ������`�F�b�N���Ă���
				bool canMatch[H_MAX][H_MAX][W_PATTERN];
				for (int i = 0; i < h; i++) {
					for (int j = 0; j < h; j++) {
						int current = 0;
						do {
							for (int k = 0; k < w; k++) {
								if (arrayA[i][patternW[k]] != arrayB[j][k]) {
									canMatch[i][j][current] = false;
									break;
								}
								canMatch[i][j][current] = true;
							}
							current++;
						} while (next_permutation(patternW, patternW + w));
					}
				}

				// h�����Ƀ`�F�b�N���A�e�g�ݍ��킹�����߂Ă���
				const int CANNOT = 10000;
				int count = CANNOT;
				do {
					int current = 0;
					do {
						int manipulationCount = getManipulationCount(patternH, h) + getManipulationCount(patternW, w);

						// ���̑g�ݍ��킹�ň�v���邩�ǂ������`�F�b�N
						bool allMatch = true;
						for (int i = 0; i < h; i++) {
							if (!canMatch[patternH[i]][i][current]) {
								allMatch = false;
								break;
							}
						}

						if (allMatch) {
							count = min(count, manipulationCount);
						}
						current++;
					} while (next_permutation(patternW, patternW + w));
				} while (next_permutation(patternH, patternH + h));

				if (count == CANNOT) {
					WRITE_LINE(-1);
				}
				else {
					WRITE_LINE(count);
				}
			}
		};
	}
}

int main() {
	ABC::_332::D solver;
	solver.solve();
}