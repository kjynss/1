#include "battle.h"
using namespace std;

class Field {
public:
	string name;
	Monster* monsters[3];
};

Field Yard = { "평원", { &Goblin, &GoblinMagician, &GoblinKing } };
Field Mountain = {"산", { &Wolf, &Dragon, &Golem } };
Field Castle = {"악마성", { &Ifrit, &DevilMember, &DevilKing } };

int FieldManu(Player& player, Field* f, int fi) {
	int fieldstate = 0;
	int battleRes = 0;
	int fieldEvent;
	DivisionLine();
	cout << f->name << "으로 왔다." << endl;
	while (fieldstate == 0) {
		DivisionLine();
		fieldEvent = ran(gen)%10;

		switch (fieldEvent) {
		case 0:
			cout << "경험치를 얻었다." << endl;
			player.GainEXP(100 * (1 + fi));
			break;
		case 1:
			cout << "경험치를 얻었다." << endl;
			player.GainEXP(100 + 10 * fi);
			break;
		case 2:
			cout << "경험치를 얻었다." << endl;
			player.GainEXP(50 * (2 + fi));
			break;
		case 3:
			battleRes = BattlePhase(player, *f->monsters[0]);
			break;
		case 4:
			battleRes = BattlePhase(player, *f->monsters[0]);
			break;
		case 5:
			battleRes = BattlePhase(player, *f->monsters[0]);
			break;
		case 6:
			battleRes = BattlePhase(player, *f->monsters[1]);
			break;
		case 7:
			battleRes = BattlePhase(player, *f->monsters[1]);
			break;
		case 8:
			battleRes = BattlePhase(player, *f->monsters[1]);
			break;
		case 9:
			battleRes = BattlePhase(player, *f->monsters[2]);
			break;

		}
		if (battleRes != Keep) {
			return battleRes;
		}
		DivisionLine();
		cout << f->name << "을 계속 탐험하시겠습니까?" << endl;
		cout << "0. 예    1. 아니오" << endl;
		cout << "선택 : ";
		cin >> fieldstate;
	}
	return 0;
}

int main() {
	cout << "당신의 이름을 알려주세요.\n이름 : ";
	string name;
	cin >> name;
	Player player(name);
	cout << player.GetName() << "님 환영합니다!\n";
	cout << "당신이 해야할 일은 간단합니다.\n";
	cout << "적을 무찌르고 성장하여 마왕을 죽이세요.\n";
	DivisionLine();
	player.ShowStatus();

	while (true) {
		int act = 0;
		int field = 0;
		int fieldRes = 0;
		DivisionLine();
		cout << "0. 능력치확인" << endl;
		cout << "1. 회복하기" << endl;
		cout << "2. 탐험하기" << endl;
		cout << "3. 종료하기" << endl;
		cout << "행동 : ";
		cin >> act;

		if (act == 0) {
			player.ShowStatus();
		}
		if (act == 1) {
			DivisionLine();
			player.Heal();
			cout << "HP와 MP를 모두 회복했다." << endl;
		}
		if (act == 2) {
			DivisionLine();
			cout << "0. 평원\n";
			cout << "1. 산\n";
			cout << "2. 악마성\n";
			cout << "3. 이전으로\n";
			cout << "갈 곳 : ";
			cin >> field;
			if (field == 0) { fieldRes = FieldManu(player, &Yard, field); }
			else if (field == 1) { fieldRes = FieldManu(player, &Mountain, field); }
			else if (field == 2) { fieldRes = FieldManu(player, &Castle, field); }
			else if (field == 3) { continue; }
			else {
				cout << "다시 선택하세요.";
				continue;
			}
		}
		if (act == 3) {
			cout << "게임을 종료합니다." << endl;
			return 0;
		}
		if (fieldRes == Die) {
			cout << "----- 게 임 오 버 -----" << endl;
			return 0;
		}
		if (fieldRes == Boss) {
			DivisionLine();
			cout << "축하합니다! 당신은 마왕을 쓰러뜨렸습니다!" << endl;
			return 0;
		}
	}
}
