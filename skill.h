#ifndef SKILL

#include <iostream>
using namespace std;

enum SkillType { Physics = 0, Magic=1 };

class Skill {
public:
	Skill(string name, int type, int power, int cost) : Name(name), Type(type), Power(power), Cost(cost) {}

	string GetName() {
		return Name;
	}
	int GetType() {
		return Type;
	}
	int GetPower() {
		return Power;
	}
	int GetCost() {
		return Cost;
	}

	void SkillInfo() const{
		cout << Name << " (타입:";
		if (Type == Physics) { cout << "물리"; }
		if (Type == Magic) { cout << "마법"; }
		cout << " 위력:" << Power << " 마나:" << Cost << ")" << endl;
	}

private:
	const string Name;
	const int Type;
	const int Power;
	const int Cost;
};

Skill NormalAttack("일반공격", Physics, 10,0 );
Skill PowerAttack("강공격", Physics, 12, 5);
Skill DoubleAttack("더블어택", Physics, 13, 7);
Skill Pounding("마구때리기", Physics, 15, 8);
Skill Bite("물기", Physics, 16, 9);
Skill TripleAttack("트리플어택", Physics, 17, 12);
Skill WingAttack("날개치기", Physics, 20, 17);
Skill SwordDance("칼춤", Physics, 23, 25);
Skill Smash("강타", Physics, 25, 30);
Skill GigaImpact("기가임팩트", Physics, 45, 55);

Skill Poison("독공격", Magic, 15, 2);
Skill Fire("불공격", Magic, 22, 7);
Skill Storm("폭풍", Magic, 29, 13);
Skill FireBreathe("화염방사", Magic, 37, 21);
Skill Blizzard("눈보라", Magic, 42, 30);
Skill Curse("저주", Magic, 60, 55);
Skill Meteor("메테오", Magic, 90, 80);

Skill HPRestore("HP회복", Magic, 0, 100);

#endif
