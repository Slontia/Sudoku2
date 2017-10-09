// copyright Wang Chenyu, Liu Chang 2017

// TODO: ���һ�����ݽṹ������¼һ�����ӵ�����Լ��
// Լ�� (figure, x, y) ��һ����Ԫ��

// �ӿ�����ٶȣ����������ֱ�ͷ������Ⱥ

#pragma once
#include "stdafx.h"

using std::list;

struct constraint {
	int figure;
	int x;
	int y;
};

typedef list<constraint> linked;

class ConstraintTable {
private:
	linked linked_constr[SIZE];
	// ����Ⱥ�������±� i �е�Ԫ�ض��ǣ���������ֶ��� i + 1
public:
	bool add_constr(int fig, int x, int y);
	bool del_constr(int fig, int x, int y);
	void dump_constr(constraint constr[], int & num);
};