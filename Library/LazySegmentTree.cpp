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

            T exceptionVal;// �͈͊O�̒l
            T initialVal;// �����l

            // �p�����[�^���X�V���鏈��
            typedef void(*UPDATER)(const T& nextValue, T& target);
            UPDATER updater;

            // �p�����[�^��[���w�ɓ`�d���鏈��
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

            // �x���]�������B�[���̐󂢕�����[�����Ɍ����Čv�Z�l��`�d���Ă����B
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

            // [left, right]��[top,last]�ƈ�v���Ă����val�ōX�V�C�����łȂ���Ε�������Update���d�|����
            void updateQuery(int left, int right, int i, int top, int last, const T& val)
            {
                if (left == top && right == last)
                {
                    // �x���Z�O�؂Ȃ̂ŁA�X�V�͈͂��ł��邾���L����ԂŎ~�߂Ă������Ƃō������B
                    haveLazy[i] = true;
                    updater(val, tree[i]);
                }
                else
                {
                    // �x���]�����A���[���w�ɐ���B
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

            // [left, right]��val�ōX�V����
            void update(int left, int right, const T& val)
            {
                if (left < 0 || right >= totalLength || right < left)
                {
                    return;
                }

                updateQuery(left, right, 0, 0, totalLength - 1, val);
            }

            // ����ʒu�̒l���擾���邽�߂̍ċA�T�������B�x���]�����s���Ȃ���[���w�ɐ����Ă����B
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

            // [left, right]�̒l��]�����Ď擾����
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