#pragma once

struct s_file {
	int len;
	char buff[2048];
};

struct s_user {
	char name[20];
	char pwd[20];
};

struct s_word {
	char desc[100];
	char mix[4][9];
	int right;
};

struct s_score {
	int pass;
	char name[20];
};

bool file_login_check(struct s_user* udata);
bool file_word_random(struct s_word* wdata);
bool file_score_write(struct s_score* sdata);
bool file_score_read(char* sdata, int slen);
