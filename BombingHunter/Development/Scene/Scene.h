#pragma once

#include <vector>
#include "../Objects/GameObject.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"


class Scene
{
private:
	std::vector<GameObject*> objects;  //オブジェクトリスト
	Player* player;
	Enemy* enemy;
	int zikan;
	int zikan_count;
	int number_image[10];
	int zikan_image;
	int finish_image;

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);
	bool IsHitCheck(Player* p, Enemy* e);

	//オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスのオブジェクトを生成する
		T* new_instance = new T();
		//GameObjectが継承しているか確認する
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("ゲームオブジェクトが生成できませんでした。/n");
		}

		//初期化処理
		new_object->Initialize();

		//位置情報の設定
		new_object->SetLocation(location);

		//シーン内に存在するオブジェクトリストに追加
		objects.push_back(new_object);

		//生成したオブジェクトのポインタを返却
		return new_instance;

	}
};