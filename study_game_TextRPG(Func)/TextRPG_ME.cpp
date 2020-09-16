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
	JOB_END//�߰��� ������ �־ ���ϰ� �����Ҽ� ���� 
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

//����
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

//����
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


	//�÷��̾� ���� ����
	//�÷��̾� �̸��� �Է¹޴´�.
	//NAEM_SIZE-1��ŭ �޴� ���� : ���ڿ��� ���� NULL�� ������ �ϴµ� ���������� �� ä��� NULL�� ��� ���ڿ��� �ν� ����
	cout << "============ĳ���� ����============" << endl;
	cout << "�г��� : ";
	cin.getline(Player.strName, NAME_SIZE - 1);

	//������ �Է� �޴´�.
	while (iJob == JOB_NONE) {
		system("cls");
		cout << "============ĳ���� ����============" << endl;
		cout << "1.�����" << endl;
		cout << "2.�ǽ�����" << endl;
		cout << "3.��ũ�θ༭" << endl;
		cout << "������ ������ �ּ��� : ";
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
			strcpy_s(Player.strJobName, "�����");
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
			strcpy_s(Player.strJobName, "�ǽ�����");
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
			strcpy_s(Player.strJobName, "��ũ�θ༭");
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
	//���͸� �����Ѵ�.
	tMonster MonsterArr[MT_BACK - 1] = {};
	//�������(����)
	strcpy_s(MonsterArr[0].strName, "���");
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

	//Ʈ�ѻ���(�븻)
	strcpy_s(MonsterArr[1].strName, "Ʈ��");
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


	//�巡�����(�ϵ�)
	strcpy_s(MonsterArr[2].strName, "�巡��");
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


	//�������� �Ǹ��� ���� ����
	tStore tStoreWeapon[STORE_MAX] = {};

	strcpy_s(tStoreWeapon[0].strItem, "������");
	strcpy_s(tStoreWeapon[0].strType, "����");
	strcpy_s(tStoreWeapon[0].strDescription, "���� �������̰� ���� ���̴�. ���߰� ������ �Ǽպ��ٴ� ������ ����.");
	tStoreWeapon[0].iMin = 20;
	tStoreWeapon[0].iMax = 20;
	tStoreWeapon[0].iPrice = 10000;
	tStoreWeapon[0].iCell = 3000;

	strcpy_s(tStoreWeapon[1].strItem, "������ ��");
	strcpy_s(tStoreWeapon[1].strType, "����");
	strcpy_s(tStoreWeapon[1].strDescription, "����� �������̰� ���� ���̴�. �ƹ��� ����� �� ����.");
	tStoreWeapon[1].iMin = 200;
	tStoreWeapon[1].iMax = 400;
	tStoreWeapon[1].iPrice = 1;
	tStoreWeapon[1].iCell = 41;

	strcpy_s(tStoreWeapon[2].strItem, "����Į����");
	strcpy_s(tStoreWeapon[2].strType, "����");
	strcpy_s(tStoreWeapon[2].strDescription, "��� �ձ��� �������̰� ���� ���̴�. �� �ô��� ������ ����� �� �ִ�");
	tStoreWeapon[2].iMin = 6500;
	tStoreWeapon[2].iMax = 8500;
	tStoreWeapon[2].iPrice = 10000000;
	tStoreWeapon[2].iCell = 300000;


	//�������� �Ǹ��� �� ����
	tStore tStoreArmor[STORE_MAX] = {};


	while (1) {
		bool bRun = true;
		system("cls");

		cout << "============����============" << endl;
		cout << "1.����" << endl;
		cout << "2.����" << endl;
		cout << "3.�κ��丮" << endl;
		cout << "4.����" << endl;
		cout << "5.��������" << endl;
		cout << "�ൿ�� ������ �ּ��� : ";
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
			cout << "============����============" << endl;
			cout << "1.��� ����" << endl;
			cout << "2.Ʈ�� ����" << endl;
			cout << "3.�巡�� ����" << endl;
			cout << "4.����" << endl;
			cout << "�̵��Ͻ� ��Ҹ� �������ּ��� : ";
			cin >> iMenu;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}

			if (iMenu == MT_BACK) {
				break;
			}
			//������ �޴����� 1�� ���ָ� ������ �迭 �ε����� �ȴ�. �׷����ؼ� ���� ��ȯ���ش�.
			tMonster MapMonster = MonsterArr[iMenu - 1];//���� ����
			while (bRun) {
				system("cls");
				switch (iMenu) {
				case MT_EASY:
					cout << "============���============" << endl;
					break;
				case MT_NORMAL:
					cout << "============Ʈ��============" << endl;
					break;
				case MT_HARD:
					cout << "============�巡��============" << endl;
					break;
				default:
					break;
				}
				system("cls");
				//�÷��̾� ���� ���
				cout << "============Player============" << endl;
				cout << "�̸� : " << Player.strName << "\t���� : " << Player.strJobName << endl;
				cout << "���� : " << Player.iLevel << "\t����ġ : " << Player.iExp << endl;
				cout << "���ݷ� : " << Player.iAttackMin << " ~ " << Player.iAttackMax << "\t���� : " << Player.iArmorMin
					<< " ~ " << Player.iArmorMax << endl;
				cout << "HP : " << Player.iHP << "/" << Player.iHPMax
					<< "\tMP : " << Player.iMP << "/" << Player.iMPMax << endl << endl;

				//�������� ���
				cout << "============Monster============" << endl;
				cout << "�̸� : " << MapMonster.strName << "\t���� : " << MapMonster.iLevel << endl;
				cout << "���ݷ� : " << MapMonster.iAttackMin << " ~ " << MapMonster.iAttackMax
					<< "\t���� : " << MapMonster.iArmorMin << " ~ " << MapMonster.iArmorMax << endl;
				cout << "HP : " << MapMonster.iHP << "/" << MapMonster.iHPMax
					<< "\tMP : " << MapMonster.iMP << "/" << MapMonster.iMPMax << endl;
				cout << "ȹ�����ġ : " << MapMonster.iExp
					<< "\tȹ���� : " << MapMonster.iGoldMin << " ~ " << MapMonster.iGoldMax << endl << endl;

				cout << "1.�ο��." << endl;
				cout << "2.����ġ��" << endl;
				cout << "�ൿ�� �������ּ��� : ";
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
					//min~max�� �������� �� ����� �Լ�(rnad���)
					//���� : rand % (Max-min+1) + min
					int iAttackPlayer = rand() % (Player.iAttackMax - Player.iAttackMin + 1) + Player.iAttackMin;
					int iArmorMonster = rand() % (MapMonster.iArmorMax - MapMonster.iArmorMin + 1) + MapMonster.iArmorMin;
					int iDamage = iAttackPlayer - iArmorMonster;

					//���׿����� ���� = ���ǽ� ? true�϶� : false�϶�
					iDamage = iDamage < 1 ? 1 : iDamage; // �������� -���� �ɼ��� �����Ƿ� 1���� ������ ������1�� �ְ���

					//���Ϳ��� �������� ����
					MapMonster.iHP -= iDamage;

					//�������� �󸶳� �������� ���
					cout << Player.strName << "(��)�� " << MapMonster.strName << "���� "
						<< iDamage << "�� ���ظ� �������ϴ�." << endl;


					//���Ͱ� �׾��� ���
					if (MapMonster.iHP <= 0) {
						cout << MapMonster.strName << "�� ����Ͽ����ϴ�" << endl << endl;

						//������ ����� ���� ����
						int iGetGold = rand() % (MapMonster.iGoldMax - MapMonster.iGoldMin + 1) + MapMonster.iGoldMin;

						//���� ������ ����ġ�� ��带 ȹ������ش�
						Player.iExp += MapMonster.iExp;
						Player.tPlayerInventory.iGold += iGetGold;


						//���� ����ġ�� ���̸� �������� �Ѵ�.
						if (Player.iExp >= iLevelUp) {
							Player.iLevel += 1;

							//�÷��̾� ����ġ �ʱ�ȭ
							Player.iExp -= iLevelUp;

							//�ʿ� ����ġ �䱸���� �������� �ش�.
							iLevelUp *= 1.5;

							cout << "�����մϴ�! �������� �Ͽ� " << Player.iLevel << "�� �Ǿ����ϴ�!" << endl << endl;

							if (strcmp(Player.strJobName, "�����")) {
								Player.iAttackMin += 5;
								Player.iAttackMax += 5;
								Player.iArmorMin += 15;
								Player.iArmorMax += 15;
								Player.iHPMax += 150;
								Player.iHP = Player.iHPMax;
								Player.iMPMax += 50;
								Player.iMP = Player.iMPMax;

							}
							else if (strcmp(Player.strJobName, "�ǽ�����")) {
								Player.iAttackMin += 10;
								Player.iAttackMax += 10;
								Player.iArmorMin += 10;
								Player.iArmorMax += 10;
								Player.iHPMax += 100;
								Player.iHP = Player.iHPMax;
								Player.iMPMax += 100;
								Player.iMP = Player.iMPMax;
							}
							else if (strcmp(Player.strJobName, "��ũ�θ༭")) {
								Player.iAttackMin += 15;
								Player.iAttackMax += 15;
								Player.iArmorMin += 5;
								Player.iArmorMax += 5;
								Player.iHPMax += 50;
								Player.iHP = Player.iHPMax;
								Player.iMPMax += 150;
								Player.iMP = Player.iMPMax;
							}


							//�÷��̾� ���� ���
							cout << "============LEVEL UP�� �ɷ�ġ============" << endl;
							cout << "�̸� : " << Player.strName << "\t���� : " << Player.strJobName << endl;
							cout << "���� : " << Player.iLevel << "\t����ġ : " << Player.iExp << endl;
							cout << "���ݷ� : " << Player.iAttackMin << " ~ " << Player.iAttackMax << "\t���� : " << Player.iArmorMin
								<< " ~ " << Player.iArmorMax << endl;
							cout << "HP : " << Player.iHP << "/" << Player.iHPMax
								<< "\tMP : " << Player.iMP << "/" << Player.iMPMax << endl << endl;
						}

						//���� ����ġ�� ��带 ���
						cout << MapMonster.iExp << "��ŭ�� ����ġ�� ȹ���߽��ϴ�." << endl;
						cout << iGetGold << "��ŭ�� Gold�� ȹ���߽��ϴ�." << endl << endl;

						cout << "�������ġ/�ʿ����ġ : " << Player.iExp << " / " << iLevelUp << endl;
						cout << "���� ��� : " << Player.tPlayerInventory.iGold << endl;
						system("pause");
						break;
					}

					//���Ͱ� ���� ������ �÷��̾�� ������ ��
					//min~max�� �������� �� ����� �Լ�(rnad���)
					//���� : rand % (Max-min+1) + min
					int iAttackMonster = rand() % (MapMonster.iAttackMax - MapMonster.iAttackMin + 1) + MapMonster.iAttackMin;
					int iArmorPlayer = rand() % (Player.iArmorMax - Player.iArmorMin + 1) + Player.iArmorMin;
					iDamage = iAttackMonster - iArmorPlayer;

					//���׿����� ���� = ���ǽ� ? true�϶� : false�϶�
					iDamage = iDamage < 1 ? 1 : iDamage; // �������� -���� �ɼ��� �����Ƿ� 1���� ������ ������1�� �ְ���

					//�÷��̾�� �������� ����
					Player.iHP -= iDamage;

					//�������� �󸶳� �������� ���
					cout << MapMonster.strName << "(��)�� " << Player.strName << "���� "
						<< iDamage << "�� ���ظ� �������ϴ�." << endl;

					//�÷��̾ �׾������
					if (Player.iHP <= 0) {
						cout << Player.strName << "(��)�� ����Ͽ����ϴ�" << endl;

						//����ġȭ Gold�� 5% ���
						int iGold = Player.tPlayerInventory.iGold * 0.05f;
						int iExp = Player.iExp *0.05f;

						Player.iExp -= iExp;
						Player.tPlayerInventory.iGold -= iGold;

						cout << Player.strName << "�� ����ġ�� " << iExp << "��ŭ �����Ͽ����ϴ�" << endl;
						cout << Player.strName << "�� Gold�� " << iGold << "��ŭ �����Ͽ����ϴ�" << endl;
						cout << "���� ����ġ : " << Player.iExp << "\t ���� ��� : " << Player.tPlayerInventory.iGold << endl;

						//HP�� MP�� 50��ŭ ȹ��������
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
				cout << "============����============" << endl;
				cout << "1.�������." << endl;
				cout << "2.������." << endl;
				cout << "3.������ ���ư���" << endl;
				cout << "�̵��Ͻ� ��Ҹ� �������ּ��� : ";
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
						cout << "============�������============" << endl;
						cout << "1.��� ���." << endl;
						cout << "2.��� �ȱ�." << endl;
						cout << "3.�������� ���ư���." << endl;
						cout << "�ൿ�� �������ּ��� : ";
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
						//�ǸŸ�� 
						if (iMenu == SBC_BUY) {
							system("cls");
							cout << "============�����ǸŸ��============" << endl;
							for (int i = 0; i < STORE_MAX; i++) {
								cout << "<" << i + 1 << ">" << endl;
								cout << "����� : " << tStoreWeapon[i].strItem << endl;
								cout << "���Ÿ�� : " << tStoreWeapon[i].strType << endl;
								cout << tStoreWeapon[i].strDescription << endl;
								cout << "���ݷ� : " << tStoreWeapon[i].iMin << " ~ " << tStoreWeapon[i].iMax << endl;
								cout << "���� : " << tStoreWeapon[i].iPrice << endl << endl;
							}

							cout << "���� ���� �ݾ� : " << Player.tPlayerInventory.iGold << endl;
							cout << "���� ��� ĭ : " << INVENTORY_SIZE - Player.tPlayerInventory.iItemCount << endl;
							cout << "�����Ͻ� �������� �������ּ��� : ";
							cin >> iMenu;

							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							int Choice = iMenu - 1;

							if (tStoreWeapon[Choice].iPrice > Player.tPlayerInventory.iGold) {
								cout << "�ݾ��� �����մϴ�. �ٽ� �������ּ���." << endl;
								system("pause");
								continue;
							}
							else if (Player.tPlayerInventory.iItemCount == INVENTORY_SIZE) {
								cout << "�κ��丮�� �����մϴ�. �κ��丮�� ����ּ��� " << endl;
								system("pause");
								continue;
							}
							else if (tStoreWeapon[Choice].iPrice <= Player.tPlayerInventory.iGold) {
								cout << "�������ּż� �����մϴ�. �����ε� ���� �������� �����ϰڽ��ϴ�." << endl;
								Player.tPlayerInventory.iGold -= tStoreWeapon[Choice].iPrice;
								//�κ��丮�� ������ ����
								Player.tPlayerInventory.tStoreInventory[Player.tPlayerInventory.iItemCount] = tStoreWeapon[Choice];
								Player.tPlayerInventory.iItemCount++;
								system("pause");
							}

						}
						else if (iMenu == SBC_CELL) {
							system("cls");
							cout << "============�����ȱ�============" << endl;
							cout << "�� ������Ʈ �� �����Դϴ�." << endl;
							system("pause");
						}
						else
							break;
					}
					break;
				case SM_ARMOR:
					while (1) {
						system("cls");
						cout << "============������============" << endl;
						//�ǸŸ�� 
					}
					break;
				default:
					break;
				}
			}
			break;
		case MM_INVENTORY:
			system("cls");
			//�÷��̾� ���� ���
			cout << "========================�κ��丮========================" << endl << endl;
			cout << "============Player �ɷ�ġ============" << endl;
			cout << "�̸� : " << Player.strName << "\t���� : " << Player.strJobName << endl;
			cout << "���� : " << Player.iLevel << "\t����ġ : " << Player.iExp << endl;
			cout << "���ݷ� : " << Player.iAttackMin << " ~ " << Player.iAttackMax << "\t���� : " << Player.iArmorMin
				<< " ~ " << Player.iArmorMax << endl;
			cout << "HP : " << Player.iHP << "/" << Player.iHPMax
				<< "\tMP : " << Player.iMP << "/" << Player.iMPMax << endl << endl;

			cout << "============���������� ���============" << endl;
			for (int i = 0; i < Player.tPlayerInventory.iItemCount; i++) {
				cout << "<" << i + 1 << ">" << endl;
				cout << "�̸� : " << Player.tPlayerInventory.tStoreInventory[i].strItem << "\n���� : "
					<< Player.tPlayerInventory.tStoreInventory[i].strType << endl;
				cout << "�ǸŰ��� : " << Player.tPlayerInventory.tStoreInventory[i].iPrice << "\n���Ű��� : "
					<< Player.tPlayerInventory.tStoreInventory[i].iCell << endl;
				cout << "���ݷ� : " << Player.tPlayerInventory.tStoreInventory[i].iMin << " ~ "
					<< Player.tPlayerInventory.tStoreInventory[i].iMax << endl;
				cout << "������ ���� : " << Player.tPlayerInventory.tStoreInventory[i].strDescription << endl << endl;
			}

			cout << "�����Ͻ� �������� �������ּ��� : ";
			cin >> iMenu;

			//��������
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}

			else if (iMenu == Player.tPlayerInventory.iItemCount + 1)
				break;
			else if (iMenu<1 || iMenu>Player.tPlayerInventory.iItemCount + 1) {
				cout << "�߸��Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
				system("pause");
				continue;
			}
			// ����� �������� ��� �ش� �������� ������ ���� ���� ������
			// �����ϰ� �Ѵ�.
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

			//�������� �����Ǿ� ���� ���(Player.bEquip[eq] == true) �������� ��ü���ش�
			if (Player.bEquip[eq] == true) {
				tStore	tSwap = Player.tEquip[eq];
				Player.tEquip[eq] = Player.tPlayerInventory.tStoreInventory[idx];
				Player.tPlayerInventory.tStoreInventory[idx] = tSwap;
			}
			//�������� �����Ǿ� ���� ���� ���
			else {
				Player.tEquip[eq] = Player.tPlayerInventory.tStoreInventory[idx];

				//�������� ���������Ƿ� ��ĭ�� ����ش�.
				for (int i = idx; i < Player.tPlayerInventory.iItemCount - 1; ++i)
				{
					Player.tPlayerInventory.tStoreInventory[i] = Player.tPlayerInventory.tStoreInventory[i + 1];
				}

				Player.tPlayerInventory.iItemCount--;

				// ������ �߱� ������ true�� ������ش�.
				Player.bEquip[eq] = true;
			}
			cout << Player.tEquip[eq].strItem << " �������� �����Ͽ����ϴ�." << endl;
			system("pause");
			break;
		case MM_TEMPLE:
			system("cls");
			cout << "============����============" << endl;
			cout << "������ ���Ű��� ȯ���մϴ� 500Gold�� �����ϸ� HP��MP�� ��� ȸ�����ѵ帳�ϴ�." << endl;
			cout << "1.�ݾ��� �����ϰ� ȸ���Ѵ�." << endl;
			cout << "2.������ ���ư���." << endl;
			cout << "�ൿ�� �������ּ��� : ";
			cin >> iMenu;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
			switch (iMenu) {
			case ANSWER_YES:
				cout << "HP��MP ��� �߽��ϴ�." << endl;
				Player.iHP = Player.iHPMax;
				Player.iMP = Player.iMPMax;

				if (Player.tPlayerInventory.iGold < 500)
					cout << "�������� �����մϴ�. ������ ���ư��ϴ�." << endl;
				else
					Player.tPlayerInventory.iGold -= 500;
				system("pause");
				break;
			case ANSWER_NO:
				cout << "������ ���ư��ϴ�." << endl;
				system("pause");
				break;
			default:
				break;
			}
			break;
		default:
			cout << "�߸������ϼ̽��ϴ�." << endl;
			break;
		}
	}
	cout << "������ �����մϴ�." << endl;
	return 0;
}