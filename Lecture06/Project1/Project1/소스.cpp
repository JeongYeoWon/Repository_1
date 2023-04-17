#include <iostream>
using namespace std;
class Animal {
	//고양이 만들기
	public:
		Animal() {
			cout << "동물 탄생" << endl;
		}
		virtual ~Animal() {
			cout << "동물 죽음" << endl;
		}

		virtual void Meow() {
			cout << "동물 소리" << endl;
		}
};
	class Cat : public Animal {
	public:
		Cat() {
			cout << "cat : 이 몸이 탄생했다." << endl;
		}
		~Cat() {
			cout << "cat : 으아악!!(사망하고 말았다...)" << endl;
		}

		void Meow() {
			cout << "cat : (당신과 눈을 마주치더니 슬쩍 웃으며)먀옹." << endl;
		}
	};

	class Tiger : public Animal {
	public:
		Tiger() {
			cout << "tiger : 제가 태어났습니까(탄생)?" << endl;
		}
		~Tiger() {
			cout << "tiger : 제가 죽었습니다(사망)." << endl;
		}

		void Meow() {
			cout << "tiger : 울고있습니다." << endl;
		}
	};

	class Hamstar : public Animal {
	public:
		Hamstar() {
			cout << "Hamstar : 쮝(탄생)?" << endl;
		}
		~Hamstar() {
			cout << "Hamstar : 쮜익..(죽음)" << endl;
		}
		void Meow() {
			cout << "Hamstar : 찍찍찍찍찍찍" << endl;
		}
	};

int main() {
	cout << "고양이 앱"<<endl;
	cout << endl;
	printf("고양이\n\n");

	int animalNum = 3;
	Animal** ani = new Animal*[animalNum];

	ani[0] = new Cat();
	ani[1] = new Tiger();
	ani[2] = new Hamstar();

	for (size_t i = 0; i < animalNum; i++) { //size_t는 문자열이나 메모리의 사이즈를 나타낼 때 사용
		ani[i] -> Meow();
		delete(ani[i]);
	}

	/*Cat *c = new Tiger();
	Tiger* t = (Tiger*)c;
	c->Meow();*/
	//c->Meo();
	/*delete (t);*/
}
