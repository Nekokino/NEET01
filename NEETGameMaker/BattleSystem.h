#pragma once

#include <NTLogic.h>


class NTCamera;
class BattleSystem : public NTLogic
{
private:
	Autoptr<NTObject> SceneCamera;
	std::vector<Autoptr<NTObject>> BattlePlayerVector;
	std::list<Autoptr<NTObject>> BattleEnemyList;

private:
	void SetPlayerPosition();

public:
	void EnterBattle(std::list<Autoptr<NTObject>>* _EnemyList);
	void EndBattle();

public:
	bool Init();
	void MainUpdate() override;
	void AfterUpdate() override;
	void DbgRender() override;
public:
	BattleSystem();
	~BattleSystem();
};