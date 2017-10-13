#include "stdafx.h"

int main() {
	Rank rank;
	char name[NAMESIZE];
	string rand_name;
	double time;

	rank.clear();
	int i = 0;
	for (double time = 1000; time > 0; time--, i++) {
		rand_name = "player " + std::to_string(i);
		strcpy_s(name, rand_name.c_str());
		rank.record(EASY, time, name);
	}

	i = 0;
	for (double time = 10000; time > 0; time--, i++) {
		rand_name = "player " + std::to_string(i);
		strcpy_s(name, rand_name.c_str());
		rank.record(MID, 0.5, name);
	}
	rank.record(MID, 0, "sucker");
	rank.encrypt_flush(ENCRYPT);
	rank.show(EASY);
	rank.show(MID);
	getchar();
	return 0;
}