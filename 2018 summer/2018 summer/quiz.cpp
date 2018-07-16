/**
* @FileName : quiz.cpp
* @Project : 2018 summer
* @Date : 2018-07-05
* @작성자 : 김동은
* @변경이력 : 2018-07-05 초기버전 작성
* @설명 : 사이냅 소프트 2018 하계 공채 채용 퀴즈
*/

#include <cstdio>
#include <string.h>
#include <windows.h>

#define font_cnt 27			// 공백 포함 폰트 수 27
#define row_size 7			// 폰트 행 크기 7
#define col_size 6			// 폰트 열 크기 6
#define str_size 32			// 응원 문구 입력값 길이 제한, str_size-2가 허용 최대 길이
#define row_enlarge 6		// 폰트 출력 행 확대 배수 6
#define col_enlarge 2		// 폰트 출력 열 확대 배수 2
#define TRUE 1				// 무한 루프 사용을 위한 TRUE 값 정의

/**
* Function Name : convert
* @작성일 : 2018-07-05
* @작성자 : 김동은
* @변경이력 : 2018-07-05 초기버전 작성
* @설명 : 폰트 저장 시 0, 1을 지정한 문자(' ', '@')로 변환해서 저장하기 위한 변환 함수
*/
char convert(char a) {
	if (a == '1') return '@';
	else return ' ';
}

/**
* Function Name : get_font
* @작성일 : 2018-07-05
* @작성자 : 김동은
* @변경이력 : 2018-07-05 초기버전 작성
* @설명 : 파일에 저장된 폰트 값을 3차원 배열에 저장하는 함수
*/
int get_font(char font[][row_size][col_size]) {
	int n = 0;				// 입력 받을 폰트의 개수
	char a = 0;				// 폰트 데이터 저장 변수
	FILE *input = NULL;		// 폰트 데이터 저장 파일 포인터
	errno_t err = 0;		// 파일 읽기 에러 확인 변수

	// 파일 읽기 후 에러 확인
	err = fopen_s(&input, "input.txt", "r");
	if (err == 0) {
		printf_s("폰트 파일 확인\n\n");
	}
	else {
		printf_s("폰트 파일 확인 불가\n");
		printf_s("프로그램을 종료합니다\n");
		system("pause");
		return 1;
	}

	fscanf_s(input, "%d\n", &n);	// 입력 받을 폰트 개수 저장

	// 입력 받을 폰트 개수 만큼 행과 열을 반복
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < row_size; ++j) {
			for (int k = 0; k < col_size; ++k) {
				fscanf_s(input, "%c", &a, sizeof(char));
				font[i][j][k] = convert(a);	// 입력받은 값(0,1)을 문자(' ','@')로 변환 후 저장
											// font[0]~[25] 에 A ~ Z 까지 폰트 데이터가 저장
			}
			fgetc(input);
		}
		fgetc(input);
	}
	fclose(input);
	//	배열의 마지막에 공백에 해당하는 데이터를 저장
	for (int j = 0; j < row_size; ++j) {
		for (int k = 0; k < col_size; ++k) {
			font[font_cnt-1][j][k] = ' ';
		}
	}
	return 0;
}

/**
* Function Name : check_font
* @작성일 : 2018-07-05
* @작성자 : 김동은
* @변경이력 : 2018-07-05 초기버전 작성
* @설명 : 폰트 데이터 정상 저장 확인용 출력 함수
*/
void check_font(char font[][row_size][col_size]) {
	//font 배열에 저장된 값을 마지막 공백까지 포함해서 확인
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
* @작성일 : 2018-07-05
* @작성자 : 김동은
* @변경이력 : 2018-07-05 초기버전 작성
* @설명 : 입력 값에 해당하는 폰트를 확대 출력하는 함수
*/
void print_font(char* str, char font[][row_size][col_size]) {
	int i = 0;
	// 입력 받은 응원 문자열이 유효한 값(영어 대문자 또는 공백)인지 차례로 확인
	for (int idx = 0; idx < strlen(str); ++idx) {
		i = str[idx] - 'A'; // 영문 대문자만 입력받기 때문에 입력받은 값에서 'A' 값을 빼고
							// 입력 값에 해당하는 폰트 데이터가 저장된 위치를 i에 저장
		if (i < 0) i = font_cnt - 1;	// 값이 0보다 작은 경우 입력 값은 공백이기 때문에
										// 공백에 해당하는 font_cnt-1 값을 i에 저장

		// 배열을 회전하여 출력하기 위해 열 우선 반복으로 행의 가장 아래 값부터 차례로 위로 올라가면서 값을 출력
		for (int k = 0; k < col_size; ++k) {
			for (int col_cnt = 0; col_cnt < col_enlarge; ++col_cnt) {			// 열 확대를 위한 반복
				for (int j = row_size - 1; j >= 0; --j) {
					for (int row_cnt = 0; row_cnt < row_enlarge; ++row_cnt) {	// 행 확대를 위한 반복
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
* @작성일 : 2018-07-05
* @작성자 : 김동은
* @변경이력 : 2018-07-05 초기버전 작성
* @설명 : 유효한 값(영문 대문자와 공백 만으로 이루어진 길이가 str_size 이내의 문자열)을
*		  입력받기 위한 함수
*/
void get_str(char* str) {
	int check = 0;
	int length = 0;
	while (TRUE) {
		printf_s("응원 문구를 입력해주세요!!(영문 대문자와 공백만) : ");
		fgets(str, str_size, stdin);
		check = 0;
		length = strlen(str) - 1;
		// 입력 받은 문자열이 \n로 종료되는지 확인
		if (str[length] != '\n') {					
			//\n로 종료되지 않았으면 입력 값 초과 메시지 출력 후 입력 버퍼 비우기
			printf("입력 문자열은 %d자를 넘을 수 없습니다.(한글 입력 불가)\n", str_size-2);
			while (getchar() != '\n') {}
			continue;
		}
		// 입력 받은 문자열을 차례로 공백이나 영어 대문자가 아닌 값이 있는지 확인
		for (int i = 0; i < length; ++i) {	
			if ((str[i] != ' ') && (str[i] < 'A' || 'Z' < str[i])) {
				check++;
				break;
			}
		}
		// 공백이나 영어 대문자가 아닌 값이 있다면 다시 입력
		if (check > 0) {
			printf("입력 값은 영문 대문자와 공백(' ')만 포함가능합니다. \n");
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
	printf_s("응원 문구 확인!! : %s\n", &str, sizeof(char)*strlen(str));
	print_font(str, font);
	printf_s("\n응원 문구가 출력되었습니다.\n프로그램을 종료합니다.\n");
	system("pause");
	return 0;
}
