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
		// �����n�������猩���ꍇ�ƉE���猩���ꍇ�ł��ꂼ��\�z���Ă���

		class RollingHash {
		private:
			static const int BASE_COUNT = 5;

			static const long* getMods() {
				// ���͈ȉ����Ƃ�B1�̊��ɂ��A�n�b�V���l�̏Փˊm����(1-(N-1))/p�iN�͑Ώۂ̕�����̒����Bp�͊��̃T�C�Y�j�炵���B�v�׋��B
				static const long mods[BASE_COUNT] = { 998244353, 1000000007, 1000000009, 1000000021, 1000000033 };
				return mods;
			}

			static const long* getBases() {
				// �O�̂��߃A���t�@�x�b�g�̌����͑傫�Ȓl�Ƃ��Ă����B�Ȃ�ł��̐��ŗǂ��̂��͒ǂ��ĕ׋��B
				static const long mods[BASE_COUNT] = { 31, 37, 41, 43, 47 };
				return mods;
			}

		public:

			long leftHashs[BASE_COUNT];// �n�b�V���l
			long pows[BASE_COUNT];// �����ɉ������ׂ����ێ����Ă����B

			RollingHash() {
				for (int i = 0; i < BASE_COUNT; i++) {
					this->leftHashs[i] = 0;
					this->pows[i] = 1;
				}
			}

			// �R�s�[�R���X�g���N�^
			RollingHash(const RollingHash& another) {
				for (int i = 0; i < BASE_COUNT; i++) {
					this->leftHashs[i] = another.leftHashs[i];
					this->pows[i] = another.pows[i];
				}
			}

			RollingHash(int c) {
				const long* mods = getMods();
				const long* bases = getBases();

				// 1�����̏ꍇ�̃n�b�V��������Ă����B
				for (int i = 0; i < BASE_COUNT; i++) {
					this->leftHashs[i] = c % mods[i];

					this->pows[i] = bases[i];
				}
			}

			// ��r���Z�q
			bool operator==(const RollingHash& another) const {
				bool res = true;
				for (int i = 0; i < BASE_COUNT; i++) {
					res &= this->leftHashs[i] == another.leftHashs[i];
				}
				return res;
			}

			static void integrate(const RollingHash& left, const RollingHash& right, RollingHash& dst) {
				const long* mods = getMods();
				const long* bases = getBases();

				for (int i = 0; i < BASE_COUNT; i++) {
					dst.leftHashs[i] = (left.leftHashs[i] + right.leftHashs[i] * left.pows[i]) % mods[i];
					dst.pows[i] = left.pows[i] * right.pows[i] % mods[i];
				}
			}
		};

		// �Z�O�����e�[�V�����c���[�̍\�z
		template <int SIZE, class T>
		class SegmentTree {
		private:
			T tree[SIZE * 4];// �T�C�Y��(�w�肵�����ȏ��2�ׂ̂���)*2-1�����K�v�B����ȏ�ɂȂ邱�Ƃ͂Ȃ��B
			T exceptionVal;// �͈͊O�̒l
			int totalLength;
			int size;

			typedef void (*MANIPULATOR)(const T& left, const T& right, T& dst);
			MANIPULATOR integrate;// ��������


		public:

			// �S�v�f���X�V����
			void updateAll() {
				for (int i = totalLength - 2; i >= 0; i--) {
					integrate(tree[i * 2 + 1], tree[i * 2 + 2], tree[i]);
				}
			}

			SegmentTree(T initialVal, T exceptionVal, const MANIPULATOR& integrate) :size(SIZE), integrate(integrate) {
				totalLength = 1;
				while (totalLength < size)
				{
					totalLength *= 2;
				}

				for (int i = 0; i < SIZE * 4; i++) {
					tree[i] = exceptionVal;
				}

				for (int i = 0; i < SIZE; i++)
				{
					tree[i + totalLength - 1] = initialVal;
				}
				this->exceptionVal = exceptionVal;

				updateAll();
			}

			// i�Ԗڂ̗v�f���X�V����
			void update(int i, T value)
			{
				int now = i + totalLength - 1;
				tree[now] = value;
				while (now > 0)
				{
					now = (now - 1) / 2;
					integrate(tree[now * 2 + 1], tree[now * 2 + 2], tree[now]);
				}
			}

			// i�Ԗڂ̗v�f���擾����
			T Look(int i)
			{
				return tree[i + totalLength - 1];
			}

			/// <summary>
			/// [left, right]��[top,last]�ƈ�v���Ă���΂��̒l���C�����łȂ���Γ������ĕԂ�
			/// �ċA����
			/// ���E�̈Ⴂ���C�ɂ���
			/// </summary>
			/// <param name="left">�z�񒆂�Scan���������[�C���f�b�N�X</param>
			/// <param name="right">�z�񒆂�Scan�������E�[�C���f�b�N�X</param>
			/// <param name="i">���݌��Ă���c���[���̗v�f�̃C���f�b�N�X</param>
			/// <param name="top">���݌��Ă���c���[���̗v�f���J�o�[����z�񒆂̍��[�C���f�b�N�X</param>
			/// <param name="last">���݌��Ă���c���[���̗v�f���J�o�[����z�񒆂̉E�[�C���f�b�N�X</param>
			void Query(T& dst, int left, int right, int i, int top, int last)
			{
				if (left == top && right == last)
				{
					dst = tree[i];
					return;
				}
				else
				{
					int half = (top + last) / 2;

					if (right <= half)// �����ɕ����������ɍ���������΂����Ȃ�q�v�f�ɔC����
					{
						Query(dst, left, right, i * 2 + 1, top, half);
						return;
					}
					if (left > half)// �����ɕ����������ɉE��������΂����Ȃ�q�v�f�ɔC����
					{
						Query(dst, left, right, i * 2 + 2, half + 1, last);
						return;
					}

					T leftNode, rightNode;
					Query(leftNode, left, half, i * 2 + 1, top, half);
					Query(rightNode, half + 1, right, i * 2 + 2, half + 1, last);
					integrate(leftNode, rightNode, dst);
				}
			}

			/// <summary>
			/// [left, right]���擾
			/// </summary>
			/// <param name="left">���[</param>
			/// <param name="right">�E�[�i���E���܂ށj</param>
			void Scan(T& dst, int left, int right)
			{
				if (left >= size || right < 0 || right < left)
				{
					dst = exceptionVal;
					return;
				}

				Query(dst, left, right, 0, 0, totalLength - 1);
			}
		};

		class F {
		public:
			static const int N_MAX = 1000000;

			F() {
			}

			void solve() {
				// �T�C�Y���傫���̂ŃO���[�o���Ɋm��
				static SegmentTree<N_MAX, RollingHash> leftTree(RollingHash(1), RollingHash(), RollingHash::integrate);
				static SegmentTree<N_MAX, RollingHash> rightTree(RollingHash(1), RollingHash(), RollingHash::integrate);

				READ_INT(n);
				READ_INT(q);

				READ_STR(str);

				// �n�b�V���̎擾
				for (int i = 0; i < n; i++) {
					leftTree.update(i, RollingHash(str[i] - 'a' + 1));
					rightTree.update(n - i - 1, RollingHash(str[i] - 'a' + 1));
				}

				for (int i = 0; i < q; i++) {
					READ_INT(mode);
					if (mode == 1) {
						// �����̒u��
						READ_INT(pos);
						READ_STR(c);
						leftTree.update(pos - 1, RollingHash(c[0] - 'a' + 1));
						rightTree.update(n - pos, RollingHash(c[0] - 'a' + 1));
					}
					else if (mode == 2) {
						// �񕶔���
						READ_INT(left);
						READ_INT(right);
						int center = (left + right) / 2;
						int centerLeft = (right - left + 1) % 2 == 0 ? center : center - 1;
						int centerRight = center + 1;

						RollingHash leftHash, rightHash;
						leftTree.Scan(leftHash, left - 1, centerLeft - 1);
						rightTree.Scan(rightHash, n - right, n - centerRight);

						if (leftHash == rightHash) {
							WRITE_LINE("Yes");
						}
						else {
							WRITE_LINE("No");
						}
					}
				}
			}

			void check() {
				RollingHash hashA(1);
				RollingHash hashB(1);
				if (hashA==hashB)
				{
					WRITE_LINE("OK");
				}else{
					WRITE_LINE("NG");
				}

				RollingHash hashE(2);

				RollingHash hashF;
				RollingHash hashG;
				RollingHash::integrate(hashF, hashA, hashG);
				if (hashG == hashA)
				{
					WRITE_LINE("OK");
				}
				else {
					WRITE_LINE("NG");
				}

				SegmentTree<2, RollingHash> tree(RollingHash(1), RollingHash(),RollingHash::integrate);
				tree.update(1, RollingHash(2));
				RollingHash hashH;
				tree.Scan(hashH, 1, 1);
				if (hashH == RollingHash(2))
				{
					WRITE_LINE("OK");
				}
				else {
					WRITE_LINE("NG");
				}

				RollingHash hashI;
				tree.Scan(hashI, 0, 1);
				RollingHash hashJ;
				RollingHash::integrate(hashA, hashE, hashJ);
				if (hashI == hashJ)
				{
					WRITE_LINE("OK");
				}
				else {
					WRITE_LINE("NG");
				}
			}
		};
	}
}

int main() {
	ABC::_331::F solver;
	//solver.check();
	solver.solve();
}