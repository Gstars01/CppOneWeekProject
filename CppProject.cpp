#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<string>

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

int Attack(Card* , vector<Card*>);

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
Card* Job[12] = { new Warrior(), new Paladin(), new Archer(), new Hunter(), new Thief(), new Assassin(), new Rogue(), new Priest(), new Bard(), new Mage(), new Sorcerer(), new Necromancer() };
vector<Card*> aiF = {};
vector<Card*> playerF = {};
void Game();
void First_Turn();
void Second_Turn();
int Pickup_Card();
int Ai_Pickup_Card();
void Ai_Turn();
int playerLP = 1;
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
		cout << "\tDef :" << aiF[i]->getDef();
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
		cout << "\tDef :" << playerF[i]->getDef();
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
int Ai_attack();
void Ai_Turn2();
// 게임진행
void Game() {
	system("cls");
	draw(aiLp, playerLP);
	First_Turn();
	Ai_Turn();
	
	while (1) {
		Second_Turn();
		if (aiLp <= 0) {
			cout << "플레이어 승";
			break;
		}
		else if (playerLP <= 0) {
			cout << "AI 승";
			break;
		}
		cin.ignore();
		cin.get();
		Ai_Turn2();
		if (aiLp <= 0) {
			cout << "플레이어 승";
			break;
		}
		else if (playerLP <= 0) {
			cout << "AI 승";
			break;
		}
	}
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

//두번째 턴 진행 함수
void Second_Turn() {
	system("cls");
	draw(aiLp, playerLP);
	cout << "| 플레이어 턴 입니다.\n";
	int choose = Pickup_Card(); 
	playerF.push_back(Job[choose]);
	system("cls");
	draw(aiLp, playerLP);
	cout << "| " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
	system("cls");
	Attack(playerF.back(), aiF);
	system("cls");
	draw(aiLp, playerLP);
}

void Ai_Turn2() {
	system("cls");
	int choose = Ai_Pickup_Card();
	aiF.push_back(Job[choose]);
	draw(aiLp, playerLP);
	cout << "| Ai 는 " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
	cout << "| Ai의 공격 단계로 넘어갑니다.\n";
	cout << "|----------------------------------------\n";
	cin.get();
	system("cls");
	Ai_attack();
	system("cls");
	draw(aiLp, playerLP);
	cout << "| Ai의 공격이 끝났습니다.\n";
	cout << "| 플레이어의 차례로 넘어갑니다.\n";
	cout << "|----------------------------------------\n";
	cin.get();
}
//ai 공격
int Ai_attack() {
	system("cls");
	draw(aiLp, playerLP);
	std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
	std::uniform_int_distribution<> did(0,aiF.size() - 1);
	int random1 = did(gen);
	Card* attacker = aiF[random1];
	int lowhp = 0;
	for (int i = 1; i < playerF.size(); i++) {
		if (playerF[i]->getHp() < playerF[lowhp]->getHp()) {
			lowhp = i;
		}
	}
	Card* defender = playerF[lowhp];
	cout << "| "<< attacker->getName() << " 카드로 " << defender->getName() << "을 공격합니다!" << endl;
	cin.get();
	if (defender->getHp() + defender->getDef() >= attacker->getAtk()) {
		if (defender->getDef() >= attacker->getAtk()) {
			defender->setDef(defender->getDef() - attacker->getAtk());
			return 0;
		}
		else {
			defender->setHp(defender->getDef() + defender->getHp() - attacker->getAtk());
			defender->setDef(0);
			return 0;
		}
	}
	else if (defender->getHp() + defender->getDef() - attacker->getAtk() <= 0) {
		int damage = attacker->getAtk() - (defender->getHp() + defender->getDef());
		playerLP -= damage;
		playerF.erase(playerF.begin() + lowhp);
		return 0;
	}
	else {
		return defender->getHp() + defender->getDef() - attacker->getAtk();
	}
	
}
// 공격
int Attack(Card* attacker, vector<Card*> defenders) {
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
	if (choose1 < 1 || choose1 > defenders.size()) {
		cout << "| 잘못된 선택입니다. 다시 입력해주세요.\n";
		return Attack(attacker, defenders);  // 다시 공격을 시도하게 할 수 있음
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
		if (defender->getHp() + defender->getDef() >= attacker->getAtk()) {
			if (defender->getDef() >= attacker->getAtk()) {
				defender->setDef(defender->getDef() - attacker->getAtk());
				return 0;
			}
			else {
				defender->setHp(defender->getDef() + defender->getHp() - attacker->getAtk());
				defender->setDef(0);
				return 0;
			}
		}
		else if (defender->getHp() + defender->getDef() - attacker->getAtk() <= 0) {
			int damage = attacker->getAtk() - (defender->getHp() + defender->getDef());
			aiLp -= damage;
			aiF.erase(aiF.begin() + (choose1 - 1));
			return 0;
		}
		else {
			return defender->getHp() + defender->getDef() - attacker->getAtk();
		}
	}
	else if (choose2 == 2) {
		//스킬
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