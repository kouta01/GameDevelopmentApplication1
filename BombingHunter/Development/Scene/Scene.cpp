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
	//����Y��h�~
	Finalize();
}

void Scene::Initialize()
{
	

	//�v���C���[����ʒ���������ɐ�������
	CreateObject<Player>(Vector2D(320.0f, 60.0f));
}

void Scene::Update()
{
	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//Z�L�[����������A�G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 400.0f));
	}

	//G�L�[����������A���A�G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_G))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 400.0f));
	}

	//W�L�[����������A�g�u�e�L�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_W))
	{
		CreateObject<WingEnemy>(Vector2D(100.0f, 200.0f));
	}

	//H�L�[����������A���𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_H))
	{
		CreateObject<Harpy>(Vector2D(100.0f, 200.0f));
	}

	//B�L�[����������A���e�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_B))
	{
		CreateObject<Bomb>(Vector2D(320.0f, 125.0f));
	}

}

void Scene::Draw()const
{
	//�摜�̓Ǎ���
	int background_image = LoadGraph("Resource/Images/BackGround.png");
	DrawGraph(0, 0, background_image, FALSE);
	//�G���[�`�F�b�N
	if (background_image == -1) {
		throw("�摜BackGround.png������܂���\n");
	}
	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��`�悷��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}


void Scene::Finalize()
{
	//�I�u�W�F�N�g���X�g������Ȃ�A�������I������
	if (objects.empty())
	{
		return;
	}

	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���������
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�Ɋm�ۂ������X�g���������
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N����(��`�̒��S�œ����蔻������
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

//�����蔻�菈��(�v���C���[�ƓG)
bool IsHitCheck(Player* p, Enemy* e)
{
	//�G��񂪂Ȃ���΁A�����蔻��𖳎�����
	if (e == nullptr) {
		return false;
	}

	//�ʒu���̍����擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();
	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����
	return ((fabs(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

#else

//�����蔻��`�F�b�N����(����̒��_���W���瓖���蔻��v�Z���s��)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif  // D_PIVOT_CNETER