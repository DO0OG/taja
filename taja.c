#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <process.h>

const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int WHITE = 7;
const int GRAY = 8;
const int DARK_GRAY = 15;
int i, j;
int score = 0, correct = 0, wrong = 0, left = 0, p, z, cg, tp, accu;

clock_t start, end;
	
void gotoXY(int, int);
void Box(int, int, int, int, int);
void disp(int, int, int);
int mainMenu();
int letter(char);
int e_letter(char);
int k_letter(char);
int word(char);
int e_word(char);
int k_word(char);
int s_text(char);
int e_s_text(char);
int k_s_text(char);
int record(char);
int choose(char);
int endpg(char, int, int, int, int); 

void Box(int x1, int y1, int x2, int y2, int COLOR) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
	
	// ��� (����������)
	gotoXY(x1, y1); printf("��");
	for (i=1; i<(x2 - x1) - 1; i++) printf("��"); 
	printf("��");

	// �ߴ� (��   ��)
	for (i=1; i<(y2 - y1); i++) {
		gotoXY(x1, y1 + i); printf("��");
		gotoXY(x2 - 1, y1 + i); printf("��");
	}

	// �ϴ� (����������)
	gotoXY(x1, y2); printf("��");
	for (i=1; i<(x2 - x1) - 1; i++) printf("��");
	printf("��");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}
void disp(int left, int correct, int wrong) {
	gotoXY(42, 5); printf("Ÿ�̸� : %04d		���� ���� : %3d", (int)start/CLOCKS_PER_SEC, left);
	gotoXY(48, 7); printf("���� : %3d	���� : %3d", correct, wrong);
	gotoXY(15, 25);
}

int letter(char type){
	char c = 0, now = 0; 
	const int y[] = { 18, 20, 22};
	const int x1 = 51, x2 = 67;

	system("cls");

	gotoXY(53, 4); printf("��  ��  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(75, 28); puts("����Ű�� Ŀ���� �̵�, ���ͷ� �����ϼ���.");

	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(x1, y[now]); printf("��");
		gotoXY(x2, y[now]); printf("��");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(48, 9); puts("���� �� �� �����ϼ���.");
		Box(20, 8, 100, 10, WHITE);
		
		if (now == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 6, y[0]); printf("��  ��");
		
		if (now == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 6, y[1]); printf("��  ��");

		if (now == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[2]); printf("�ڷΰ���");
		Box(46, 17, 73, 23, WHITE);
		puts(" ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

		c = _getch();
		if (c == 0x00 || c == 0xE0) c = _getch();
		if (c == 80 || c == 72) {
			switch (c) {
				// UP
				case 72: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now > 0) now--;
					else if (now == 0) now = 2;
					break;
				}
				// DOWN
				case 80: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now < 2) now++;
					else if (now == 2) now = 0;
					break;
				}
			}
			continue;
		}
		// ���� Ȥ�� ����
		else if (c == 13) break;
		else if (c == 27) {
			now = -1;
			break;
		}
	}
	return now;
}
int e_letter(char type){
	char c = 0, now = 0; 
	const int y[] = {18, 20, 22};
	const int x1 = 51, x2 = 67;
	int count = 0, random, len[100];
	char ch, FLAG = 0;
	char input[1], answer[33];
	char el_txt[33];
	int left = 0, correct = 0, wrong = 0;
	double tresult;
	
	start = clock();
	
	system("cls");

	gotoXY(48, 2); printf("�� ��  ��  ��  -  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(55, 28); puts("������ �ʷϻ����� ǥ��, ���� �Է� �� ���͸� ���� �����մϴ�.");
	
	Box(15, 9, 105, 19, WHITE);
	
	gotoXY(36, 11); puts("q   w   e   r   t   y   u   i   o   p   [   ]");
	gotoXY(39, 14); puts("a   s   d   f   g   h   j   k   ;   '");
	gotoXY(39, 17); puts("z   x   c   v   b   n   m   ,   .   /");
	
	Box(20, 4, 100, 8, WHITE);
	Box(25, 20, 95, 22, WHITE);
	gotoXY(58, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	
	FILE *et;
	et = fopen("e_letter.txt", "r");
	fscanf(et, "%c", &el_txt[0]);
	
	if(z == 15){
		left = 15;
		p = 15;
		for(i=0; i<15; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 33) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=1; i<33; i++){
				fscanf(et, "%c ", &el_txt[i]);
			}
			for(i=0; i<1; i++){
		    	answer[0] = el_txt[random];
		    	printf("%c", el_txt[random]);
			}
		}
	}
	else if(z == 25){
		left = 25;
		p = 25;
		for(i=0; i<25; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 33) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=1; i<33; i++){
				fscanf(et, "%c ", &el_txt[i]);
			}
			for(i=0; i<1; i++){
		    	answer[0] = el_txt[random];
		    	printf("%c", el_txt[random]);
			}
		}
	}
	else if(z == 35){
		left = 35;
		p = 35;
		for(i=0; i<35; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 33) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=1; i<33; i++){
				fscanf(et, "%c ", &el_txt[i]);
			}
			for(i=0; i<1; i++){
		    	answer[0] = el_txt[random];
		    	printf("%c", el_txt[random]);
			}
		}
	}
	
	for(i=0; i<100; i++){
		input[i] = NULL;
	}
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	Box(3, 24, 116, 26, WHITE);
	gotoXY(5, 25);
	printf("�Է� : %50c", ' ');
	gotoXY(15, 25);
	disp(left, correct, wrong); 
	
	
	while (1) {
		if (_kbhit()) {
			ch = _getch();
			// �齺���̽�
			if (ch == 27) return 0;
			if (ch == 8) {
				if (count > 0) {
					// �����̽��� �� ĭ ���� 
					if (input[count - 1] == ' ') {
						input[count - 1] = NULL;
						count -= 1;
					}
					// ����� �� ĭ ���� 
					else if (('z' >= input[count - 1] && input[count - 1] >= 'a') || ('Z' >= input[count - 1] && input[count - 1] >= 'A')) {
						input[count - 1] = NULL;
						count -= 1;
					}
					// �ѱ��̸� �� ĭ ���� 
					else {
						input[count - 2] = NULL;
						input[count - 1] = NULL;
						count -= 2;
					}

					gotoXY(15, 25); printf("%60c", ' ');
					gotoXY(15, 25); printf("%s", input);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
			}

			// ���� ó��
			else if (ch == 13) {
				// ��ġ�ϸ� ����
				if(strcmp(input, answer) == 0){
					FLAG = 1;
					correct += 1;
					left -= 1;
				}
				else {
					for(i=0; i<100; i++) input[i] = NULL;

					count = 0;
					
					FLAG = 1;
					wrong += 1;
					left -= 1;

					gotoXY(5, 25);
					printf("�Է� : %50c", ' ');
					gotoXY(15, 25);
				}
			}

			else {
				// �ѱ� 2Byte - �� ĭ ���� 
				input[count++] = ch;
				if (_kbhit()) {
					ch = _getch();
					input[count++] = ch;
					// �ѱ� �� ����Ʈ�� �Բ� ���
					printf("%c", input[count - 2]);
				}
				printf("%c\b ", input[count - 1]);

				gotoXY(15, 25); printf("%60c", ' ');
				gotoXY(15, 25); printf("%s", input);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			disp(left, correct, wrong);
			if(left <= 0){
				break;
			}
		}
		else if (FLAG == 1) {
			Box(3, 24, 116, 26, WHITE);
			gotoXY(5, 25);
			printf("�Է� : %50c", ' ');
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			gotoXY(58, 21);
			if(z == 15){
				for(i=0; i<15; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 33) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=1; i<33; i++){
						fscanf(et, "%c ", &el_txt[i]);
					}
					for(i=0; i<1; i++){
				    	printf("%c", el_txt[random]);
		    			answer[0] = el_txt[random];
					}
				}
			}
			else if(z == 25){
				for(i=0; i<25; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 33) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=1; i<33; i++){
						fscanf(et, "%c ", &el_txt[i]);
					}
					for(i=0; i<1; i++){
				    	printf("%c", el_txt[random]);
		    			answer[0] = el_txt[random];
					}
				}
			}
			else if(z == 35){
				for(i=0; i<35; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 33) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=1; i<33; i++){
						fscanf(et, "%c ", &el_txt[i]);
					}
					for(i=0; i<1; i++){
				    	printf("%c", el_txt[random]);
		    			answer[0] = el_txt[random];
					}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

			for (i=0; i<100; i++) input[i] = NULL;

			count = 0;

			disp(left, correct, wrong);
			gotoXY(15, 25);

			FLAG = 0;
		}
	}
	end = clock();
	tresult = (double)(end - start) / CLOCKS_PER_SEC;
	accu = ((double)correct / p)*100;
	endpg(now, tresult, p, correct, wrong);
}
int k_letter(char type){
	char c = 0, now = 0; 
	const int y[] = {18, 20, 22};
	const int x1 = 51, x2 = 67;
	int count = 0, random, len[100];
	char ch, FLAG = 0;
	char input[1], answer[33];
	char el_txt[33];
	int left = 0, correct = 0, wrong = 0;
	double tresult;
	
	start = clock();
	
	system("cls");

	gotoXY(48, 2); printf("�� ��  ��  ��  -  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(55, 28); puts("������ �ʷϻ����� ǥ��, ���� �Է� �� ���͸� ���� �����մϴ�.");
	
	Box(15, 9, 105, 19, WHITE);
	
	gotoXY(36, 11); puts("q   w   e   r   t   y   u   i   o   p   [   ]");
	gotoXY(39, 14); puts("a   s   d   f   g   h   j   k   ;   '");
	gotoXY(39, 17); puts("z   x   c   v   b   n   m   ,   .   /");
	
	Box(20, 4, 100, 8, WHITE);
	Box(25, 20, 95, 22, WHITE);
	gotoXY(58, 21);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	
	FILE *et;
	et = fopen("k_letter.txt", "r");
	fscanf(et, "%c", &el_txt[0]);
	
	if(z == 15){
		left = 15;
		p = 15;
		for(i=0; i<15; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 33) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=1; i<33; i++){
				fscanf(et, "%c ", &el_txt[i]);
			}
			for(i=0; i<1; i++){
		    	answer[0] = el_txt[random];
		    	printf("%c", el_txt[random]);
			}
		}
	}
	else if(z == 25){
		left = 25;
		p = 25;
		for(i=0; i<25; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 33) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=1; i<33; i++){
				fscanf(et, "%c ", &el_txt[i]);
			}
			for(i=0; i<1; i++){
		    	answer[0] = el_txt[random];
		    	printf("%c", el_txt[random]);
			}
		}
	}
	else if(z == 35){
		left = 35;
		p = 35;
		for(i=0; i<35; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 33) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=1; i<33; i++){
				fscanf(et, "%c ", &el_txt[i]);
			}
			for(i=0; i<1; i++){
		    	answer[0] = el_txt[random];
		    	printf("%c", el_txt[random]);
			}
		}
	}
	
	for(i=0; i<100; i++){
		input[i] = NULL;
	}
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
//	Box(3, 24, 116, 26, WHITE);
	gotoXY(5, 25);
	printf("�Է� : %50c", ' ');
	gotoXY(15, 25);
	disp(left, correct, wrong); 
	
	
	while (1) {
			ch = _getch();

			if (ch == 27) return 0;
			if (ch == 8) {
				if (count > 0) {
					if (input[count - 1] == ' ') {
						input[count - 1] = NULL;
						count -= 1;
					}
					else if (('z' >= input[count - 1] && input[count - 1] >= 'a') || ('Z' >= input[count - 1] && input[count - 1] >= 'A')) {
						input[count - 1] = NULL;
						count -= 1;
					}
					else {
						input[count - 2] = NULL;
						input[count - 1] = NULL;
						count -= 2;
					}

					gotoXY(15, 25); printf("%60c", ' ');
					gotoXY(15, 25); printf("%s", input);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
			}

			else if (ch == 13) {
				if(strcmp(input, answer) == 0){
					FLAG = 1;
					correct += 1;
					left -= 1;
				}
				else {
					for(i=0; i<100; i++) input[i] = NULL;

					count = 0;
					
					FLAG = 1;
					wrong += 1;
					left -= 1;

					gotoXY(5, 25);
					printf("�Է� : %50c", ' ');
					gotoXY(15, 25);
				}
			}

			else {
				input[count++] = ch;
				ch = _getch();
				input[count++] = ch;
				printf("%c", input[count - 2]);
				printf("%c\b ", input[count - 1]);

				gotoXY(15, 25); printf("%60c", ' ');
				gotoXY(15, 25); printf("%s", input);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			disp(left, correct, wrong);
			if(left <= 0){
				break;
			}
		
		else if (FLAG == 1) {
			Box(3, 24, 116, 26, WHITE);
			gotoXY(5, 25);
			printf("�Է� : %50c", ' ');
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			gotoXY(58, 21);
			if(z == 15){
				for(i=0; i<15; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 33) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=1; i<33; i++){
						fscanf(et, "%c ", &el_txt[i]);
					}
					for(i=0; i<1; i++){
				    	printf("%c", el_txt[random]);
		    			answer[0] = el_txt[random];
					}
				}
			}
			else if(z == 25){
				for(i=0; i<25; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 33) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=1; i<33; i++){
						fscanf(et, "%c ", &el_txt[i]);
					}
					for(i=0; i<1; i++){
				    	printf("%c", el_txt[random]);
		    			answer[0] = el_txt[random];
					}
				}
			}
			else if(z == 35){
				for(i=0; i<35; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 33) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=1; i<33; i++){
						fscanf(et, "%c ", &el_txt[i]);
					}
					for(i=0; i<1; i++){
				    	printf("%c", el_txt[random]);
		    			answer[0] = el_txt[random];
					}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

			for (i=0; i<100; i++) input[i] = NULL;

			count = 0;

			disp(left, correct, wrong);
			gotoXY(15, 25);

			FLAG = 0;
		}
	}
	end = clock();
	tresult = (double)(end - start) / CLOCKS_PER_SEC;
	accu = ((double)correct / p)*100;
	endpg(now, tresult, p, correct, wrong);
}
int word(char type){
	char c = 0, now = 0; 
	const int y[] = { 18, 20, 22};
	const int x1 = 51, x2 = 67;

	system("cls");

	gotoXY(53, 4); printf("��  ��  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(75, 28); puts("����Ű�� Ŀ���� �̵�, ���ͷ� �����ϼ���.");

	while (1) {
		// ȭ��ǥ ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(x1, y[now]); printf("��");
		gotoXY(x2, y[now]); printf("��");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(48, 9); puts("���� �� �� �����ϼ���.");
		Box(20, 8, 100, 10, WHITE);
		
		// �޴� ���
		if (now == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 6, y[0]); printf("��  ��");
		
		if (now == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 6, y[1]); printf("��  ��");

		if (now == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[2]); printf("�ڷΰ���");
		Box(46, 17, 73, 23, WHITE);
		puts(" ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

		// ����Ű�� �Է��ϸ� �޴� ���õǵ���
		c = _getch();
		if (c == 0x00 || c == 0xE0) c = _getch();
		if (c == 80 || c == 72) {
			switch (c) {
				// UP
				case 72: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now > 0) now--;
					else if (now == 0) now = 2;
					break;
				}
				// DOWN
				case 80: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now < 2) now++;
					else if (now == 2) now = 0;
					break;
				}
			}
			continue;
		}
		// ���� Ȥ�� ����
		else if (c == 13) break;
		else if (c == 27) {
			now = -1;
			break;
		}
	}
	return now;
}
int e_word(char type){
	char c = 0, now = 0; 
	const int y[] = {18, 20, 22};
	const int x1 = 51, x2 = 67;
	int count = 0, random;
	char ch, FLAG = 0;
	char input[100], *answer[100];
	char *e, *ew_txt[50];
	int left = 0, correct = 0, wrong = 0;
	double tresult;
	
	system("cls");
	
	gotoXY(47, 2); printf("�� ��  ��  ��  -  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(55, 28); puts("������ �ʷϻ����� ǥ��, ���� �Է� �� ���͸� ���� �����մϴ�.");
	Box(20, 4, 100, 8, WHITE);
	gotoXY(57, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	
	FILE *et;
	et = fopen("e_word.txt", "r");
	
	if(z == 15){
		left = 15;
		p = 15;
		for(i=0; i<15; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		e = (char*)malloc(sizeof(char) *100);
				fgets(e, sizeof(ew_txt), et);
				ew_txt[i] = e;
			}
			for(i=0; i<1; i++){
				printf("%s", ew_txt[random]);
				answer[0] = ew_txt[random];
			}
		}
	}
	else if(z == 25){
		left = 25;
		p = 25;
		for(i=0; i<25; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		e = (char*)malloc(sizeof(char) *100);
				fgets(e, sizeof(ew_txt), et);
				ew_txt[i] = e;
			}
			for(i=0; i<1; i++){
				printf("%s", ew_txt[random]);
				answer[0] = ew_txt[random];
			}
		}
	}
	else if(z == 35){
		left = 35;
		p = 35;
		for(i=0; i<35; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		e = (char*)malloc(sizeof(char) *100);
				fgets(e, sizeof(ew_txt), et);
				ew_txt[i] = e;
			}
			for(i=0; i<1; i++){
				printf("%s", ew_txt[random]);
				answer[0] = ew_txt[random];
			}
		}
	}
	
	for(i=0; i<100; i++){
		input[i] = NULL;
	}
	
	Box(15, 9, 105, 23, WHITE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	Box(3, 24, 116, 26, WHITE);
	gotoXY(5, 25);
	printf("�Է� : %50c", ' ');
	gotoXY(15, 25);
	disp(left, correct, wrong); 
	
	while (1) {
		if (_kbhit()) {
			ch = _getch();

			if (ch == 27) return 0;
			if (ch == 8) {
				if (count > 0) {
					if (input[count - 1] == ' ') {
						input[count - 1] = NULL;
						count -= 1;
					}
					else if (('z' >= input[count - 1] && input[count - 1] >= 'a') || ('Z' >= input[count - 1] && input[count - 1] >= 'A')) {
						input[count - 1] = NULL;
						count -= 1;
					}
					else {
						input[count - 2] = NULL;
						input[count - 1] = NULL;
						count -= 2;
					}

					gotoXY(15, 25); printf("%60c", ' ');
					gotoXY(15, 25); printf("%s", input);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
			}

			// ����
			else if (ch == 13) {
				//answer (\n) ����, ������ �ڲ� Ʋ�� 
				gotoXY(57, 15);	
				char *ptr = answer[0];
				while(*ptr != '\n') {
					ptr++;
				}
				*ptr = '\0';
//				printf("%d", strcmp(input, answer[0]));
				// ����
				if(strcmp(input, answer[0])== 0) {
					FLAG = 1;
					correct += 1;
					left -= 1;
				}
				else {
					for(i=0; i<100; i++) input[i] = NULL;
					
					count = 0;
					
					FLAG = 1;
					wrong += 1;
					left -= 1;

					gotoXY(5, 25);
					printf("�Է� : %50c", ' ');
					gotoXY(15, 25);
				}
			}

			// ���� �Է�
			else {
				input[count++] = ch;
				if (_kbhit()) {
					ch = _getch();
					input[count++] = ch;
					printf("%c", input[count - 2]);
				}
				printf("%c\b ", input[count - 1]);

				gotoXY(15, 25); printf("%60c", ' ');
				gotoXY(15, 25); printf("%s", input);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			disp(left, correct, wrong);
			if(left <= 0){
				break;
			}
		}
		else if (FLAG == 1) {
			gotoXY(57, 16); printf("%60c", ' ');
			Box(15, 9, 105, 23, WHITE);
			Box(3, 24, 116, 26, WHITE);
			gotoXY(5, 25);
			printf("�Է� : %50c", ' ');
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			gotoXY(57, 16);
			
			if(z == 15){
				for(i=0; i<15; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						printf("%s", ew_txt[random]);
						answer[0] = ew_txt[random];
					}
				}
			}
			else if(z == 25){
				for(i=0; i<25; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						printf("%s", ew_txt[random]);
						answer[0] = ew_txt[random];
					}
				}
			}
			else if(z == 35){
				for(i=0; i<35; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						printf("%s", ew_txt[random]);
						answer[0] = ew_txt[random];
					}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

			for (i=0; i<100; i++) input[i] = NULL;

			count = 0;

			disp(left, correct, wrong);
			gotoXY(15, 25);

			FLAG = 0;
		}
	}
	end = clock();
	tresult = (double)(end - start) / CLOCKS_PER_SEC;
	accu = ((double)correct / p)*100;
	endpg(now, tresult, p, correct, wrong);
}
int k_word(char type){
	char c = 0, now = 0; 
	const int y[] = {18, 20, 22};
	const int x1 = 51, x2 = 67;
	int count = 0, random;
	char ch, FLAG = 0;
	char input[100], *answer[100];
	char *k, *kw_txt[50];
	int left = 0, correct = 0, wrong = 0;
	double tresult;
	
	system("cls");
	
	gotoXY(47, 2); printf("�� ��  ��  ��  -  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(55, 28); puts("������ �ʷϻ����� ǥ��, ���� �Է� �� ���͸� ���� �����մϴ�.");
	Box(20, 4, 100, 8, WHITE);
	gotoXY(57, 16);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	
	FILE *kt;
	kt = fopen("k_word.txt", "r");
	
	if(z == 15){
		left = 15;
		p = 15;
		for(i=0; i<15; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(kt == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		k = (char*)malloc(sizeof(char) *100);
				fgets(k, sizeof(kw_txt), kt);
				kw_txt[i] = k;
			}
			for(i=0; i<1; i++){
				printf("%s", kw_txt[random]);
				answer[0] = kw_txt[random];
			}
		}
	}
	else if(z == 25){
		left = 25;
		p = 25;
		for(i=0; i<25; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(kt == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		k = (char*)malloc(sizeof(char) *100);
				fgets(k, sizeof(kw_txt), kt);
				kw_txt[i] = k;
			}
			for(i=0; i<1; i++){
				printf("%s", kw_txt[random]);
				answer[0] = kw_txt[random];
			}
		}
	}
	else if(z == 35){
		left = 35;
		p = 35;
		for(i=0; i<35; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(kt == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		k = (char*)malloc(sizeof(char) *100);
				fgets(k, sizeof(kw_txt), kt);
				kw_txt[i] = k;
			}
			for(i=0; i<1; i++){
				printf("%s", kw_txt[random]);
				answer[0] = kw_txt[random];
			}
		}
	}
	
	for(i=0; i<100; i++){
		input[i] = NULL;
	}
	
	Box(15, 9, 105, 23, WHITE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	Box(3, 24, 116, 26, WHITE);
	gotoXY(5, 25);
	printf("�Է� : %50c", ' ');
	gotoXY(15, 25);
	disp(left, correct, wrong); 
	
	while (1) {
			ch = _getch();

			if (ch == 27) return 0;
			if (ch == 8) {
				if (count > 0) {
					if (input[count - 1] == ' ') {
						input[count - 1] = NULL;
						count -= 1;
					}
					else if (('z' >= input[count - 1] && input[count - 1] >= 'a') || ('Z' >= input[count - 1] && input[count - 1] >= 'A')) {
						input[count - 1] = NULL;
						count -= 1;
					}
					else {
						input[count - 2] = NULL;
						input[count - 2] = NULL;
						count -= 2;
					}

					gotoXY(15, 25); printf("%60c", ' ');
					gotoXY(15, 25); printf("%s", input);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
			}

			// ����
			else if (ch == 13) {
				//answer (\n) ����, ������ �ڲ� Ʋ�� 
				gotoXY(57, 15);	
				char *ptr = answer[0];
				while(*ptr != '\n') {
					ptr++;
				}
				*ptr = '\0';
//				printf("%d", strcmp(input, answer[0]));
				// ����
				if(strcmp(input, answer[0])== 0) {
					FLAG = 1;
					correct += 1;
					left -= 1;
				}
				else {
					for(i=0; i<100; i++) input[i] = NULL;
					
					count = 0;
					
					FLAG = 1;
					wrong += 1;
					left -= 1;

					gotoXY(5, 25);
					printf("�Է� : %50c", ' ');
					gotoXY(15, 25);
				}
			}

			// ���� �Է�
			else {
				input[count++] = ch;
				ch = _getch();
				input[count++] = ch;
				printf("%c", input[count]);
				printf("%c\b ", input[count]);

				gotoXY(15, 25); printf("%60c", ' ');
				gotoXY(15, 25); printf("%s", input);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			disp(left, correct, wrong);
			if(left <= 0){
				break;
			}
		else if (FLAG == 1) {
			gotoXY(57, 16); printf("%60c", ' ');
			Box(15, 9, 105, 23, WHITE);
			Box(3, 24, 116, 26, WHITE);
			gotoXY(5, 25);
			printf("�Է� : %50c", ' ');
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			gotoXY(57, 16);
			
			if(z == 15){
				for(i=0; i<15; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(kt == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						printf("%s", kw_txt[random]);
						answer[0] = kw_txt[random];
					}
				}
			}
			else if(z == 25){
				for(i=0; i<25; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(kt == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						printf("%s", kw_txt[random]);
						answer[0] = kw_txt[random];
					}
				}
			}
			else if(z == 35){
				for(i=0; i<35; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(kt == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						printf("%s", kw_txt[random]);
						answer[0] = kw_txt[random];
					}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

			for (i=0; i<100; i++) input[i] = NULL;

			count = 0;

			disp(left, correct, wrong);
			gotoXY(15, 25);

			FLAG = 0;
		}
	}
	end = clock();
	tresult = (double)(end - start) / CLOCKS_PER_SEC;
	accu = ((double)correct / p)*100;
	endpg(now, tresult, p, correct, wrong);
}
int s_text(char type){
	char c = 0, now = 0; 
	const int y[] = { 18, 20, 22};
	const int x1 = 51, x2 = 67;

	system("cls");

	gotoXY(52, 4); printf("ª ��  ��  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(75, 28); puts("����Ű�� Ŀ���� �̵�, ���ͷ� �����ϼ���.");

	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(x1, y[now]); printf("��");
		gotoXY(x2, y[now]); printf("��");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(48, 9); puts("���� �� �� �����ϼ���.");
		Box(20, 8, 100, 10, WHITE);
		
		if (now == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 6, y[0]); printf("��  ��");
		
		if (now == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 6, y[1]); printf("��  ��");

		if (now == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[2]); printf("�ڷΰ���");
		Box(46, 17, 73, 23, WHITE);
		puts(" ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

		c = _getch();
		if (c == 0x00 || c == 0xE0) c = _getch();
		if (c == 80 || c == 72) {
			switch (c) {
				// UP
				case 72: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now > 0) now--;
					else if (now == 0) now = 2;
					break;
				}
				// DOWN
				case 80: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now < 2) now++;
					else if (now == 2) now = 0;
					break;
				}
			}
			continue;
		}
		// ���� Ȥ�� ����
		else if (c == 13) break;
		else if (c == 27) {
			now = -1;
			break;
		}
	}
	return now;
}
int e_s_text(char type){
	char c = 0, now = 0; 
	const int y[] = {18, 20, 22};
	const int x1 = 51, x2 = 67;
	int count = 0, random;
	char ch, FLAG = 0;
	char input[100], *answer[100];
	char *e, *ew_txt[50];
	int left = 0, correct = 0, wrong = 0;
	int len;
	double tresult;
	
	system("cls");
	
	gotoXY(45, 2); printf("ª�� ��  ��  ��  -  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(55, 28); puts("������ �ʷϻ����� ǥ��, ���� �Է� �� ���͸� ���� �����մϴ�.");
	Box(20, 4, 100, 8, WHITE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

	
	FILE *et;
	et = fopen("e_short.txt", "r");
	
	if(z == 15){
		left = 15;
		p = 15;
		for(i=0; i<15; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		e = (char*)malloc(sizeof(char) *100);
				fgets(e, sizeof(ew_txt), et);
				ew_txt[i] = e;
			}
			for(i=0; i<1; i++){
				len = strlen(ew_txt[random]);
				gotoXY(60 - len / 2, 16);
				printf("%s", ew_txt[random]);
				answer[0] = ew_txt[random];
			}
		}
	}
	else if(z == 25){
		left = 25;
		p = 25;
		for(i=0; i<25; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		e = (char*)malloc(sizeof(char) *100);
				fgets(e, sizeof(ew_txt), et);
				ew_txt[i] = e;
			}
			for(i=0; i<1; i++){
				len = strlen(ew_txt[random]);
				gotoXY(60 - len / 2, 16);
				printf("%s", ew_txt[random]);
				answer[0] = ew_txt[random];
			}
		}
	}
	else if(z == 35){
		left = 35;
		p = 35;
		for(i=0; i<35; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(et == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		e = (char*)malloc(sizeof(char) *100);
				fgets(e, sizeof(ew_txt), et);
				ew_txt[i] = e;
			}
			for(i=0; i<1; i++){
				len = strlen(ew_txt[random]);
				gotoXY(60 - len / 2, 16);
				printf("%s", ew_txt[random]);
				answer[0] = ew_txt[random];
			}
		}
	}
	
	for(i=0; i<100; i++){
		input[i] = NULL;
	}
	
	Box(15, 9, 105, 23, WHITE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	Box(3, 24, 116, 26, WHITE);
	gotoXY(5, 25);
	printf("�Է� : %100c", ' ');
	gotoXY(15, 25);
	disp(left, correct, wrong); 
	
	while (1) {
		if (_kbhit()) {
			ch = _getch();

			if (ch == 27) return 0;
			if (ch == 8) {
				if (count > 0) {
					if (input[count - 1] == ' ') {
						input[count - 1] = NULL;
						count -= 1;
					}
					else if (('z' >= input[count - 1] && input[count - 1] >= 'a') || ('Z' >= input[count - 1] && input[count - 1] >= 'A')) {
						input[count - 1] = NULL;
						count -= 1;
					}
					else {
						input[count - 2] = NULL;
						input[count - 1] = NULL;
						count -= 2;
					}

					gotoXY(15, 25); printf("%100c", ' ');
					gotoXY(15, 25); printf("%s", input);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
			}

			// ����
			else if (ch == 13) {
				//answer (\n) ����, ������ �ڲ� Ʋ�� 
				gotoXY(57, 15);	
				char *ptr = answer[0];
				while(*ptr != '\n') {
					ptr++;
				}
				*ptr = '\0';
//				printf("%d", strcmp(input, answer[0]));
				// ����
				if(strcmp(input, answer[0])== 0) {
					FLAG = 1;
					correct += 1;
					left -= 1;
				}
				else {
					for(i=0; i<100; i++) input[i] = NULL;
					
					count = 0;
					
					FLAG = 1;
					wrong += 1;
					left -= 1;

					gotoXY(5, 25);
					printf("�Է� : %100c", ' ');
					gotoXY(15, 25);
				}
				//ȭ���� ���� ���� ���� 
				system("cls");
				gotoXY(45, 2); printf("ª�� ��  ��  ��  -  ��  ��");
				Box(20, 4, 100, 8, WHITE);
				Box(15, 9, 105, 23, WHITE);
				Box(3, 24, 116, 26, WHITE);
				gotoXY(55, 28); puts("������ �ʷϻ����� ǥ��, ���� �Է� �� ���͸� ���� �����մϴ�.");
			}

			// ���� �Է�
			else {
				input[count++] = ch;
				if (_kbhit()) {
					ch = _getch();
					input[count++] = ch;
					printf("%c", input[count - 2]);
				}
				printf("%c\b ", input[count - 1]);

				gotoXY(15, 25); printf("%100c", ' ');
				gotoXY(15, 25); printf("%s", input);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			disp(left, correct, wrong);
			if(left <= 0){
				break;
			}
		}
		else if (FLAG == 1) {
			gotoXY(57, 16); printf("%100c", ' ');
			Box(15, 9, 105, 23, WHITE);
			Box(3, 24, 116, 26, WHITE);
			gotoXY(5, 25);
			printf("�Է� : %100c", ' ');
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			
			if(z == 15){
				for(i=0; i<15; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						len = strlen(ew_txt[random]);
						gotoXY(60 - len / 2, 16);
						printf("%s", ew_txt[random]);
						answer[0] = ew_txt[random];
					}
				}
			}
			else if(z == 25){
				for(i=0; i<25; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						len = strlen(ew_txt[random]);
						gotoXY(60 - len / 2, 16);
						printf("%s", ew_txt[random]);
						answer[0] = ew_txt[random];
					}
				}
			}
			else if(z == 35){
				for(i=0; i<35; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(et == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						len = strlen(ew_txt[random]);
						gotoXY(60 - len / 2, 16);
						printf("%s", ew_txt[random]);
						answer[0] = ew_txt[random];
					}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

			for (i=0; i<100; i++) input[i] = NULL;

			count = 0;

			disp(left, correct, wrong);
			gotoXY(15, 25);

			FLAG = 0;
		}
	}
	end = clock();
	tresult = (double)(end - start) / CLOCKS_PER_SEC;
	accu = ((double)correct / p)*100;
	endpg(now, tresult, p, correct, wrong);
}
int k_s_text(char type){
	char c = 0, now = 0; 
	const int y[] = {18, 20, 22};
	const int x1 = 51, x2 = 67;
	int count = 0, random;
	char ch, FLAG = 0;
	char input[100], *answer[100];
	char *k, *kw_txt[50];
	int left = 0, correct = 0, wrong = 0;
	int len;
	double tresult;
	
	system("cls");
	
	gotoXY(45, 2); printf("ª�� ��  ��  ��  -  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(55, 28); puts("������ �ʷϻ����� ǥ��, ���� �Է� �� ���͸� ���� �����մϴ�.");
	Box(20, 4, 100, 8, WHITE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

	
	FILE *kt;
	kt = fopen("k_short.txt", "r");
	
	if(z == 15){
		left = 15;
		p = 15;
		for(i=0; i<15; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(kt == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		k = (char*)malloc(sizeof(char) *500);
				fgets(k, sizeof(kw_txt), kt);
				kw_txt[i] = k;
			}
			for(i=0; i<1; i++){
				len = strlen(kw_txt[random]);
				gotoXY(60 - len / 2, 16);
				printf("%s", kw_txt[random]);
				answer[0] = kw_txt[random];
			}
		}
	}
	else if(z == 25){
		left = 25;
		p = 25;
		for(i=0; i<25; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(kt == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		k = (char*)malloc(sizeof(char) *500);
				fgets(k, sizeof(kw_txt), kt);
				kw_txt[i] = k;
			}
			for(i=0; i<1; i++){
				len = strlen(kw_txt[random]);
				gotoXY(60 - len / 2, 16);
				printf("%s", kw_txt[random]);
				answer[0] = kw_txt[random];
			}
		}
	}
	else if(z == 35){
		left = 35;
		p = 35;
		for(i=0; i<35; i++){
			srand((unsigned)time(NULL));
			random = ((rand() % 50) + 1);	
		}
		if(kt == NULL){
			printf("���� �б⸦ �����߽��ϴ�.");
		}
		else{
			for(i=0; i<50; i++){
        		k = (char*)malloc(sizeof(char) *500);
				fgets(k, sizeof(kw_txt), kt);
				kw_txt[i] = k;
			}
			for(i=0; i<1; i++){
				len = strlen(kw_txt[random]);
				gotoXY(60 - len / 2, 16);
				printf("%s", kw_txt[random]);
				answer[0] = kw_txt[random];
			}
		}
	}
	
	for(i=0; i<100; i++){
		input[i] = NULL;
	}
	
	Box(15, 9, 105, 23, WHITE);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	Box(3, 24, 116, 26, WHITE);
	gotoXY(5, 25);
	printf("�Է� : %100c", ' ');
	gotoXY(15, 25);
	disp(left, correct, wrong); 
	
	while (1) {
			ch = _getch();

			if (ch == 27) return 0;
			if (ch == 8) {
				if (count > 0) {
					if (input[count - 1] == ' ') {
						input[count - 1] = NULL;
						count -= 1;
					}
					else if (('z' >= input[count - 1] && input[count - 1] >= 'a') || ('Z' >= input[count - 1] && input[count - 1] >= 'A')) {
						input[count - 1] = NULL;
						count -= 1;
					}
					else {
						input[count - 2] = NULL;
						input[count - 1] = NULL;
						count -= 2;
					}

					gotoXY(15, 25); printf("%100c", ' ');
					gotoXY(15, 25); printf("%s", input);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				}
			}

			// ����
			else if (ch == 13) {
				//answer (\n) ����, ������ �ڲ� Ʋ�� 
				gotoXY(57, 15);	
				char *ptr = answer[0];
				while(*ptr != '\n') {
					ptr++;
				}
				*ptr = '\0';
//				printf("%d", strcmp(input, answer[0]));
				// ����
				if(strcmp(input, answer[0])== 0) {
					FLAG = 1;
					correct += 1;
					left -= 1;
				}
				else {
					for(i=0; i<100; i++) input[i] = NULL;
					
					count = 0;
					
					FLAG = 1;
					wrong += 1;
					left -= 1;

					gotoXY(5, 25);
					printf("�Է� : %100c", ' ');
					gotoXY(15, 25);
				}
				//ȭ���� ���� ���� ���� 
				system("cls");
				gotoXY(45, 2); printf("ª�� ��  ��  ��  -  ��  ��");
				Box(20, 4, 100, 8, WHITE);
				Box(15, 9, 105, 23, WHITE);
				Box(3, 24, 116, 26, WHITE);
				gotoXY(55, 28); puts("������ �ʷϻ����� ǥ��, ���� �Է� �� ���͸� ���� �����մϴ�.");
			}

			// ���� �Է�
			else {
				input[count++] = ch;
				ch = _getch();
				input[count++] = ch;
				printf("%c", input[count - 2]);
				printf("%c\b ", input[count - 1]);

				gotoXY(15, 25); printf("%100c", ' ');
				gotoXY(15, 25); printf("%s", input);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			}
			disp(left, correct, wrong);
			if(left <= 0){
				break;
			}
		
		else if (FLAG == 1) {
			gotoXY(57, 16); printf("%100c", ' ');
			Box(15, 9, 105, 23, WHITE);
			Box(3, 24, 116, 26, WHITE);
			gotoXY(5, 25);
			printf("�Է� : %100c", ' ');
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			
			if(z == 15){
				for(i=0; i<15; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(kt == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						len = strlen(kw_txt[random]);
						gotoXY(60 - len / 2, 16);
						printf("%s", kw_txt[random]);
						answer[0] = kw_txt[random];
					}
				}
			}
			else if(z == 25){
				for(i=0; i<25; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(kt == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						len = strlen(kw_txt[random]);
						gotoXY(60 - len / 2, 16);
						printf("%s", kw_txt[random]);
						answer[0] = kw_txt[random];
					}
				}
			}
			else if(z == 35){
				for(i=0; i<35; i++){
					srand((unsigned)time(NULL));
					random = ((rand() % 50) + 1);	
				}
				if(kt == NULL){
					printf("���� �б⸦ �����߽��ϴ�.");
				}
				else{
					for(i=0; i<1; i++){
						len = strlen(kw_txt[random]);
						gotoXY(60 - len / 2, 16);
						printf("%s", kw_txt[random]);
						answer[0] = kw_txt[random];
					}
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

			for (i=0; i<100; i++) input[i] = NULL;

			count = 0;

			disp(left, correct, wrong);
			gotoXY(15, 25);

			FLAG = 0;
		}
	}
	end = clock();
	tresult = (double)(end - start) / CLOCKS_PER_SEC;
	accu = ((double)correct / p)*100;
	endpg(now, tresult, p, correct, wrong);
}
int record(char type){
	char c = 0, now = 0;
	const int y[] = {20, 22, 24};
	const int x1 = 51, x2 = 67;
	int rcd[10], dis = -40, q = 1;
	
	FILE *rc;
	rc = fopen("udata.txt", "r");
	
	fseek(rc, dis, SEEK_END);
	for(i=0; i<10; i++){
		fscanf(rc, "%d", &rcd[i]);
	}
	if(rcd[0] > 4) fseek(rc, -77, SEEK_END);
	if(rcd[2] > 10){
		fseek(rc, -35, SEEK_END);
		for(i=0; i<10; i++){
			fscanf(rc, "%d", &rcd[i]);
		}
	}
	
	if(cg == 1){
		q++;
		dis = -100;
		fseek(rc, dis, SEEK_END);
		for(i=0; i<10; i++){
			fscanf(rc, "%d", &rcd[i]);
		}
		if(rcd[0] > 4) fseek(rc, -75, SEEK_END);
		for(i=0; i<10; i++){
			fscanf(rc, "%d", &rcd[i]);
		}
		cg=0;
	}

	system("cls");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(75, 28); puts("����Ű�� Ŀ���� �̵�, ���ͷ� �����ϼ���.");

	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(x1, y[now]); printf("��");
		gotoXY(x2, y[now]); printf("��");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(46, 2);
		if(rcd[0] == 1) printf("�ֱ� ������ ���� : �ڸ� ����");
		else if(rcd[0] == 2) printf("�ֱ� ������ ���� : �ܾ� ����");
		else if(rcd[0] == 3) printf("�ֱ� ������ ���� : ª�� �� ����");
		else printf("�ֱ� ������ ���� : ��� ����");
		gotoXY(42, 6); printf("��¥ : 			%08d", rcd[1]);
		gotoXY(42, 8); printf("��ǥ ���� :			%d", rcd[2]);
		gotoXY(42, 10); printf("�ɸ� �ð� :			%04d", rcd[3]);
		gotoXY(42, 12); printf("���� :			%d", rcd[4]);
		gotoXY(42, 14); printf("���� :			%d", rcd[5]);
		gotoXY(42, 16); printf("��Ȯ�� :			%d", rcd[6]);
		Box(20, 4, 100, 18, WHITE);
		
		if (now == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 4, y[0]); printf("����  ���");
		
		if (now == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 4, y[1]); printf("����  ���");

		if (now == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[2]); printf("�ڷΰ���");
		Box(46, 19, 73, 25, WHITE);
		puts(" ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

		c = _getch();
		if (c == 0x00 || c == 0xE0) c = _getch();
		if (c == 80 || c == 72) {
			switch (c) {
				// UP
				case 72: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now > 0) now--;
					else if (now == 0) now = 2;
					break;
				}
				// DOWN
				case 80: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now < 2) now++;
					else if (now == 2) now = 0;
					break;
				}
			}
			continue;
		}
		// ���� Ȥ�� ����
		else if (c == 13) break;
		else if (c == 27) {
			now = -1;
			break;
		}
	}
	return now;
}
int choose(char type){
	char c = 0, now = 0; 
	const int y[] = { 17, 19, 21, 23};
	const int x1 = 51, x2 = 67;

	system("cls");

	gotoXY(53, 4); printf("Ÿ  ��  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(75, 28); puts("����Ű�� Ŀ���� �̵�, ���ͷ� �����ϼ���.");

	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(x1, y[now]); printf("��");
		gotoXY(x2, y[now]); printf("��");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(50, 9); puts("��ǥ ������ �����ϼ���.");
		Box(20, 8, 100, 10, WHITE);
		
		if (now == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 7, y[0]); printf("1  5");
		
		if (now == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 7, y[1]); printf("2  5");

		if (now == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 7, y[2]); printf("3  5");

		if (now == 3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[3]); printf("�ڷΰ���");
		Box(46, 14, 73, 26, WHITE);
		puts(" ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

		c = _getch();
		if (c == 0x00 || c == 0xE0) c = _getch();
		if (c == 80 || c == 72) {
			switch (c) {
				// UP
				case 72: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now > 0) now--;
					else if (now == 0) now = 3;
					break;
				}
				// DOWN
				case 80: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now < 3) now++;
					else if (now == 3) now = 0;
					break;
				}
			}
			continue;
		}
		// ���� Ȥ�� ����
		else if (c == 13) break;
		else if (c == 27) {
			now = -1;
			break;
		}
	}
	return now;
}
int endpg(char type, int tresult, int p, int correct, int wrong){
	char c = 0, now = 0; 
	int m, s;
	const int y[] = {21, 23};
	const int x1 = 51, x2 = 67;
	struct tm* t;
	
	time_t base = time(NULL);
	
	t = localtime(&base);
	
	tresult %= 3600;
	tresult %= 3600;
	m = tresult / 60;
	s = tresult % 60;
	
	system("cls");
	
	FILE *udat;
	udat = fopen("udata.txt", "a+");
	if(udat == NULL){
		system("cls");
		printf("����");
	}
	else{
		fprintf(udat, "%d\n", tp);
		fprintf(udat, "%04d%02d%02d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
		fprintf(udat, "%d\n", p);
		fprintf(udat, "%02d%02d\n", m, s);
		fprintf(udat, "%d\n", correct);
		fprintf(udat, "%d\n", wrong);
		fprintf(udat, "%d\n\n", accu);
	}
	fclose(udat);

	gotoXY(50, 3); printf("��  ��  ��  ��  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(75, 28); puts("����Ű�� Ŀ���� �̵�, ���ͷ� �����ϼ���.");

	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(x1, y[now]); printf("��");
		gotoXY(x2, y[now]); printf("��");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(48, 8); printf("��ǥ ���� :	%d", p);
		gotoXY(48, 10); printf("�ɸ� �ð� :	%02d%02d", m, s);
		gotoXY(48, 12); printf("���� :		%d", correct);
		gotoXY(48, 14); printf("���� :		%d", wrong);
		gotoXY(48, 16); printf("��Ȯ�� :	%d", accu);
		Box(20, 6, 100, 18, WHITE);
		
		if (now == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 6, y[0]); printf("�絵��");

		if (now == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[1]); printf("�ڷΰ���");
		Box(46, 19, 73, 25, WHITE);
		puts(" ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

		c = _getch();
		if (c == 0x00 || c == 0xE0) c = _getch();
		if (c == 80 || c == 72) {
			switch (c) {
				// UP
				case 72: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now > 0) now--;
					else if (now == 0) now = 1;
					break;
				}
				// DOWN
				case 80: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now < 1) now++;
					else if (now == 1) now = 0;
					break;
				}
			}
			continue;
		}
		// ���� Ȥ�� ����
		else if (c == 13) break;
		else if (c == 27) {
			now = -1;
			break;
		}
	}
	return now;
}

void gotoXY(int x, int y) {
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int mainMenu() {
	char c = 0, now = 0; 
	const int y[] = {16, 18, 20, 22, 24};
	const int x1 = 51, x2 = 67;
	int rcd[10];
	
	FILE *rc;
	rc = fopen("udata.txt", "r");
	
	fseek(rc, -40, SEEK_END);
	for(i=0; i<10; i++){
		fscanf(rc, "%d", &rcd[i]);
	}
	if(rcd[2] > 10){
		fseek(rc, -35, SEEK_END);
		for(i=0; i<10; i++){
			fscanf(rc, "%d", &rcd[i]);
		}
	}

	system("cls");

	gotoXY(53, 4); printf("Ÿ  ��  ��  ��");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoXY(75, 28); puts("����Ű�� Ŀ���� �̵�, ���ͷ� �����ϼ���.");

	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(x1, y[now]); printf("��");
		gotoXY(x2, y[now]); printf("��");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoXY(42, 9); 
		if(rcd[0] == 1) printf("�ֱ� ������ ���� :	�ڸ� ����");
		else if(rcd[0] == 2) printf("�ֱ� ������ ���� :	�ܾ� ����");
		else if(rcd[0] == 3) printf("�ֱ� ������ ���� :	ª�� �� ����");
		else printf("�ֱ� ������ ���� :	��� ����");
		gotoXY(27, 11); printf("�ֱ� ���(��ǥ/�ɸ��ð�/����/����/��Ȯ��) : %d / %04d / %d / %d / %d", rcd[2], rcd[3], rcd[4], rcd[5], rcd[6], rcd[7]);
		Box(20, 7, 100, 13, WHITE);
		
		if (now == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 4, y[0]); printf("�ڸ�  ����");
		
		if (now == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 4, y[1]); printf("�ܾ�  ����");

		if (now == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 3, y[2]); printf("ª�� �� ����");

		if (now == 3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 4, y[3]); printf("���  Ȯ��");

		if (now == 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY);
		gotoXY(x1 + 5, y[4]); printf("��    ��");
		Box(46, 14, 73, 26, WHITE);
		puts(" ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

		c = _getch();
		if (c == 0x00 || c == 0xE0) c = _getch();
		if (c == 80 || c == 72) {
			switch (c) {
				// UP
				case 72: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now > 0) now--;
					else if (now == 0) now = 4;
					break;
				}
				// DOWN
				case 80: {
					gotoXY(x1, y[now]); printf("  ");
					gotoXY(x2, y[now]); printf("  ");
					if (now < 4) now++;
					else if (now == 4) now = 0;
					break;
				}
			}
			continue;
		}
		// ���� Ȥ�� ����
		else if (c == 13) break;
		else if (c == 27) {
			now = -1;
			break;
		}
	}
	return now;
}

int main(int argc, char* argv[]) {
	char selectedMenu;
	char keep;
	
	//UI 
	system("title Ÿ�� ����");
	system("mode con cols=120 lines=30");

	while (1) {
		system("cls");

		// �׸� ����
		selectedMenu = mainMenu();

		system("cls");

		switch (selectedMenu) {
			// ����
			case -1: {
				system("cls");
				gotoXY(50, 3);
				puts("���α׷��� �����մϴ�\n\n\n\n\n\n\n\n");
				return 0;
			}
			// �ڸ� ���� 
			case 0:{
				while (1) {
					keep = letter(selectedMenu);
					if (keep == -1 || keep == 2){
						break;
					}
					else if (keep == 0){
						keep = choose(selectedMenu);
						if(keep == 0){
							z = 15;
							tp = 1;
							keep = k_letter(selectedMenu);
						}
						else if(keep == 1){
							z = 25;
							tp = 1;
							keep = k_letter(selectedMenu);
						}
						else if(keep == 2){
							z = 35;
							tp = 1;
							keep = k_letter(selectedMenu);
						}
						else if(keep == 3){
							break;
						}
					}
					else if (keep == 1){
						keep = choose(selectedMenu);
						if(keep == 0){
							z = 15;
							tp = 1;
							keep = e_letter(selectedMenu);
						}
						else if(keep == 1){
							z = 25;
							tp = 1;
							keep = e_letter(selectedMenu);
						}
						else if(keep == 2){
							z = 35;
							tp = 1;
							keep = e_letter(selectedMenu);
						}
						else if(keep == 3){
							break;
						}
					}
				}
				break;
			}
			//�ܾ� ���� 
			case 1:{
				while (1) {
					keep = word(selectedMenu);
					if (keep == -1 || keep == 2){
						break;
					}
					else if (keep == 0){
						keep = choose(selectedMenu);
						if(keep == 0){
							z = 15;
							tp = 2;
							keep = k_word(selectedMenu);
						}
						else if(keep == 1){
							z = 25;
							tp = 2;
							keep = k_word(selectedMenu);
						}
						else if(keep == 2){
							z = 35;
							tp = 2;
							keep = k_word(selectedMenu);
						}
					}
					else if (keep == 1){
						keep = choose(selectedMenu);
						if(keep == 0){
							z = 15;
							tp = 2;
							keep = e_word(selectedMenu);
						}
						else if(keep == 1){
							z = 25;
							tp = 2;
							keep = e_word(selectedMenu);
						}
						else if(keep == 2){
							z = 35;
							tp = 2;
							keep = e_word(selectedMenu);
						}
					}
				}
				break;
			}
			//ª�� �� ���� 
			case 2: {
				while (1) {
					keep = s_text(selectedMenu);
					if (keep == -1 || keep == 2){
						break;
					}
					else if (keep == 0){
						keep = choose(selectedMenu);
						if(keep == 0){
							z = 15;
							tp = 3;
							keep = k_s_text(selectedMenu);
						}
						else if(keep == 1){
							z = 25;
							tp = 3;
							keep = k_s_text(selectedMenu);
						}
						else if(keep == 2){
							z = 25;
							tp = 3;
							keep = k_s_text(selectedMenu);
						}
					}
					else if (keep == 1){
						keep = choose(selectedMenu);
						if(keep == 0){
							z = 15;
							tp = 3;
							keep = e_s_text(selectedMenu);
						}
						else if(keep == 1){
							z = 25;
							tp = 3;
							keep = e_s_text(selectedMenu);
						}
						else if(keep == 2){
							z = 25;
							tp = 3;
							keep = e_s_text(selectedMenu);
						}
					}
				}
				break;
			}
			//��� Ȯ�� 
			case 3: {
				while (1) {
					keep = record(selectedMenu);
					if (keep == 0) cg = 1;
					else if (keep == 1) cg = 2;
					else if (keep == 2 || keep == -1) break;
				}
				break;
			}
			//���� 
			case 4: {
				system("cls");
				gotoXY(50, 3);
				puts("���α׷��� �����մϴ�\n\n\n\n\n\n\n\n");
				return 0;
			}
		}
	}
}
