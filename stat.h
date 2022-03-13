#ifndef Stat

#include "weapon.h"

void DivisionLine() {
	cout << "--------------------\n\n";
}

class Stat {
public:
	void ShowStats(Weapon* w) {
		ResetStat(w);
		cout << "STR : " << TotalSTR << endl;
		cout << "INT : " << TotalINT << endl;
	}

	void ResetStat(Weapon* w) {
		GetWeaponStat(w);
		TotalINT = BaseINT + WeaponINT;
		TotalSTR = BaseSTR + WeaponSTR;
	}

	void LevelUP() {
		BaseINT++;
		BaseSTR++;
	}

	void GetStat() {
		int get;
	rechoose:
		cout << endl;
		DivisionLine();
		cout << "추가 능력치를 얻을 수 있다!\n";
		cout << "0. STR : 최대체력과 공격력이 증가한다!\n";
		cout << "1. INT : 최대마나와 마법력이 증가한다!\n";
		cout << "선택 : ";
		cin >> get;
		if (get == 0) {
			cout << "STR 증가!\n";
			GetSTR();
		}
		else if (get == 1) {
			cout << "INT 증가!\n";
			GetINT();
		}
		else {
			cout << "다시 선택하세요." << endl;
			goto rechoose;
		}
	}

	void GetWeaponStat(Weapon* w) {
		WeaponSTR = w->GetSTR();
		WeaponINT = w->GetINT();
	}

	void GetSTR() { BaseSTR++; }
	void GetINT() { BaseINT++; }

	int TotalSTR, TotalINT;
	int BaseSTR, BaseINT;
	int WeaponSTR, WeaponINT;
};

#endif
