#ifndef Weapon

#include <iostream>
using namespace std;

class Weapon {
public:
	Weapon(string name, int str, int in) : WeaponName(name), STR(str), INT(in){}

	string GetName () {
		return WeaponName;
	}
	int GetSTR() {
		return STR;
	}
	int GetINT() {
		return INT;
	}

	void WeaponInfo() const{
		cout << "무기 : " << WeaponName << " (STR +" << STR << ", INT +" << INT << endl;
	}

private:
	const string WeaponName;
	const int STR;
	const int INT;
};

Weapon WoodSword("목검", 1, 0);
Weapon IronSword("철검", 2, 1);
Weapon DiamondSword("다이아몬드 검", 7, 3);
Weapon Excaribur("엑스칼리버", 16, 6);

Weapon MagicCap("마술모자", 1, 3);
Weapon WoodWand("나무지팡이", 3, 9);
Weapon OrbofVoid("공허의 보주", 6, 23);
#endif
