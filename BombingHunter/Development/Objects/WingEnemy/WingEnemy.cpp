#include "WingEnemy.h"
#include "../../Objects/Bomb/Bomb.h"
#include "../GameObject.h"
#include "DxLib.h"

WingEnemy::WingEnemy() : animation_count(0), direction(0.0f)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

WingEnemy::~WingEnemy()
{

}

//初期化処理
void WingEnemy::Initialize()
{
	if (!isActive) return;
	//画像の読込み
	animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
	taip = WINGENEMY;

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("トブテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);
}

//更新処理
void WingEnemy::Update()
{
	if (!isActive) return;
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void WingEnemy::Draw() const
{
	if (!isActive) return;
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//情報を基にトブテキ画像を描画する
	DrawRotaGraphF(location.x, location.y, 0.7, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void WingEnemy::Finalize()
{
	//使用した画像の解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void WingEnemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object->Gettaip() == BOMB)
	{
		if (dynamic_cast<Bomb*>(hit_object) != nullptr)
		{
			//当たった時の処理
			direction = 0.0f;
			box_size = 0.0f;
			Finalize();
			deleteflag = TRUE;
			if (!isActive) return;
			//当たった時の処理
			//direction = 0.0f;
		}
	}
}

//移動処理
void WingEnemy::Movement()
{
	if (!isActive) return;
	//画面端に到達したら、進行方向を反転する
	if (((location.x + direction.x) < box_size.x) ||
		(640.0f - box_size.x) < (location.x + direction.y))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void WingEnemy::AnimationControl()
{
	if (!isActive) return;
	//アニメーションカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切替
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}