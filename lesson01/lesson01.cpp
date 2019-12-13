// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// 输出题目内容并返回题目答案
int show_question(int difficulty, int question_idx)
{
	int a=0, b=0, c=0, sign=0, ret=0;
	char sign_char=0;

	// 根据不同的题目难度随机出题
	if (difficulty == 1) {
		// 一年级：两位数以内的加减，并且计算结果没有负数。
		sign = rand() % 2;		// 0~1表示加减
		a = rand() % 100;			// 取两位以内的整数
		b = rand() % 100;			// 取两位以内的整数
		// 加法不做限制
		if (sign == 1 && a < b) {
			// 减法：被减数小于减数，交换减数与被减数的位置
			c = a;
			a = b;
			b = c;
		}
	}
	else if (difficulty == 2) {
		// 二年级：两位数以内的加减乘除，并且计算结果没有负数没有小数。
		sign = rand() % 4;		// 0~3表示加减乘除
		a = rand() % 100;			// 取两位以内的整数
		b = rand() % 100;			// 取两位以内的整数
		// 加法不做限制
		if (sign == 1 && a < b) {
			// 减法：被减数小于减数，交换减数与被减数的位置
			c = a;
			a = b;
			b = c;
		}
		else if (sign == 2 && a >= 10 && b >= 10) {
			// 乘法：乘数与被乘数同时大于两位数时，重新获取乘数
			b = rand() % 10;		// 重新取乘数为个位数
		}
		else if (sign == 3) {
			// 除法：除数不为0，此处重新获取个位数的除数
			b = rand() % 9 + 1;	// 取0~8然后+1等于取1~9
			a = rand() % 100 * b;	// 重新取被除数的值等于除数乘以一个随机的两位数，这样避免了小数运算
			while (a > 99) {	// 被除数超过3位数则重新取被除数
				a = rand() % 100 * b;
			}
		}
	}
	else if (difficulty == 3) {
		// 三年级：四位数以内的加减乘除，并且计算结果没有负数没有小数。
		sign = rand() % 4;		// 0~3表示加减乘除
		a = rand() % 10000;		// 取四位以内的整数
		b = rand() % 10000;		// 取四位以内的整数
		// 加法
		if (sign == 1 && a < b) {
			// 减法：被减数小于减数，交换减数与被减数的位置
			c = a;
			a = b;
			b = c;
		}
		else if (sign == 2 && a >= 100 && b >= 100) {
			// 乘法：乘数与被乘数同时大于三位数时，重新获取乘数
			b = rand() % 10;		// 重新取乘数为个位数
		}
		else if (sign == 3) {
			// 除法：除数不为0，此处重新获取个位数的除数
			b = rand() % 9 + 1;		// 取0~8然后+1等于取1~9
			a = rand() % 1000 * b;	// 重新取被除数的值等于除数乘以一个随机的三位数，这样避免了小数运算
			while (a > 9999) {		// 被除数超过4位数则重新取被除数
				a = rand() % 1000 * b;
			}
		}
	}
	switch (sign) {
	case 0: {
		// 加法
		ret = a + b;
		sign_char = '+';
		break;
	}
	case 1: {
		// 减法
		ret = a - b;
		sign_char = '-';
		break;
	}
	case 2: {
		// 乘法
		ret = a * b;
		sign_char = '*';
		break;
	}
	case 3: {
		// 除法
		ret = a / b;
		sign_char = '/';
		break;
	}
	}
	printf("第%d题：%d%c%d=?\n", question_idx, a, sign_char, b);
	return ret;
}

// 打印提示信息，并返回键盘输入值
int show_info_and_get_input(const char* info)
{
	int input;
	char character;

	printf("请输入题目%s，并按回车确认（输入q返回主页，输入Q退出程序）。\n", info);
	if (scanf_s("%d", &input) == 1) {
		// 获取到1个数字
	}
	else if (scanf_s("%c", &character) == 1 && character == 'q') {
		// 获取到1个值且该值为q字符
		input = character;
	}
	else if (scanf_s("%c", &character) == 1 && character == 'Q') {
		// 获取到1个值且该值为q字符
		input = character;
	}
	return input;
}

// 打印提示信息，并返回键盘输入值
int show_tips_and_get_input(char num)
{
	int input;
	char character;

	switch(num) {
		case 0: {
			printf("请输入题目难度，并按回车确认（输入q返回主页，输入Q退出程序）。\n");
			break;
		}
		case 1: {
			printf("请输入题目数量，并按回车确认（输入q返回主页，输入Q退出程序）。\n");
			break;
		}
		case 2: {
			printf("请输入题目答案，并按回车确认（输入q返回主页，输入Q退出程序）。\n");
			break;
		}
	}
	if (scanf_s("%d", &input) == 1) {
		// 获取到1个数字
	}
	else if (scanf_s("%c", &character) == 1 && character == 'q') {
		// 获取到1个值且该值为q字符
		input = character;
	}
	else if (scanf_s("%c", &character) == 1 && character == 'Q') {
		// 获取到1个值且该值为q字符
		input = character;
	}
	return input;
}

int main()
{
	int user_input = 'q';		// 用户输入变量
	int user_difficulty = 0;	// 用户选择的难度
	int user_questions = 0;		// 用户选择的题目数量
	int user_question_idx = 0;	// 当前题目序号
	int user_workout = 0;		// 用户计算的答案总数量
	int user_conrrect = 0;		// 用户计算的答案正确数量
	int question_max = 10;		// 用户可输入的最大题目数量，最大数量不超过int正整数最大值
	int question_answer;

	srand(time(NULL));			// 设置随机数种子，方式每次打开程序的随机数都是固定的

	while (1)
	{
		if (user_input == 'Q') {
			break;
		}
		if (user_input == 'q') {
			if (user_difficulty == 0 || user_questions == 0) {
				// 用户未处于答题状态，提示用户选择
				printf("=====小学生口算表达式自动生成系统=====\n");
				printf("=====题目难度范围（1~3）=====\n");
				printf("=====题目数量范围（1~%d）=====\n", question_max);
				// user_input = show_info_and_get_input("难度");
				user_input = show_tips_and_get_input(0);	// 难度
			}else {
				// 用户答题结束
				// 计算正确率
				printf("\n\n");
				printf("答题结束\n");
				printf("题目难度：%d\n", user_difficulty);
				printf("题目总数量：%d\n", user_questions);
				printf("用户完成答题数量：%d\n", user_workout);
				printf("用户答题正确数量：%d\n", user_conrrect);
				printf("用户答题的正确率：%d%%\n", user_conrrect * 100 / user_workout);
				printf("\n\n");
				// 用户答题中途退出复位程序状态
				user_difficulty = 0;
				user_questions = 0;
				user_input = 'q';
			}
		}
		else if (user_difficulty == 0) {
			// 分析用户输入数据是否为合法的难度信息
			if (user_input < 1 || user_input > 3) {
				// 用户输入异常，提示输入错误，并重新提示输入难度
				printf("请输入正确的难度范围\n");
				// user_input = show_info_and_get_input("难度");
				user_input = show_tips_and_get_input(0);	// 难度
			}
			else {
				// 用户输入正确，修改user_difficulty值，并提示输入题目数量
				user_difficulty = user_input;
				// user_input = show_info_and_get_input("数量");
				user_input = show_tips_and_get_input(1);	// 数量
			}
		}
		else {
			if (user_questions == 0) {
				// 分析用户输入数据是否为合法的数量信息
				if (user_input < 1 || user_input > question_max) {
					printf("请输入正确的题目数量范围\n");
					// user_input = show_info_and_get_input("数量");
					user_input = show_tips_and_get_input(1);	// 数量
				}
				else {
					// 用户输入正确，修改user_questions值，并提示输入题目数量
					user_questions = user_input;
					// 用户已选择完题目难度和数量，复位当前题目序号和答题统计信息，并开始出题
					user_workout = 0;
					user_conrrect = 0;
					user_question_idx = 1;

					question_answer = show_question(user_difficulty, user_question_idx);
					// user_input = show_info_and_get_input("答案");
					user_input = show_tips_and_get_input(2);	// 答案
				}
			}
			else {
				// 用户处于答题阶段并输入了答案
				user_workout++;		// 用户答题数+1
				if (user_input == question_answer) {
					user_conrrect++;	// 用户答题正确数+1
					printf("答题正确！\n");
				}
				else {
					printf("答题错误！正确答案为：%d\n", question_answer);
				}
				if (user_workout >= user_questions) {
					// 用户已完成所有题目
					user_input = 'q';		// 这里取巧，直接赋值q给用户输入变量，程序循环一圈判断答题结束，避免重复代码
				}
				else {
					user_question_idx++;
					question_answer = show_question(user_difficulty, user_question_idx);
					// user_input = show_info_and_get_input("答案");
					user_input = show_tips_and_get_input(2);	// 答案
				}
			}
		}
	}
	return 0;
}
