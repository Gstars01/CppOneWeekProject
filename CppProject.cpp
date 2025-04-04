﻿#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<string>

#define EMPTY 13

using namespace std;

//카드 구현부
class Card {
protected:
	int atk, def, hp, coolTime = 0;
	string name;
public:
	Card(int a, int b, int c, string d) : atk(a), def(b), hp(c), name(d) {}
	string getName() { return name; }
	void setDef(int a) { def = a; }
	void setHp(int a) { hp = a; }
	void setCoolTime(int a) { coolTime = a; }
	int getAtk() { return atk; }
	int getDef() { return def; }
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
Card* Job[12];
vector<Card*> aiF = {};
vector<Card*> playerF = {};
void Game();
void Player_First_Turn();
void Ai_First_Turn();
void Player_Turn();
void Ai_Turn();
void Attack(Card*, vector<Card*>);
void Ai_attack();
int Pickup_Card();
int Ai_Pickup_Card();
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
	cout << "|";
	for (int i = 0; i < 60; i++) {
		cout << "-";
	}
	cout << "\n";
	cout << "|\t\t     AI LP : " << ai_Lp << "\n";
	cout << "|\n";
	cout << "|";
	for (int i = 0; i < aiF.size(); i++) {
		cout << "\t" << aiF[i]->getName();
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size(); i++) {
		cout << "\tAtk : " << aiF[i]->getAtk() << "  ";;
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size(); i++) {
		cout << "\tDef :" << aiF[i]->getDef() << "  ";;
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size(); i++) {
		cout << "\tHp  : " << aiF[i]->getHp() << "  ";;
	}
	cout << "\n";
	cout << "|\n";
	cout << "|\n";
	cout << "|";
	for (int i = 0; i < playerF.size(); i++) {
		cout << "\t" << playerF[i]->getName();
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < playerF.size(); i++) {
		cout << "\tAtk : " << playerF[i]->getAtk() << "  ";
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < playerF.size(); i++) {
		cout << "\tDef :" << playerF[i]->getDef() << "  ";
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < playerF.size(); i++) {
		cout << "\tHp  : " << playerF[i]->getHp()<<"  ";
	}
	cout << "\n";
	cout << "|\n";
	cout << "|\t\t    Player LP : " << player_Lp << "\n";
	cout << "|";
	for (int i = 0; i < 60; i++) {
		cout << "-";
	}
	cout << "\n";

	/*	cout << "|\t" << card6 << endl;
		cout << "|\t" << card6 << endl;
		cout << "|\t" << card6 << endl;
		cout << "|\t" << card6 << endl;
		cout << "|\t" << "턴을 종료합니다. " << endl;
		cout << "|-----------------------------------------\n";	*/

}

void initializeJobs() {
	Job[0] = new Warrior();
	Job[1] = new Paladin();
	Job[2] = new Archer();
	Job[3] = new Hunter();
	Job[4] = new Thief();
	Job[5] = new Assassin();
	Job[6] = new Rogue();
	Job[7] = new Priest();
	Job[8] = new Bard();
	Job[9] = new Mage();
	Job[10] = new Sorcerer();
	Job[11] = new Necromancer();
}

// 게임진행
void Game() {
	system("cls");
	draw(aiLp, playerLP);
	Player_First_Turn(); // Ai_Turn (랜덤) 
	while (1){
		Ai_Turn();
		if (playerLP <= 0) break; // 게임 종료 조건
		Player_Turn();
		if (aiLp <= 0) break; // 게임 종료 조건
	}
}

// 플레이어 첫번째 턴
void Player_First_Turn() {
	system("cls");
	draw(aiLp, playerLP);
	cout << "| 플레이어 턴 입니다.\n";
	int choose = Pickup_Card(); // 카드 뽑기( 인풋)
	if (choose != EMPTY) {
		playerF.push_back(Job[choose]);
	}
	//여기서 그려지는게 맞음 
	system("cls");
	draw(aiLp, playerLP);
	if (choose != EMPTY) {
		cout << "| " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
	}
	cout << "| 첫턴이므로 공격단계를 종료합니다.\n";
	cout << "| 엔터를 눌러서 플레이어 턴을 종료합니다.\n";
	cout << "|";
	for (int i = 0; i < 60; i++) {
		cout << "-";
	}
	cin.ignore();
	cin.get( ); // Enter 입력 대기
} 

// AI 첫번째 턴
void Ai_First_Turn() {
	system("cls");
	int choose = Ai_Pickup_Card();
	aiF.push_back(Job[choose]);//필드 소환
	draw(aiLp, playerLP);
	cout << "| AI 는 " << Job[choose]->getName() << " 을(를) 소환했다!";
	cout << "| 첫턴이므로 공격단계를 종료합니다.\n";
	cout << "| 엔터를 눌러서 AI 턴을 종료합니다.\n";
	cout << "|";
	for (int i = 0; i < 60; i++) {
		cout << "-";
	}
	cin.get( ); // Enter 입력 대기
}

// 플레이어 턴 진행 함수
void Player_Turn() {
	system("cls");
	draw(aiLp, playerLP);
	cout << "| 플레이어 턴 입니다.\n";
	if (playerF.size() < 3) {
		int choose = Pickup_Card();
		if (choose != EMPTY) {
			playerF.push_back(Job[choose]);
		}
		system("cls");
		draw(aiLp, playerLP);
		if (choose != EMPTY) {
			cout << "| " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
		}
		else {
			// 스킵메시지
		}

		if (playerF.size() > 0) {
			system("cls");
			Attack(playerF.back(), aiF);
		}
		else {
			cout << "| 공격할 카드가 없으므로 공격단계를 종료합니다.\n";
			cout << "| 엔터를 눌러서 플레이어 턴을 종료합니다.\n";
			cout << "|";
			for (int i = 0; i < 60; i++) {
				cout << "-";
			}
			cin.ignore();
			cin.get();
		}
	}
	else {
		cout << "| 필드가 가득 찼으므로 소환단계를 종료합니다.\n";
		cout << "| 플레이어의 공격 단계로 넘어갑니다.\n";
		cout << "|";
		for (int i = 0; i < 60; i++) {
			cout << "-";
		}
		cin.get();
		Attack(playerF.back(), aiF);
	}

	if (aiLp <= 0) {
		system("cls");
		draw(aiLp, playerLP);
		cout << "| 플레이어 승" << endl;
		cout << "|";
		for (int i = 0; i < 60; i++) {
			cout << "-";
		}
		return;
	}
}

// AI 턴 진행 함수
void Ai_Turn() {
	system("cls");
	if (aiF.size() < 3) {
		int choose = Ai_Pickup_Card();
		aiF.push_back(Job[choose]);
		draw(aiLp, playerLP);
		cout << "| AI 턴 입니다.\n";
		cout << "| Ai 는 " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
		cout << "| Ai의 공격 단계로 넘어갑니다.\n";
		cout << "|";
		for (int i = 0; i < 60; i++) {
			cout << "-";
		}
	}
	else {
		draw(aiLp, playerLP);
		cout << "| AI 턴 입니다.\n";
		cout << "| 필드가 가득 찼으므로 소환단계를 종료합니다.\n";
		cout << "| AI의 공격 단계로 넘어갑니다.\n";
		cout << "|";
		for (int i = 0; i < 60; i++) {
			cout << "-";
		}
	}
	cin.get();
	system("cls");
	Ai_attack();
	if (playerLP <= 0) {
		system("cls");
		draw(aiLp, playerLP);
		cout << "| AI 승" << endl;
		cout << "|";
		for (int i = 0; i < 60; i++) {
			cout << "-";
		}
		return ;
	}
	system("cls");
	draw(aiLp, playerLP);
}
// AI 공격
void Ai_attack() {
	system("cls");
	draw(aiLp, playerLP);
	std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
	std::uniform_int_distribution<> did(0, aiF.size() - 1);
	int random1 = did(gen);
	Card* attacker = aiF[random1];
	int lowhp = 0;
	for (int i = 1; i < playerF.size(); i++) {
		if (playerF[i]->getHp() < playerF[lowhp]->getHp()) {
			lowhp = i;
		}
	}
	if (playerF.size() != 0) {
		Card* defender = playerF[lowhp];
		cout << "| " << attacker->getName() << " 카드로 " << defender->getName() << "을(를) 공격합니다!" << endl;
		if (defender->getHp() + defender->getDef() > attacker->getAtk()) {
			if (defender->getDef() >= attacker->getAtk()) {
				defender->setDef(defender->getDef() - attacker->getAtk());
			}
			else {
				defender->setHp(defender->getDef() + defender->getHp() - attacker->getAtk());
				defender->setDef(0);
			}
		}
		else if (defender->getHp() + defender->getDef()  <= attacker->getAtk()) {
			int damage = attacker->getAtk() - (defender->getHp() + defender->getDef());
			playerLP -= damage;
			playerF.erase(playerF.begin() + lowhp);

		}
	}
	else {
		playerLP -= attacker->getAtk();
		cout << "| " << attacker->getName() << " 카드로 플레이어를 직접 공격합니다!" << endl;
	}
	cout << "| 엔터를 눌러서 Ai턴 종료를 확인 합니다.\n";
	cout << "|";
	for (int i = 0; i < 60; i++) {
		cout << "-";
	}
	cin.get();
}
// 공격
void Attack(Card* attacker, vector<Card*> defenders) {
	//공격할 내 카드 선택
	system("cls");
	draw(aiLp, playerLP); 
	cout << "| 카드 선택\n";
	for (int i=0; i < playerF.size(); i++) {
		cout << "| " << i+1 << ". " << playerF[i]->getName() << endl;
	}
	cout << "| 상대를 공격할 카드를 선택하세요. : ";
	int choose0 = 0;
	cin >> choose0;
	//공격할 ai카드 선택
	system("cls");
	draw(aiLp, playerLP);
	cout << "| 상대 카드 목록:\n";
	for (int i = 0; i < defenders.size(); i++) {
		cout << "| " << i + 1 << ". " << defenders[i]->getName() << "\n";
	}
	cout << "| 공격할 상대 카드를 선택하세요. : ";
	int choose1 = 0;
	cin >> choose1;
	Card* chosenAttacker = playerF[choose0 - 1];
	if (choose1 < 1 || choose1 > defenders.size()) {
		cout << "| 잘못된 선택입니다. 다시 입력해주세요.\n";
		Attack(attacker, defenders);  // 다시 공격을 시도하게 할 수 있음
	}
	Card* defender = defenders[choose1-1];
	//공격 방법 선택
	system("cls");
	draw(aiLp, playerLP);
	cout << "| 공격명령\n";
	cout << "| 1. 일반 공격\n";
	cout << "| 2. 스킬 공격\n";
	cout << "| 공격 방법을 선택하세요. : ";
	int choose2 = 0;
	cin >> choose2;
	if (choose2 == 1) {
		system("cls");
		draw(aiLp, playerLP);
		cout << "| " << chosenAttacker->getName() << " 카드로 " << defender->getName() << "을 공격합니다!" << endl;
		cin.get();
		if (defender->getHp() + defender->getDef() > chosenAttacker->getAtk()) {
			if (defender->getDef() >= chosenAttacker->getAtk()) {
				defender->setDef(defender->getDef() - chosenAttacker->getAtk());
			}
			else {
				defender->setHp(defender->getDef() + defender->getHp() - chosenAttacker->getAtk());
				defender->setDef(0);
			}
		}
		else if (defender->getHp() + defender->getDef() <= chosenAttacker->getAtk()) {
			int damage = chosenAttacker->getAtk() - (defender->getHp() + defender->getDef());
			aiLp -= damage;
			aiF.erase(aiF.begin() + (choose1 - 1));
		}
		cout << "| 엔터를 눌러서 턴을 종료합니다.\n";
		cout << "|";
		for (int i = 0; i < 60; i++) {
			cout << "-";
		}
		cin.get();
	}
	else if (choose2 == 2) {
		//스킬
	}
}


//카드뽑기함수
int Pickup_Card() {
	std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
	std::uniform_int_distribution<> dis(0, 11);
	int randomCard1 = dis(gen); //랜덤카드뽑기 
	int randomCard2 = dis(gen);
	int randomCard3 = dis(gen);
	int empty = EMPTY;
	initializeJobs(); // 객체 초기화
	cout << "| 뽑은 카드\n";
	cout << "| 1. " << Job[randomCard1]->getName() << endl;
	cout << "| 2. " << Job[randomCard2]->getName() << endl;
	cout << "| 3. " << Job[randomCard3]->getName() << endl;
	cout << "| 4. 소환을 스킵하기."<<endl;
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
	else if (choose == 4) {
		return empty;
	}
	else {
		system("cls");
		draw(aiLp,playerLP);
		cout << "| 입력이 잘못되었습니다 !!\n";
		return Pickup_Card();
	}
}

int Ai_Pickup_Card() {
	std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
	std::uniform_int_distribution<> dis(0, 11);
	std::uniform_int_distribution<> did(1, 3);
	int randomCard1 = dis(gen); //랜덤카드뽑기 
	int randomCard2 = dis(gen);
	int randomCard3 = dis(gen);
	initializeJobs(); // 객체 초기화
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