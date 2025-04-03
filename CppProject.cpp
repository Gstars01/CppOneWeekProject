#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<string>

using namespace std;

void Game();
void First_Turn();
int Pickup_Card();
int Attack(vector<Card*>);

//카드 구현부
class Card {
protected:
	int atk, def, hp, coolTime = 0;
	string name;
public:
	Card(int a, int b, int c, string d) : atk(a), def(b), hp(c), name(d) {}
	string getName() { return name; }
	void setDef(int a) { def = a; }
	void setHp(int a) { hp = a;}
	void setCoolTime(int a) { coolTime = a; }
	int getAtk() { return atk; }
	int getdef() { return def; }
	int getHp() { return hp; }
	virtual int Skill(vector<Card*>) = 0;
};

class Warrior : public Card {
public:
	Warrior() : Card(6, 0, 12, "전사") {}
	int Skill(vector<Card*> p) override {
		// 방어력 4
		p[0]->setDef(def + 4);
		// 쿨타임 3
		p[0]->setCoolTime(3);
		return 0;
	}
};

class Paladin : public Card {
public:
	Paladin() : Card(5, 0, 14, "성기사") {}
	int Skill(vector<Card*> p) override {
		// 방어력 4 회복 2
		p[0]->setDef(def + 4);
		p[0]->setHp(hp + 2);
		// 쿨타임 4
		p[0]->setCoolTime(4);
		return 0;
	}
};

class Archer : public Card {
public:
	Archer() : Card(7, 0, 9, "궁수") {}
	int Skill(vector<Card*> p) override {
		// 3명 히트
		Attack(p);
		// 쿨타임 3
		setCoolTime(3);
		return 0;
	}
};

class Hunter : public Card {
public:
	Hunter() : Card(8, 0, 10, "헌터") {}
	int Skill(vector<Card*> p) override {
		// 1명 1.2배 나머지 0.5배 히트
		// 쿨타임 3
		setCoolTime(3);
		return 0;
	}
};

class Thief : public Card {
public:
	Thief() : Card(7, 0, 8, "도적") {}
	int Skill(vector<Card*> p) override {
		// 데미지 2배
		// 쿨타임 3
		setCoolTime(3);
		return 0;
	}
};

class Assassin : public Card {
public:
	Assassin() : Card(8, 0, 7, "암살자") {}
	int Skill(vector<Card*> p) override {
		// 1명 1.5배
		// 쿨타임 3
		setCoolTime(3);
		return 0;
	}
};

class Rogue : public Card {
public:
	Rogue() : Card(6, 0, 9, "로그") {}
	int Skill(vector<Card*> p) override {
		// 1명 0.9배 2회 타격
		// // 쿨타임 3
		setCoolTime(3);
		return 0;
	}
};

class Priest : public Card {
public:
	Priest() : Card(4, 0, 12, "성직자") {}
	int Skill(vector<Card*> p) override {
		// 4 회복
		// 쿨타임 4
		setCoolTime(4);
		return 0;
	}
};

class Bard : public Card {
public:
	Bard() : Card(4, 0, 10, "음유시인") {}
	int Skill(vector<Card*> p) override {
		// 1명 공격력 +1 체력 +2
		// 쿨타임 3
		setCoolTime(3);
		return 0;
	}
};

class Mage : public Card {
public:
	Mage() : Card(9, 0, 6, "마법사") {}
	int Skill(vector<Card*> p) override {
		// 데미지 2배
		// 쿨타임 3
		setCoolTime(3);
		return 0;
	}
};

class Sorcerer : public Card {
public:
	Sorcerer() : Card(8, 0, 6, "소서러") {}
	int Skill(vector<Card*> p) override {
		// 3명 히트
		// 쿨타임 3
		setCoolTime(3);
		return 0;
	}
};

class Necromancer : public Card {
public:
	Necromancer() : Card(8, 0, 6, "네크로맨서") {}
	int Skill(vector<Card*> p) override {
		// 공격력 1.5배 스텟 흡수
		// 쿨타임 4
		setCoolTime(4);
		return 0;
	}
};


// 게임 시스템 
Card* Job[12] = { new Warrior(), new Paladin(), new Archer(), new Hunter(), new Thief(), new Assassin(), new Rogue(), new Priest(), new Bard(), new Mage(), new Sorcerer(), new Necromancer() };

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
		cout << "|-----------------------------------------\n";	*/

}

// 게임진행
void Game() {
	system("cls");
	draw(1000, 1000, 10, 10, 10, 10, 10, 10);
	First_Turn();
}

// 첫번째 턴 진행 함수
void First_Turn() {
	cout << "플레이어 턴 입니다.\n";
	int choose = Pickup_Card();
	cout << "| " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
}

// 턴 진행 함수
void Turn() {

}

// 공격
template <typename T>
T Attack(Card* attacker, vector<Card*> defenders) {
	for (Card* defender : defenders) {
		if (defender->def >= attacker->atk) {
			defender->setDef(defender->def -= attacker->atk);
			return 0;
		}
		else if (defender->hp + defender->def - attacker->atk < 0) {
			// 사망
		}
		else {
			return defender->hp + defender->def - attacker->atk;
		}
	}
}

int Heal(int skill, int hp) {
	return skill + hp;
}

//카드뽑기함수
int Pickup_Card() {
	std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
	std::uniform_int_distribution<> dis(0, 11);
	int randomCard1 = dis(gen); //랜덤카드뽑기 
	int randomCard2 = dis(gen);
	int randomCard3 = dis(gen);
	cout << "| 뽑은 카드\n";
	cout << "| 1. " << Job[randomCard1]->getName() << endl;
	cout << "| 2. " << Job[randomCard2]->getName() << endl;
	cout << "| 3. " << Job[randomCard3]->getName() << endl;
	cout << "| 낼 카드를 고르세요. : ";
	int choose = 0;
	cin >> choose;
	if (choose == 1) {
		return randomCard1;
	}
	else if (choose == 2) {
		return randomCard2;
	}
	else if (choose == 3) {
		return randomCard3;
	}
	else {
		cout << "입력이 잘못되었습니다 !!";
		Game();
	}
}