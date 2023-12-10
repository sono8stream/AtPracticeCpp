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
				// ���͈ȉ����Ƃ�B1�̊��ɂ��A�n�b�V���l�̏Փˊm����(1-(N-1))/p�iN�͑Ώۂ̕�����̒����Bp�͊��̃T�C�Y�j�炵���B�v�׋��B
				static const long mods[BASE_COUNT] = { 998244353, 1000000007, 1000000009, 1000000021, 1000000033 };
				return mods;
			}

			const long* getBases() {
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