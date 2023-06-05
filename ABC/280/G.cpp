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
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];�p
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;

namespace ABC {
	namespace _280 {
		using namespace std;
		// ���j
		// ���������A�n�j�J���\���ł�2�_�Ԃ̋�����max(|X|,|Y|,|X-Y|)�ŕ\�����B
		// �����3������ԁiX,Y,X-Y�j�ɂ��`�F�r�V�F�t�����ɕϊ��ł��適�����ɋC�Â��Ȃ�����
		// ����3������ԓ���D*D*D�̗����̓��Ɋ܂܂��_�ǂ����̃`�F�r�V�F�t�����͕K��D�ȉ��ƂȂ邽�߁A��蕶�̏������肪�ł���悤�ɂȂ�
		// ����A����D*D*D����2�_�Ԃł�Z���W��D�𒴂���\��������
		// �e���͓Ɨ��ɍl������̂ŁAX,Y���Œ肵��Z�����̂ݎڎ��ŋ��߂�΂悢
		// �d����h���ɂ́A�e���ɂ��čŏ��̍��W���Œ肵�Ȃ��瓮����
		// �[�ɂ���_�͍ł��C���f�b�N�X�����������̂��Œ肷��悤�ɂ���

		class G {
		public:

			static void solve() {
				READ_LONG(n);
				READ_LONG(d);

				vector<long> xs(n, 0), ys(n, 0);
				vector<vector<long>> poses;
				for (int i = 0; i < n; i++) {
					cin >> xs[i] >> ys[i];
					vector<long> pos{ xs[i],ys[i],xs[i] - ys[i] };
					poses.emplace_back(pos);
				}

				long mask = 998244353;

				vector<long> pows(n + 10);
				pows[0] = 1;
				for (int i = 1; i < pows.size(); i++) {
					pows[i] = pows[i - 1] * 2;
					pows[i] %= mask;
				}

				long res = 0;

				for (int i = 0; i < n; i++) {// X���W�ŏ��̓_
					for (int j = 0; j < n; j++) {// Y���W�ŏ��̓_
						// i��X���W�ŏ��łȂ���΃X�L�b�v
						if (poses[j][0] < poses[i][0]
							|| (poses[i][0] == poses[j][0] && j < i)) {
							continue;
						}
						// j��Y���W�ŏ��łȂ���΃X�L�b�v
						if (poses[i][1] < poses[j][1]
							|| (poses[i][1] == poses[j][1] && i < j)) {
							continue;
						}
						// 2�_�݂̂ŏ����𖞂����Ȃ��ꍇ���X�L�b�v
						if (poses[j][0] > poses[i][0] + d
							|| poses[i][1] > poses[j][1] + d) {
							continue;
						}

						vector<int> ids;
						for (int k = 0; k < n; k++) {
							// X�����ɔ͈͓��ɖ����ꍇ�̓X�L�b�v
							if (poses[k][0]<poses[i][0] || poses[k][0]>poses[i][0] + d
								|| (poses[k][0] == poses[i][0] && k < i)) {
								continue;
							}
							// Y�����ɔ͈͓��ɖ����ꍇ�̓X�L�b�v
							if (poses[k][1]<poses[j][1] || poses[k][1]>poses[j][1] + d
								|| (poses[k][1] == poses[j][1] && k < j)) {
								continue;
							}

							ids.emplace_back(k);
						}

						sort(ids.begin(), ids.end(), [&](int a, int b) {
							return poses[a][2] < poses[b][2] || (poses[a][2] == poses[b][2] && a < b);
							});

						// �ڎ��
						int right = 0;// Z���W�ŏ��l
						for (int left = 0; left < ids.size(); left++) {
							int id = ids[left];
							// �Œ肵��2�_�������𖞂����Ȃ��ꍇ�̓X�L�b�v
							if (poses[i][2]<poses[id][2] || poses[i][2]>poses[id][2] + d
								|| (poses[i][2] == poses[id][2] && i < id)) {
								continue;
							}
							if (poses[j][2]<poses[id][2] || poses[j][2]>poses[id][2] + d
								|| (poses[j][2] == poses[id][2] && j < id)) {
								continue;
							}

							while (right < ids.size() && poses[ids[right]][2] <= poses[id][2] + d) {
								right++;
							}

							int num = right - left - set<int>({ i, j, id }).size();
							res += pows[num];
							res %= mask;
						}
					}
				}

				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ABC::_280::G::solve();
}