#include "PlayerShot.h"

/**
 * �R���X�g���N�^
 */
CPlayerShot::CPlayerShot() :
m_pMesh(NULL),
m_Pos(0.0f,0.0f,0.0f),
m_bShow(false){
}

/**
 * �f�X�g���N�^
 */
CPlayerShot::~CPlayerShot(){
}

/**
 * ������
 */
void CPlayerShot::Initialize(void){
}

/**
 * ����
 */
void CPlayerShot::Fire(const Vector3& p){

}

/**
 * �X�V
 */
void CPlayerShot::Update(void){

}

/**
 * �`��
 */
void CPlayerShot::Render(void){

}

void CPlayerShot::RenderDebug(void) {
	if (!m_bShow)
	{
		return;
	}
	CGraphicsUtilities::RenderSphere(GetSphere(), Vector4(0, 1, 0, 0.3f));
}
