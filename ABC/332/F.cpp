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
		// �|���鐔�Ƒ������킹�鐔��x���Z�O�؂ŕێ����Ă���

        // �x���Z�O�؁B�͈͍X�V��1�̍��W�̎��o���������Ȃ��ł��V���v���Ȃ��́B
        template <int SIZE, class T>
		class LazySegmentTree {
        private:
            T tree[SIZE * 4];
            bool haveLazy[SIZE * 4];
            int totalLength;

            T exceptionVal;// �͈͊O�̒l
            T initialVal;// �����l

            // �p�����[�^���X�V���鏈��
            typedef void(*UPDATER)(const T& nextValue, T& target);
            UPDATER updater;

            // �p�����[�^��[���w�ɓ`�d���鏈��
            typedef void(*DISPATCHER)(T& shallower, T& deeper);
            DISPATCHER dispatcher;

        public:

            LazySegmentTree(UPDATER updater, DISPATCHER dispatcher, T initialVal, T exceptionVal)
                : updater(updater), dispatcher(dispatcher), initialVal(initialVal), exceptionVal(exceptionVal)
            {
                totalLength = 1;
                while (totalLength < SIZE)
                {
                    totalLength *= 2;
                }

                for (int i = 0; i < SIZE * 4; i++) {
                    tree[i] = exceptionVal;
                }

                for (int i = 0; i < totalLength * 2 - 1; i++)
                {
                    tree[i] = initialVal;
                }
            }

            // �x���]�������B�[���̐󂢕�����[�����Ɍ����Čv�Z�l��`�d���Ă����B
            void dispatchLazy(int i)
            {
                if (haveLazy[i] && i * 2 + 2 < totalLength * 2 - 1)
                {
                    haveLazy[i * 2 + 1] = true;
                    dispatcher(tree[i], tree[i * 2 + 1]);

                    haveLazy[i * 2 + 2] = true;
                    dispatcher(tree[i], tree[i * 2 + 2]);

                    haveLazy[i] = false;
                    tree[i] = initialVal;
                }
            }

            // [left, right]��[top,last]�ƈ�v���Ă����val�ōX�V�C�����łȂ���Ε�������Update���d�|����
            void updateQuery(int left, int right, int i, int top, int last, const T& val)
            {
                if (left == top && right == last)
                {
                    // �x���Z�O�؂Ȃ̂ŁA�X�V�͈͂��ł��邾���L����ԂŎ~�߂Ă������Ƃō������B
                    haveLazy[i] = true;
                    updater(val, tree[i]);
                }
                else
                {
                    // �x���]�����A���[���w�ɐ���B
                    dispatchLazy(i);

                    int half = (top + last) / 2;
                    if (left <= half)
                    {
                        updateQuery(left, min(right, half), i * 2 + 1, top, half, val);
                    }
                    if (right >= half + 1)
                    {
                        updateQuery(max(left, half + 1), right, i * 2 + 2, half + 1, last, val);
                    }
                }
            }

            // [left, right]��val�ōX�V����
            void update(int left, int right, const T& val)
            {
                if (left < 0 || right >= totalLength || right < left)
                {
                    return;
                }

                updateQuery(left, right, 0, 0, totalLength - 1, val);
            }

            // ����ʒu�̒l���擾���邽�߂̍ċA�T�������B�x���]�����s���Ȃ���[���w�ɐ����Ă����B
            const T& scanQuery(int pos, int i, int top, int last)
            {
                if (pos == top && pos == last)
                {
                    return tree[i];
                }
                else
                {
                    dispatchLazy(i);

                    int half = (top + last) / 2;

                    if (pos <= half)
                    {
                        return scanQuery(pos, i * 2 + 1, top, half);
                    }
                    else
                    {
						return scanQuery(pos, i * 2 + 2, half + 1, last);
					}
                }
            }

            // [left, right]�̒l��]�����Ď擾����
            const T& get(int pos)
            {
                if (pos < 0 || pos >= totalLength)
                {
                    return exceptionVal;
                }

                return scanQuery(pos, 0, 0, totalLength - 1);
            }
        };

        // �]��v�Z���s���N���X�B�����Z�A�����Z�A�|���Z�A����Z���T�|�[�g�B
        class ModInt {
        private:
            static const int MOD = 998244353;

            int value;

        public:
            ModInt() {
                value = 0;
            }

            ModInt(int value) :value(value) {
            }

            ModInt(const ModInt& other) :value(other.value) {
            }

            ModInt& operator=(const ModInt& other) {
                this->value = other.value;
                return *this;
            }

            ModInt& operator+=(const ModInt& other) {
                this->value = (static_cast<long>(this->value) + other.value) % MOD;
                return *this;
            }

            ModInt& operator-=(const ModInt& other) {
                this->value = (static_cast<long>(this->value) - other.value + MOD) % MOD;
                return *this;
            }

            ModInt& operator*=(const ModInt& other) {
                this->value = static_cast<long>(this->value) * other.value % MOD;
                return *this;
            }

            ModInt& operator/=(const ModInt& other) {
                this->value = static_cast<long>(this->value) * other.inverse().value % MOD;
                return *this;
            }

            ModInt operator+(const ModInt& other) const {
                return ModInt(*this) += other;
            }

            ModInt operator-(const ModInt& other) const {
                return ModInt(*this) -= other;
            }

            ModInt operator*(const ModInt& other) const {
                return ModInt(*this) *= other;
            }

            ModInt operator/(const ModInt& other) const {
                return ModInt(*this) /= other;
            }

            ModInt inverse() const {
                return pow(MOD - 2);
            }

            ModInt pow(int n) const {
                ModInt x = *this;
                ModInt ret = 1;
                while (n > 0) {
                    if (n & 1) {
                        ret *= x;
                    }
                    x *= x;
                    n >>= 1;
                }
                return ret;
            }

            int get() const {
                return value;
            }

            bool operator==(const ModInt& other) const {
                return this->value == other.value;
            }
        };

        class Modifier {
        public:
            ModInt coef;
            ModInt add;

            Modifier() {
                coef = 0;
                add = 0;
            }

            Modifier(ModInt coef, ModInt add) :coef(coef), add(add) {
            }

            Modifier(const Modifier& other) :coef(other.coef), add(other.add) {
			}

            Modifier& operator=(const Modifier& other) {
				this->coef = other.coef;
                this->add = other.add;
                return *this;
            }
        };

        class F {
        public:
            static const int NM_MAX = 200000;

            F() {
            }

            void solve() {
                READ_INT(n);
                READ_INT(m);

                static ModInt array[NM_MAX];

                // ���̒l�ɂ����邽�߂̌W����ێ�����x���Z�O��
                static LazySegmentTree<NM_MAX, ModInt> coefTree(
                    [](const ModInt& nextValue, ModInt& target) {
                        target *= nextValue;
                    },
                    [](ModInt& shallower, ModInt& deeper) {
                        deeper *= shallower;
                    },
                    1, 0);

                // ���̒l�ɑ������킹�邽�߂̒l��ێ�����x���Z�O��
                static LazySegmentTree<NM_MAX, Modifier> addTree(
                    [](const Modifier& nextValue, Modifier& target) {
                        target.coef *= nextValue.coef;
                        target.add *= nextValue.coef;
                        target.add += nextValue.add;
                    },
                    [](Modifier& shallower, Modifier& deeper) {
                        deeper.coef *= shallower.coef;
                        deeper.add *= shallower.coef;
                        deeper.add += shallower.add;
                    },
                    Modifier(1, 0), Modifier(0, 0));

                for (int i = 0; i < n; i++) {
                    int val;
                    cin >> val;
                    array[i] = ModInt(val);
                }

                for (int i = 0; i < m; i++) {
                    READ_INT(l);
                    READ_INT(r);
                    READ_INT(x);

                    // �������킹��l���v�Z�B
                    ModInt coef(ModInt(r - l) / ModInt(r - l + 1));
                    ModInt add(ModInt(x) / ModInt(r - l + 1));

                    coefTree.update(l - 1, r - 1, coef);
                    addTree.update(l - 1, r - 1, Modifier(coef, add));
                }

                for (int i = 0; i < n; i++) {
                    // �W���������āA�������킹��l�𑫂��B
                    Modifier modifier = addTree.get(i);
                    array[i] *= coefTree.get(i);
                    array[i] += modifier.add;
                    std::cout << array[i].get() << " ";
                }
            }

            void check() {
                LazySegmentTree<5, ModInt> coefTree(
                    [](const ModInt& nextValue, ModInt& target) {
                        target *= nextValue;
                    },
                    [](ModInt& shallower, ModInt& deeper) {
                        deeper *= shallower;
                    },
                    1, 0);

                coefTree.update(0, 4, ModInt(1) / ModInt(2));
                coefTree.update(0, 2, ModInt(1) / ModInt(3));

                if (ModInt(1) / ModInt(6) == coefTree.get(0)) {
                    std::cout << "OK" << std::endl;
                }
                else {
                    std::cout << "NG" << std::endl;
                }

                if (ModInt(1) / ModInt(6) == coefTree.get(2)) {
					std::cout << "OK" << std::endl;
				}
                else {
					std::cout << "NG" << std::endl;
				}

                if (ModInt(1) / ModInt(2) == coefTree.get(4)) {
                    std::cout << "OK" << std::endl;
                }
                else {
                    std::cout << "NG" << std::endl;
                }

                if (ModInt(1) == coefTree.get(5)) {
                    std::cout << "OK" << std::endl;
                }
                else {
                    std::cout << "NG" << std::endl;
                }
            }
        };
	}
}

int main() {
	ABC::_332::F solver;
	solver.solve();
    //solver.check();

}