#include "Boss.h"

// ボスの登場アニメーション

// 手前から奥へ回転しながら登場
ANIM_DATA g_BossAnimPosZ[2] = {
	{ 0.0f,-FIELD_HALF_Z,EASE_LINEAR },
	{ 2.0f,2.0f,EASE_OUT_SINE },
};
ANIM_DATA g_BossAnimRotZ[2] = {
	{ 0.0f,MOF_MATH_2PI,EASE_LINEAR },
	{ 2.0f,0.0f,EASE_OUT_SINE },
};
// 手前側に向くように回転
ANIM_DATA g_BossAnimRotX[2] = {
	{ 2.0f,MOF_MATH_PI,EASE_LINEAR },
	{ 4.0f,0.0f,EASE_INOUT_SINE },
};
// 浮上する
ANIM_DATA g_BossAnimPosY[2] = {
	{ 4.0f,-10.0f,EASE_LINEAR },
	{ 6.0f,-3.5f,EASE_INOUT_SINE },
};

/**
 * コンストラクタ
 *
 */
CBoss::CBoss():
m_Mesh(),
m_PartsMesh(),
m_Pos(0,0,0),
m_Rot(0,0,0),
m_matWorld(),
m_bShow(false),
m_HP(200),
m_ShotWait(0),
m_TargetPos(0,0,0),
m_AnimTime(0),
m_Parts(){
}

/**
 * デストラクタ
 *
 */
CBoss::~CBoss(){
}

/**
 * 読み込み
 *
 */
bool CBoss::Load(){
	// ボス本体のメッシュ
	if(!m_Mesh.Load("boss_core.mom"))
	{
		return false;
	}
	// ボスのパーツのメッシュ
	if(!m_PartsMesh.Load("boss_parts.mom"))
	{
		return false;
	}
	return true;
}

/**
 * 初期化
 *
 */
void CBoss::Initialize(){
	m_Pos = Vector3(0,0,0);
	m_Rot = Vector3(0,0,0);
	m_matWorld.Identity();
	m_bShow = false;
	m_HP = 200;
	m_ShotWait = 0;
	m_TargetPos = Vector3(0,0,0);
	m_AnimTime = 0;
	for(int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		m_Parts[i].Initialize();
	}
}

/**
 * 開始
 *
 */
void CBoss::Start(){
	m_Pos = Vector3(0,0,0);
	m_Rot = Vector3(0,0,0);
	m_matWorld.Identity();
	m_bShow = true;
	m_HP = 200;
	m_ShotWait = 0;
	m_TargetPos = Vector3(0,0,0);
	m_AnimTime = 0;

	//各パーツの初期化
}

/**
 * 更新
 *
 */
void CBoss::Update(CEnemyShot* shot,int smax){
	// 非表示
	if(!GetShow())
	{
		return;
	}
}

/**
 * ダメージ処理
 *
 */
void CBoss::Damage(int dmg){
	m_HP -= dmg;
	if(m_HP <= 0)
	{
		m_bShow = false;
	}
}

/**
 * 相手の方向へ回転する
 *
 */
void CBoss::RotateTarget(){
}

/**
 * 全方位への弾発射
 *
 */
void CBoss::ShotAllDirShot(CEnemyShot* shot, int smax, int sCnt){
}

/**
 * パーツ更新
 *
 */
void CBoss::UpdateParts(int idx, CEnemyShot* shot, int smax, bool bShot){
}

/**
 * 描画
 *
 */
void CBoss::Render(){
}

/**
 * デバッグ描画
 *
 */
void CBoss::RenderDebug(){
	// 非表示
	if(!GetShow())
	{
		return;
	}
	// 当たり判定の表示
	CGraphicsUtilities::RenderSphere(GetSphere(),Vector4(1,0,0,0.3f));
	
	for(int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		m_Parts[i].RenderDebug();
	}
}

/**
 * 表示中のパーツの数
 *
 */
int CBoss::GetPartsCount(){
	int partsCnt = 0;
	for(int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		if(m_Parts[i].GetShow())
		{
			partsCnt++;
		}
	}
	return partsCnt;
}

/**
 * 解放
 *
 */
void CBoss::Release(){
	m_Mesh.Release();
	m_PartsMesh.Release();
}
