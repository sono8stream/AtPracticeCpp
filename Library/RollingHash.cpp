#include <iostream>
#include <string>
#include <vector>

namespace ABC {
	namespace Library {
		using namespace std;

		class RollingHash {
		private:
			static const int BASE_COUNT = 5;

			static const int* getMods() {
				// 基底は以下をとる。1つの基底につき、ハッシュ値の衝突確率は(1-(N-1))/p（Nは対象の文字列の長さ。pは基底のサイズ）らしい。要勉強。
				static const int mods[BASE_COUNT] = { 998244353, 1000000007, 1000000009, 1000000021, 1000000033 };
				return mods;
			}

			static const int* getBases() {
				// 念のためアルファベットの個数よりは大きな値としておく。なんでこの数で良いのかは追って勉強。
				static const int bases[BASE_COUNT] = { 31, 37, 41, 43, 47 };
				return bases;
			}

		public:

			int hashs[BASE_COUNT];// ハッシュ値
			int pows[BASE_COUNT];// 桁数に応じたべき乗を保持しておく。

			RollingHash() {
				for (int i = 0; i < BASE_COUNT; i++) {
					this->hashs[i] = 0;
					this->pows[i] = 1;
				}
			}

			// コピーコンストラクタ
			RollingHash(const RollingHash& another) {
				for (int i = 0; i < BASE_COUNT; i++) {
					this->hashs[i] = another.hashs[i];
					this->pows[i] = another.pows[i];
				}
			}

			RollingHash(int c) {
				const int* mods = getMods();
				const int* bases = getBases();

				// 1文字の場合のハッシュを取っておく。
				for (int i = 0; i < BASE_COUNT; i++) {
					this->hashs[i] = c % mods[i];
					this->pows[i] = bases[i];
				}
			}

			// 比較演算子
			bool operator==(const RollingHash& another) const {
				bool res = true;
				for (int i = 0; i < BASE_COUNT; i++) {
					res &= this->hashs[i] == another.hashs[i];
				}
				return res;
			}

			static void integrate(const RollingHash& left, const RollingHash& right, RollingHash& dst) {
				const int* mods = getMods();

				for (int i = 0; i < BASE_COUNT; i++) {
					// オーバーフローしないよう、最初に計算する値をlongにキャストしておく。
					// 最初のものでなければオーバーフローする。最初にオーバーフローしやすい掛け算の頭に1LLをつけておくのが良いだろう。
					dst.hashs[i] = (left.hashs[i] + 1LL * right.hashs[i] * left.pows[i]) % mods[i];
					dst.pows[i] = 1LL * left.pows[i] * right.pows[i] % mods[i];
				}
			}
		};
	}
}