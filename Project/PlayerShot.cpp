#include "PlayerShot.h"

/**
* コンストラクタ
*/
CPlayerShot::CPlayerShot() :
	m_pMesh(NULL),
	m_pos(0.0f, 0.0f, 0.0f),
	m_bShow(false) {
}

/**
* デストラクタ
*/
CPlayerShot::~CPlayerShot() {
}

/**
* 初期化
*/
void CPlayerShot::Initialize(void) {
	m_pos = Vector3(0.0f, 0.0f, 0.0f);
	m_bShow = true;
}

void CPlayerShot::Fire(const Vector3& p)
{
	m_pos = p;
	m_bShow = true;
}

void CPlayerShot::Update()
{
	if (!m_bShow)
	{
		return;
	}
	m_pos.z += PLAYERSHOT_SPEED;
	if (FIELD_HALF_Z < m_pos.z)
	{
		m_bShow = false;
	}
}

/**
* 描画
*/
void CPlayerShot::Render(void) {
	if (!m_bShow)
	{
		return;
	}
	CMatrix44 wMat;
	wMat.Translation(m_pos);
	m_pMesh->Render(wMat);
}