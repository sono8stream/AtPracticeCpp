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
		// 方針
		// ロリハを左から見た場合と右から見た場合でそれぞれ構築しておく

		class RollingHash {
		private:
			static const int BASE_COUNT = 5;

			static const long* getMods() {
				// 基底は以下をとる。1つの基底につき、ハッシュ値の衝突確率は(1-(N-1))/p（Nは対象の文字列の長さ。pは基底のサイズ）らしい。要勉強。
				static const long mods[BASE_COUNT] = { 998244353, 1000000007, 1000000009, 1000000021, 1000000033 };
				return mods;
			}

			static const long* getBases() {
				// 念のためアルファベットの個数よりは大きな値としておく。なんでこの数で良いのかは追って勉強。
				static const long mods[BASE_COUNT] = { 31, 37, 41, 43, 47 };
				return mods;
			}

		public:

			long leftHashs[BASE_COUNT];// ハッシュ値
			long pows[BASE_COUNT];// 桁数に応じたべき乗を保持しておく。

			RollingHash() {
				for (int i = 0; i < BASE_COUNT; i++) {
					this->leftHashs[i] = 0;
					this->pows[i] = 1;
				}
			}

			// コピーコンストラクタ
			RollingHash(const RollingHash& another) {
				for (int i = 0; i < BASE_COUNT; i++) {
					this->leftHashs[i] = another.leftHashs[i];
					this->pows[i] = another.pows[i];
				}
			}

			RollingHash(int c) {
				const long* mods = getMods();
				const long* bases = getBases();

				// 1文字の場合のハッシュを取っておく。
				for (int i = 0; i < BASE_COUNT; i++) {
					this->leftHashs[i] = c % mods[i];

					this->pows[i] = bases[i];
				}
			}

			// 比較演算子
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

		// セグメンテーションツリーの構築
		template <int SIZE, class T>
		class SegmentTree {
		private:
			T tree[SIZE * 4];// サイズは(指定した数以上の2のべき乗)*2-1だけ必要。これ以上になることはない。
			T exceptionVal;// 範囲外の値
			int totalLength;
			int size;

			typedef void (*MANIPULATOR)(const T& left, const T& right, T& dst);
			MANIPULATOR integrate;// 統合処理


		public:

			// 全要素を更新する
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

			// i番目の要素を更新する
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

			// i番目の要素を取得する
			T Look(int i)
			{
				return tree[i + totalLength - 1];
			}

			/// <summary>
			/// [left, right]が[top,last]と一致していればその値を，そうでなければ統合して返す
			/// 再帰処理
			/// 左右の違いを気にする
			/// </summary>
			/// <param name="left">配列中のScanしたい左端インデックス</param>
			/// <param name="right">配列中のScanしたい右端インデックス</param>
			/// <param name="i">現在見ているツリー中の要素のインデックス</param>
			/// <param name="top">現在見ているツリー中の要素がカバーする配列中の左端インデックス</param>
			/// <param name="last">現在見ているツリー中の要素がカバーする配列中の右端インデックス</param>
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

					if (right <= half)// 半分に分割した時に左だけ見ればいいなら子要素に任せる
					{
						Query(dst, left, right, i * 2 + 1, top, half);
						return;
					}
					if (left > half)// 半分に分割した時に右だけ見ればいいなら子要素に任せる
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
			/// [left, right]を取得
			/// </summary>
			/// <param name="left">左端</param>
			/// <param name="right">右端（境界を含む）</param>
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
				// サイズが大きいのでグローバルに確保
				static SegmentTree<N_MAX, RollingHash> leftTree(RollingHash(1), RollingHash(), RollingHash::integrate);
				static SegmentTree<N_MAX, RollingHash> rightTree(RollingHash(1), RollingHash(), RollingHash::integrate);

				READ_INT(n);
				READ_INT(q);

				READ_STR(str);

				// ハッシュの取得
				for (int i = 0; i < n; i++) {
					leftTree.update(i, RollingHash(str[i] - 'a' + 1));
					rightTree.update(n - i - 1, RollingHash(str[i] - 'a' + 1));
				}

				for (int i = 0; i < q; i++) {
					READ_INT(mode);
					if (mode == 1) {
						// 文字の置換
						READ_INT(pos);
						READ_STR(c);
						leftTree.update(pos - 1, RollingHash(c[0] - 'a' + 1));
						rightTree.update(n - pos, RollingHash(c[0] - 'a' + 1));
					}
					else if (mode == 2) {
						// 回文判定
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