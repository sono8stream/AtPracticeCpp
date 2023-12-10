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
	namespace _331 {
		using namespace std;
		// ���j
		// �ł������g�ݍ��킹���珇�Ɍ��Ă����A���߂đ����̈����g�ݍ��킹�łȂ��Ȃ������̂�I��

		class Dish {
			// ���i��ID��ێ�
		public:
			int price;
			int id;
			Dish() :price(0), id(0) {
			}
			Dish(int price, int id) :price(price), id(id) {
			}
			bool operator<(const Dish& another) const {
				return this->price < another.price;
			}
			bool operator>(const Dish& another) const {
				return this->price > another.price;
			}

			// ������Z�q
			Dish& operator=(const Dish& another) {
				this->price = another.price;
				this->id = another.id;
				return *this;
			}

			static bool greater(const Dish& d1, const Dish& d2) {
				return d1.price > d2.price;
			}
		};

		class E {
		public:
			static const int ARR_MAX = 100000;

			E() {
			}

			void solve() {
				// �T�C�Y���傫���̂ŃO���[�o���Ɋm��
				static Dish mains[ARR_MAX];// ���C���f�B�b�V���̉��i
				static Dish subs[ARR_MAX];// ���؂̉��i

				READ_INT(n);
				READ_INT(m);
				READ_INT(l);

				for (int i = 0; i < n; i++) {
					READ_INT(price)
						mains[i] = Dish(price, i);
				}
				for (int i = 0; i < m; i++) {
					READ_INT(price)
						subs[i] = Dish(price, i);
				}

				// �����̈����g�ݍ��킹��ێ�
				map<int,set<int>> badChoices;
				for (int i = 0; i < l; i++) {
					READ_INT(c);
					READ_INT(d);
					badChoices[c - 1].insert(d - 1);
				}

				// ���i�̍������Ƀ\�[�g
				sort(mains, mains + n, Dish::greater);
				sort(subs, subs + m, Dish::greater);

				// �������ɒ�H���i���擾�����ꍇ��l+1�ڂ̒�H���i��񕪒T���ŋ��߂�
				int low = 0;// ��������
				int high = mains[0].price + subs[0].price + 1;// �������Ȃ���
				while (high - low > 1) {
					int mid = (low + high) / 2;
					// ���i��mid�ȏ�̂��̂�l+1�ȏ゠�邩�ǂ����`�F�b�N
					int count = 0;
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < m; j++) {
							int price = mains[i].price + subs[j].price;
							if (price < mid) {
								break;
							}

							count++;
							if (count >= l + 1) {
								break;
							}
						}
						if (count >= l + 1) {
							break;
						}
					}

					if (count >= l + 1) {
						low = mid;
					}
					else {
						high = mid;
					}
				}

				int minPrice = low;// �Œቿ�i�B���߂鉿�i�͕K������ȏ�
				// ���i�̍������̂��}���肵�Ȃ��猩�Ă���
				int resPrice = 0;
				int checkedCount = 0;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						int price = mains[i].price + subs[j].price;
						if (price < minPrice || price <= resPrice) {
							// ���Ƀ`�F�b�N�ς݂̉��i�͎}����̂��߃X�L�b�v�B
							// �������Ȃ��ƍŒቿ�i����ʂɂ������ꍇ��TLE����
							break;
						}

						if (badChoices.find(mains[i].id) == badChoices.end()
							|| badChoices[mains[i].id].find(subs[j].id) == badChoices[mains[i].id].end()) {
							// �����g�ݍ��킹�łȂ���Ή��i���X�V
							resPrice = max(resPrice, price);
						}
					}
				}

				WRITE_LINE(resPrice);
			}
		};
	}
}

int main() {
	ABC::_331::E solver;
	solver.solve();
}