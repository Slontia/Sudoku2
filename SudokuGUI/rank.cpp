#include "rank.h"
#include <malloc.h>
//#include <iostream>

//using namespace std;

int Rank::fetch_rank(int mode, int r_lower, int r_upper, char* names[], double times[]) {
	int ranking = 0;
	int index = board.list[mode].used_head;
	int counter = 0;
	while (index != -1) {
		ranking++;
		rank_entry* entry = &board.list[mode].entry[index];
		if (r_lower <= ranking && r_upper >= ranking) {
			times[counter] = entry->time;
			names[counter] = (char*)malloc(sizeof(char) * NAMESIZE);
			strcpy_s(names[counter], NAMESIZE, entry->name);
			counter++;
		}
		index = entry->next;
	}

	for (int i = 0; i < counter; i++) {
		for (int j = 0; j < counter - i - 1; j++) {
			double time_temp;
			char* name_temp;
			if (times[j] > times[j + 1]) {
				time_temp = times[j];
				times[j] = times[j + 1];
				times[j + 1] = time_temp;
				name_temp = names[j];
				names[j] = names[j + 1];
				names[j + 1] = name_temp;
			}
		}
	}

	return counter;
	//return 0;
}

Rank::Rank() {
	fopen_s(&dbfile, DBFILE, "rb+");
	if (dbfile == NULL) {
		cout << "init new" << endl;
		init_db();
	}
	else {
		load_db(ENCRYPT);
		if (board.magic != MAGIC) {
			fclose(dbfile);
			init_db();
		}
	}
}

Rank::~Rank() {
	encrypt_flush(ENCRYPT);
	fclose(dbfile);
}

void Rank::init_db() {
	fopen_s(&dbfile, DBFILE, "wb+");
	if (dbfile) {
		init_board();
		encrypt_flush(ENCRYPT);
	}
	else {
		cout << "Open " << DBFILE << " failed" << endl;
	}
}

void Rank::init_board() {
	board.magic = MAGIC;
	// init heads
	for (int mode = 0; mode < MODE_COUNT; mode++) {
		board.list[mode].used_head = NIL;
		board.list[mode].free_head = 0;
		int entry_index = board.list[mode].free_head;
		for (; entry_index <= ENTRYSIZE - 2; entry_index++) {
			board.list[mode].entry[entry_index].next = entry_index + 1;
			// link up the list of free entries
		}
		board.list[mode].entry[entry_index].next = NIL;
		// tail to be nil
	}
}

bool Rank::encrypt_flush(bool encrypt) {
	if (encrypt == true) {
		//TODO: implement encryption
	}
	fseek(dbfile, 0, SEEK_SET);
	if (fwrite(&board, sizeof(board), 1, dbfile) != 1) {
		cout << "fwrite failed" << endl;
		return false;
	}
	fflush(dbfile);
	return true;
}

void Rank::load_db(bool encrypt) {
	fseek(dbfile, 0, SEEK_SET);
	fread(&board, sizeof(board), 1, dbfile);
	cout << "magic:" << hex << board.magic << dec << endl;
}

bool Rank::record(int mode, double time, char* name) {
	int index = board.list[mode].used_head;
	int next_index = -1;
	int free_index = -2;
	//cout << "inserting " << name << endl;
	if (fetch_free(mode, free_index, time) == false) {
		return false;
	}
	if (strlen(name) + 1 > NAMESIZE) {
		cout << "name too long" << endl;
		return false;
	}

	ptr_last_record = &board.list[mode].entry[free_index];
	if (board.list[mode].used_head == NIL) {
		board.list[mode].entry[free_index].next = board.list[mode].used_head;
		board.list[mode].used_head = free_index;
		board.list[mode].entry[free_index].time = time;
		strcpy_s(board.list[mode].entry[free_index].name, name);
		//cout << "inserted: " << name << endl;
		return true;
	}
	else {
		if (time < board.list[mode].entry[board.list[mode].used_head].time) {
			board.list[mode].entry[free_index].next = board.list[mode].used_head;
			board.list[mode].used_head = free_index;
			board.list[mode].entry[free_index].time = time;
			strcpy_s(board.list[mode].entry[free_index].name, name);
			//cout << "inserted: " << name << endl;
			return true;
		}
		else {
			while (true) {
				//cout << "while" << endl;
				rank_entry* entry = &board.list[mode].entry[index];
				next_index = entry->next;
				rank_entry* next_entry = &board.list[mode].entry[next_index];
				if ((next_index == -1) || (time < next_entry->time)) {
					board.list[mode].entry[free_index].time = time;
					strcpy_s(board.list[mode].entry[free_index].name,
						sizeof(board.list[mode].entry[free_index].name), name);
					insert_after(mode, index, free_index);
					//cout << "inserted: " << name << endl;
					return true;
				}
				index = next_index;
			}
		}
	}
}

bool Rank::fetch_rank(int mode, int r, char * name, double & time)
{
	int ranking = 0;
	int index = board.list[mode].used_head;
	while (index != -1) {
		ranking++;
		rank_entry* entry = &board.list[mode].entry[index];
		if (r == ranking) {
			time = entry->time;
			strcpy_s(name, NAMESIZE, entry->name);
			return true;
		}
		index = entry->next;
	}
	cout << "beyond ranking range. " << endl;
	return false;
}

bool Rank::clear()
{
	init_board();
	return true;
}

bool Rank::fetch_last_record(char * name, double & time)
{
	if (ptr_last_record == NULL) {
		return false;
	}
	else {
		strcpy_s(name, NAMESIZE, ptr_last_record->name);
		time = ptr_last_record->time;
		return true;
	}

}

bool Rank::fetch_free(int mode, int & index, double time) {
	//cout << "free_count : " << --free_count << endl;
	if (board.list[mode].free_head == NIL) {
		//cout << "No free entry." << endl;
		// abandon the tail
		int traverse_index = board.list[mode].used_head;
		int next_index = traverse_index;
		rank_entry* last_entry = NULL, *entry = NULL;
		do {
			//cout << "travese_index:" << traverse_index << endl;
			traverse_index = next_index;
			last_entry = entry;
			entry = &board.list[mode].entry[traverse_index];
			next_index = entry->next;

		} while (next_index != NIL);
		if (time < last_entry->time) {
			last_entry->next = NIL;
			index = traverse_index;
			return true;
		}
		else {
			return false;
		}

	}
	else {
		index = board.list[mode].free_head;
		//cout << "free_count : " << --free_count << endl;
		board.list[mode].free_head = board.list[mode].entry[index].next;
		return true;
	}
}

bool Rank::insert_after(int mode, int tg_id, int new_id) {
	rank_entry* tg_entry = &board.list[mode].entry[tg_id];
	rank_entry* new_entry = &board.list[mode].entry[new_id];
	new_entry->next = tg_entry->next;
	tg_entry->next = new_id;
	return true;
}

bool Rank::show(int mode) {
	int index = board.list[mode].used_head;
	//cout << "show " << mode << endl;
	while (index != -1) {
		rank_entry* entry = &board.list[mode].entry[index];
		printf("%s %lf\n", entry->name, entry->time);
		index = entry->next;
	}
	return true;
}