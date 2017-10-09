#include "stdafx.h"

FgMap::FgMap(int unit_type, int unit_id) {
	id = unit_id;
	type = unit_type;
	clear();
}

FgMap::FgMap() {
	id = 0;
	type = 0;
	clear();
}

void FgMap::clear() {
	for (int index = 0; index < SIZE; index++) {
		map[index] = 0x1FF;
		pos_count[index] = 9;
	}
}



bool FgMap::inside_lock(int figure, int index, bool unlock) {
	// �ڵ�Ԫ��λ��Ϊindex(zero indexed)����һ��������
	// ��ɱ��������ֵ����п������Լ�������������λ�õĿ����ԡ�
	map[F2INDEX(figure)] &= 0;
	pos_count[F2INDEX(figure)] = 0;

	//cout << "inside_lock: " << endl;

	for (int figure_x = 1; figure_x <= 9; figure_x++) {
		lock(figure_x, index, unlock);
	}

	return true;
}

bool FgMap::lock(int figure_x, int index, bool unlock) {
	if (unlock == false) {
		if (map[F2INDEX(figure_x)] & INDEX2TARGETBIT(index)) {
			/*if (figure_x == 1) {
				cout << "	locked. figure_x: " << figure_x << endl;
				cout << "	id: " << id << endl;
				cout << "	type: " << type << endl;
				cout << "	index: " << index << endl;
				cout << endl;
			}*/

			//  ����ԭ�������������
			pos_count[F2INDEX(figure_x)]--;
			assert(pos_count[F2INDEX(figure_x)] > 0);
			map[F2INDEX(figure_x)] &= INDEX2MASK(index);
			assert(map[F2INDEX(figure_x)] != 0);
			return true;
		}
	}
	else {
		if ((~map[F2INDEX(figure_x)]) & INDEX2TARGETBIT(index)) {
			/*if (figure_x == 1) {
			cout << "	locked. figure_x: " << figure_x << endl;
			cout << "	id: " << id << endl;
			cout << "	type: " << type << endl;
			cout << "	index: " << index << endl;
			cout << endl;
			}*/

			//  ����ԭ������������Ѿ���ɾ���ˣ���ζ��ȡ���Ժ����λ��Ϊ 1
			pos_count[F2INDEX(figure_x)]++;
			assert(pos_count[F2INDEX(figure_x)] <= 9);
			map[F2INDEX(figure_x)] |= INDEX2MASK(index);
			assert(map[F2INDEX(figure_x)] != 0);
			return true;
		}
	}
	return false;
}

bool FgMap::outside_lock(int figure, int i, int j, bool unlock) {
	// ����������±�Ϊ (i,j) (zero-indexed) ��λ��������һ����
	// ��ʹ��һ����Ԫ�У���Ӧ�����ֲ�����֮������ͻ���Ӷ�������ĳЩ������
	for (int _index = 0; _index < 9; _index++) {
		int x, y;
		//assert(index < 9);
		index2co(_index, x, y);
		if (SAMEGROUP(x, y, i, j) || (x == i) || (y == j)) {
			//cout << "outside lock, figure: " << figure << endl;
			lock(figure, _index, unlock);
		}
	}

	return true;
}

bool FgMap::get_decisive(int & figure, int &i, int &j) const{
	//cout << "type: " << type << endl;
	//cout << "min_map: " << min_map << endl;
	int min_index = 0;
	int min_count = INT32_MAX;
	for (int fig_index = 0; fig_index < SIZE; fig_index++) {
		if (pos_count[fig_index] != 0 && (pos_count[fig_index] < min_count)) {
			min_index = fig_index;
			min_count = pos_count[fig_index];
		}
	}
	if (min_count == 1) {
		figure = min_index + 1;
		index2co(get_one(map[min_index]), i, j);
		//cout << "decisive: " << "figure " << figure << "("
		//	<< i << "," << j << ")" << "index: " << min_index << endl;
	}
	return min_count == 1;
}

bool FgMap::index2co(int index, int & i, int & j) const{
	assert(index < 9);
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
	assert(i <= 8);
	assert(j <= 8);
	return true;
}
