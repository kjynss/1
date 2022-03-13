#ifndef Character

#include "skill.h"
#include "stat.h"
#include <random>

random_device rd;
mt19937_64 gen(rd());
uniform_int_distribution<> ran(0,99);

class Character {
public:
	string GetName() { return Name; }

	int GetAttack() {return Attack;	}
	int GetMagicPower() { return MagicPower; }
	int GetHP() { return HP; }
	void HPReduce(int dam) { HP -= dam; }
	void MPReduce(int cost) { MP -= cost; }

	void BattleState() {
		cout << "HP : " << HP << '/' << MaxHP << endl;
		cout << "MP : " << MP << '/' << MaxMP << endl;
	}

protected:
	string Name;
	int MaxHP;
	int HP;
	int MaxMP;
	int MP;
	int Attack;
	int MagicPower;
	Skill* Skills[4];
};

class Player : public Character {
public:
	Player(string n) {
		Name = n;
		BaseHP = 500;
		BaseMP = 100;
		BaseAttack = 10;
		Skills[0] = &DoubleAttack;
		for (int i = 1; i < 4; i++) {
			Skills[i] = NULL;
		}
		Level = 1;
		MaxEXP = 100;
		EXP = 0;
		Stat = {0,0,0,0,0,0};
		PlayerWeapon = &WoodSword;
		ReSetStatus();
		Heal();
	}

	void GainEXP(int exp) {
		EXP += exp;
		cout << exp << "만큼의 경험치를 얻었다!\n";
		LevelUP();
	}

	void Heal() {
		ReSetStatus();
		HP = MaxHP;
		MP = MaxMP;
	}

	void HPRes() {
		if (HP > MaxHP / 2) HP = MaxHP;
		else if (HP <= MaxHP / 2) HP += MaxHP / 2;

		cout << "체력을 회복했다.\n";
	}

	void ShowStatus() {
		cout << endl;
		DivisionLine();
		cout << "LV. " << Level << endl;
		cout << "HP : " << HP << '/' << MaxHP << endl;
		cout << "MP : " << MP << '/' << MaxMP << endl;
		cout << "EXP : " << EXP << '/' << MaxEXP << endl;
		cout << endl;
		Stat.ShowStats(PlayerWeapon);
		cout << endl;
		PlayerWeapon->WeaponInfo();
		cout << endl;
		cout << "----- 기 술 목 록 -----\n";
		ShowSkills();
		cout << endl;
	}

	void ShowSkills() const {
		for (int i = 0; i < 4; i++) {
			if (Skills[i] != NULL) {
				cout << i << ". ";
				Skills[i]->SkillInfo();
			}
		}
	}

	Skill* GetSkill(int num) { return Skills[num]; }

	void LevelUP() {
		if (EXP >= MaxEXP) {
			EXP -= MaxEXP;
			Level++;
			MaxEXP = MaxEXP * 1.1;
			Stat.LevelUP();
			cout << endl;
			DivisionLine();
			cout << "LEVEL UP!" << endl;
			Stat.GetStat();
			ReSetStatus();
			Heal();
			LearnSkill(Level);
		}
	}

	void GetWeapon(Weapon* w) {
		get_weapon:
		DivisionLine();
		int act;
		cout << "무기 " << w->GetName() << "을(를) 획득했다.\n";
		w->WeaponInfo();
		cout << "현재 무기 : ";
		PlayerWeapon->WeaponInfo();
		cout << "장착하시겠습니까?\n";
		cout << "0. 장착한다.\n1. 장착하지않는다.\n행동 : ";
		cin >> act;

		if (act == 0) {
			cout << "무기를 장착했다.\n";
			PlayerWeapon = w;
		}
		else if (act == 1) { cout << "무기를 장착하지 않았다."; }
		else {
			cout << "다시 선택하세요.\n";
			goto get_weapon;
		}
	}

private:
	enum Learnable {
		fire = 3,
		tripleAttack = 5,
		storm = 7,
		swordDance = 10,
		blizzard = 15,
		gigaImpact = 25,
		hprestore = 35,
		meteor = 45
	};

	void LearnSkill(int lv) {
		if (lv == fire) {
			Skills[1] = &Fire;
			cout << "새로운 기술을 배웠다!\n";
			Fire.SkillInfo();
		}
		if (lv == tripleAttack) {
			Skills[2] = &TripleAttack;
			cout << "새로운 기술을 배웠다!\n";
			TripleAttack.SkillInfo();
		}
		if (lv == storm) {
			Skills[3] = &Storm;
			cout << "새로운 기술을 배웠다!\n";
			Storm.SkillInfo();
		}
		if (lv == swordDance) { Learn(&SwordDance); }
		if (lv == blizzard) { Learn(&Blizzard); }
		if (lv == gigaImpact) { Learn(&GigaImpact); }
		if (lv == hprestore) { Learn(&HPRestore); }
		if (lv == meteor) { Learn(&Meteor); }
	}

	void Learn(Skill* s) {
		cout << "새로운 기술을 배울 수 있지만 기술칸이 부족하다." << endl;
	rechoose:
		cout << "배울 기술 : ";
		s->SkillInfo();
		cout << "보유중인 기술을 지우고 기술을 배울 수 있다.";
		for (int i = 0; i < 4; i++) {
			cout << i << ". ";
			Skills[i]->SkillInfo();
		}
		cout << "4. 기술을 배우지 않는다.\n\n";
		int learn;
		cout << "선택 : ";
		cin >> learn;
		if (learn >= 1 && learn <= 4) {
			cout << Skills[learn]->GetName() << "을 잊고 " << s->GetName() << "을 배웠다.\n";
			Skills[learn] = s;
		}
		else if (learn == 5) {
			cout << "기술을 배우지 않았다.\n";
		}
		else {
			cout << "다시 선택하세요.\n";
			goto rechoose;
		}
	}

	void ReSetStatus() {
		Stat.ResetStat(PlayerWeapon);
		MaxHP = BaseHP + Stat.TotalSTR * 10;
		MaxMP = BaseMP + Stat.TotalINT * 5;
		Attack = BaseAttack + Stat.TotalSTR;
		MagicPower = Stat.TotalINT * 2;
	}

	int BaseHP;
	int BaseMP;
	int BaseAttack;
	int Level;
	int MaxEXP;
	int EXP;
	Stat Stat;
	Weapon* PlayerWeapon;
};

class Monster : public Character {
public:
	Monster(string name, int attack, int hp, int mp, int magic, Skill* skill[4], int exp, Weapon* reward) {
		Name = name;
		Attack = attack;
		MaxHP = HP = hp;
		MaxMP = MP = mp;
		MagicPower = magic;
		EXP = exp;
		RewardWeapon = reward;

		for (int i = 0; i < 4; i++) {
			Skills[i] = skill[i];
		}
	}

	Skill* MonsterSkill() {
		return Skills[ran(gen)%4];
	}

	int EXPReward() { return EXP; }
	Weapon* WeaponReward() { return RewardWeapon; }

private:
	int EXP;
	Weapon* RewardWeapon;
};

Skill* GoblinSkill[4] = { & NormalAttack, &NormalAttack, &PowerAttack, &PowerAttack};
Monster Goblin = {"고블린", 10, 200, 20, 1,	GoblinSkill, 100, &IronSword};

Skill* GoblinMagicianSkill[4] = { &NormalAttack, &Fire, &Poison, &PowerAttack };
Monster GoblinMagician = { "고블린 마법사", 5, 150, 70, 15,	GoblinMagicianSkill, 110, &MagicCap };

Skill* GoblinKingSkill[4] = { &NormalAttack, &Pounding, &PowerAttack, &PowerAttack };
Monster GoblinKing = { "고블린 왕", 35, 1000, 50, 10,GoblinKingSkill, 550, &DiamondSword };


Skill* WolfSkill[4] = { &NormalAttack, &Bite, &NormalAttack, &PowerAttack };
Monster Wolf = { "늑대", 30, 650, 70, 15, WolfSkill, 250, &DiamondSword };

Skill* DragonSkill[4] = { &Bite, &WingAttack, &FireBreathe, &Storm };
Monster Dragon = { "용", 20, 800, 125, 20,	DragonSkill, 300, &WoodWand };

Skill* GolemSkill[4] = { &Pounding, &Smash, &Smash, &PowerAttack };
Monster Golem = { "골렘", 50, 5000, 200, 15,	GolemSkill, 2000, &WoodWand };


Skill* IfritSkill[4] = { &Curse, &FireBreathe, &Smash, &Blizzard };
Monster Ifrit = { "악마 정령", 35, 2500, 250, 35,	IfritSkill, 600, &OrbofVoid };

Skill* DevilMemberSkill[4] = { &TripleAttack, &Smash, &Curse, &SwordDance };
Monster DevilMember = { "골렘", 60, 3500, 200, 25,	DevilMemberSkill, 700, &WoodWand };

Skill* DevilKingSkill[4] = { &Curse, &Meteor, &Smash, &GigaImpact };
Monster DevilKing = { "악마왕 디아블로", 88, 44444, 444, 44,	DevilKingSkill, 1, &WoodSword};

#endif