// kmjpさんのコードを試してみる
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <tuple>
#include <utility>
#include <time.h>

using namespace std;
typedef signed long long ll;

#define _P(...) (void)printf(__VA_ARGS__)
#define FOR(x,to) for(x=0;x<(to);x++)
#define FORR(x,arr) for(auto& x:arr)
#define FORR2(x,y,arr) for(auto& [x,y]:arr)
#define ALL(a) (a.begin()),(a.end())
#define ZERO(a) memset(a,0,sizeof(a))
#define MINUS(a) memset(a,0xff,sizeof(a))
template<class T> bool chmax(T& a, const T& b) { if (a < b) { a = b; return 1; }return 0; }
template<class T> bool chmin(T& a, const T& b) { if (a > b) { a = b; return 1; }return 0; }
#ifdef _DEBUG
#define debugOut(message){cout<<message<<endl;}
#else
#define debugOut(message){}
#endif
//-------------------------------------------------------


class Timer {
private:
	clock_t _now;
	static Timer* _it;
	Timer() :_now(clock()) {
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

int N, M, C[11];
const ll mo = 998244353;

ll modpow(ll a, ll n = mo - 2) {
	ll r = 1; a %= mo;
	while (n) r = r * ((n % 2) ? a : 1) % mo, a = a * a % mo, n >>= 1;
	return r;
}

void getSampleInput(int& n, int& m, vector<int>& arr) {
	n = 100000;
	m = 11 * n / 4;

	arr = vector<int>(n);
	for (int i = 0; i < n; i++) {
		arr[i] = i * 10 / n + 1;
	}
}

template <class T> using vec = vector<T>; //using vec=valarray<T>;

template<class T> vec<T> fft(vec<T> v, bool rev = false) {
	int n = v.size(), i, j, m;
	for (int m = n; m >= 2; m /= 2) {
		T wn = modpow(5, (mo - 1) / m);
		if (rev) wn = modpow(wn);
		for (i = 0; i < n; i += m) {
			T w = 1;
			for (int j1 = i, j2 = i + m / 2; j2 < i + m; j1++, j2++) {
				T t1 = v[j1], t2 = v[j2];
				v[j1] = t1 + t2;
				v[j2] = ll(t1 + mo - t2) * w % mo;
				while (v[j1] >= mo) v[j1] -= mo;
				w = (ll)w * wn % mo;
			}
		}
	}
	for (i = 0, j = 1; j < n - 1; j++) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (i > j) swap(v[i], v[j]);
	}
	if (rev) {
		ll rv = modpow(n);
		FOR(i, n) v[i] = (ll)v[i] * rv % mo;
	}
	return v;
}

template<class T> vec<T> MultPoly(vec<T> P, vec<T> Q, bool resize = false) {
	if (resize) {
		int maxind = 0, pi = 0, qi = 0, i;
		int s = 2;
		FOR(i, P.size()) if (P[i]!=0) pi = i;
		FOR(i, Q.size()) if (Q[i]!=0) qi = i;
		maxind = pi + qi + 1;
		while (s * 2 < maxind) s *= 2;

		if (s <= 16) { //fastpath
			vec<T> R(s * 2);
			for (int x = 0; x <= pi; x++) for (int y = 0; y <= qi; y++) (R[x + y] += P[x] * Q[y]) %= mo;
			return R;
		}
		vec<T> P2(s * 2), Q2(s * 2);
		FOR(i, pi + 1) P2[i] = P[i];
		FOR(i, qi + 1) Q2[i] = Q[i];
		swap(P, P2), swap(Q, Q2);
	}

	Timer::getInstance().writeTime("start ntt for" + to_string(P.size()));
	P = fft(P);
	Timer::getInstance().writeTime("end ntt for" + to_string(P.size()));
	Q = fft(Q);
	Timer::getInstance().writeTime("end ntt for" + to_string(Q.size()));

	for (int i = 0; i < P.size(); i++) P[i] = (ll)P[i] * Q[i] % mo;
	return fft(P, true);
}
ll comb(ll N_, ll C_) {
	const int NUM_ = 400001;
	static ll fact[NUM_ + 1], factr[NUM_ + 1], inv[NUM_ + 1];
	if (fact[0] == 0) {
		inv[1] = fact[0] = factr[0] = 1;
		for (int i = 2; i <= NUM_; ++i) inv[i] = inv[mo % i] * (mo - mo / i) % mo;
		for (int i = 1; i <= NUM_; ++i) fact[i] = fact[i - 1] * i % mo, factr[i] = factr[i - 1] * inv[i] % mo;
	}
	if (C_<0 || C_>N_) return 0;
	return factr[C_] * fact[N_] % mo * factr[N_ - C_] % mo;
}


void solve() {
	int i, j, k, l, r, x, y; string s;

	cin >> N >> M;
	vector<int> vals(N);
	FOR(i, N) {
		cin >> vals[i];
	}

	getSampleInput(N, M, vals);

	FOR(i, N) {
		C[vals[i]]++;
	}

	vector<pair<int, int>> V;
	for (i = 1; i <= 10; i++) V.push_back({ i * C[i] + 1,i });
	sort(ALL(V));
	vector<ll> A[2];
	A[0] = { 1 };
	A[1] = { 0 };
	for (auto& curPair : V) {
		int a = curPair.first;
		int i = curPair.second;
		if (a > 1) {
			vector<ll> B[2];
			B[0].resize(a);
			B[1].resize(a);
			FOR(j, C[i] + 1) {
				B[j & 1][i * j] = comb(C[i], j);
			}
			vector<ll> X[4];
			X[0] = MultPoly(A[0], B[0], 1);
			X[1] = MultPoly(A[1], B[1], 1);
			X[2] = MultPoly(A[1], B[0], 1);
			X[3] = MultPoly(A[0], B[1], 1);
			int ma = max({ X[0].size(),X[1].size(),X[2].size(),X[3].size() });
			A[0].resize(ma);
			A[1].resize(ma);
			FOR(j, ma) {
				A[0][j] = A[1][j] = 0;
				if (j < X[0].size()) A[0][j] += X[0][j];
				if (j < X[1].size()) A[0][j] += X[1][j];
				if (j < X[2].size()) A[1][j] += X[2][j];
				if (j < X[3].size()) A[1][j] += X[3][j];
				A[0][j] %= mo;
				A[1][j] %= mo;
			}
		}
	}
	if (M < A[1].size()) {
		cout << A[1][M] << endl;
	}
	else {
		cout << 0 << endl;
	}


}


int main(int argc, char** argv) {
	string s; int i;
	if (argc == 1) ios::sync_with_stdio(false), cin.tie(0);
	FOR(i, argc - 1) s += argv[i + 1], s += '\n'; FOR(i, s.size()) ungetc(s[s.size() - 1 - i], stdin);
	cout.tie(0); solve(); return 0;
}
