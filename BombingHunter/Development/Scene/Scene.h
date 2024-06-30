#pragma once

#include <vector>
#include "../Objects/GameObject.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"


class Scene
{
private:
	std::vector<GameObject*> objects;  //�I�u�W�F�N�g���X�g
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
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);
	bool IsHitCheck(Player* p, Enemy* e);

	//�I�u�W�F�N�g��������
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�̃I�u�W�F�N�g�𐶐�����
		T* new_instance = new T();
		//GameObject���p�����Ă��邩�m�F����
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("�Q�[���I�u�W�F�N�g�������ł��܂���ł����B/n");
		}

		//����������
		new_object->Initialize();

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�V�[�����ɑ��݂���I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//���������I�u�W�F�N�g�̃|�C���^��ԋp
		return new_instance;

	}
};