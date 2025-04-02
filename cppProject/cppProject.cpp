#include<iostream>
#include<windows.h>
#include<random>
#include<ctime>
using namespace std;

class Card {
protected:
	int atk, hp;
public:
	Card(int a, int b) : atk(a), hp(b) {}
	virtual int Skill() = 0;
};

class Warrior : public Card {
public:
	Warrior() : Card(6, 12) {}
	int Skill() override {
		// 데미지 감소 40%
		// 쿨타임 3
	}
};

class Paladin : public Card {
public:
	Paladin() : Card(5, 14) {}
	int Skill() override {
		// 데미지 감소 50% + 회복 2
		// 쿨타임 4
	}
};

class Archer : public Card {
public:
	Archer() : Card(7, 9) {}
	int Skill() override {
		// 3명 히트
		// 쿨타임 2
	}
};

class Hunter : public Card {
public:
	Hunter() : Card(8, 10) {}
	int Skill() override {
		// 1명 1.2배 나머지 0.5배 히트
		// 쿨타임 3
	}
};

class Thief : public Card {
public:
	Thief() : Card(7, 8) {}
	int Skill() override {
		// 데미지 2배, 기절 1턴
		// 쿨타임 2

	}
};

class Assassin : public Card {
public:
	Assassin() : Card(8, 7) {}
	int Skill() override {
		// 1명 1.5배
		// 쿨타임 3
	}
};

class Rogue : public Card {
public:
	Rogue() : Card(6, 9) {}
	int Skill() override {
		// 1명 0.9배 2회 타격
		// // 쿨타임 2
	}
};

class Priest : public Card {
public:
	Priest() : Card(4, 12) {}
	int Skill() override {
		// 4 회복
		// 쿨타임 4
	}
};

class Bard : public Card {
public:
	Bard() : Card(4, 10) {}
	int Skill() override {
		// 1명 공격력 +1 체력 +2
		// 쿨타임 3
	}
};

class Mage : public Card {
public:
	Mage() : Card(9, 6) {}
	int Skill() override {
		// 데미지 2배
		// 쿨타임 3
	}
};

class Sorcerer : public Card {
public:
	Sorcerer() : Card(8, 6) {}
	int Skill() override {
		// 3명 히트
		// 쿨타임 3
	}
};

class Necromancer : public Card {
public:
	Necromancer() : Card(8, 6) {}
	int Skill() override {
		// 공격력 1.5배 스텟 흡수
		// 쿨타임 4
	}
};

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