#include <iostream>
#include <string>
#include <vector>
#include <queue>

namespace ABC {
	namespace Library {
		using namespace std;

        class CaseCalculator
        {

        private:
            long mask;
            vector<long> allPermutations;
            vector<long> allInverses;

        public:

            long multi(long left,long right)
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
	}
}