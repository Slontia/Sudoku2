// copyright Wang Chenyu, Liu Chang 2017
// ����ļ��ж����� FgMap���� figure-grid map
// ����������������¼ һ�� �� �� �� �� �� �����Ϊ��Ԫ�� �У����� 1-9 ��λ�� 1-9 �����п���ӳ��
// �Ӷ����������� f �� [1-9] ʹ��ӳ��Ψһȷ��ʱ �� �������һ�����ֵ�λ�õ��Ƶ�

#pragma once
#include "stdafx.h"
#define ROW 1
#define COLUMN 2
#define GROUP 3

#define F2INDEX(f) (f-1)
#define INDEX2MASK(I) (~(1 << (I)))
#define INDEX2TARGETBIT(I) (1 << (I))

#define SAMEGROUP(x,y,i,j) (((x)/3 == (i)/3) && ((y)/3 == (j)/3))

class FgMap {
private:
	int map[9] = { 0 } ;  // map[i] �� �� j �� bit Ϊ 1 ��ʾ���� i+1 ������� j ����
	int pos_count[9] = { 0 };   // pos_count[i] ��¼�� map[i] �����ж��ٸ� bit �� 1.
	int min_map_index = 0;  // ָ�� map �� 1 bit ���ٵģ��Ż��Ƶ�
	int min_map = INT32_MAX;
public:
	FgMap();
	int type = -1;  // ���л����л��ǹ��е�����-λ��ӳ��
	int id;  // �У����л򹬵���ţ������Ҵ��ϵ����� 0 ������

	bool inside_lock(int figure, int place);

	bool lock(int figure_x, int index);

	bool outside_lock(int figure, int i, int j);

	bool index2co(int index, int & i, int & j);

};