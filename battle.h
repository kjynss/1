#ifndef Battle

#include "character.h"

enum BattleResult {
	Die = -1,
	Keep = 0,
	Boss = 1
};

int GetDamage(Character* attacker, Skill* s) {
	attacker->MPReduce(s->GetCost());
	if (s->GetType() == Physics) {
		return attacker->GetAttack() * s->GetPower();
	}
	if (s->GetType() == Magic) {
		return attacker->GetMagicPower() * s->GetPower();
	}
}

int BattlePhase(Player &player, Monster monster) {
	int act;
	Skill* usingskill;
	cout << monster.GetName() << "이(가) 나타났다!";

	//행동선택
	while (true) {
		DivisionLine();
		cout << "----- 적 의 상 태 -----" << endl;
		monster.BattleState();
		cout << "----- 나 의 상 태 -----" << endl;
		player.BattleState();
		cout << endl;
		DivisionLine();
		cout << "무엇을 하시겠습니까?\n";
		cout << "0. 일반공격" << endl;
		cout << "1. 기술공격" << endl;
		cout << "2. 능력치확인" << endl;
		cout << "3. 도망친다" << endl;
		cout << "행동 : ";
		cin >> act;
		DivisionLine();
		if (act == 0) { usingskill = &NormalAttack; }
		else if (act == 1) {
			player.ShowSkills();
			cout << "4. 돌아간다.";
			cout << "기술을 선택하세요.\n";
			cout << "기술사용 : ";
			cin >> act;
			if (act >= 0 && act <= 3) {
				usingskill = player.GetSkill(act);
			}
			else if (act == 4) { continue; }
			else {
				cout << "다시 선택하세요.";
				continue;
			}
		}
		else if (act == 2) {
			player.ShowStatus();
			continue;
		}
		else if (act == 3) {
			cout << "도망쳤다.\n";
			return 0;
		}
		else {
			cout << "다시 선택하세요.\n";
			continue;
		}

		//전투(공격)
		int damage;
		if (usingskill == &HPRestore) {
			player.HPRes();
		}
		else {
			damage = GetDamage(&player, usingskill);
			monster.HPReduce(damage);
			cout << usingskill->GetName() << "을 썼다." << endl;
			cout << "적에게 " << damage << "의 피해를 입혔다."<<endl;
		}

		if (monster.GetHP() <= 0) {
			cout << "적을 무찔렀다.\n";
			break;
		}

		usingskill = monster.MonsterSkill();
		damage = GetDamage(&monster, usingskill);
		player.HPReduce(damage);
		cout << monster.GetName() << "이(가) " << usingskill->GetName() << "을 썼다." << endl;
		cout << "적에게 " << damage << " 의 피해를 입었다."<<endl;

		if (player.GetHP() <= 0) {
			cout << "체력을 모두 잃었다...\n";
			return Die;
		}
	}

	DivisionLine();
	player.GainEXP(monster.EXPReward());
	int reward = ran(gen)%20;
	if (reward == 0) {
		player.GetWeapon(monster.WeaponReward());
	}
	return 0;
}

#endif
