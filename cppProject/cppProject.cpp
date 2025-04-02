#include<iostream>
#include<vector>
#include<windows.h>
#include<random>
#include<ctime>
#include<string>
using namespace std;


//카드 구현부
class Card {
protected:
	int atk, hp;
public:
	Card(int a, int b) : atk(a), hp(b) {}
	virtual string getName() = 0;
	virtual int Skill() = 0;
};

class Warrior : public Card {
	string name = "전사";
public:
	Warrior() : Card(6, 12) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 데미지 감소 40%
		// 쿨타임 3
		return 0;
	}
};

class Paladin : public Card {
	string name = "성기사";
public:
	Paladin() : Card(5, 14) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 데미지 감소 50% + 회복 2
		// 쿨타임 4
		return 0;
	}
};

class Archer : public Card {
	string name = "궁수";
public:
	Archer() : Card(7, 9) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 3명 히트
		// 쿨타임 2
		return 0;
	}
};

class Hunter : public Card {
	string name = "헌터";
public:
	Hunter() : Card(8, 10) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 1명 1.2배 나머지 0.5배 히트
		// 쿨타임 3
		return 0;
	}
};

class Thief : public Card {
	string name = "도적";
public:
	Thief() : Card(7, 8) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 데미지 2배, 기절 1턴
		// 쿨타임 2
		return 0;
	}
};

class Assassin : public Card {
	string name = "암살자";
public:
	Assassin() : Card(8, 7) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 1명 1.5배
		// 쿨타임 3
		return 0;
	}
};

class Rogue : public Card {
	string name = "로그";
public:
	Rogue() : Card(6, 9) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 1명 0.9배 2회 타격
		// // 쿨타임 2
		return 0;
	}
};

class Priest : public Card {
	string name = "성직자";
public:
	Priest() : Card(4, 12) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 4 회복
		// 쿨타임 4
		return 0;
	}
};

class Bard : public Card {
	string name = "음유시인";
public:
	Bard() : Card(4, 10) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 1명 공격력 +1 체력 +2
		// 쿨타임 3
		return 0;
	}
};

class Mage : public Card {
	string name = "마법사";
public:
	Mage() : Card(9, 6) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 데미지 2배
		// 쿨타임 3
		return 0;
	}
};

class Sorcerer : public Card {
	string name = "소서러";
public:
	Sorcerer() : Card(8, 6) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 3명 히트
		// 쿨타임 3
		return 0;
	}
};

class Necromancer : public Card {
	string name = "네크로맨서";
public:
	Necromancer() : Card(8, 6) {}
	string getName() override {
		return name;
	}
	int Skill() override {
		// 공격력 1.5배 스텟 흡수
		// 쿨타임 4
		return 0;
	}
};

	
//출력부
// 
// 
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
/*	cout << "|\t" << card6 << endl;
	cout << "|\t" << card6 << endl;
	cout << "|\t" << card6 << endl;
	cout << "|\t" << card6 << endl;
	cout << "|\t" << "턴을 종료합니다. " << endl;
	cout << "|----------------------------------------\n";	*/

}
void Trun();
void Game();
int Pickup_Card();
int Attack();
int Heal();
void First_Turn();

//게임 시스템 
Card* Job[] = { new Warrior(), new Paladin(), new Archer(), new Hunter(), new Thief(), new Assassin(), new Rogue(), new Priest(), new Bard(), new Mage(), new Sorcerer(), new Necromancer()};
void Turn() {

}

//게임진행
void Game() {
	system("cls");
	draw(1000, 1000, 10, 10, 10, 10, 10, 10);
	First_Turn();
}

//첫턴은 다르게 돌려야함 
void First_Turn() {
	cout << "플레이어 턴 입니다.\n";
	int choose = Pickup_Card();
	cout << "| " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
}

//카드뽑기함수
int Pickup_Card() {
	std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
	std::uniform_int_distribution<> dis(0, 11);
	int randomCard1 = dis(gen); //랜덤카드뽑기 
	int randomCard2 = dis(gen);
	int randomCard3 = dis(gen);
	cout << "| 뽑은 카드\n";
	cout << "| 1. "<<Job[randomCard1]->getName() <<endl;
	cout << "| 2. "<<Job[randomCard2]->getName() <<endl;
	cout << "| 3. "<<Job[randomCard3]->getName() <<endl;
	cout << "| 낼 카드를 고르세요. : ";
	int choose = 0;
	cin >> choose;
	if (choose == 1) {
		return randomCard1;
	}
	else if (choose == 2) {
		return randomCard1;
	}
	else if (choose == 3) {
		return randomCard3;
	}
	else {
		cout << "입력이 잘못되었습니다 !!";
		Game();
	}
}

//사용자의 공격력과 체력을 받아서 공격력-체력을 return
int Attack(int atk, int hp) {
	if (atk - hp < 0) {
		//죽어야함 (함수)
	}
	return atk - hp;
}
int Heal(int skill, int hp) {
	return skill + hp;
}

int main() {
	int choose;
	cout << "===Parallel Deck===\n1. Insert Coin\n2. end\ninput : ";
	cin >> choose;
	if (choose == 1) {
		Game();
	}
	else if (choose == 2) {
		return 0;
	}
}
