#include "Bomb.h"
#include "../Enemy/Enemy.h"
#include "../GoldEnemy/GoldEnemy.h"
#include "../Harpy/Harpy.h"
#include "../WingEnemy/WingEnemy.h"
#include "../GameObject.h"
#include "DxLib.h"

Bomb::Bomb() : animation_count(0), anima_count(0), direction(0.0f)
{
	animation[0] = NULL;
	anima[0] = NULL;
	anima[1] = NULL;
	anima[2] = NULL;
}

Bomb::~Bomb()
{

}

//初期化処理
void Bomb::Initialize()
{
	//画像の読込み
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	taip = BOMB;

	//エラーチェック
	if (animation[0] == -1 || animation[0] == -1)
	{
		throw("ボムの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(0.0f, 1.0f);
}

//更新処理
void Bomb::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void Bomb::Draw() const
{
	//情報を基にボム画像を描画する
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE);

	//親クラスを描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Bomb::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	{
		if (hit_object->Gettaip() == ENEMY)
		{
			if (dynamic_cast<Enemy*>(hit_object) != nullptr)
			{
				//当たった時の処理
				direction = 0.0f;
				box_size = 0.0f;
				anima[0] = LoadGraph("Resource/Images/Blast/1.png");
				anima[1] = LoadGraph("Resource/Images/Blast/2.png");
				anima[2] = LoadGraph("Resource/Images/Blast/3.png");
				deleteflag = TRUE;
			}
		}

		if (hit_object->Gettaip() == GOLDENEMY)
		{
			if (dynamic_cast<GoldEnemy*>(hit_object) != nullptr)
			{
				//当たった時の処理
				direction = 0.0f;
				box_size = 0.0f;
				anima[0] = LoadGraph("Resource/Images/Blast/1.png");
				anima[1] = LoadGraph("Resource/Images/Blast/2.png");
				anima[2] = LoadGraph("Resource/Images/Blast/3.png");
				deleteflag = TRUE;
			}
		}

		if (hit_object->Gettaip() == WINGENEMY)
		{
			if (dynamic_cast<WingEnemy*>(hit_object) != nullptr)
			{
				//当たった時の処理
				direction = 0.0f;
				box_size = 0.0f;
				anima[0] = LoadGraph("Resource/Images/Blast/1.png");
				anima[1] = LoadGraph("Resource/Images/Blast/2.png");
				anima[2] = LoadGraph("Resource/Images/Blast/3.png");
				deleteflag = TRUE;
			}
		}

		if (hit_object->Gettaip() == HARPY)
		{
			if (dynamic_cast<Harpy*>(hit_object) != nullptr)
			{
				//当たった時の処理
				direction = 0.0f;
				box_size = 0.0f;
				anima[0] = LoadGraph("Resource/Images/Blast/1.png");
				anima[1] = LoadGraph("Resource/Images/Blast/2.png");
				anima[2] = LoadGraph("Resource/Images/Blast/3.png");
				deleteflag = TRUE;
			}
		}
	}
}

//移動処理
void Bomb::Movement()
{
	//進行方向に向かって、位置座標を変更する
	location += direction;
	if (location.y >= 400)
	{
		deleteflag = TRUE;
	}
	if (location.x >= 640 || location.x <= 0)
	{
		Finalize();
	}
}

//アニメーション制御
void Bomb::AnimationControl()
{
	//アニメーションカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;
	}
}