#include <iostream>
#include <string>
#include <vector>

namespace ABC {
	namespace Library {
		using namespace std;

		template <int SIZE, class T>
		class SegmentTree {
		private:
			T tree[SIZE * 4];// �T�C�Y��(�w�肵�����ȏ��2�ׂ̂���)*2-1�����K�v�B����ȏ�ɂȂ邱�Ƃ͂Ȃ��B
			T exceptionVal;// �͈͊O�̒l
			int totalLength;

			typedef void (*MANIPULATOR)(const T& left, const T& right, T& dst);
			MANIPULATOR integrate;// ��������


		public:

			// �S�v�f���X�V����
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

			// i�Ԗڂ̗v�f���X�V����
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

			// i�Ԗڂ̗v�f���擾����
			T Look(int i)
			{
				return tree[i + totalLength - 1];
			}

			/// <summary>
			/// [left, right]��[top,last]�ƈ�v���Ă���΂��̒l���C�����łȂ���Γ������ĕԂ�
			/// �ċA����
			/// ���E�̈Ⴂ���C�ɂ���
			/// </summary>
			/// <param name="left">�z�񒆂�Scan���������[�C���f�b�N�X</param>
			/// <param name="right">�z�񒆂�Scan�������E�[�C���f�b�N�X</param>
			/// <param name="i">���݌��Ă���c���[���̗v�f�̃C���f�b�N�X</param>
			/// <param name="top">���݌��Ă���c���[���̗v�f���J�o�[����z�񒆂̍��[�C���f�b�N�X</param>
			/// <param name="last">���݌��Ă���c���[���̗v�f���J�o�[����z�񒆂̉E�[�C���f�b�N�X</param>
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

					if (right <= half)// �����ɕ����������ɍ���������΂����Ȃ�q�v�f�ɔC����
					{
						Query(dst, left, right, i * 2 + 1, top, half);
						return;
					}
					if (left > half)// �����ɕ����������ɉE��������΂����Ȃ�q�v�f�ɔC����
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
			/// [left, right]���擾
			/// </summary>
			/// <param name="left">���[</param>
			/// <param name="right">�E�[�i���E���܂ށj</param>
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