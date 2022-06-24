/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "Player.h"
#include     "stage.h"
#include	"Stage1.h"
#include	"Boss.h"

//カメラ
CCamera		gCamera;

//ライト
CDirectionalLight	gLight;

//プレイヤー
CPlayer		gPlayer;

#define		ENEMY_COUNT				(20)
CEnemy		gEnemyArray[ENEMY_COUNT];

#define ENEMYSHOT_COUNT				(200)
CEnemyShot gShotArray[ENEMYSHOT_COUNT];
CMeshContainer gEnemyShotMesh;

CBoss		gBoss;

//ステージ
CStage		gStage;

bool		gbEnemyDestroyed = false;

bool		gbClear = false;

// デバッグ表示フラグ
bool		gbDebug = false;


/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	//カメラの初期化
	gCamera.SetViewPort();
	gCamera.LookAt(Vector3(0, 6.0f, -17.0f), Vector3(0, 0, -10), Vector3(0, 1, 0));
	gCamera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	CGraphicsUtilities::SetCamera(&gCamera);

	//ライト初期化
	gLight.SetDirection(Vector3(-1, -2, 1.5f));
	gLight.SetDiffuse(MOF_COLOR_WHITE);
	gLight.SetAmbient(MOF_COLOR_HWHITE);
	gLight.SetSpeculer(MOF_COLOR_WHITE);
	CGraphicsUtilities::SetDirectionalLight(&gLight);

	//プレイヤーの素材読み込み
	gPlayer.Load();

	//ステージの読み込み
	gStage.Load();

	if (!gEnemyShotMesh.Load("eShot.mom"))
	{
		return false;
	}

	gBoss.Load();

	//プレイヤーの状態初期化
	gPlayer.Initialize();

	//ステージの状態初期化
	gStage.Initialize(&gStg1EnemyStart);
	
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gEnemyArray[i].Initialize();
	}

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		gShotArray[i].Initialize();
		gShotArray[i].SetMesh(&gEnemyShotMesh);
	}
	gBoss.Initialize();

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	//ステージの更新
	gStage.Update(gEnemyArray,ENEMY_COUNT);
	//プレイヤーの更新
	gPlayer.Update();

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gEnemyArray[i].SetTargetPos(gPlayer.GetPosition());
		gEnemyArray[i].Update(gShotArray, ENEMYSHOT_COUNT);
	}

	gBoss.SetTargetPos(gPlayer.GetPosition());
	gBoss.Update(gShotArray, ENEMYSHOT_COUNT);

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		gShotArray[i].Update();
	}

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gPlayer.CollisionEnemy(gEnemyArray[i]);
	}

	gPlayer.CollisionBoss(gBoss);

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		gPlayer.CollisionEnemyShot(gShotArray[i]);
	}

	if (!gbEnemyDestroyed && gStage.IsAllEnemy())
	{
		bool btmp = true;
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			if (gEnemyArray[i].GetShow())
			{
				btmp = false;
			}
		}
		gbEnemyDestroyed = btmp;

		if (gbEnemyDestroyed)
		{
			gBoss.Start();
			gBoss.SetTargetPos(gPlayer.GetPosition());
			gBoss.Update(gShotArray, ENEMYSHOT_COUNT);
		}
	}

	if (!gbClear && gbEnemyDestroyed && !gBoss.GetShow())
	{
		gbClear = true;
	}
	//デバッグ表示切り替え
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gbDebug = ((gbDebug) ? false : true);
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && (gPlayer.IsDead() || gbClear))
	{
		gbEnemyDestroyed = false;
		gbClear = false;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && gPlayer.IsDead())
	{
		gPlayer.Initialize();
		gStage.Initialize(&gStg1EnemyStart);
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			gEnemyArray[i].Initialize();
		}
		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			gShotArray[i].Initialize();
		}
		gBoss.Initialize();
	}
	//プレイヤーの動きに合わせてカメラを動かす
	float posX = gPlayer.GetPosition().x * 0.4f;
	CVector3 cpos = gCamera.GetViewPosition();
	CVector3 tpos = gCamera.GetTargetPosition();
	CVector3 vup = CVector3(0, 1, 0);
	cpos.x = posX;
	tpos.x = posX;
	vup.RotationZ(gPlayer.GetPosition().x / FIELD_HALF_X * MOF_ToRadian(10.0f));
	gCamera.LookAt(cpos, tpos, vup);
	gCamera.Update();
	return TRUE;
}

/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画処理
	g_pGraphics->RenderStart();
	// 画面のクリア
	g_pGraphics->ClearTarget(0.65f,0.65f,0.67f,0.0f,1.0f,0);

	g_pGraphics->SetDepthEnable(TRUE);

	//ステージの描画
	gStage.Render();

	//プレイヤーの描画
	gPlayer.Render();

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gEnemyArray[i].Render();
	}

	for (int i = 0; i < ENEMYSHOT_COUNT; i++)
	{
		gShotArray[i].Render();
	}

	gBoss.Render();


	// 3Dデバッグ描画
	if (gbDebug)
	{
		gPlayer.RenderDebug();

		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			gEnemyArray[i].RenderDebug();
		}

		for (int i = 0; i < ENEMYSHOT_COUNT; i++)
		{
			gShotArray[i].RenderDebug();
		}

		gBoss.RenderDebug();

		//移動可能範囲の表示
		CMatrix44 matWolrd;
		matWolrd.Scaling(FIELD_HALF_X * 2, 1, FIELD_HALF_Z * 2);
		CGraphicsUtilities::RenderPlane(matWolrd, Vector4(1, 1, 1, 0.4f));
	}

	g_pGraphics->SetDepthEnable(FALSE);

	//2Dデバッグ描画
	if (gbDebug)
	{
		// ステージのデバッグ文字描画
		gStage.RenderDebugText();

		//プレイヤーのデバッグ文字描画
		gPlayer.RenderDebugText();

		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			gEnemyArray[i].RenderDebugText(i);
		}
	}

	if (gPlayer.IsDead())
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームオーバー : Enterキーでもう一度最初から");
	}

	else if (gbClear)
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームクリア : Enterキーでもう一度最初から");
	}

	// 描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){
	gPlayer.Release();
	gStage.Release();
	gEnemyShotMesh.Release();
	gBoss.Release();
	return TRUE;
}