#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/GoldEnemy/GoldEnemy.h"
#include "../Objects/Harpy/Harpy.h"
#include "../Objects/WingEnemy/WingEnemy.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

#define D_PIVOT_CENTER

Scene::Scene() : objects()
{

}

Scene::~Scene()
{
	//解放忘れ防止
	Finalize();
}

void Scene::Initialize()
{
	

	//プレイヤーを画面中央あたりに生成する
	CreateObject<Player>(Vector2D(320.0f, 60.0f));
}

void Scene::Update()
{
	//オブジェクトリスト内のオブジェクトを更新する
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//Zキーを押したら、敵を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 400.0f));
	}

	//Gキーを押したら、レア敵を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_G))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 400.0f));
	}

	//Wキーを押したら、トブテキを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_W))
	{
		CreateObject<WingEnemy>(Vector2D(100.0f, 200.0f));
	}

	//Hキーを押したら、鳥を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_H))
	{
		CreateObject<Harpy>(Vector2D(100.0f, 200.0f));
	}

	//Bキーを押したら、爆弾を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_B))
	{
		CreateObject<Bomb>(Vector2D(320.0f, 125.0f));
	}

}

void Scene::Draw()const
{
	//画像の読込み
	int background_image = LoadGraph("Resource/Images/BackGround.png");
	DrawGraph(0, 0, background_image, FALSE);
	//エラーチェック
	if (background_image == -1) {
		throw("画像BackGround.pngがありません\n");
	}
	//オブジェクトリスト内のオブジェクトを描画する
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}


void Scene::Finalize()
{
	//オブジェクトリスト内が空なら、処理を終了する
	if (objects.empty())
	{
		return;
	}

	//オブジェクトリスト内のオブジェクトを解放する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的に確保したリストを解放する
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//当たり判定チェック処理(矩形の中心で当たり判定を取る
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

//あたり判定処理(プレイヤーと敵)
bool IsHitCheck(Player* p, Enemy* e)
{
	//敵情報がなければ、当たり判定を無視する
	if (e == nullptr) {
		return false;
	}

	//位置情報の差分取得
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//当たり判定サイズの大きさを取得
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
	//コリジョンデータより位置情報の差分が小さいなら、ヒット判定
	return ((fabs(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

#else

//当たり判定チェック処理(左上の頂点座標から当たり判定計算を行う)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif  // D_PIVOT_CNETER