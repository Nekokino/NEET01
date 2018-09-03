#pragma once

#include <NTLogic.h>


class NTCamera;
class NTPieceWindow;
class NTFontRenderer;
class NTSpRenderer;
class BattleSystem : public NTLogic
{
private:
	enum BATTLEWINDOWSTATUS
	{
		BWS_IDLE,
		BWS_TURN,
		BWS_ATTACK,
		BWS_SKILL,
		BWS_ITEM,
		BWS_MAX
	};

	Autoptr<NTObject> SceneCamera;

	Autoptr<NTObject> PlayerStatusObj;

	Autoptr<NTPieceWindow> PlayerStatusWindow;
	Autoptr<NTFontRenderer> Player01Name;
	Autoptr<NTFontRenderer> Player01HP;
	Autoptr<NTFontRenderer> Player01MP;
	Autoptr<NTObject> Player01TurnBar;

	Autoptr<NTFontRenderer> Player02Name;
	Autoptr<NTFontRenderer> Player02HP;
	Autoptr<NTFontRenderer> Player02MP;
	Autoptr<NTObject> Player02TurnBar;

	Autoptr<NTFontRenderer> Player03Name;
	Autoptr<NTFontRenderer> Player03HP;
	Autoptr<NTFontRenderer> Player03MP;
	Autoptr<NTObject> Player03TurnBar;

	Autoptr<NTObject> EnemyListObj;
	Autoptr<NTPieceWindow> EnemyListWindow;
	Autoptr<NTFontRenderer> EnemyList01;
	Autoptr<NTFontRenderer> EnemyList02;
	Autoptr<NTFontRenderer> EnemyList03;
	Autoptr<NTFontRenderer> EnemyList04;

	Autoptr<NTObject> PlayerOrderObj;
	Autoptr<NTPieceWindow> PlayerOrderWindow;
	Autoptr<NTFontRenderer> AttackString;
	Autoptr<NTFontRenderer> SkillString;
	Autoptr<NTFontRenderer> ItemString;

	Autoptr<NTObject> PlayerSkillObj;
	Autoptr<NTPieceWindow> PlayerSkillWindow;

	Autoptr<NTObject> PlayerItemObj;
	Autoptr<NTPieceWindow> PlayerItemWindow;

	Autoptr<NTSpRenderer> Cursor;

	BATTLEWINDOWSTATUS CurStatus;
	NTVEC WinSize;
	int CurPlayerIndex;
	int CurOrderIndex;
	int CurEnemyIndex;
	bool TurnReady;



	std::vector<Autoptr<NTObject>> BattlePlayerVector;
	std::list<Autoptr<NTObject>> BattleEnemyList;

	std::list<Autoptr<NTObject>>::iterator ListIter;

	bool bCursor;

private:
	void SetPlayerPosition();

	void CalDamage(Autoptr<NTObject> _Attacker, Autoptr<NTObject> _Target);

public:
	void EnterBattle(std::list<Autoptr<NTObject>>* _EnemyList);
	void EndBattle();

public:
	bool Init();
	void PreUpdate() override;
	void MainUpdate() override;
	void AfterUpdate() override;
	void DbgRender() override;
public:
	BattleSystem();
	~BattleSystem();
};