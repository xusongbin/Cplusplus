#include <iostream>
#include <stdlib.h>

#include "file_operation.h"

char file_user[] = ".\\data_user.txt";
char file_word[] = ".\\data_word.txt";
char file_score[] = ".\\data_score.txt";

struct s_file fdata;
struct s_file *data_p = &fdata;
char* key_argv[100];
char* dat_argv[100];

int file_parse(void)
{
	int row, idx, tmp;

	row = 0;
	idx = 0;
	key_argv[0] = &data_p->buff[0];
	while (1) {
		tmp = data_p->buff[idx];
		if (tmp == '\0') {
			break;
		}
		else if (tmp == ':') {
			data_p->buff[idx] = '\0';
			dat_argv[row] = &data_p->buff[idx + 1];
		}
		else if (tmp == '\n') {
			row++;
			if (row >= 100) {
				break;
			}
			data_p->buff[idx] = '\0';
			if (data_p->buff[idx + 1] == '\0') {
				break;
			}
			key_argv[row] = &data_p->buff[idx + 1];
		}
		idx++;
	}

	return row;
}

int file_read(char* file_name)
{
	FILE* fp;

	fopen_s(&fp, file_name, "r");
	if (fp == NULL) {
		printf("file: open %s error!", file_name);
		return 0;
	}
	data_p->len = fread(data_p->buff, sizeof(char), sizeof(data_p->buff), fp);
	fclose(fp);
	if (data_p->len <= 0) {
		return 0;
	}

	return file_parse();
}

bool file_write(char* file_name, int num)
{
	FILE* fp;
	int len, i;

	for (i = 0; i < num; i++) {
		len = strlen(key_argv[i]);
		key_argv[i][len] = ':';
		len = strlen(dat_argv[i]);
		dat_argv[i][len] = '\n';
	}
	data_p->len = strlen(data_p->buff);

	fopen_s(&fp, file_name, "w+");
	if (fp == NULL) {
		printf("file: open %s error!", file_name);
		return false;
	}
	len = fwrite(data_p->buff, sizeof(char), data_p->len, fp);
	fclose(fp);

	if (len == data_p->len) {
		return true;
	}

	return false;
}

bool file_login_check(struct s_user* udata)
{
	int row, idx;

	row = file_read(file_user);
	if (row == 0) {
		return false;
	}

	for (idx = 0; idx < row; idx++) {
		if (strcmp(key_argv[idx], udata->name) == 0 && strcmp(dat_argv[idx], udata->pwd) == 0) {
			return true;
		}
	}
	return false;
}

bool file_word_random(struct s_word* wdata)
{
	int row, idx, idy;
	int key[4];
	bool repet;

	row = file_read(file_word);
	if (row == 0) {
		return false;
	}

	for (idx = 0; idx < 4; idx++) {
		while (1) {
			key[idx] = rand() % row;
			repet = false;
			for (idy = 0; idy < idx; idy++) {
				if (key[idy] == key[idx]) {
					repet = true;
				}
			}
			if (repet) {
				continue;
			}
			else {
				break;
			}
		}
	}

	wdata->right = rand() % 4;
	strcpy_s(wdata->desc, dat_argv[key[wdata->right]]);
	strcpy_s(wdata->mix[0], key_argv[key[0]]);
	strcpy_s(wdata->mix[1], key_argv[key[1]]);
	strcpy_s(wdata->mix[2], key_argv[key[2]]);
	strcpy_s(wdata->mix[3], key_argv[key[3]]);

	return true;
}

bool file_score_write(struct s_score* sdata)
{
	int row, idx, ins, len;
	char buff[2048];

	row = file_read(file_score);

	ins = 0;
	for (idx = 0; idx < row; idx++) {
		if ( strlen(key_argv[idx]) == 0 ) {
			continue;
		}
		if (strcmp(key_argv[idx], sdata->name) == 0) {
			if (atoi(dat_argv[idx]) > sdata->pass) {
				ins = 10;
			}
			else {
				key_argv[idx][0] = '\0';
			}
		}
	}

	for (; ins < row; ins++) {
		if (strlen(key_argv[idx]) != 0 && sdata->pass >= atoi(dat_argv[ins])) {
			break;		// ins: insert index
		}
	}
	if (ins >= 10) {
		return true;	// out of ranking(0~9)
	}

	len = 0;
	for (idx = 0; idx < ins; idx++) {
		if (strlen(key_argv[idx]) == 0) {
			continue;
		}
		len += snprintf(&buff[len], sizeof(buff)- len, "%s:%s\n", key_argv[idx], dat_argv[idx]);
	}
	len += snprintf(&buff[len], sizeof(buff) - len, "%s:%d\n", sdata->name, sdata->pass);
	for (idx = ins; idx < row; idx++) {
		if (strlen(key_argv[idx]) == 0) {
			continue;
		}
		len += snprintf(&buff[len], sizeof(buff) - len, "%s:%s\n", key_argv[idx], dat_argv[idx]);
	}
	memcpy(data_p->buff, buff, strlen(buff));

	return file_write(file_score, file_parse());
}

bool file_score_read(char* sdata, int slen)
{
	int row, idx, len;

	row = file_read(file_score);
	if (row == 0) {
		return false;
	}

	len = 0;
	len += snprintf(&sdata[len], slen - len, "========================================\n");
	len += snprintf(&sdata[len], slen - len, "Ranking\t\tName\t\tScore\n");
	for (idx = 0; idx < row; idx++) {
		len += snprintf(&sdata[len], slen - len, "%d\t\t%s\t\t%s\n", idx+1, key_argv[idx], dat_argv[idx]);
	}

	return true;
}
