#include <iostream>
#include <string>
#include <vector>

namespace ABC {
	namespace Library {
		using namespace std;

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
	}
}