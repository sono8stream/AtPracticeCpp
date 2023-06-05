#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <time.h>

#define READ_INT(var) int var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;
#define long long long
#ifdef _DEBUG
#define debugOut(message){cout<<message<<endl;}
#else
#define debugOut(message){}
#endif

namespace ABC {
	namespace _267 {
		using namespace std;
		// 方針
		// Π(1+xy^(ai))の多項式の係数の復元問題に落とし込む
		// x=1, x=-1それぞれでNTTを行い、各係数を引いて2で割る

		// 原始根
		// 1<<20のpは7340033、w=5

        class Timer {
        private:
            clock_t _now;
            static Timer* _it;
            Timer():_now(clock()) {
            }

        public:
            static Timer& getInstance() {
                if (nullptr == _it) {
                    _it = new Timer();
                }

                return *_it;
            }

            void writeTime(const string& name) {
                clock_t current = clock();
                debugOut(name << " = +" << (double)(current - _now) << "msec.\n");
                _now = current;
            }
        };
        Timer* Timer::_it = nullptr;

        class CaseCalculator
        {

        private:
            long mask;
            vector<long> allPermutations;
            vector<long> allInverses;

        public:

            long multi(long left, long right)
            {
                long val = left % mask;
                val *= right % mask;
                val %= mask;
                return val;
            }

            void getAllPermutations(long n, vector<long>& vec)
            {
                vec = vector<long>(n + 1, 1);
                for (int i = 1; i <= n; i++)
                {
                    vec[i] = multi(vec[i - 1], i);
                }
            }

            void getAllInverses(long n, vector<long>& vec)
            {
                vector<long> inverses(n + 1, 0);
                inverses[1] = 1;
                vec = vector<long>(n + 1, 1);
                for (int i = 2; i <= n; i++)
                {
                    inverses[i] = mask - inverses[mask % i] * (mask / i) % mask;
                    vec[i] = multi(vec[i - 1], inverses[i]);
                }
            }

            CaseCalculator(long mask, long permutationCnt)
                :mask(mask)
            {
                getAllPermutations(permutationCnt, allPermutations);
                getAllInverses(permutationCnt, allInverses);
            }

            long getCombination(long n, long m)
            {
                if (n < m) {
                    return 0;
                }

                if (n - m < m) {
                    m = n - m;
                }
                return multi(multi(allPermutations[n], allInverses[n - m]), allInverses[m]);
            }

            long getPermutation(long n, long m)
            {
                if (n < m) {
                    return 0;
                }

                return multi(allPermutations[n], allInverses[n - m]);
            }

            long inverse(long val)
            {
                long a = mask;
                long b = val % mask;
                long x = 1;
                long x1 = 0;
                long y = 0;
                long y1 = 1;
                while (b > 0)
                {
                    long q = a / b;
                    long r = a % b;
                    long x2 = (mask + x - (q * x1) % mask) % mask;
                    long y2 = (mask + y - (q * y1) % mask) % mask;
                    a = b;
                    b = r;
                    x = x1;
                    x1 = x2;
                    y = y1;
                    y1 = y2;
                }
                return y;
            }
        };

        // 高速数論変換クラス
        class FNTT {
        public:

            int n;
            int p;
            int g;
            int nInv;
            vector<int> bitReversals;
            vector<int> roots;

            // 受け取った値以上となる2のべき乗を計算
            // 計算の都合で最低値は2
            static int toPowerOf2(int n) {
                int val = 1;
                while (val < n) {
                    val *= 2;
                }

                return val;
            }

            // ビットを左→右から右→左に読むように変換
            // 例) 011 -> 110, 110 -> 011
            void initBitReversals() {
                bitReversals = vector<int>(n, 0);
                int d = n / 2;
                for (int p = 1; p < n; p *= 2, d /= 2) {
                    for (int k = 0; k < p; k++) {
                        bitReversals[k | p] = bitReversals[k] | d;
                    }
                }
            }

            // valをmod pの条件でi乗する
            int modPow(int val, int i) const {
                long r = 1;
                long valL = val;
                for (; i > 0; valL = valL * valL % p, i /= 2) {
                    if ((i & 1) > 0) {
                        r = r * valL % p;
                    }
                }

                return static_cast<int>(r);
            }

            // n乗根の配列を取得
            void initRoots(int w) {
                roots = vector<int>(n / 2, 1);
                for (int k = 1; k < roots.size(); k++) {
                    long prev = roots[k - 1];
                    roots[k] = static_cast<int>(prev * w % p);
                }
            }

            FNTT(int length, int p, int g)
                :n(toPowerOf2(length)), p(p), g(g), nInv(modPow(n, p - 2))
            {
                initBitReversals();

                // p = a * n + 1として、gをa乗したものがN乗根となる
                // gの1乗はp-1乗根だが、これをa乗することでa個飛ばしでスキップできるイメージ
                initRoots(modPow(g, (p - 1) / n));
            }

            void transformAll(vector<int>& c) const {
                int mo = 998244353;
                int step = 1;
                int d = n / 2;

                while (step <= c.size() / 2) {
                    for (int i = 0; i < c.size(); i += step * 2) {
                        for (int j = 0; j < step; j++) {
                            long v0 = c[i + j];
                            long v1 = c[i + j + step];
                            v1 = v1 * roots[d * j] % mo;
                            c[i + j] = int((v0 + v1) % mo);
                            c[i + j + step] = int((v0 - v1 + mo) % mo);
                        }
                    }
                    step *= 2;
                    d /= 2;
                }
            }

            // 数論変換
            // cの長さはn以下とすること
            vector<int> transform(vector<int> c, bool rev = false) const {
                int currentN = toPowerOf2(c.size());
                while (c.size() < currentN) {
                    c.emplace_back(0);
                }

                // バタフライ演算のため、ビットを逆から見た場合のインデックスと入れ替えておく
                // 例）n=8の場合、0 4 2 6 1 5 3 7と並び替えられる
                Timer::getInstance().writeTime("start swap");
                int div = n / currentN;
                for (int k = 0; k < c.size(); k++) {
                    int reversal = bitReversals[k*div];
                    if (k < reversal) {
                        swap(c[k], c[reversal]);
                    }
                }
                Timer::getInstance().writeTime("end swap");

                transformAll(c);
                return c;
            }

            // 逆数論変換
            void transformInverse(vector<int>& c) const {
                c = transform(c);

                reverse(c.begin() + 1, c.end());
                long inv = n / c.size() * nInv % p;
                for (int k = 0; k < c.size(); k++) {
                    c[k] = static_cast<int>(c[k] * inv % p);
                }
            }

            // 高速化のために可能な限りvectorを使いまわす
            // vectorは値渡しすると各要素も値渡しになる
            void convolution(vector<vector<int>>& vals) const {

                while (vals.size() > 1) {
                    Timer::getInstance().writeTime("start init");

                    sort(vals.begin(), vals.end(), [](auto const& lhs, auto const& rhs) {
                        return lhs.size() < rhs.size();
                        });

                    int leftSize = vals[0].size();
                    int rightSize = vals[1].size();

                    while (leftSize > 0 && vals[0][leftSize - 1] == 0) {
                        leftSize--;
                    }
                    while (rightSize > 0 && vals[1][rightSize - 1] == 0) {
                        rightSize--;
                    }

                    int size = toPowerOf2(leftSize + rightSize - 1);
                    while (vals[0].size() < size) {
                        vals[0].emplace_back(0);
                    }
                    while (vals[1].size() < size) {
                        vals[1].emplace_back(0);
                    }

                    Timer::getInstance().writeTime("end init");

                    // 数論変換
                    vals[0] = transform(vals[0]);
                    Timer::getInstance().writeTime("end ntt for" + to_string(vals[0].size()));
                    vals[1]=transform(vals[1]);
                    Timer::getInstance().writeTime("end ntt for" + to_string(vals[1].size()));

                    // 数論変換後の積を計算
                    for (int k = 0; k < vals[0].size(); k++) {
                        long val = vals[0][k];
                        val = val * vals[1][k] % p;
                        vals[0][k] = val;
                    }

                    // 逆数論変換
                    transformInverse(vals[0]);
                    vals.erase(vals.begin() + 1);

                     Timer::getInstance().writeTime("end multiply");
                }
            }

            vector<int> convolution(vector<int> a,vector<int> b) const {
                vector<vector<int>> vals;
                vals.emplace_back(a);
                vals.emplace_back(b);
                convolution(vals);
                return vals[0];
            }
        };

        class Ex {
        public:
            static void getSampleInput(int& n, int& m, vector<int>& arr) {
                n = 100000;
                m = 11 * n / 4;

                arr = vector<int>(n);
                for (int i = 0; i < n; i++) {
                    arr[i] = i * 10 / n + 1;
                }
            }

            static void solve() {
                READ_INT(n);
                READ_INT(m);
                READ_INT_ARRAY(arr, n);

                //getSampleInput(n, m, arr);

                vector<vector<int>> cnts(11, vector<int>(3, 0));
                for (int i = 0; i <= 10; i++) {
                    cnts[i][2] = i;
                }
                int sum = 0;
                for (int i = 0; i < n; i++) {
                    cnts[arr[i]][0] += arr[i];
                    cnts[arr[i]][1]++;
                    sum += arr[i];
                }
                sort(cnts.begin(), cnts.end(), [](auto const& lhs, auto const& rhs) {
                    return lhs[0] < rhs[0];
                    });

                long mo = 998244353;
                long g = 3;

                CaseCalculator calculator(mo, sum + 10);
                FNTT fntt(sum + 10, mo, g);

                vector<vector<int>> coefs(2);
                coefs[0].emplace_back(1);
                coefs[1].emplace_back(0);
                for (int i = 1; i <= 10; i++) {
                    vector<vector<int>> coefs2(2);
                    coefs2[0].resize(cnts[i][0] + 1);
                    coefs2[1].resize(cnts[i][0] + 1);
                    for (int j = 0; j <= cnts[i][1]; j++) {
                        int comb = calculator.getCombination(cnts[i][1], j);
                        if (j % 2 == 0) {
                            coefs2[0][cnts[i][2] * j] = comb;
                        }
                        else {
                            coefs2[1][cnts[i][2] * j] = comb;
                        }
                    }

                    Timer::getInstance().writeTime("start multi");
                    vector<vector<int>> xs(4);
                    xs[0] = fntt.convolution(coefs[0], coefs2[0]);
                    xs[1] = fntt.convolution(coefs[1], coefs2[1]);
                    xs[2] = fntt.convolution(coefs[1], coefs2[0]);
                    xs[3] = fntt.convolution(coefs[0], coefs2[1]);
                    int ma = max({ xs[0].size(),xs[1].size(),xs[2].size(),xs[3].size() });

                    Timer::getInstance().writeTime("end multi");

                    coefs[0].resize(ma);
                    coefs[1].resize(ma);
                    for (int j = 0; j < ma; j++) {
                        coefs[0][j] = coefs[1][j] = 0;
                        if (j < xs[0].size()) coefs[0][j] += xs[0][j];
                        if (j < xs[1].size()) coefs[0][j] += xs[1][j];
                        if (j < xs[2].size()) coefs[1][j] += xs[2][j];
                        if (j < xs[3].size()) coefs[1][j] += xs[3][j];
                        coefs[0][j] %= mo;
                        coefs[1][j] %= mo;
                    }
                }

                if (m < coefs[1].size()) {
                    WRITE_LINE(coefs[1][m]);
                }
                else {
                    WRITE_LINE(0);
                }
            }
        };
	}
}

int main() {
	ABC::_267::Ex::solve();
}