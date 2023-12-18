#include <iostream>
#include <string>
#include <vector>

namespace ABC {
	namespace Library {
		using namespace std;

        template <int SIZE, class T>
        class LazySegmentTree {
        private:
            T tree[SIZE * 4];
            bool haveLazy[SIZE * 4];
            int totalLength;

            T exceptionVal;// 範囲外の値
            T initialVal;// 初期値

            // パラメータを更新する処理
            typedef void(*UPDATER)(const T& nextValue, T& target);
            UPDATER updater;

            // パラメータを深い層に伝播する処理
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

            // 遅延評価処理。深さの浅い方から深い方に向けて計算値を伝播しておく。
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

            // [left, right]が[top,last]と一致していればvalで更新，そうでなければ分割してUpdateを仕掛ける
            void updateQuery(int left, int right, int i, int top, int last, const T& val)
            {
                if (left == top && right == last)
                {
                    // 遅延セグ木なので、更新範囲ができるだけ広い状態で止めておくことで高速化。
                    haveLazy[i] = true;
                    updater(val, tree[i]);
                }
                else
                {
                    // 遅延評価し、より深い層に潜る。
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

            // [left, right]をvalで更新する
            void update(int left, int right, const T& val)
            {
                if (left < 0 || right >= totalLength || right < left)
                {
                    return;
                }

                updateQuery(left, right, 0, 0, totalLength - 1, val);
            }

            // 特定位置の値を取得するための再帰探索処理。遅延評価を行いながら深い層に潜っていく。
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

            // [left, right]の値を評価して取得する
            const T& get(int pos)
            {
                if (pos < 0 || pos >= totalLength)
                {
                    return exceptionVal;
                }

                return scanQuery(pos, 0, 0, totalLength - 1);
            }
        };
	}
}