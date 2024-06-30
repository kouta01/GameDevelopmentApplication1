#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER  //���W�̌��_���摜�̒��S�ɂ���

#define ENEMY (1)
#define GOLDENEMY (2)
#define HARPY (3)
#define PLAYER (4)
#define WINGENEMY (5)
#define BOMB (6)

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;  //�ʒu���
	Vector2D box_size;  //��`�̑傫��
	double radian;      //����
	int image;          //�摜
	int sound;          //����
	int taip;

public:
	GameObject();
	virtual ~GameObject();
	bool isActive;
	bool deleteflag;
	bool Deleteobject();

	virtual void Initialize();
	virtual void Update();
	virtual void Draw() const;
	virtual void Finalize();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;

	int Gettaip();
};