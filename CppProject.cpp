#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<string>

#define PLAYER_TURN 1
#define AI_TURN 2

#define EMPTY 13

using namespace std;

//카드 구현부 ( 부모클래스 )
class Card {
protected:
	int atk, hp, coolTime = 0;
	string name, skillFun;
public:
	Card(int a, int b, string c, string d) : atk(a), hp(b), name(c), skillFun(d) {}
	string getName() { return name; }
	void setHp(int a) { hp = a; }
	void setAtk(int a) { atk = a; }
	void setCoolTime(int a) { coolTime = a; }
	int getAtk() { return atk; }
	int getHp() { return hp; }
	int getCoolTime() { return coolTime; }
	string getSkillFun() { return skillFun;  }
	virtual void Skill() = 0;
};

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
void draw(int, int);
int Pickup_Card();
int Ai_Pickup_Card();
int playerLP = 20;
int aiLp = 20;
int turn;
// ( 자식클래스 ) 부모클래스 카드를 상속받음 
class Warrior : public Card {
public:
	Warrior() : Card(6, 12, "전사", "(본인 체력 6 증가/쿨타임 3턴)") {}
	void Skill() override {	//함수 오버라이딩 
		// 체력 6
		setHp(hp + 6);
		// 쿨타임 3
		setCoolTime(3);
	}
};

class Paladin : public Card {
public:
	Paladin() : Card(5, 14, "성기사", "(본인 체력 8 증가/쿨타임 4턴)") {}
	void Skill() override {
		// 체력 8
		setHp(hp + 8);
		// 쿨타임 4
		setCoolTime(4);
	}
};

class Archer : public Card {
public:
	Archer() : Card(7, 9, "궁수", "(모든 상대 6 데미지/쿨타임 5턴)") {}
	void Skill() override {
		// 상대 전체 데미지 6
		if (turn == PLAYER_TURN) {
			for (Card* p : aiF) {
				p->setHp(p->getHp() - 6);
			}
		}
		else {
			for (Card* p : playerF) {
				p->setHp(p->getHp() - 6);
			}
		}
		
		// 쿨타임 5
		setCoolTime(5);
	}
};

class Hunter : public Card {
public:
	Hunter() : Card(8, 10, "헌터", "(모든 상대 4 데미지/쿨타임 3턴)") {}
	void Skill() override {
		// 상대 전체 데미지 4
		if (turn == PLAYER_TURN) {
			for (Card* p : aiF) {
				p->setHp(p->getHp() - 4);
			}
		}
		else {
			for (Card* p : playerF) {
				p->setHp(p->getHp() - 4);
			}
		}

		// 쿨타임 3
		setCoolTime(3);
	}
};

class Thief : public Card {
public:
	Thief() : Card(7, 8, "도적", "(랜덤 상대 8데미지 및 본인 체력 1 증가/쿨타임 3턴)") {}
	void Skill() override {
		// 체력 1
		setHp(hp + 1);
		// 랜덤 상대 1명 데미지 8
		if (turn == PLAYER_TURN) {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, aiF.size() - 1);
			Card* ai = aiF[did(gen)];
			ai->setHp(ai->getHp() - 8);
		}
		else {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, playerF.size() - 1);
			Card* player = playerF[did(gen)];
			player->setHp(player->getHp() - 8);
		}
		// 쿨타임 3
		setCoolTime(3);
	}
};

class Assassin : public Card {
public:
	Assassin() : Card(8, 7, "암살자", "(랜덤 상대 10 데미지/쿨타임 3턴)") {}
	void Skill() override {
		// 랜덤 상대 1명 데미지 10
		if (turn == PLAYER_TURN) {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, aiF.size() - 1);
			Card* ai = aiF[did(gen)];
			ai->setHp(ai->getHp() - 10);
		}
		else {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, playerF.size() - 1);
			Card* player = playerF[did(gen)];
			player->setHp(player->getHp() - 10);
		}
		setCoolTime(3);
	}
};

class Rogue : public Card {
public:
	Rogue() : Card(6, 9, "로그", "(랜덤 상대 7 데미지 및 2 공격력 감소/쿨타임 3턴)") {}
	void Skill() override {
		if (turn == PLAYER_TURN) {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, aiF.size() - 1);
			Card* ai = aiF[did(gen)];
			ai->setHp(ai->getHp() - 7);
			ai->setAtk(ai->getAtk() - 2);
		}
		else {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, playerF.size() - 1);
			Card* player = playerF[did(gen)];
			player->setHp(player->getHp() - 7);
			player->setAtk(player->getAtk() - 2);;
		}
		setCoolTime(3);
	}
};

class Priest : public Card {
public:
	Priest() : Card(4, 12, "성직자", "(모든 본인 카드 체력 4 증가/쿨타임 4턴)") {}
	void Skill() override {
		if (turn == PLAYER_TURN) {
			for (Card* p : playerF) {
				p->setHp(p->getHp() + 4);
			}
		}
		else {
			for (Card* p : aiF) {
				p->setHp(p->getHp() + 4);
			}
		}
		setCoolTime(4);
	}
};

class Bard : public Card {
public:
	Bard() : Card(4, 10, "바드", "(랜덤 본인 카드 체력 4 증가 및 공격력 2 증가/쿨타임 4턴)") {}
	void Skill() override {
		if (turn == PLAYER_TURN) {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, playerF.size() - 1);
			Card* player = playerF[did(gen)];
			player->setHp(player->getHp() + 4);
			player->setAtk(player->getAtk() + 2);
		}
		else {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, aiF.size() - 1);
			Card* ai = aiF[did(gen)];
			ai->setHp(ai->getHp() + 4);
			ai->setAtk(ai->getAtk() + 2);
		}
		setCoolTime(4);
	}
};

class Mage : public Card {
public:
	Mage() : Card(9, 6, "마법사", "(랜덤 상대 12 데미지/쿨타임 6턴)") {}
	void Skill() override {
		// 랜덤 상대 1명 데미지 12
		if (turn == PLAYER_TURN) {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, aiF.size() - 1);
			Card* ai = aiF[did(gen)];
			ai->setHp(ai->getHp() - 12);
		}
		else {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, playerF.size() - 1);
			Card* player = playerF[did(gen)];
			player->setHp(player->getHp() - 12);
		}
		setCoolTime(6);
	}
};

class Sorcerer : public Card {
public:
	Sorcerer() : Card(8, 6, "소서러", "(랜덤 상대 10 데미지 및 공격력 2 감소/쿨타임 5턴)") {}
	void Skill() override {
		// 랜덤 상대 1명 데미지 10
		if (turn == PLAYER_TURN) {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, aiF.size() - 1);
			Card* ai = aiF[did(gen)];
			ai->setHp(ai->getHp() - 10);
			ai->setAtk(ai->getAtk() - 2);
		}
		else {
			std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
			std::uniform_int_distribution<> did(0, playerF.size() - 1);
			Card* player = playerF[did(gen)];
			player->setHp(player->getHp() - 10);
			player->setAtk(player->getAtk() - 2);
		}
		setCoolTime(5);
	}
};

class Necromancer : public Card {
public:
	Necromancer() : Card(8, 6, "주술사", "(상대LP 3 흡수/쿨타임 5턴)") {}
	void Skill() override {
		if (turn == PLAYER_TURN) {
			aiLp -= 3; 
			playerLP += 3;
		}
		else {
			playerLP -= 3;
			aiLp += 3;
		}
		setCoolTime(5);
	}
};

// 게임 시스템 (시작/ 종료의 관리)
int main() {
	int choose;
	cout << "=======================Parallel Deck=========================\n";
	draw(aiLp,playerLP);
	cout << "\n| 1. Insert Coin\n| 2. end\n| input : ";
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
		cout << "\t" << aiF[i]->getName()<<"\t";
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size(); i++) {
		cout << "\tAtk : " << aiF[i]->getAtk() << "\t";;
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size(); i++) {
		cout << "\tHp  : " << aiF[i]->getHp() << " ";;
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < aiF.size(); i++) {
		cout << "\tcool: " << aiF[i]->getCoolTime() << " ";;
	}
	cout << "\n";
	cout << "|\n";
	cout << "|\n";
	cout << "|";
	for (int i = 0; i < playerF.size(); i++) {
		cout << "\t" << playerF[i]->getName() << "\t";
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < playerF.size(); i++) {
		cout << "\tAtk : " << playerF[i]->getAtk() << "\t";
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < playerF.size(); i++) {
		cout << "\tHp  : " << playerF[i]->getHp()<<" ";
	}
	cout << "\n";
	cout << "|";
	for (int i = 0; i < playerF.size(); i++) {
		cout << "\tcool: " << playerF[i]->getCoolTime() << " ";;
	}
	cout << "\n";
	cout << "|\n";
	cout << "|\t\t    Player LP : " << player_Lp << "\n";
	cout << "|";
	for (int i = 0; i < 60; i++) {
		cout << "-";
	}
	cout << "\n";
	 
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

void freeJobs(Card* p) {
	for (int i = 0; i < 12; i++) {
		if (Job[i] == p) continue;
		delete Job[i];
	}
}

// 게임진행	(첫턴이후 체력조건 만족시까지 무한반복)
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

// 플레이어 첫번째 턴	(첫턴은 공격하지 않으므로 별도 함수로 작성)
void Player_First_Turn() {
	turn = PLAYER_TURN;
	system("cls");
	draw(aiLp, playerLP);
	cout << "| 플레이어 턴 입니다.\n";
	int choose = Pickup_Card(); // 카드 뽑기( 인풋)
	if (choose != EMPTY) {
		playerF.push_back(Job[choose]);
		freeJobs(Job[choose]);
	}
	//여기서 그려지는게 맞음 
	system("cls");
	draw(aiLp, playerLP);
	if (choose != EMPTY) {
		cout << "| " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
	}
	else {
		cout << "| 카드 소환을 스킵했습니다. \n";
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
	turn = AI_TURN;
	system("cls");
	int choose = Ai_Pickup_Card();
	aiF.push_back(Job[choose]);//필드 소환
	freeJobs(Job[choose]);
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
	turn = PLAYER_TURN;
	system("cls");
	draw(aiLp, playerLP);
	cout << "| 플레이어 턴 입니다.\n";
	if (playerF.size() < 3) {
		int choose = Pickup_Card();
		if (choose != EMPTY) {
			playerF.push_back(Job[choose]);
			freeJobs(Job[choose]);
		}
		system("cls");
		draw(aiLp, playerLP);
		if (choose != EMPTY) {
			cout << "| " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
			system("cls");
			if (playerF.size() > 0) {
				system("cls");
				Attack(playerF.back(), aiF);
			}
			else {
				cout << "| 소환을 스킵합니다. \n";
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
			cout << "| 소환을 스킵합니다. \n";
			if (playerF.size() > 0) {
				system("cls");
				Attack(playerF.back(), aiF);
			}
			else {
				cout << "| 엔터를 눌러서 플레이어 턴을 종료합니다.\n";
				cout << "|";
				for (int i = 0; i < 60; i++) {
					cout << "-";
				}
				cin.ignore();
				cin.get();
			}
			
		}

	}
	else {
		cout << "| 필드가 가득 찼으므로 소환단계를 종료합니다.\n";
		cout << "| 플레이어의 공격 단계로 넘어갑니다.\n";
		cout << "|";
		for (int i = 0; i < 60; i++) {
			cout << "-";
		}
		cin.ignore();
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
	turn = AI_TURN;
	system("cls");
	if (aiF.size() < 3) {
		int choose = Ai_Pickup_Card();
		aiF.push_back(Job[choose]);
		freeJobs(Job[choose]);
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
	if (attacker->getCoolTime() == 0) {
		attacker->Skill();
		cout << "| " << attacker->getName() << "카드가 스킬을 사용합니다." << endl;
		for (int i = 0; i < playerF.size(); i++) {
			if (playerF[i]->getHp() <= 0) {
				playerLP += playerF[i]->getHp();
				delete playerF[i];
				playerF.erase(playerF.begin() + i);
			}
		}
	}
	else if (playerF.size() != 0) {
		Card* defender = playerF[lowhp];
		cout << "| " << attacker->getName() << " 카드로 " << defender->getName() << "을(를) 공격합니다!" << endl;
		if (defender->getHp() > attacker->getAtk()) {
			defender->setHp(defender->getHp() - attacker->getAtk());
		}
		else if (defender->getHp() <= attacker->getAtk()) {
			int damage = attacker->getAtk() - (defender->getHp());
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
	cout << "| 2. 스킬 공격" << chosenAttacker->getSkillFun() << '\n';
	cout << "| 공격 방법을 선택하세요. : ";
	int choose2 = 0;
	cin >> choose2;
	if (choose2 == 1) {
		system("cls");
		draw(aiLp, playerLP);
		cout << "| " << chosenAttacker->getName() << " 카드로 " << defender->getName() << "을 공격합니다!" << endl;
		cin.get();
		if (defender->getHp()> chosenAttacker->getAtk()) {
			defender->setHp( defender->getHp() - chosenAttacker->getAtk());
		}
		else if (defender->getHp()<= chosenAttacker->getAtk()) {
			int damage = chosenAttacker->getAtk() - (defender->getHp());
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
	else if (choose2 == 2 && chosenAttacker->getCoolTime() == 0) {
		system("cls");
		draw(aiLp, playerLP);
		//스킬
		cout << "| " << chosenAttacker->getName() << "카드가 스킬을 사용합니다." << endl;
		cin.get();
		chosenAttacker->Skill();
		for (int i = 0; i < aiF.size(); i++) {
			if (aiF[i]->getHp() <= 0) {
				aiLp += aiF[i]->getHp();
				delete aiF[i];
				aiF.erase(aiF.begin() + i);
			}
		}
	}
	else if (choose2 == 2) {
		system("cls");
		draw(aiLp, playerLP);
		cout << "| " << chosenAttacker->getName() << "카드의 스킬 쿨타임이 남아있습니다." << endl;
		cout << "| 엔터를 눌러 공격페이즈로 다시 돌아갑니다." << endl;
		cout << "|";
		for (int i = 0; i < 60; i++) {
			cout << "-";
		}
		cin.ignore();
		cin.get();
		Attack(attacker, defenders);
	}
	else {
		cout << "| 해당 명령은 존재하지 않습니다." << endl;
		Attack(attacker, defenders);
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
	else {
		return empty;
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