#include "util.h"

void CHECKERROR(int e) { // 에러 검사
	if (e == 1) { // e가 1일때
		printf("[line:%d, %s] 에러가 발생하였습니다.\n", __LINE__, __func__);
		exit(1);
	}
}