#include <iostream>
#include <string>
#include <vector>

namespace ABC {
	namespace Library {
		using namespace std;

		class RollingHash {
		private:
			static const int BASE_COUNT = 5;

			const long* getMods() {
				// 基底は以下をとる。1つの基底につき、ハッシュ値の衝突確率は(1-(N-1))/p（Nは対象の文字列の長さ。pは基底のサイズ）らしい。要勉強。
				static const long mods[BASE_COUNT] = { 998244353, 1000000007, 1000000009, 1000000021, 1000000033 };
				return mods;
			}

			const long* getBases() {
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

			RollingHash integrate(const RollingHash& another) {
				const long* mods = getMods();
				const long* bases = getBases();

				RollingHash res;
				for (int i = 0; i < BASE_COUNT; i++) {
					res.leftHashs[i] = (this->leftHashs[i] + another.leftHashs[i] * this->pows[i]) % mods[i];
					res.pows[i] = this->pows[i] * another.pows[i] % mods[i];
				}

				return res;
			}
		};
	}
}