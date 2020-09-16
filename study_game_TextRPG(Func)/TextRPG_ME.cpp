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

enum MAP_TYPE {
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB {
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END//중간에 직업을 넣어도 편리하게 저장할수 있음 
};

enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum  ANSWER {
	ANSWER_NONE,
	ANSWER_YES,
	ANSWER_NO
};

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU {
	SM_NONE,
	SM_WEWAPON,
	SM_ARMOR,
	SM_BACK
};

enum STORE_BUY_CELL {
	SBC_NONE,
	SBC_BUY,
	SBC_CELL,
	SBC_BACK
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};


#define NAME_SIZE 32
#define DESCRIPTION_SIZE 512
#define INVENTORY_SIZE 20
#define STORE_MAX 3

//공부
struct tStore {
	char strItem[NAME_SIZE];
	char strType[NAME_SIZE];
	ITEM_TYPE eItemType;
	int iMax;
	int iMin;
	int iPrice;
	int iCell;
	char strDescription[DESCRIPTION_SIZE];
};

//공부
struct tInventory {
	tStore tStoreInventory[INVENTORY_SIZE];
	int iItemCount;
	int iGold;
};

struct tPlayer {
	char strName[NAME_SIZE];
	char strJobName[NAME_SIZE];
	JOB eJOB;
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iExp;
	int iLevel;
	tStore tEquip[EQ_MAX];
	bool bEquip[EQ_MAX];
	tInventory tPlayerInventory;

};

struct tMonster {
	char strName[NAME_SIZE];
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iLevel;
	int iExp;
	int iGoldMin;
	int iGoldMax;
};


int main() {
	srand((unsigned int)time(0));
	int iMenu;
	int iJob = JOB_NONE;
	int iLevelUp = 2000;
	tPlayer Player = {};


	//플레이어 정보 설정
	//플레이어 이름을 입력받는다.
	//NAEM_SIZE-1만큼 받는 이유 : 문자열의 끝은 NULL로 끝나야 하는데 마지막까지 꽉 채우면 NULL이 없어서 문자열을 인식 못함
	cout << "============캐릭터 생성============" << endl;
	cout << "닉네임 : ";
	cin.getline(Player.strName, NAME_SIZE - 1);

	//직업을 입력 받는다.
	while (iJob == JOB_NONE) {
		system("cls");
		cout << "============캐릭터 생성============" << endl;
		cout << "1.성기사" << endl;
		cout << "2.건슬링거" << endl;
		cout << "3.네크로멘서" << endl;
		cout << "직업을 선택해 주세요 : ";
		cin >> iJob;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iJob <= JOB_NONE || iJob >= JOB_END) {
			iJob = JOB_NONE;
		}

		Player.eJOB = (JOB)iJob;

		Player.iLevel = 1;
		Player.iExp = 0;
		Player.eJOB = (JOB)iJob;
		Player.tPlayerInventory.iGold = 10000;

		switch (Player.eJOB) {
		case JOB_KNIGHT:
			strcpy_s(Player.strJobName, "성기사");
			Player.iAttackMin = 10;
			Player.iAttackMax = 20;
			Player.iArmorMin = 15;
			Player.iArmorMax = 20;
			Player.iHPMax = 500;
			Player.iHP = 500;
			Player.iMPMax = 100;
			Player.iMP = 100;
			break;
		case JOB_ARCHER:
			strcpy_s(Player.strJobName, "건슬링거");
			Player.iAttackMin = 20;
			Player.iAttackMax = 30;
			Player.iArmorMin = 10;
			Player.iArmorMax = 15;
			Player.iHPMax = 300;
			Player.iHP = 300;
			Player.iMPMax = 200;
			Player.iMP = 200;
			break;
		case JOB_WIZARD:
			strcpy_s(Player.strJobName, "네크로멘서");
			Player.iAttackMin = 30;
			Player.iAttackMax = 40;
			Player.iArmorMin = 5;
			Player.iArmorMax = 10;
			Player.iHPMax = 300;
			Player.iHP = 300;
			Player.iMPMax = 300;
			Player.iMP = 300;
			break;
		}
	}
	//몬스터를 생성한다.
	tMonster MonsterArr[MT_BACK - 1] = {};
	//고블린생성(이지)
	strcpy_s(MonsterArr[0].strName, "고블린");
	MonsterArr[0].iAttackMin = 20;
	MonsterArr[0].iAttackMax = 30;
	MonsterArr[0].iArmorMin = 2;
	MonsterArr[0].iArmorMax = 5;
	MonsterArr[0].iHPMax = 100;
	MonsterArr[0].iHP = 100;
	MonsterArr[0].iMPMax = 10;
	MonsterArr[0].iMP = 10;
	MonsterArr[0].iLevel = 1;
	MonsterArr[0].iExp = 1000;
	MonsterArr[0].iGoldMin = 500;
	MonsterArr[0].iGoldMax = 1500;

	//트롤생성(노말)
	strcpy_s(MonsterArr[1].strName, "트롤");
	MonsterArr[1].iAttackMin = 80;
	MonsterArr[1].iAttackMax = 130;
	MonsterArr[1].iArmorMin = 60;
	MonsterArr[1].iArmorMax = 90;
	MonsterArr[1].iHPMax = 2000;
	MonsterArr[1].iHP = 2000;
	MonsterArr[1].iMPMax = 100;
	MonsterArr[1].iMP = 100;
	MonsterArr[1].iLevel = 5;
	MonsterArr[1].iExp = 7000;
	MonsterArr[1].iGoldMin = 6000;
	MonsterArr[1].iGoldMax = 9000;


	//드래곤생성(하드)
	strcpy_s(MonsterArr[2].strName, "드래곤");
	MonsterArr[2].iAttackMin = 250;
	MonsterArr[2].iAttackMax = 500;
	MonsterArr[2].iArmorMin = 200;
	MonsterArr[2].iArmorMax = 400;
	MonsterArr[2].iHPMax = 30000;
	MonsterArr[2].iHP = 30000;
	MonsterArr[2].iMPMax = 20000;
	MonsterArr[2].iMP = 20000;
	MonsterArr[2].iLevel = 10;
	MonsterArr[2].iExp = 30000;
	MonsterArr[2].iGoldMin = 20000;
	MonsterArr[2].iGoldMax = 50000;


	//상점에서 판매한 무기 생성
	tStore tStoreWeapon[STORE_MAX] = {};

	strcpy_s(tStoreWeapon[0].strItem, "낡은검");
	strcpy_s(tStoreWeapon[0].strType, "무기");
	strcpy_s(tStoreWeapon[0].strDescription, "흔한 대장장이가 만든 검이다. 보잘것 없지만 맨손보다는 나을것 같다.");
	tStoreWeapon[0].iMin = 20;
	tStoreWeapon[0].iMax = 20;
	tStoreWeapon[0].iPrice = 10000;
	tStoreWeapon[0].iCell = 3000;

	strcpy_s(tStoreWeapon[1].strItem, "빛나는 검");
	strcpy_s(tStoreWeapon[1].strType, "무기");
	strcpy_s(tStoreWeapon[1].strDescription, "고명한 대장장이가 만든 검이다. 아무나 사용할 수 없다.");
	tStoreWeapon[1].iMin = 200;
	tStoreWeapon[1].iMax = 400;
	tStoreWeapon[1].iPrice = 1;
	tStoreWeapon[1].iCell = 41;

	strcpy_s(tStoreWeapon[2].strItem, "엑스칼리버");
	strcpy_s(tStoreWeapon[2].strType, "무기");
	strcpy_s(tStoreWeapon[2].strDescription, "고대 왕국의 대장장이가 만든 검이다. 그 시대의 영웅만 사용할 수 있다");
	tStoreWeapon[2].iMin = 6500;
	tStoreWeapon[2].iMax = 8500;
	tStoreWeapon[2].iPrice = 10000000;
	tStoreWeapon[2].iCell = 300000;


	//상점에서 판매한 방어구 생성
	tStore tStoreArmor[STORE_MAX] = {};


	while (1) {
		bool bRun = true;
		system("cls");

		cout << "============마을============" << endl;
		cout << "1.던전" << endl;
		cout << "2.상점" << endl;
		cout << "3.인벤토리" << endl;
		cout << "4.신전" << endl;
		cout << "5.게임종료" << endl;
		cout << "행동을 선택해 주세요 : ";
		cin >> iMenu;


		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT) {
			break;
		}

		switch (iMenu) {
		case MM_MAP:
			system("cls");
			cout << "============던전============" << endl;
			cout << "1.고블린 둥지" << endl;
			cout << "2.트롤 둥지" << endl;
			cout << "3.드래곤 둥지" << endl;
			cout << "4.마을" << endl;
			cout << "이동하실 장소를 선택해주세요 : ";
			cin >> iMenu;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}

			if (iMenu == MT_BACK) {
				break;
			}
			//선택한 메뉴에서 1을 빼주면 몬스터의 배열 인덱스가 된다. 그렇게해서 몬스터 소환해준다.
			tMonster MapMonster = MonsterArr[iMenu - 1];//몬스터 생성
			while (bRun) {
				system("cls");
				switch (iMenu) {
				case MT_EASY:
					cout << "============고블린============" << endl;
					break;
				case MT_NORMAL:
					cout << "============트롤============" << endl;
					break;
				case MT_HARD:
					cout << "============드래곤============" << endl;
					break;
				default:
					break;
				}
				system("cls");
				//플레이어 정보 출력
				cout << "============Player============" << endl;
				cout << "이름 : " << Player.strName << "\t직업 : " << Player.strJobName << endl;
				cout << "레벨 : " << Player.iLevel << "\t경험치 : " << Player.iExp << endl;
				cout << "공격력 : " << Player.iAttackMin << " ~ " << Player.iAttackMax << "\t방어력 : " << Player.iArmorMin
					<< " ~ " << Player.iArmorMax << endl;
				cout << "HP : " << Player.iHP << "/" << Player.iHPMax
					<< "\tMP : " << Player.iMP << "/" << Player.iMPMax << endl << endl;

				//몬스터정보 출력
				cout << "============Monster============" << endl;
				cout << "이름 : " << MapMonster.strName << "\t레벨 : " << MapMonster.iLevel << endl;
				cout << "공격력 : " << MapMonster.iAttackMin << " ~ " << MapMonster.iAttackMax
					<< "\t방어력 : " << MapMonster.iArmorMin << " ~ " << MapMonster.iArmorMax << endl;
				cout << "HP : " << MapMonster.iHP << "/" << MapMonster.iHPMax
					<< "\tMP : " << MapMonster.iMP << "/" << MapMonster.iMPMax << endl;
				cout << "획득경험치 : " << MapMonster.iExp
					<< "\t획득골드 : " << MapMonster.iGoldMin << " ~ " << MapMonster.iGoldMax << endl << endl;

				cout << "1.싸운다." << endl;
				cout << "2.도망치기" << endl;
				cout << "행동을 선택해주세요 : ";
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (iMenu == BATTLE_BACK) {
					break;
				}
				else if (iMenu == BATTLE_ATTACK) {
					//min~max의 데미지와 방어를 만드는 함수(rnad사용)
					//공식 : rand % (Max-min+1) + min
					int iAttackPlayer = rand() % (Player.iAttackMax - Player.iAttackMin + 1) + Player.iAttackMin;
					int iArmorMonster = rand() % (MapMonster.iArmorMax - MapMonster.iArmorMin + 1) + MapMonster.iArmorMin;
					int iDamage = iAttackPlayer - iArmorMonster;

					//삼항연산자 형태 = 조건식 ? true일때 : false일때
					iDamage = iDamage < 1 ? 1 : iDamage; // 데미지가 -값이 될수는 없으므로 1보다 작으면 무조건1을 주게함

					//몬스터에게 데미지를 입힘
					MapMonster.iHP -= iDamage;

					//데미지를 얼마나 입혔는지 출력
					cout << Player.strName << "(이)가 " << MapMonster.strName << "에게 "
						<< iDamage << "의 피해를 입혔습니다." << endl;


					//몬스터가 죽었을 경우
					if (MapMonster.iHP <= 0) {
						cout << MapMonster.strName << "이 사망하였습니다" << endl << endl;

						//랜덤한 골드의 값을 생성
						int iGetGold = rand() % (MapMonster.iGoldMax - MapMonster.iGoldMin + 1) + MapMonster.iGoldMin;

						//죽인 몬스터의 경험치와 골드를 획득시켜준다
						Player.iExp += MapMonster.iExp;
						Player.tPlayerInventory.iGold += iGetGold;


						//일정 경험치가 쌓이면 레벨업을 한다.
						if (Player.iExp >= iLevelUp) {
							Player.iLevel += 1;

							//플레이어 경험치 초기화
							Player.iExp -= iLevelUp;

							//필요 경험치 요구랑을 증가시켜 준다.
							iLevelUp *= 1.5;

							cout << "축하합니다! 레벨업을 하여 " << Player.iLevel << "이 되었습니다!" << endl << endl;

							if (strcmp(Player.strJobName, "성기사")) {
								Player.iAttackMin += 5;
								Player.iAttackMax += 5;
								Player.iArmorMin += 15;
								Player.iArmorMax += 15;
								Player.iHPMax += 150;
								Player.iHP = Player.iHPMax;
								Player.iMPMax += 50;
								Player.iMP = Player.iMPMax;

							}
							else if (strcmp(Player.strJobName, "건슬링거")) {
								Player.iAttackMin += 10;
								Player.iAttackMax += 10;
								Player.iArmorMin += 10;
								Player.iArmorMax += 10;
								Player.iHPMax += 100;
								Player.iHP = Player.iHPMax;
								Player.iMPMax += 100;
								Player.iMP = Player.iMPMax;
							}
							else if (strcmp(Player.strJobName, "네크로멘서")) {
								Player.iAttackMin += 15;
								Player.iAttackMax += 15;
								Player.iArmorMin += 5;
								Player.iArmorMax += 5;
								Player.iHPMax += 50;
								Player.iHP = Player.iHPMax;
								Player.iMPMax += 150;
								Player.iMP = Player.iMPMax;
							}


							//플레이어 정보 출력
							cout << "============LEVEL UP한 능력치============" << endl;
							cout << "이름 : " << Player.strName << "\t직업 : " << Player.strJobName << endl;
							cout << "레벨 : " << Player.iLevel << "\t경험치 : " << Player.iExp << endl;
							cout << "공격력 : " << Player.iAttackMin << " ~ " << Player.iAttackMax << "\t방어력 : " << Player.iArmorMin
								<< " ~ " << Player.iArmorMax << endl;
							cout << "HP : " << Player.iHP << "/" << Player.iHPMax
								<< "\tMP : " << Player.iMP << "/" << Player.iMPMax << endl << endl;
						}

						//얻은 경험치와 골드를 출력
						cout << MapMonster.iExp << "만큼의 경험치를 획득했습니다." << endl;
						cout << iGetGold << "만큼의 Gold를 획득했습니다." << endl << endl;

						cout << "현재경험치/필요경험치 : " << Player.iExp << " / " << iLevelUp << endl;
						cout << "소지 골드 : " << Player.tPlayerInventory.iGold << endl;
						system("pause");
						break;
					}

					//몬스터가 죽지 않으면 플레이어에게 공격을 함
					//min~max의 데미지와 방어를 만드는 함수(rnad사용)
					//공식 : rand % (Max-min+1) + min
					int iAttackMonster = rand() % (MapMonster.iAttackMax - MapMonster.iAttackMin + 1) + MapMonster.iAttackMin;
					int iArmorPlayer = rand() % (Player.iArmorMax - Player.iArmorMin + 1) + Player.iArmorMin;
					iDamage = iAttackMonster - iArmorPlayer;

					//삼항연산자 형태 = 조건식 ? true일때 : false일때
					iDamage = iDamage < 1 ? 1 : iDamage; // 데미지가 -값이 될수는 없으므로 1보다 작으면 무조건1을 주게함

					//플레이어에게 데미지를 입힘
					Player.iHP -= iDamage;

					//데미지를 얼마나 입혔는지 출력
					cout << MapMonster.strName << "(이)가 " << Player.strName << "에게 "
						<< iDamage << "의 피해를 입혔습니다." << endl;

					//플레이어가 죽었을경우
					if (Player.iHP <= 0) {
						cout << Player.strName << "(이)가 사망하였습니다" << endl;

						//경험치화 Gold를 5% 드랍
						int iGold = Player.tPlayerInventory.iGold * 0.05f;
						int iExp = Player.iExp *0.05f;

						Player.iExp -= iExp;
						Player.tPlayerInventory.iGold -= iGold;

						cout << Player.strName << "의 경험치가 " << iExp << "만큼 감소하였습니다" << endl;
						cout << Player.strName << "의 Gold가 " << iGold << "만큼 감소하였습니다" << endl;
						cout << "남은 경험치 : " << Player.iExp << "\t 남은 골드 : " << Player.tPlayerInventory.iGold << endl;

						//HP와 MP를 50만큼 획복시켜줌
						Player.iHP = 50;
						Player.iMP = 50;

						system("pause");
						break;
					}
				}
				system("pause");
			}
			break;
		case MM_STORE:
			while (1) {
				system("cls");
				cout << "============시장============" << endl;
				cout << "1.무기상점." << endl;
				cout << "2.방어구상점." << endl;
				cout << "3.마을로 돌아가기" << endl;
				cout << "이동하실 장소를 선택해주세요 : ";
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (iMenu == SM_BACK) {
					break;
				}

				switch (iMenu) {
				case SM_WEWAPON:
					while (1) {
						system("cls");
						cout << "============무기상점============" << endl;
						cout << "1.장비를 사기." << endl;
						cout << "2.장비를 팔기." << endl;
						cout << "3.시장으로 돌아가기." << endl;
						cout << "행동을 선택해주세요 : ";
						cin >> iMenu;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}
						else if (iMenu == SBC_BACK)
							break;

						/*
						struct tStore {
							char strItem[NAME_SIZE];
							char strType[NAME_SIZE];
							ITEM_TYPE eItemType;
							int iMax;
							int iMin;
							int iPrice;
							int iCell;
							char strDescription[DESCRIPTION_SIZE];
						};
						*/
						//판매목록 
						if (iMenu == SBC_BUY) {
							system("cls");
							cout << "============무기판매목록============" << endl;
							for (int i = 0; i < STORE_MAX; i++) {
								cout << "<" << i + 1 << ">" << endl;
								cout << "무기명 : " << tStoreWeapon[i].strItem << endl;
								cout << "장비타입 : " << tStoreWeapon[i].strType << endl;
								cout << tStoreWeapon[i].strDescription << endl;
								cout << "공격력 : " << tStoreWeapon[i].iMin << " ~ " << tStoreWeapon[i].iMax << endl;
								cout << "가격 : " << tStoreWeapon[i].iPrice << endl << endl;
							}

							cout << "현재 보유 금액 : " << Player.tPlayerInventory.iGold << endl;
							cout << "남은 장비 칸 : " << INVENTORY_SIZE - Player.tPlayerInventory.iItemCount << endl;
							cout << "구매하실 아이템을 선택해주세요 : ";
							cin >> iMenu;

							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							int Choice = iMenu - 1;

							if (tStoreWeapon[Choice].iPrice > Player.tPlayerInventory.iGold) {
								cout << "금액이 부족합니다. 다시 선택해주세요." << endl;
								system("pause");
								continue;
							}
							else if (Player.tPlayerInventory.iItemCount == INVENTORY_SIZE) {
								cout << "인벤토리가 부족합니다. 인벤토리를 비워주세요 " << endl;
								system("pause");
								continue;
							}
							else if (tStoreWeapon[Choice].iPrice <= Player.tPlayerInventory.iGold) {
								cout << "구매해주셔서 감사합니다. 앞으로도 좋은 물건으로 보답하겠습니다." << endl;
								Player.tPlayerInventory.iGold -= tStoreWeapon[Choice].iPrice;
								//인벤토리에 아이템 저장
								Player.tPlayerInventory.tStoreInventory[Player.tPlayerInventory.iItemCount] = tStoreWeapon[Choice];
								Player.tPlayerInventory.iItemCount++;
								system("pause");
							}

						}
						else if (iMenu == SBC_CELL) {
							system("cls");
							cout << "============무기팔기============" << endl;
							cout << "곧 업데이트 될 예정입니다." << endl;
							system("pause");
						}
						else
							break;
					}
					break;
				case SM_ARMOR:
					while (1) {
						system("cls");
						cout << "============방어구상점============" << endl;
						//판매목록 
					}
					break;
				default:
					break;
				}
			}
			break;
		case MM_INVENTORY:
			system("cls");
			//플레이어 정보 출력
			cout << "========================인벤토리========================" << endl << endl;
			cout << "============Player 능력치============" << endl;
			cout << "이름 : " << Player.strName << "\t직업 : " << Player.strJobName << endl;
			cout << "레벨 : " << Player.iLevel << "\t경험치 : " << Player.iExp << endl;
			cout << "공격력 : " << Player.iAttackMin << " ~ " << Player.iAttackMax << "\t방어력 : " << Player.iArmorMin
				<< " ~ " << Player.iArmorMax << endl;
			cout << "HP : " << Player.iHP << "/" << Player.iHPMax
				<< "\tMP : " << Player.iMP << "/" << Player.iMPMax << endl << endl;

			cout << "============소지아이템 목록============" << endl;
			for (int i = 0; i < Player.tPlayerInventory.iItemCount; i++) {
				cout << "<" << i + 1 << ">" << endl;
				cout << "이름 : " << Player.tPlayerInventory.tStoreInventory[i].strItem << "\n종류 : "
					<< Player.tPlayerInventory.tStoreInventory[i].strType << endl;
				cout << "판매가격 : " << Player.tPlayerInventory.tStoreInventory[i].iPrice << "\n구매가격 : "
					<< Player.tPlayerInventory.tStoreInventory[i].iCell << endl;
				cout << "공격력 : " << Player.tPlayerInventory.tStoreInventory[i].iMin << " ~ "
					<< Player.tPlayerInventory.tStoreInventory[i].iMax << endl;
				cout << "아이템 설명 : " << Player.tPlayerInventory.tStoreInventory[i].strDescription << endl << endl;
			}

			cout << "장착하실 아이템을 선택해주세요 : ";
			cin >> iMenu;

			//예외조건
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}

			else if (iMenu == Player.tPlayerInventory.iItemCount + 1)
				break;
			else if (iMenu<1 || iMenu>Player.tPlayerInventory.iItemCount + 1) {
				cout << "잘못입력하셨습니다. 다시 입력해주세요." << endl;
				system("pause");
				continue;
			}
			// 제대로 선택했을 경우 해당 아이템의 종류에 따라 장착 부위를
			// 결정하게 한다.
			EQUIP	eq;

			switch (Player.tPlayerInventory.tStoreInventory[iMenu - 1].eItemType)
			{
			case IT_WEAPON:
				eq = EQ_WEAPON;
				break;
			case IT_ARMOR:
				eq = EQ_ARMOR;
				break;
			}

			Player.bEquip[eq] = false;
			int idx = iMenu - 1;

			//아이템이 장착되어 있을 경우(Player.bEquip[eq] == true) 아이템을 교체해준다
			if (Player.bEquip[eq] == true) {
				tStore	tSwap = Player.tEquip[eq];
				Player.tEquip[eq] = Player.tPlayerInventory.tStoreInventory[idx];
				Player.tPlayerInventory.tStoreInventory[idx] = tSwap;
			}
			//아이템이 장착되어 있지 않은 경우
			else {
				Player.tEquip[eq] = Player.tPlayerInventory.tStoreInventory[idx];

				//아이템을 장착했으므로 한칸씩 당겨준다.
				for (int i = idx; i < Player.tPlayerInventory.iItemCount - 1; ++i)
				{
					Player.tPlayerInventory.tStoreInventory[i] = Player.tPlayerInventory.tStoreInventory[i + 1];
				}

				Player.tPlayerInventory.iItemCount--;

				// 장착을 했기 때문에 true로 만들어준다.
				Player.bEquip[eq] = true;
			}
			cout << Player.tEquip[eq].strItem << " 아이템을 장착하였습니다." << endl;
			system("pause");
			break;
		case MM_TEMPLE:
			system("cls");
			cout << "============신전============" << endl;
			cout << "신전에 오신것을 환영합니다 500Gold를 지불하면 HP와MP를 모두 회복시켜드립니다." << endl;
			cout << "1.금액을 지불하고 회복한다." << endl;
			cout << "2.마을로 돌아간다." << endl;
			cout << "행동을 선택해주세요 : ";
			cin >> iMenu;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
			switch (iMenu) {
			case ANSWER_YES:
				cout << "HP와MP 모두 했습니다." << endl;
				Player.iHP = Player.iHPMax;
				Player.iMP = Player.iMPMax;

				if (Player.tPlayerInventory.iGold < 500)
					cout << "소지금이 부족합니다. 마을로 돌아갑니다." << endl;
				else
					Player.tPlayerInventory.iGold -= 500;
				system("pause");
				break;
			case ANSWER_NO:
				cout << "마을로 돌아갑니다." << endl;
				system("pause");
				break;
			default:
				break;
			}
			break;
		default:
			cout << "잘못선택하셨습니다." << endl;
			break;
		}
	}
	cout << "게임을 종료합니다." << endl;
	return 0;
}