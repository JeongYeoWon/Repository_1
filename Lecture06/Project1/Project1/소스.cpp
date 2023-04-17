#include <iostream>
using namespace std;
class Animal {
	//����� �����
	public:
		Animal() {
			cout << "���� ź��" << endl;
		}
		virtual ~Animal() {
			cout << "���� ����" << endl;
		}

		virtual void Meow() {
			cout << "���� �Ҹ�" << endl;
		}
};
	class Cat : public Animal {
	public:
		Cat() {
			cout << "cat : �� ���� ź���ߴ�." << endl;
		}
		~Cat() {
			cout << "cat : ���ƾ�!!(����ϰ� ���Ҵ�...)" << endl;
		}

		void Meow() {
			cout << "cat : (��Ű� ���� ����ġ���� ��½ ������)�Ͽ�." << endl;
		}
	};

	class Tiger : public Animal {
	public:
		Tiger() {
			cout << "tiger : ���� �¾���ϱ�(ź��)?" << endl;
		}
		~Tiger() {
			cout << "tiger : ���� �׾����ϴ�(���)." << endl;
		}

		void Meow() {
			cout << "tiger : ����ֽ��ϴ�." << endl;
		}
	};

	class Hamstar : public Animal {
	public:
		Hamstar() {
			cout << "Hamstar : �t(ź��)?" << endl;
		}
		~Hamstar() {
			cout << "Hamstar : ����..(����)" << endl;
		}
		void Meow() {
			cout << "Hamstar : ������������" << endl;
		}
	};

int main() {
	cout << "����� ��"<<endl;
	cout << endl;
	printf("�����\n\n");

	int animalNum = 3;
	Animal** ani = new Animal*[animalNum];

	ani[0] = new Cat();
	ani[1] = new Tiger();
	ani[2] = new Hamstar();

	for (size_t i = 0; i < animalNum; i++) { //size_t�� ���ڿ��̳� �޸��� ����� ��Ÿ�� �� ���
		ani[i] -> Meow();
		delete(ani[i]);
	}

	/*Cat *c = new Tiger();
	Tiger* t = (Tiger*)c;
	c->Meow();*/
	//c->Meo();
	/*delete (t);*/
}
