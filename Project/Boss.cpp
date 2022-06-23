#include "Boss.h"

// �{�X�̓o��A�j���[�V����

// ��O���牜�։�]���Ȃ���o��
ANIM_DATA g_BossAnimPosZ[2] = {
	{ 0.0f,-FIELD_HALF_Z,EASE_LINEAR },
	{ 2.0f,2.0f,EASE_OUT_SINE },
};
ANIM_DATA g_BossAnimRotZ[2] = {
	{ 0.0f,MOF_MATH_2PI,EASE_LINEAR },
	{ 2.0f,0.0f,EASE_OUT_SINE },
};
// ��O���Ɍ����悤�ɉ�]
ANIM_DATA g_BossAnimRotX[2] = {
	{ 2.0f,MOF_MATH_PI,EASE_LINEAR },
	{ 4.0f,0.0f,EASE_INOUT_SINE },
};
// ���シ��
ANIM_DATA g_BossAnimPosY[2] = {
	{ 4.0f,-10.0f,EASE_LINEAR },
	{ 6.0f,-3.5f,EASE_INOUT_SINE },
};

/**
 * �R���X�g���N�^
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
 * �f�X�g���N�^
 *
 */
CBoss::~CBoss(){
}

/**
 * �ǂݍ���
 *
 */
bool CBoss::Load(){
	// �{�X�{�̂̃��b�V��
	if(!m_Mesh.Load("boss_core.mom"))
	{
		return false;
	}
	// �{�X�̃p�[�c�̃��b�V��
	if(!m_PartsMesh.Load("boss_parts.mom"))
	{
		return false;
	}
	return true;
}

/**
 * ������
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
 * �J�n
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

	//�e�p�[�c�̏�����
}

/**
 * �X�V
 *
 */
void CBoss::Update(CEnemyShot* shot,int smax){
	// ��\��
	if(!GetShow())
	{
		return;
	}
}

/**
 * �_���[�W����
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
 * ����̕����։�]����
 *
 */
void CBoss::RotateTarget(){
}

/**
 * �S���ʂւ̒e����
 *
 */
void CBoss::ShotAllDirShot(CEnemyShot* shot, int smax, int sCnt){
}

/**
 * �p�[�c�X�V
 *
 */
void CBoss::UpdateParts(int idx, CEnemyShot* shot, int smax, bool bShot){
}

/**
 * �`��
 *
 */
void CBoss::Render(){
}

/**
 * �f�o�b�O�`��
 *
 */
void CBoss::RenderDebug(){
	// ��\��
	if(!GetShow())
	{
		return;
	}
	// �����蔻��̕\��
	CGraphicsUtilities::RenderSphere(GetSphere(),Vector4(1,0,0,0.3f));
	
	for(int i = 0; i < BOSS_PARTS_MAX; i++)
	{
		m_Parts[i].RenderDebug();
	}
}

/**
 * �\�����̃p�[�c�̐�
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
 * ���
 *
 */
void CBoss::Release(){
	m_Mesh.Release();
	m_PartsMesh.Release();
}
