#include "stdafx.h"

FgMap::FgMap(int unit_type, int unit_id) {
	id = unit_id;
	type = unit_type;
}

bool FgMap::inside_lock(int figure, int index) {
	// �ڵ�Ԫ��λ��Ϊindex(zero indexed)����һ��������
	// ��ɱ��������ֵ����п������Լ�������������λ�õĿ����ԡ�
	map[F2INDEX(figure)] &= 0;
	pos_count[F2INDEX(figure)] = 0;
	for (int figure_x = 1; figure_x <= 9; figure_x++) {
		lock(figure_x, index);
	}
	return true;
}

bool FgMap::lock(int figure_x, int index) {
	if (map[F2INDEX(figure_x)] & INDEX2TARGETBIT(index)) {
		//  ����ԭ�������������
		pos_count[F2INDEX(figure_x)]--;
		assert(pos_count[F2INDEX(figure_x)] >= 0);
		if ((pos_count[F2INDEX(figure_x)] <= min_map)
			&& pos_count[F2INDEX(figure_x)] >= 1) {
			// ������µ���С���Ҳ�Ϊ 0 �ֿ���
			min_map_index = F2INDEX(figure_x);
			// ������С���±�
			min_map = pos_count[F2INDEX(figure_x)];
			// ������С��ֵ
		}
		map[F2INDEX(figure_x)] &= INDEX2MASK(index);
	}
	return true;
}

bool FgMap::outside_lock(int figure, int i, int j) {
	// ����������±�Ϊ (i,j) (zero-indexed) ��λ��������һ����
	// ��ʹ��һ����Ԫ�У���Ӧ�����ֲ�����֮������ͻ���Ӷ�������ĳЩ������
	for (int index = 0; index < 9; index++) {
		int x, y;
		index2co(index, x, y);
		if (SAMEGROUP(x, y, i, j) || (x == i) || (y == j)) {
			lock(figure, index);
		}
	}

	return true;
}

bool FgMap::index2co(int index, int & i, int & j) {
	// ����Ԫ�ڲ������ת��Ϊ������������
	int base_x, base_y;
	switch (type) {
	case ROW:
		i = id;
		j = index;
		break;
	case COLUMN:
		i = index;
		j = id;
		break;
	case GROUP:
		base_x = (id / 3) * 3;
		base_y = (id % 3) * 3;
		i = base_x + index / 3;
		j = base_y + index % 3;
		break;
	default:
		return false;
	}
	return true;
}