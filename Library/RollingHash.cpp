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
				// ���͈ȉ����Ƃ�B1�̊��ɂ��A�n�b�V���l�̏Փˊm����(1-(N-1))/p�iN�͑Ώۂ̕�����̒����Bp�͊��̃T�C�Y�j�炵���B�v�׋��B
				static const int mods[BASE_COUNT] = { 998244353, 1000000007, 1000000009, 1000000021, 1000000033 };
				return mods;
			}

			static const int* getBases() {
				// �O�̂��߃A���t�@�x�b�g�̌����͑傫�Ȓl�Ƃ��Ă����B�Ȃ�ł��̐��ŗǂ��̂��͒ǂ��ĕ׋��B
				static const int bases[BASE_COUNT] = { 31, 37, 41, 43, 47 };
				return bases;
			}

		public:

			int hashs[BASE_COUNT];// �n�b�V���l
			int pows[BASE_COUNT];// �����ɉ������ׂ����ێ����Ă����B

			RollingHash() {
				for (int i = 0; i < BASE_COUNT; i++) {
					this->hashs[i] = 0;
					this->pows[i] = 1;
				}
			}

			// �R�s�[�R���X�g���N�^
			RollingHash(const RollingHash& another) {
				for (int i = 0; i < BASE_COUNT; i++) {
					this->hashs[i] = another.hashs[i];
					this->pows[i] = another.pows[i];
				}
			}

			RollingHash(int c) {
				const int* mods = getMods();
				const int* bases = getBases();

				// 1�����̏ꍇ�̃n�b�V��������Ă����B
				for (int i = 0; i < BASE_COUNT; i++) {
					this->hashs[i] = c % mods[i];
					this->pows[i] = bases[i];
				}
			}

			// ��r���Z�q
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
					// �I�[�o�[�t���[���Ȃ��悤�A�ŏ��Ɍv�Z����l��long�ɃL���X�g���Ă����B
					// �ŏ��̂��̂łȂ���΃I�[�o�[�t���[����B�ŏ��ɃI�[�o�[�t���[���₷���|���Z�̓���1LL�����Ă����̂��ǂ����낤�B
					dst.hashs[i] = (left.hashs[i] + 1LL * right.hashs[i] * left.pows[i]) % mods[i];
					dst.pows[i] = 1LL * left.pows[i] * right.pows[i] % mods[i];
				}
			}
		};
	}
}