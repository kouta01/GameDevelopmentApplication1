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

//����������
void Bomb::Initialize()
{
	//�摜�̓Ǎ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	taip = BOMB;

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[0] == -1)
	{
		throw("�{���̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, 1.0f);
}

//�X�V����
void Bomb::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Bomb::Draw() const
{
	//������Ƀ{���摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE);

	//�e�N���X��`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Bomb::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	{
		if (hit_object->Gettaip() == ENEMY)
		{
			if (dynamic_cast<Enemy*>(hit_object) != nullptr)
			{
				//�����������̏���
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
				//�����������̏���
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
				//�����������̏���
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
				//�����������̏���
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

//�ړ�����
void Bomb::Movement()
{
	//�i�s�����Ɍ������āA�ʒu���W��ύX����
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

//�A�j���[�V��������
void Bomb::AnimationControl()
{
	//�A�j���[�V�����J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;
	}
}