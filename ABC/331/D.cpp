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
	namespace _331 {
		using namespace std;
		// ���j
		// ���O��1000*1000�Ō��J�E���g���Ă����i�ݐϘa�j
		// �ЂƂ܂Ƃ܂�̂��̂Ɨ]���������J�E���g���Ă���

		class D {
		public:
			static const int N_MAX = 1000;
			static bool isBlack[][N_MAX];// [i][j] := i�sj�񂪍����ǂ���
			static int sums[][N_MAX];// [i][j] := i�sj��܂ł̗ݐϘa

			static long getSum(long y1, long x1, long y2, long x2, int sums[N_MAX][N_MAX]) {
				return sums[y2][x2]
					- (y1 > 0 ? sums[y1 - 1][x2] : 0)
					- (x1 > 0 ? sums[y2][x1 - 1] : 0)
					+ (y1 > 0 && x1 > 0 ? sums[y1 - 1][x1 - 1] : 0);
			}

			static void solve() {
				READ_INT(n);
				READ_INT(q);

				// C++11���珉���������悤�ɂȂ����炵�����AC++03�ł͖����I�ɏ��������K�v�B�g���܂킵��������������
				for (int i = 0; i < N_MAX; i++)
				{
					for (int j = 0; j < N_MAX; j++)
					{
						sums[i][j] = 0;
					}
				}

				// 2�����̕����񂪗^������̂ŁA������B�̂Ƃ����true�ɂ���
				for (int i = 0; i < n; i++) {
					READ_STR(s);
					for (int j = 0; j < n; j++) {
						if (s[j] == 'B') {
							isBlack[i][j] = true;
						}
					}
				}

				// 2�����̗ݐϘa���v�Z����
				for (int i = 0; i < n; i++) {
					int currentSum = 0;
					for (int j = 0; j < n; j++) {
						currentSum += (isBlack[i][j] ? 1 : 0);
						sums[i][j] = currentSum + (i > 0 ? sums[i - 1][j] : 0);
					}
				}

				// �N�G������
				for (int i = 0; i < q; i++) {
					READ_LONG(a);
					READ_LONG(b);
					READ_LONG(c);
					READ_LONG(d);

					long upperA = a - a % n + n;
					long lowerC = c - c % n;
					long upperB = b - b % n + n;
					long lowerD = d - d % n;

					long modA = a % n;
					long modB = b % n;
					long modC = c % n;
					long modD = d % n;

					long skipCountY = (lowerC - upperA) / n;
					long skipCountX = (lowerD - upperB) / n;

					long count = 0;
					if (upperA > lowerC && upperB > lowerD) {
						// x�������ɂ�y�������ɂ��u���b�N���ׂ��Ȃ��ꍇ
						// ���ʂ̗ݐϘa�����
						count = getSum(modA, modB, modC, modD, sums);
					}
					else if (upperA <= lowerC && upperB > lowerD) {
						// y�������ɂ̂݃u���b�N���ׂ��ꍇ�A�㉺�ɉ�̒[���c��̂��l�����đ���
						count = getSum(modA, modB, n - 1, modD, sums)
							+ getSum(0, modB, modC, modD, sums);
						//�ׂ����u���b�N���������B
						count += skipCountY * getSum(0, modB, n - 1, modD, sums);
					}
					else if (upperA > lowerC && upperB <= lowerD) {
						// x�������ɂ̂݃u���b�N���ׂ��ꍇ
						count = getSum(modA, modB, modC, n - 1, sums)
							+ getSum(modA, 0, modC, modD, sums);
						//�ׂ����u���b�N���������B
						count += skipCountX * getSum(modA, 0, modC, n - 1, sums);
					}
					else {
						// x�������ɂ�y�������ɂ��u���b�N���ׂ��ꍇ
						// �܂��͎l���𑫂�
						count = getSum(modA, modB, n - 1, n - 1, sums)
							+ getSum(modA, 0, n - 1, modD, sums)
							+ getSum(0, modB, modC, n - 1, sums)
							+ getSum(0, 0, modC, modD, sums);

						// ����4�ӂ𑫂�
						// �܂��͏c����
						count += skipCountY * (getSum(0, modB, n - 1, n - 1, sums) + getSum(0, 0, n - 1, modD, sums));

						// ���ɉ�����
						count += skipCountX * (getSum(modA, 0, n - 1, n - 1, sums) + getSum(0, 0, modC, n - 1, sums));

						// �Ō�Ɋ��S�Ɍׂ����u���b�N�𑫂�
						count += skipCountX * skipCountY * getSum(0, 0, n - 1, n - 1, sums);
					}

					WRITE_LINE(count);
				}
			}
		};

		bool D::isBlack[D::N_MAX][D::N_MAX];
		int D::sums[D::N_MAX][D::N_MAX];
	}
}

int main() {
	ABC::_331::D::solve();
}