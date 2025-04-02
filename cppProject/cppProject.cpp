#include <iostream>
#include <vector>
#include <windows.h>
#include <random>
#include <ctime>
#include <string>
using namespace std;

// 카드 구현부
class Card {
protected:
    int atk, hp;
    string name;
public:
    Card(int a, int b, string n) : atk(a), hp(b), name(n) {}
    virtual string getName() {
        return name;
    }
    virtual int Skill() = 0;
    int getAtk() { return atk; }
    int getHp() { return hp; }
};

class Warrior : public Card {
public:
    Warrior() : Card(6, 12, "전사") {}
    int Skill() override {
        return 0;
    }
};

class Paladin : public Card {
public:
    Paladin() : Card(5, 14, "성기사") {}
    int Skill() override {
        return 0;
    }
};

class Archer : public Card {
public:
    Archer() : Card(7, 9, "궁수") {}
    int Skill() override {
        return 0;
    }
};

class Hunter : public Card {
public:
    Hunter() : Card(8, 10, "헌터") {}
    int Skill() override {
        return 0;
    }
};

class Thief : public Card {
public:
    Thief() : Card(7, 8, "도적") {}
    int Skill() override {
        return 0;
    }
};

class Assassin : public Card {
public:
    Assassin() : Card(8, 7, "암살자") {}
    int Skill() override {
        return 0;
    }
};

class Rogue : public Card {
public:
    Rogue() : Card(6, 9, "로그") {}
    int Skill() override {
        return 0;
    }
};

class Priest : public Card {
public:
    Priest() : Card(4, 12, "성직자") {}
    int Skill() override {
        return 0;
    }
};

class Bard : public Card {
public:
    Bard() : Card(4, 10, "음유시인") {}
    int Skill() override {
        return 0;
    }
};

class Mage : public Card {
public:
    Mage() : Card(9, 6, "마법사") {}
    int Skill() override {
        return 0;
    }
};

class Sorcerer : public Card {
public:
    Sorcerer() : Card(8, 6, "소서러") {}
    int Skill() override {
        return 0;
    }
};

class Necromancer : public Card {
public:
    Necromancer() : Card(8, 6, "네크로맨서") {}
    int Skill() override {
        return 0;
    }
};

// 게임 시스템
Card* Job[11] = { new Warrior(), new Paladin(), new Archer(), new Hunter(), new Thief(), new Assassin(), new Rogue(), new Priest(), new Bard(), new Mage(), new Sorcerer(), new Necromancer() };

vector<Card*> aiF;
vector<Card*> playerF;

void draw(int Ai_Lp, int Player_Lp) {
    cout << "|----------------------------------------\n";
    cout << "|\t\tAI LP : " << Ai_Lp << "\n";
    cout << "| \n";
    for (auto& card : playerF) {
        cout << "| " << card->getName() << "\n";
    }
    cout << "|----------------------------------------\n";
}

// 게임 진행
void Game() {
    system("cls");
    draw(1000, 1000);
    First_Turn();
}

// 첫 턴
void First_Turn() {
    cout << "플레이어 턴 입니다.\n";
    int choose = Pickup_Card();
    cout << "| " << Job[choose]->getName() << " 을(를) 소환했다!" << endl;
    playerF.push_back(Job[choose]);
}

// 카드 뽑기 함수
int Pickup_Card() {
    std::mt19937 gen(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<> dis(0, 10); // 카드 11개 중 0부터 10까지
    int randomCard1 = dis(gen); // 랜덤 카드 뽑기 
    int randomCard2 = dis(gen);
    int randomCard3 = dis(gen);

    cout << "| 뽑은 카드\n";
    cout << "| 1. " << Job[randomCard1]->getName() << endl;
    cout << "| 2. " << Job[randomCard2]->getName() << endl;
    cout << "| 3. " << Job[randomCard3]->getName() << endl;

    int choose;
    while (true) {
        cout << "| 낼 카드를 고르세요. : ";
        cin >> choose;
        if (choose >= 1 && choose <= 3) {
            break;
        }
        cout << "잘못된 입력입니다. 1, 2, 3 중에서 선택해주세요.\n";
    }

    if (choose == 1) {
        return randomCard1;
    }
    else if (choose == 2) {
        return randomCard2;
    }
    else {
        return randomCard3;
    }
}

// 메인 함수
int main() {
    int choose;
    cout << "===Parallel Deck===\n1. Insert Coin\n2. End\ninput : ";
    cin >> choose;
    if (choose == 1) {
        Game();
    }
    else if (choose == 2) {
        return 0;
    }
}
