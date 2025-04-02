#include<iostream>
#include<windows.h>
#include<random>
#include<ctime>
using namespace std;

// card는 객체임 안쓸때는 빈 객체를 생성하여 0을 전달할것 
void draw(int Ai_Lp, int Player_Lp, int card1, int card2, int card3, int card4, int card5, int card6) {
	cout << "|----------------------------------------\n";
	cout << "|\t\tAI LP : " << Ai_Lp << "\n";
	cout << "|\n";
	cout << "|    " << card1 << "\t\t   " << card2 << "\t\t   " << card3 << "\n";
	cout << "| atk :\t" << card1 << "\tatk : " << card2 << "\tatk : " << card3 << "\n";
	cout << "| HP  :\t" << card1 << "\tHP  : " << card2 << "\tHP  : " << card3 << "\n";
	cout << "|\n";
	cout << "|\n";
	cout << "|\n";
	cout << "|    " << card1 << "\t\t   " << card2 << "\t\t   " << card3 << "\n";
	cout << "| atk :\t" << card1 << "\tatk : " << card2 << "\tatk : " << card3 << "\n";
	cout << "| HP  :\t" << card1 << "\tHP  : " << card2 << "\tHP  : " << card3 << "\n";
	cout << "|\n";
	cout << "|\t    Player LP : " << Ai_Lp << "\n";
	cout << "|----------------------------------------\n";
	cout << "|\t" << card6 << endl;
	cout << "|\t" << card6 << endl;
	cout << "|\t" << card6 << endl;
	cout << "|\t" << card6 << endl;
	cout << "|\t" << "턴을 종료합니다. " << endl;
	cout << "|----------------------------------------\n";

}

void turn() {

}

//게임진행
void game() {
	system("cls");
	draw(1000, 1000, 10, 10, 10, 10, 10, 10);

}

//첫턴은 다르게 돌려야함 
void First_Turn() {
	cout << "플레이어 턴 입니다.\n";
	cout << "낼 카드를 고르세요. : ";
	int choose = 0;
	cin >> choose;
	pickup_Card(choose);
	
}

//카드뽑기함수
void pickup_Card(int choose) {
	std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
	std::uniform_int_distribution<> dis(1, 12);
	int randomCard1 = dis(gen); //랜덤카드뽑기 
	int randomCard2 = dis(gen);
	int randomCard3 = dis(gen);
}

//사용자의 공격력과 체력을 받아서 공격력-체력을 return
int Attack(int atk, int hp) {
	if (atk - hp < 0) {
		//죽어야함 (함수)
		return atk - hp;
	}
	return atk - hp;
}
int Heal(int skill, int hp) {
	return skill + hp;
}

int main() {
	int choose;
	cout << "===Game !===\n1. Insert Coin\n2. end\ninput : ";
	cin >> choose;
	if (choose == 1) {
		game();
	}
	else if (choose == 2) {
		return 0;
	}
}