#pragma once

#include "GameDefine.h"
#include "PlayerShot.h"
#include "Enemy.h"
#include "Boss.h"

// ˆÚ“®‘¬“x
#define PLAYER_SPEED		(0.1f)

#define	PLAYERSHOT_COUNT		(40)

#define PLAYERSHOT_WAIT			(5)

class CPlayer{
private:
	CMeshContainer	m_ShotMesh;
	CPlayerShot		m_ShotArry[PLAYERSHOT_COUNT];
	int				m_ShotWait;
	CMeshContainer	m_Mesh;
	CVector3		m_Pos;
	float			m_RotZ;
	bool			m_bDead;
public:
	CPlayer();
	~CPlayer();
	void RenderDebug();
	CSphere GetSphere() { return CSphere(m_Pos, 0.4f); }
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebugText();
	const CVector3 GetPosition(){ return m_Pos; }
	void CollisionEnemy(CEnemy& ene);
	bool IsDead() { return m_bDead; }
	void CollisionEnemyShot(CEnemyShot& shot);
	void CollisionBoss(CBoss& boss);
	void Release();
};