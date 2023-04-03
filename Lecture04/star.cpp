#include <iostream>
#include <conio.h>
int main(){
	int count = 0;
	while(1){
		std::cout<<"*";
		if(-kbhit()){
			if(getchar() == 27){
				break;
			}
		}
	}
	return 0;
}	
