#include<iostream>
#include<time.h>

using namespace std;

enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_TEMPLE,
	MM_EXIT
};

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};


enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

enum  ANSWER {
	ANSWER_NONE,
	ANSWER_YES,
	ANSWER_NO
};

#define	NAME_SIZE	32
#define	ITEM_DESC_LENGTH	512
#define	INVENTORY_MAX		20
#define	STORE_WEAPON_MAX	3
#define	STORE_ARMOR_MAX		3
#define	LEVEL_MAX			10

struct _tagItem
{
	char	strName[NAME_SIZE];
	char	strTypeName[NAME_SIZE];
	ITEM_TYPE	eType;
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory
{
	_tagItem	tItem[INVENTORY_MAX];
	int			iItemCount;
	int			iGold;
};


struct _tagPlayer
{
	char	strName[NAME_SIZE];
	char	strJobName[NAME_SIZE];
	JOB		eJob;
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;
	_tagItem	tEquip[EQ_MAX];
	bool		bEquip[EQ_MAX];
	_tagInventory	tInventory;
};

struct _tagMonster
{
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGoldMin;
	int		iGoldMax;
};

struct _tagLevelUpStatus
{
	int	iAttackMin;
	int	iAttackMax;
	int	iArmorMin;
	int	iArmorMax;
	int	iHPMin;
	int	iHPMax;
	int	iMPMin;
	int	iMPMax;
};

const int	g_iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
_tagLevelUpStatus	tLvUpTable[JOB_END - 1] = {};


//input int (check error)
int InputInt() {
	int Input;
	cin >> Input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}
	return Input;
}

//menu
int MainMenu() {
	system("cls");
	cout << "*************************** Village ***************************" << endl;
	cout << "1. Dungeon" << endl;
	cout << "2. Market" << endl;
	cout << "3. Inventory" << endl;
	cout << "4. Temple" << endl;
	cout << "5. end Game" << endl;
	cout << "Please choose an action : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || MM_NONE > iMenu || iMenu > MM_EXIT)
		return MM_NONE;

	return iMenu;
}

int MapMenu() {
	system("cls");

	cout << "*************************** Dungeon ***************************" << endl;
	cout << "1. Enter the Goblin Tomb" << endl;
	cout << "2. Enter the troll habitat" << endl;
	cout << "3. Enter the the last battlefield" << endl;
	cout << "4. Back to Village" << endl;
	cout << "Please choose an action : ";

	int iMenu = InputInt();

		if (iMenu == INT_MAX || MT_NONE > iMenu || iMenu > MT_BACK)
			return MM_NONE;
		return iMenu;
}

int SelectJob() {
	int iMenu = JOB_NONE;

	while (iMenu == JOB_NONE) {
		system("cls");
		cout << "1. Knight" << endl;
		cout << "2. Archer" << endl;
		cout << "3. Wizard" << endl;
		cout << "Choice your job : ";
		iMenu = InputInt();

		if (iMenu == INT_MAX || iMenu <= JOB_NONE || iMenu >= JOB_END)
			iMenu =  JOB_NONE;
	}
	return iMenu;
}

//SetPlayer Job
void SetPlayer(_tagPlayer* pPlayer) {
	cout << "Set your Job : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);
	pPlayer->eJob = (JOB)SelectJob();

	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;

	switch (pPlayer->eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "Knight");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;
		pPlayer->iHPMax = 500;
		pPlayer->iHP = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "Archer");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;
		pPlayer->iHPMax = 400;
		pPlayer->iHP = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "Wizard");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;
		pPlayer->iHPMax = 300;
		pPlayer->iHP = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	}
}

//CreatMonster
_tagMonster CreatMonster(const char* pName, int iAttackMin, int iAttackMax, int iArmorMin,
	int iArmorMax, int iHP, int iMP, int iLevel, int iExp, int iGoldMin, int iGoldMax) {

	_tagMonster tMonster = {}; 

	strcpy(tMonster.strName, pName);
	tMonster.iAttackMin = iAttackMin;
	tMonster.iAttackMax = iAttackMax;
	tMonster.iArmorMax = iArmorMax;
	tMonster.iArmorMin = iArmorMin;
	tMonster.iHP = iHP;
	tMonster.iHPMax = iHP;
	tMonster.iMP = iMP;
	tMonster.iMPMax = iMP;
	tMonster.iLevel = iLevel;
	tMonster.iExp = iExp;
	tMonster.iGoldMin = iGoldMin;
	tMonster.iGoldMax = iGoldMax;

	return tMonster;
}

void SetMonster(_tagMonster* pMonsterArr) {
	pMonsterArr[0] = CreatMonster("Goblin", 20, 30, 2, 5, 100, 100, 1, 5000, 500, 1500);
	pMonsterArr[1] = CreatMonster("Troll", 50, 80, 60, 90, 2000, 2000, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreatMonster("Dragon", 250, 400, 100, 150, 10000, 10000, 10, 20000, 20000, 30000);
}

_tagLevelUpStatus LevelUp(int iAttackMin, int iAttackMax, int iArmorMin,
	int iArmorMax, int iHPMin, int iHPMax, int iMPMin, int iMPMax) {

	_tagLevelUpStatus tLevelUpStatus = {}; 

	tLevelUpStatus.iAttackMin = iAttackMin;
	tLevelUpStatus.iAttackMax = iAttackMax;
	tLevelUpStatus.iArmorMax = iArmorMax;
	tLevelUpStatus.iArmorMin = iArmorMin;
	tLevelUpStatus.iHPMin = iHPMin;
	tLevelUpStatus.iHPMax = iHPMax;
	tLevelUpStatus.iMPMin = iMPMin;
	tLevelUpStatus.iMPMax = iMPMax;
	
	return tLevelUpStatus;
}

void OutputBattleMonster(int iMenu) {

		switch (iMenu)
		{
		case MT_EASY:
			system("cls");
			cout << "*************************** Goblin ***************************" << endl;
			break;
		case MT_NORMAL:
			system("cls");
			cout << "*************************** Troll ***************************" << endl;
			break;
		case MT_HARD:
			system("cls");
			cout << "*************************** Dragon ***************************" << endl;
			break;
		case MT_BACK:
			break;
		}
}

void OutputPlayer(_tagPlayer* pPlayer) {
	cout << "================== Player ==================" << endl;
	cout << "Name : " << pPlayer->strName << "\tJob : " <<
		pPlayer->strJobName << endl;
	cout << "Level : " << pPlayer->iLevel << "\t\tExp : " <<
		pPlayer->iExp << " / " << g_iLevelUpExp[pPlayer->iLevel - 1] << endl;

	// adding weapons Attack point
	if (pPlayer->bEquip[EQ_WEAPON] == true)
	{
		cout << "Attack point : " << pPlayer->iAttackMin << " + " <<
			pPlayer->tEquip[EQ_WEAPON].iMin << " ~ " <<
			pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	else
	{
		cout << "Attack point : " << pPlayer->iAttackMin << " ~ " <<
			pPlayer->iAttackMax;
	}

	// adding armor Defensive point
	if (pPlayer->bEquip[EQ_ARMOR] == true)
	{
		cout << "\tDefensive point : " << pPlayer->iArmorMin << " + " <<
			pPlayer->tEquip[EQ_ARMOR].iMin << " ~ " <<
			pPlayer->iArmorMax << " + " << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}

	else
	{
		cout << "\tDefensive point : " << pPlayer->iArmorMin << " ~ " <<
			pPlayer->iArmorMax << endl;
	}

	cout << "HP : " << pPlayer->iHP << " / " << pPlayer->iHPMax <<
		"\tMP : " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;

	if (pPlayer->bEquip[EQ_WEAPON])
		cout << "Weapon : " << pPlayer->tEquip[EQ_WEAPON].strName;

	else
		cout << "Weapon : Null";

	if (pPlayer->bEquip[EQ_ARMOR])
		cout << "\t armor : " << pPlayer->tEquip[EQ_ARMOR].strName << endl;

	else
		cout << "\t armor : Null" << endl;

	cout << "Gold : " << pPlayer->tInventory.iGold << " Gold" << endl << endl;
}

void OutputMonster(_tagMonster* pMonster) {
	cout << "================== Monster ==================" << endl;
	cout << "Name : " << pMonster->strName << "\t\tLevel : " <<
		pMonster->iLevel << endl;
	cout << "Attack point : " << pMonster->iAttackMin << " - " <<
		pMonster->iAttackMax << "\tDefensive point : " << pMonster->iArmorMin <<
		" - " << pMonster->iArmorMax << endl;
	cout << "HP : " << pMonster->iHP << " / " << pMonster->iHPMax <<
		"\tMP : " << pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "Gold : " << pMonster->iExp << "\tExp : " <<
		pMonster->iGoldMin << " - " << pMonster->iGoldMax << endl << endl;
}

int OutputBattleMenu() {
	cout << "1. Attack" << endl;
	cout << "2. Run" << endl;
	cout << "Please choose an action : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || BATTLE_NONE > iMenu || iMenu > BATTLE_BACK)
		return BATTLE_NONE;

	return iMenu;
}

void Battle(_tagPlayer* pPlayer, _tagMonster* pMonster) {
	//random damge
	int	iAttackMin = pPlayer->iAttackMin;
	int	iAttackMax = pPlayer->iAttackMax;

	//add weapon
	if (pPlayer->bEquip[EQ_WEAPON])
	{
		iAttackMin += pPlayer->tEquip[EQ_WEAPON].iMin;
		iAttackMax += pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	int	iAttack = rand() % (iAttackMax - iAttackMin + 1) +
		iAttackMin;
	int	iArmor = rand() % (pMonster->iArmorMax - pMonster->iArmorMin + 1) +
		pMonster->iArmorMin;

	int	iDamage = iAttack - iArmor;
	
	//if low damage damage point is 1
	iDamage = iDamage < 1 ? 1 : iDamage;

	pMonster->iHP -= iDamage;

	cout << pPlayer->strName << " is " << pMonster->strName <<
		"attack " << iDamage << " damage" << endl;

	// monster is dead
	if (pMonster->iHP <= 0)
	{
		cout << pMonster->strName << " is Dead" << endl;

		pPlayer->iExp += pMonster->iExp;
		int	iGold = (rand() % (pMonster->iGoldMax - pMonster->iGoldMin + 1) +
			pMonster->iGoldMin);
		pPlayer->tInventory.iGold += iGold;

		cout << pMonster->iExp << " Get Exp" << endl;
		cout << iGold << " Get Gold" << endl;

		//recovery HP, MP
		pMonster->iHP = pMonster->iHPMax;
		pMonster->iMP = pMonster->iMPMax;

		// Check Exp(Level up)
		if (pPlayer->iExp >= g_iLevelUpExp[pPlayer->iLevel - 1])
		{
			// sub Exp
			pPlayer->iExp -= g_iLevelUpExp[pPlayer->iLevel - 1];

			// Level up
			++pPlayer->iLevel;

			cout << "Level up" << endl;

			//add State point
			int	iJobIndex = pPlayer->eJob - 1;
			int	iHPUp = rand() % (tLvUpTable[iJobIndex].iHPMax - tLvUpTable[iJobIndex].iHPMin + 1) +
				tLvUpTable[iJobIndex].iHPMin;
			int	iMPUp = rand() % (tLvUpTable[iJobIndex].iMPMax - tLvUpTable[iJobIndex].iMPMin + 1) +
				tLvUpTable[iJobIndex].iMPMin;

			 pPlayer->iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
			 pPlayer->iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
			 pPlayer->iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
			 pPlayer->iArmorMax += tLvUpTable[iJobIndex].iArmorMax;

			 pPlayer->iHPMax += iHPUp;
			 pPlayer->iMPMax += iMPUp;

			// recovery HP, MP
			 pPlayer->iHP = pPlayer->iHPMax;
			 pPlayer->iMP = pPlayer->iMPMax;
		}
		return;
	}

	// if monster is alive
	iAttack = rand() % (pMonster->iAttackMax - pMonster->iAttackMin + 1) +
		pMonster->iAttackMin;

	int	iArmorMin =  pPlayer->iArmorMin;
	int	iArmorMax =  pPlayer->iArmorMax;

	if (pPlayer->bEquip[EQ_ARMOR])
	{
		iArmorMin +=  pPlayer->tEquip[EQ_ARMOR].iMin;
		iArmorMax +=  pPlayer->tEquip[EQ_ARMOR].iMax;
	}

	iArmor = rand() % (iArmorMax - iArmorMin + 1) +
		iArmorMin;

	iDamage = iAttack - iArmor;
	
	iDamage = iDamage < 1 ? 1 : iDamage;

	
	pPlayer->iHP -= iDamage;

	cout << pMonster->strName << " is " << pPlayer->strName <<
		"attack " << iDamage << " damage" << endl;

	// if player is dead
	if (pPlayer->iHP <= 0)
	{
		cout << pPlayer->strName << " play is dead" << endl;

		int	iExp = pPlayer->iExp * 0.1f;
		int	iGold = pPlayer->tInventory.iGold * 0.1f;

		 pPlayer->iExp -= iExp;
		 pPlayer->tInventory.iGold -= iGold;

		cout << iExp << " Lose Exp." << endl;
		cout << iGold << " Lose Gold." << endl;

		// get HP, MP 10%
		 pPlayer->iHP =  (pPlayer->iHPMax) / 10;
		 pPlayer->iMP =  (pPlayer->iMPMax) / 10;

	}

}

void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu) {
	_tagMonster tMonster = pMonsterArr[iMenu - 1]; // choice monster

	while (true) {
		//OutputBattleMonster
		OutputBattleMonster(iMenu);

		// OutputPlayer
		OutputPlayer(pPlayer);

		//몬스터 정보를 출력한다.
		OutputMonster(&tMonster);

		//BattleMenu
		switch (OutputBattleMenu()) {
		case BATTLE_ATTACK : 
			Battle(pPlayer, &tMonster);
			break;
		case BATTLE_BACK :
			return;
		}
		system("pause");
	}
}

void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr) {
	bool bLoop = true;
	while (bLoop) {

		int iMenu = MapMenu();

		if (MT_BACK == iMenu)
			return;


		RunBattle(pPlayer, pMonsterArr, iMenu);
	}
}

int OutputStoreMenu() {
	system("cls");
	cout << "*************************** Store ***************************" << endl;
	cout << "1. weapon shop" << endl;
	cout << "2. armor Shop" << endl;
	cout << "3. Back to Vilage" << endl;
	int iMenu = InputInt();

	if (iMenu == INT_MAX ||  SM_NONE> iMenu || iMenu > SM_BACK)
		return SM_NONE;

	return iMenu;
}

int OutputStoreItemList(_tagInventory* pInventory, _tagItem* pStore, int iItemCount) {
	// OutputStoreItemList
	for (int i = 0; i < iItemCount; ++i)
	{
		cout << i + 1 << " Name : " << pStore[i].strName <<
			"\tType : " << pStore[i].strTypeName << endl;
		cout << "Attack point : " << pStore[i].iMin << " - " <<
			pStore[i].iMax << endl;
		cout << "Price : " << pStore[i].iPrice <<
			"\tSell : " << pStore[i].iSell << endl;
		cout << "explanation : " << pStore[i].strDesc << endl << endl;
	}

	cout << iItemCount + 1 << ". Back to Store" << endl;
	cout << "Gold : " << pInventory->iGold << " Gold" << endl;
	cout << "Storage : " << INVENTORY_MAX - pInventory->iItemCount << endl;
	cout << "Choice Item : ";
	int iMenu = InputInt();

	if (iMenu <1 || iMenu>iItemCount + 1) {
		return INT_MAX;
	}

	else
		return iMenu;			
}

void BuyItem(_tagInventory* pInventory, _tagItem* pStore, int iItemCount, int iStoreType) {
	while (1) {
		switch(iStoreType) {
		case SM_WEAPON :
			system("cls");
			cout << "*************************** Weapon Store ***************************" << endl;
			break;
		case SM_ARMOR :
			system("cls");
			cout << "*************************** Armor Store ***************************" << endl;
			break;
		}
		int iInput = OutputStoreItemList(pInventory, pStore, iItemCount);

		if (iInput == INT_MAX) {
			cout << "Invalid input." << endl;
			system("pause");
			continue;
		}
		else if (iInput == iItemCount + 1) {
			break;
		}

		int	iIndex = iInput - 1;

		// Check INVENTORY
		if (pInventory->iItemCount == INVENTORY_MAX)
		{
			cout << "Inventory is full" << endl;
			system("pause");
			continue;
		}

		// Less money.
		else if (pInventory->iGold < pStore[iIndex].iPrice)
		{
			cout << "Less money." << endl;
			system("pause");
			continue;
		}

		
		//add inventory
		pInventory->tItem[pInventory->iItemCount] =
			pStore[iIndex];
		++pInventory->iItemCount;

		//sub gold
		pInventory->iGold -= pStore[iIndex].iPrice;

		cout << pStore[iIndex].strName << " Successfully purchased item." << endl;
		system("pause");

	}
}

void RunStore(_tagInventory* pInventory, _tagItem* pWeapon, _tagItem* pArmor) {

	while (1) {
		switch (OutputStoreMenu()) {
		case SM_WEAPON :
			BuyItem(pInventory, pWeapon, STORE_WEAPON_MAX, SM_WEAPON);
			break;
		case SM_ARMOR :
			BuyItem(pInventory, pArmor, STORE_ARMOR_MAX, SM_ARMOR);
			break;
		case SM_BACK:
			return;
		}
	}
}

_tagItem CreatItem(const char* pName, ITEM_TYPE eType, int iMin, int iMax, int iPrice, int iSell, const char* pDesc) {
	_tagItem tItem = {};

	strcpy_s(tItem.strName, pName);
	tItem.eType = eType;

	switch (eType) {
	case IT_WEAPON:
		strcpy_s(tItem.strTypeName, "Weapon");
		break;
	case IT_ARMOR:
		strcpy_s(tItem.strTypeName, "Armor");
		break;
	}

	tItem.iMin = iMin;
	tItem.iMax = iMax;
	tItem.iPrice = iPrice;
	tItem.iSell = iSell;
	strcpy_s(tItem.strDesc, pDesc);

	return tItem;

}

int OutputInventory(_tagPlayer* pPlayer) {
	system("cls");
	while (true) {
		cout << "*************************** Inventory ***************************" << endl;
		OutputPlayer(pPlayer);
		for (int i = 0; i < pPlayer->tInventory.iItemCount; ++i)
		{
			cout << i + 1 << ". Name : " << pPlayer->tInventory.tItem[i].strName <<
				"\tType : " << pPlayer->tInventory.tItem[i].strTypeName << endl;
			cout << "Attack Point : " << pPlayer->tInventory.tItem[i].iMin << " - " <<
				pPlayer->tInventory.tItem[i].iMax << endl;
			cout << "Price : " << pPlayer->tInventory.tItem[i].iPrice <<
				"\tsell : " << pPlayer->tInventory.tItem[i].iSell << endl;
			cout << "Desc : " << pPlayer->tInventory.tItem[i].strDesc << endl << endl;
		}

		cout << pPlayer->tInventory.iItemCount + 1 << ". Back" << endl;
		cout << "Please select the efficiency of the item. : ";
		int iMenu = InputInt();

		if (iMenu <1 || iMenu > pPlayer->tInventory.iItemCount + 1) 
			return INT_MAX;

		return iMenu;
			
	}

}

void RunInventory(_tagPlayer* pPlayer) {
	while (true) {
		int iInput = OutputInventory(pPlayer);

		if (iInput == INT_MAX) {
			continue;
		}

		else if (iInput == pPlayer->tInventory.iItemCount + 1) {
			break;
		}


		int	idx = iInput - 1;
		EQUIP	eq;

		switch (pPlayer->tInventory.tItem[idx].eType)
		{
		case IT_WEAPON:
			eq = EQ_WEAPON;
			break;
		case IT_ARMOR:
			eq = EQ_ARMOR;
			break;
		}

	
		if (pPlayer->bEquip[eq] == true)
		{
			_tagItem	tSwap = pPlayer->tEquip[eq];
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];
			pPlayer->tInventory.tItem[idx] = tSwap;
		}
		else
		{
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];

			for (int i = idx; i < pPlayer->tInventory.iItemCount - 1; ++i)
			{
				pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
			}

			--pPlayer->tInventory.iItemCount;

			
			pPlayer->bEquip[eq] = true;
		}

		cout << pPlayer->tEquip[eq].strName << " Mounting item." << endl;

		system("pause");
	}
}

int OutputTemple() {
	
	system("cls");
	cout << "============Temple============" << endl;
	cout << "Welcome to the temple. If you pay 500Gold, we'll recover both HP and MP." << endl;
	cout << "1.pay and recover." << endl;
	cout << "2.Back to Village." << endl;
	cout << "Please choose an action : ";
	int iMenu = InputInt();

	if (iMenu < 1 || iMenu >2)
		return INT_MAX;
	return iMenu;
}

void RunTemple(_tagPlayer* pPlayer) {
	bool bRun = true;

	while (bRun) {
		int iInput = OutputTemple();

		if (iInput == INT_MAX)
			continue;

		switch (iInput) {
		case ANSWER_YES:
			cout << "Recovery HP, MP." << endl;
			pPlayer->iHP = pPlayer->iHPMax;
			pPlayer->iMP = pPlayer->iMPMax;

			if (pPlayer->tInventory.iGold < 500) {
				cout << "You don't have enough money in your possession. back to village." << endl;
				bRun = false;
			}
			else {
				pPlayer->tInventory.iGold -= 500;
				bRun = false;
			}
			system("pause");
			break;
		case ANSWER_NO:
			cout << "back to village." << endl;
			bRun = false;
			system("pause");
			break;
		}
	}
}

int main() {
	srand((unsigned int)time(0));
	bool bLoop = true;

	//Initialization plyer
	_tagPlayer tPlayer = {};

	//Initialization Monster
	_tagMonster	tMonsterArr[MT_BACK - 1] = {};

	//Set Player
	SetPlayer(&tPlayer);

	//Set Monster
	SetMonster(tMonsterArr);

	//Set table(Level)
	tLvUpTable[JOB_KNIGHT - 1] = LevelUp(4, 10, 8, 6, 50, 100, 10, 20);
	tLvUpTable[JOB_ARCHER - 1] = LevelUp(10, 15, 5, 10, 30, 60, 30, 50);
	tLvUpTable[JOB_WIZARD - 1] = LevelUp(15, 20, 3, 7, 20, 40, 50, 100);


	// Set Item
	_tagItem	tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreArmor[STORE_ARMOR_MAX] = {};

	//Create Weapon
	tStoreWeapon[0] = CreatItem("The old sword", IT_WEAPON, 10, 20, 10000, 3000,
		"It is a sword made by a common blacksmith. It's not much but I think it's better than bare hands.");
	tStoreWeapon[1] = CreatItem("shining sword", IT_WEAPON, 100, 150, 400000, 120000,
		"It is a sword made by a famous blacksmith. You can't use anyone.");
	tStoreWeapon[2] = CreatItem("Xcaliber", IT_WEAPON, 650, 800, 1000000, 300000,
		"A sword made by a blacksmith of the ancient kingdom. Only heroes of the time can be used.");

	//Create Armor
	tStoreArmor[0] = CreatItem("leather armor", IT_ARMOR, 10, 20, 10000, 3000,
		"It is an armor made by a common blacksmith. I think it's better than bare body because it's made of leather.");
	tStoreArmor[1] = CreatItem("iron armor", IT_ARMOR, 100, 150, 400000, 120000,
		"This is an iron armor made by a famous blacksmith. Only skilled people can use it.");
	tStoreArmor[2] = CreatItem("용포", IT_ARMOR, 650, 800, 1000000, 300000,
		"This armor was used by the ancient god Sonokong. Only heroes of the time can be used.");


	while (bLoop) {
		switch (MainMenu()) {
		case MM_MAP :
			RunMap(&tPlayer, tMonsterArr);
			break;
		case MM_STORE:
			RunStore(&tPlayer.tInventory, tStoreWeapon, tStoreArmor); //
			break;
		case MM_INVENTORY:
			RunInventory(&tPlayer);
			break;
		case MM_TEMPLE:
			RunTemple(&tPlayer);
			break;
		case MM_EXIT:
			bLoop = false;
			break;
		}
	}
	cout << "End game." << endl;
	return 0;
}