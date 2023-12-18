#include <iostream>
#include <string>
#include <vector>

namespace ABC {
	namespace Library {
		using namespace std;

		template <int SIZE, class T>
		class SegmentTree {
		private:
			T tree[SIZE * 4];// サイズは(指定した数以上の2のべき乗)*2-1だけ必要。これ以上になることはない。
			T exceptionVal;// 範囲外の値
			int totalLength;

			typedef void (*MANIPULATOR)(const T& left, const T& right, T& dst);
			MANIPULATOR integrate;// 統合処理


		public:

			// 全要素を更新する
			void updateAll() {
				for (int i = totalLength - 2; i >= 0; i--) {
					integrate(tree[i * 2 + 1], tree[i * 2 + 2], tree[i]);
				}
			}

			SegmentTree(T initialVal, T exceptionVal, const MANIPULATOR& integrate) :integrate(integrate) {
				totalLength = 1;
				while (totalLength < SIZE)
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
				if (left >= SIZE || right < 0 || right < left)
				{
					dst = exceptionVal;
					return;
				}

				Query(dst, left, right, 0, 0, totalLength - 1);
			}
		};
	}
}