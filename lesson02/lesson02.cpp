
#include <iostream>
#include <time.h>

#include "file_operation.h"

bool exercises_task(struct s_word* word, int num)
{
    char character;

    printf("%d、根据语义选择成语：%s\n", num+1, word->desc);
    printf("A：%s\tB：%s\tC：%s\tD：%s\n", word->mix[0], word->mix[1], word->mix[2], word->mix[3]);
    printf("请输入正确答案：\n");
    while (1) {
        scanf_s("%c", &character, 1);
        if (character == '\n') {
            continue;
        }
        if (character < 'A' || character > 'D') {
            printf("输入错误，请输入A~D：\n");
            continue;
        }
        if (character == ('A' + word->right)) {
            printf("答题正确\n");
            return true;
        }
        else {
            break;
        }
    }
    printf("答题错误\n");

    return false;
}

int main()
{
    struct s_word word;
    struct s_user user;
    struct s_score score;
    int status = 0;
    int topic_idx;

    srand((unsigned)time(NULL));

    while (1) {
        switch (status) {
            case 0:
                printf("username:");
                scanf_s("%s", user.name, sizeof(user.name));
                printf("password:");
                scanf_s("%s", user.pwd, sizeof(user.pwd));
                if (file_login_check(&user)) {
                    printf("welcome:%s\n", user.name);
                    topic_idx = 0;
                    score.pass = 0;
                    strcpy_s(score.name, user.name);
                    status = 1;
                }
                else {
                    system("cls");
                    printf("User or pwd error!\n");
                }
                break;
            case 1:
                file_word_random(&word);
                if (exercises_task(&word, topic_idx) == true) {
                    score.pass++;
                }
                topic_idx++;
                if (topic_idx >= 10) {
                    status = 2;
                    file_score_write(&score);
                }
                break;
            case 2:
                char rank[1024] = {0};
                file_score_read(rank, sizeof(rank));
                printf("%s", rank);
                status = 0;
                break;
        }
    }
}


