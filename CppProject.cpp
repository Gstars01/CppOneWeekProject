#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<string>

using namespace std;

//카드 구현부
class Card {
protected:
	int atk, def, hp;
	string name;
public:
	Card(int a, int b, int c, string d) : atk(a), def(b), hp(c), name(d) {}
	string getName() { return name; }
	int getAtk() { return atk; }
	int getdef() { return def; }
	int getHp() { return hp; }
	virtual int Skill() = 0;
};

class Warrior : public Card {
public:
	Warrior() : Card(6, 0, 12, "전사") {}
	int Skill() override {
		// 데미지 감소 40%
		
		// 쿨타임 3
		return 0;
	}
};

class Paladin : public Card {
public:
	Paladin() : Card(5, 0, 14, "성기사") {}
	int Skill() override {
		// 데미지 감소 50% + 회복 2
		// 쿨타임 4
		return 0;
	}
};

class Archer : public Card {
public:
	Archer() : Card(7, 0, 9, "궁수") {}
	int Skill() override {
		// 3명 히트
		// 쿨타임 2
		return 0;
	}
};

class Hunter : public Card {
public:
	Hunter() : Card(8, 0, 10, "헌터") {}
	int Skill() override {
		// 1명 1.2배 나머지 0.5배 히트
		// 쿨타임 3
		return 0;
	}
};

class Thief : public Card {
public:
	Thief() : Card(7, 0, 8, "도적") {}
	int Skill() override {
		// 데미지 2배
		// 쿨타임 2
		return 0;
	}
};

class Assassin : public Card {
public:
	Assassin() : Card(8, 0, 7, "암살자") {}
	int Skill() override {
		// 1명 1.5배
		// 쿨타임 3
		return 0;
	}
};

class Rogue : public Card {
public:
	Rogue() : Card(6, 0, 9, "로그") {}
	int Skill() override {
		// 1명 0.9배 2회 타격
		// // 쿨타임 2
		return 0;
	}
};

class Priest : public Card {
public:
	Priest() : Card(4, 0, 12, "성직자") {}
	int Skill() override {
		// 4 회복
		// 쿨타임 4
		return 0;
	}
};

class Bard : public Card {
public:
	Bard() : Card(4, 0, 10, "음유시인") {}
	int Skill() override {
		// 1명 공격력 +1 체력 +2
		// 쿨타임 3
		return 0;
	}
};

class Mage : public Card {
public:
	Mage() : Card(9, 0, 6, "마법사") {}
	int Skill() override {
		// 데미지 2배
		// 쿨타임 3
		return 0;
	}
};

class Sorcerer : public Card {
public:
	Sorcerer() : Card(8, 0, 6, "소서러") {}
	int Skill() override {
		// 3명 히트
		// 쿨타임 3
		return 0;
	}
};

class Necromancer : public Card {
public:
	Necromancer() : Card(8, 0, 6, "네크로맨서") {}
	int Skill() override {
		// 공격력 1.5배 스텟 흡수
		// 쿨타임 4
		return 0;
	}
};


// 게임 시스템 
Card* Job[12] = { new Warrior(), new Paladin(), new Archer(), new Hunter(), new Thief(), new Assassin(), new Rogue(), new Priest(), new Bard(), new Mage(), new Sorcerer(), new Necromancer() };
vector<Card*> aiF = {};
vector<Card*> playerF = {};
void Game();
void First_Turn();
int Pickup_Card();
int Ai_Pickup_Card();
void Ai_Turn();
int playerLP = 20;
int aiLp = 20;

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
void draw(int ai_Lp, int player_Lp) {
	cout << "|----------------------------------------\n";
	cout << "|\t\tAI LP : " << ai_Lp << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size();i++) {
		cout << "\t" << aiF[i]->getName();
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size();i++) {
		cout << "\tAtk : " << aiF[i]->getAtk();
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size();i++) {
		cout << "\tDef :" << aiF[i]->getdef();
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size();i++) {
		cout << "\tHp  : " << aiF[i]->getHp();
	}
	cout << "\n";
	cout << "|\n";
	cout << "|\n";
	cout << "|";
	for (int i = 0; i < playerF.size();i++) {
		cout << "\t" << playerF[i]->getName();
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < playerF.size();i++) {
		cout <<  "\tAtk : " << playerF[i]->getAtk();
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < playerF.size();i++) {
		cout << "\tDef :" << playerF[i]->getdef();
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < playerF.size();i++) {
		cout << "\tHp  : " << playerF[i]->getHp();
	}
	cout << "\n";
	cout << "|\n";
	cout << "|\t    Player LP : " << player_Lp << "\n";
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
	draw(aiLp, playerLP);
	First_Turn();
	Ai_Turn();
	First_Turn();
}

// 첫번째 턴 진행 함수
void First_Turn() {
	system("cls");
	draw(aiLp, playerLP);
	cout << "| 플레이어 턴 입니다.\n";
	int choose = Pickup_Card(); // 카드 뽑기( 인풋)
	playerF.push_back(Job[choose]);//필드 소환 
	//여기서 그려지는게 맞음 
	system("cls");
	draw(aiLp, playerLP);
	cout << "| " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
	cout << "| 첫턴이므로 공격을 수행하지 못합니다.\n";
	cout << "| 엔터를 눌러서 턴을 종료합니다.\n";
	cout << "|----------------------------------------";
	cin.ignore();
	cin.get( ); // Enter 입력 대기
} 

// 턴 진행 함수
void Turn() {
	system("cls");
	draw(aiLp, playerLP);
	cout << "|플레이어 턴 입니다\n";

}

void Ai_Turn() {
	system("cls");
	int choose = Ai_Pickup_Card();
	aiF.push_back(Job[choose]);//필드 소환
	draw(aiLp, playerLP);
	cout << "| Ai 는 " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
	cout << "| 엔터를 눌러서 Ai턴 종료를 확인 합니다.\n";
	cout << "|----------------------------------------\n";
	cin.get( ); // Enter 입력 대기
}

//방어력 적용하지 않는 공격
int Attack(int atk, int hp) {
	if (atk - hp < 0) {
		//죽어야함 (함수)
	}
	return atk - hp;
}
//방어력을 적용하는 공격
int Attack(int atk, int hp, double def) {
	if (hp - atk * def < 0) {
		//죽어야함 (함수)
	}
	return hp - atk * def;
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

int Ai_Pickup_Card() {
	std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
	std::uniform_int_distribution<> dis(0, 11);
	std::uniform_int_distribution<> did(1, 3);
	int randomCard1 = dis(gen); //랜덤카드뽑기 
	int randomCard2 = dis(gen);
	int randomCard3 = dis(gen);
	int choose = 0;
	choose = did(gen); 
	if (choose == 1) {
		return randomCard1;
	}
	else if (choose == 2) {
		return randomCard2;
	}
	else if (choose == 3) {
		return randomCard3;
	}
}