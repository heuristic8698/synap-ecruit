/**
* @FileName : quiz.cpp
* @Project : 2018 summer
* @Date : 2018-07-05
* @�ۼ��� : �赿��
* @�����̷� : 2018-07-05 �ʱ���� �ۼ�
* @���� : ���̳� ����Ʈ 2018 �ϰ� ��ä ä�� ����
*/

#include <cstdio>
#include <string.h>
#include <windows.h>

#define font_cnt 27			// ���� ���� ��Ʈ �� 27
#define row_size 7			// ��Ʈ �� ũ�� 7
#define col_size 6			// ��Ʈ �� ũ�� 6
#define str_size 32			// ���� ���� �Է°� ���� ����, str_size-2�� ��� �ִ� ����
#define row_enlarge 6		// ��Ʈ ��� �� Ȯ�� ��� 6
#define col_enlarge 2		// ��Ʈ ��� �� Ȯ�� ��� 2
#define TRUE 1				// ���� ���� ����� ���� TRUE �� ����

/**
* Function Name : convert
* @�ۼ��� : 2018-07-05
* @�ۼ��� : �赿��
* @�����̷� : 2018-07-05 �ʱ���� �ۼ�
* @���� : ��Ʈ ���� �� 0, 1�� ������ ����(' ', '@')�� ��ȯ�ؼ� �����ϱ� ���� ��ȯ �Լ�
*/
char convert(char a) {
	if (a == '1') return '@';
	else return ' ';
}

/**
* Function Name : get_font
* @�ۼ��� : 2018-07-05
* @�ۼ��� : �赿��
* @�����̷� : 2018-07-05 �ʱ���� �ۼ�
* @���� : ���Ͽ� ����� ��Ʈ ���� 3���� �迭�� �����ϴ� �Լ�
*/
int get_font(char font[][row_size][col_size]) {
	int n = 0;				// �Է� ���� ��Ʈ�� ����
	char a = 0;				// ��Ʈ ������ ���� ����
	FILE *input = NULL;		// ��Ʈ ������ ���� ���� ������
	errno_t err = 0;		// ���� �б� ���� Ȯ�� ����

	// ���� �б� �� ���� Ȯ��
	err = fopen_s(&input, "input.txt", "r");
	if (err == 0) {
		printf_s("��Ʈ ���� Ȯ��\n\n");
	}
	else {
		printf_s("��Ʈ ���� Ȯ�� �Ұ�\n");
		printf_s("���α׷��� �����մϴ�\n");
		system("pause");
		return 1;
	}

	fscanf_s(input, "%d\n", &n);	// �Է� ���� ��Ʈ ���� ����

	// �Է� ���� ��Ʈ ���� ��ŭ ��� ���� �ݺ�
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < row_size; ++j) {
			for (int k = 0; k < col_size; ++k) {
				fscanf_s(input, "%c", &a, sizeof(char));
				font[i][j][k] = convert(a);	// �Է¹��� ��(0,1)�� ����(' ','@')�� ��ȯ �� ����
											// font[0]~[25] �� A ~ Z ���� ��Ʈ �����Ͱ� ����
			}
			fgetc(input);
		}
		fgetc(input);
	}
	fclose(input);
	//	�迭�� �������� ���鿡 �ش��ϴ� �����͸� ����
	for (int j = 0; j < row_size; ++j) {
		for (int k = 0; k < col_size; ++k) {
			font[font_cnt-1][j][k] = ' ';
		}
	}
	return 0;
}

/**
* Function Name : check_font
* @�ۼ��� : 2018-07-05
* @�ۼ��� : �赿��
* @�����̷� : 2018-07-05 �ʱ���� �ۼ�
* @���� : ��Ʈ ������ ���� ���� Ȯ�ο� ��� �Լ�
*/
void check_font(char font[][row_size][col_size]) {
	//font �迭�� ����� ���� ������ ������� �����ؼ� Ȯ��
	for (int i = 0; i < font_cnt; ++i) {
		for (int j = 0; j < row_size; ++j) {
			for (int k = 0; k < col_size; ++k) {
				printf_s("%c", font[i][j][k]);
			}
			printf_s("\n");
		}
		printf_s("\n");
	}
}

/**
* Function Name : print_font
* @�ۼ��� : 2018-07-05
* @�ۼ��� : �赿��
* @�����̷� : 2018-07-05 �ʱ���� �ۼ�
* @���� : �Է� ���� �ش��ϴ� ��Ʈ�� Ȯ�� ����ϴ� �Լ�
*/
void print_font(char* str, char font[][row_size][col_size]) {
	int i = 0;
	// �Է� ���� ���� ���ڿ��� ��ȿ�� ��(���� �빮�� �Ǵ� ����)���� ���ʷ� Ȯ��
	for (int idx = 0; idx < strlen(str); ++idx) {
		i = str[idx] - 'A'; // ���� �빮�ڸ� �Է¹ޱ� ������ �Է¹��� ������ 'A' ���� ����
							// �Է� ���� �ش��ϴ� ��Ʈ �����Ͱ� ����� ��ġ�� i�� ����
		if (i < 0) i = font_cnt - 1;	// ���� 0���� ���� ��� �Է� ���� �����̱� ������
										// ���鿡 �ش��ϴ� font_cnt-1 ���� i�� ����

		// �迭�� ȸ���Ͽ� ����ϱ� ���� �� �켱 �ݺ����� ���� ���� �Ʒ� ������ ���ʷ� ���� �ö󰡸鼭 ���� ���
		for (int k = 0; k < col_size; ++k) {
			for (int col_cnt = 0; col_cnt < col_enlarge; ++col_cnt) {			// �� Ȯ�븦 ���� �ݺ�
				for (int j = row_size - 1; j >= 0; --j) {
					for (int row_cnt = 0; row_cnt < row_enlarge; ++row_cnt) {	// �� Ȯ�븦 ���� �ݺ�
						printf_s("%c", font[i][j][k], sizeof(char));
					}
				}
				printf_s("\n");
			}
		}
		printf_s("\n");
	}
}

/**
* Function Name : get_str
* @�ۼ��� : 2018-07-05
* @�ۼ��� : �赿��
* @�����̷� : 2018-07-05 �ʱ���� �ۼ�
* @���� : ��ȿ�� ��(���� �빮�ڿ� ���� ������ �̷���� ���̰� str_size �̳��� ���ڿ�)��
*		  �Է¹ޱ� ���� �Լ�
*/
void get_str(char* str) {
	int check = 0;
	int length = 0;
	while (TRUE) {
		printf_s("���� ������ �Է����ּ���!!(���� �빮�ڿ� ���鸸) : ");
		fgets(str, str_size, stdin);
		check = 0;
		length = strlen(str) - 1;
		// �Է� ���� ���ڿ��� \n�� ����Ǵ��� Ȯ��
		if (str[length] != '\n') {					
			//\n�� ������� �ʾ����� �Է� �� �ʰ� �޽��� ��� �� �Է� ���� ����
			printf("�Է� ���ڿ��� %d�ڸ� ���� �� �����ϴ�.(�ѱ� �Է� �Ұ�)\n", str_size-2);
			while (getchar() != '\n') {}
			continue;
		}
		// �Է� ���� ���ڿ��� ���ʷ� �����̳� ���� �빮�ڰ� �ƴ� ���� �ִ��� Ȯ��
		for (int i = 0; i < length; ++i) {	
			if ((str[i] != ' ') && (str[i] < 'A' || 'Z' < str[i])) {
				check++;
				break;
			}
		}
		// �����̳� ���� �빮�ڰ� �ƴ� ���� �ִٸ� �ٽ� �Է�
		if (check > 0) {
			printf("�Է� ���� ���� �빮�ڿ� ����(' ')�� ���԰����մϴ�. \n");
			continue;
		}
		break;
	}
}

int main() {
	char font[font_cnt][row_size][col_size] = { 0, };
	char str[str_size] = { 0, };
	if (get_font(font)) return 0;
	//check_font(font);
	get_str(str);
	printf_s("���� ���� Ȯ��!! : %s\n", &str, sizeof(char)*strlen(str));
	print_font(str, font);
	printf_s("\n���� ������ ��µǾ����ϴ�.\n���α׷��� �����մϴ�.\n");
	system("pause");
	return 0;
}
