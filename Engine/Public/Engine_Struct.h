#pragma once

namespace Engine
{
	typedef struct tagLineIndices32 //4����Ʈ
	{
		unsigned long _1, _2;
	}LINEINDICES32;

	typedef struct tagLineIndices16 //2����Ʈ
	{
		unsigned short _1, _2;
	}LINEINDICES16;

	typedef struct tagFaceIndices32 //4����Ʈ
	{
		unsigned long _1, _2, _3;
	}FACEINDICES32;

	typedef struct tagFaceIndices16 //2����Ʈ
	{
		unsigned short _1, _2, _3;
	}FACEINDICES16;

	/*
	�ε������� ������ ���ؽ��� �ε��� ũ�⿡ ���� 2����Ʈ�� ���� 4����Ʈ�� ������ �ٸ���.
	���� ��� ������ ���ؽ� ��ȣ�� ũ�ٸ� short���� long�� ������ ���̴�.
	*/
	typedef struct tagVertex_XYZ
	{
		float		x, y, z;

		tagVertex_XYZ(const D3DXVECTOR3& _Pos)
		{
			x = _Pos.x;
			y = _Pos.y;
			z = _Pos.z;
		}

		tagVertex_XYZ(const float& _x, const float& _y, const float& _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		static const DWORD FVF = D3DFVF_XYZ;
	}VTX;


	typedef struct tagVertex_Texture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR2		vTexUV;

		tagVertex_Texture(const D3DXVECTOR3& _Pos, const D3DXVECTOR2& _Tex)
		{
			vPosition = _Pos;
			vTexUV = _Tex;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
	}VTXTEX;

	typedef struct tagVertex_CubeTexture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vTexUV;

		tagVertex_CubeTexture(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Tex)
		{
			vPosition = _Pos;
			vTexUV = _Tex;
		}

		static const DWORD SKY = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);
	}VTXCUBETEX;

	typedef struct tagVertex_Color
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNorm;
		D3DCOLOR		DColor;

		tagVertex_Color(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Norm, const D3DCOLOR& _Color)
		{
			vPosition = _Pos;
			vNorm = _Norm;
			DColor = _Color;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;
	}VTXCOLOR;

	typedef struct tagVertex_OnlyColor
	{
		D3DXVECTOR3		vPosition;
		D3DCOLOR		DColor;

		tagVertex_OnlyColor(const D3DXVECTOR3& _Pos, const D3DCOLOR& _Color)
		{
			vPosition = _Pos;
			DColor = _Color;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	}VTXONLYCOLOR;

	typedef struct tagVertex_Default
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNorm;
		D3DXVECTOR2		vUV;

		tagVertex_Default(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Norm, const D3DXVECTOR2& _vUV)
		{
			vPosition = _Pos;
			vNorm = _Norm;
			vUV = _vUV;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	}VTXDEFAULT;

	typedef struct tagVertex_Sub
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNorm;

		tagVertex_Sub(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Norm)
		{
			vPosition = _Pos;
			vNorm = _Norm;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL ;
	}VTXSUB;

	typedef struct tagVertex_Normal
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNorm;


		tagVertex_Normal(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Norm)
		{
			vPosition = _Pos;
			vNorm = _Norm;

		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
	}VTXNORMAL;

	typedef struct tagGraphicDesc
	{
		unsigned int iWinCX, iWinCY;
		HWND	hWnd;
		bool	isWindowMode;
	}GRAPHICDESC;

	typedef struct tagTextInfo
	{
		RECT rcTemp;
		_tchar szBuff[MAX_PATH] = L"";
		D3DXCOLOR color;
	}TEXTINFO;

	typedef struct tagRay
	{
		D3DXVECTOR3 Dir;
		D3DXVECTOR3 Pos;
		float		fLength;

	}RAY;

	typedef struct tagOBBBoxInfo
	{
		//OBB�ڽ��� ����(������Ʈ�� �� ����� �Ǿ�� ��)
		D3DXVECTOR3 ObbCenterPos;

		// �� ��� ������ ���ؽ��� ����
		D3DXVECTOR3 ObbSize;

		// �� ���ؽ����� ������� ��ǥ
		D3DXVECTOR3 tVertex[8];

		//���� ��
		D3DXVECTOR3 LocalAxis[3];

		//�������� ��ĺ�ȯ�� ���� ���� ��������� �� = 6���� ���� ��ġ�� �ʴ� 3�鿡 ���� ��������
		D3DXVECTOR3 WorldAxis[3];

		tagOBBBoxInfo()
		{
			ObbCenterPos = { 0, 0, 0 };
			ObbSize = { 0, 0, 0 };
			LocalAxis[0] = { 1, 0, 0 };
			LocalAxis[1] = { 0, 1, 0 };
			LocalAxis[2] = { 0, 0, 1 };
		}

		tagOBBBoxInfo(D3DXVECTOR3& size)
		{
			ObbSize = size;
			LocalAxis[0] = { 1, 0, 0 };
			LocalAxis[1] = { 0, 1, 0 };
			LocalAxis[2] = { 0, 0, 1 };
		}

		void SetSize(const D3DXVECTOR3& size)
		{
			ObbSize = size;


			tVertex[0] = { 0 - (ObbSize.x), 0 + (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[1] = { 0 + (ObbSize.x), 0 + (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[2] = { 0 + (ObbSize.x), 0 - (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[3] = { 0 - (ObbSize.x), 0 - (ObbSize.y), 0 - (ObbSize.z) };

			//4-7 -> z < 0, �ð�(�� ������ �ݽð�)
			tVertex[4] = { 0 - (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[5] = { 0 + (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[6] = { 0 + (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[7] = { 0 - (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };
		}

		void SetMatrix(D3DXMATRIX* pmatWorld)
		{
			ObbCenterPos.x = pmatWorld->_41;
			ObbCenterPos.y = pmatWorld->_42;
			ObbCenterPos.z = pmatWorld->_43;

			for (int i = 0; i < 3; ++i)
			{
				WorldAxis[i] = LocalAxis[i];
				D3DXVec3TransformNormal(&WorldAxis[i], &WorldAxis[i], pmatWorld);
			}

			tVertex[0] = { 0 - (ObbSize.x), 0 + (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[1] = { 0 + (ObbSize.x), 0 + (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[2] = { 0 + (ObbSize.x), 0 - (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[3] = { 0 - (ObbSize.x), 0 - (ObbSize.y), 0 - (ObbSize.z) };

			//4-7 -> z < 0, �ð�(�� ������ �ݽð�)
			tVertex[4] = { 0 - (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[5] = { 0 + (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[6] = { 0 + (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[7] = { 0 - (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };

			//���� ���� 8�� ����ȭ
			for (int i = 0; i < 8; ++i)
			{
				D3DXVec3TransformCoord(&tVertex[i], &tVertex[i], pmatWorld);
			}
		}

	}OBBINFO;

	union COLLIDER_ID
	{
		struct
		{
			unsigned long Left_id;
			unsigned long Right_id;
		};
		unsigned long long  ID;

	};

	/*struct COLLIDER_ID
	{
		unsigned long Left_id;
		unsigned long Right_id;
		unsigned long long  ID;
	};*/


	enum class RENDERGROUP 
	{ 
		RENDER_PRIORITY = 0, 
		RENDER_DEFERRED, 
		RENDER_NONALPHABLEND,
		RENDER_BLOOMABLE,
		RENDER_ALPHABLEND, 
		RENDER_UNDER_UI, 
		RENDER_UI, 
		RENDER_NORMAL, 
		RENDER_DEPTH,
		RENDER_DIFFUSE,
		RENDER_SPECULAR,
		RENDER_VIEWBLOOM,
		RENDER_VIEWLIGHT,
		RENDER_HDR,
		RENDER_BLOOM,
		RENDER_BRIGHTNESS,
		RENDER_FADEOUT,
		RENDER_POSTPROCCESSING,
		RENDER_END 
	};

	enum CHANNELID { BGM, PLAYER, PLAYERBULLET, EFFECT, EFFECT2, UI, SYSTEM_EFFECT, SYSTEM_EFFECT2, SYSTEM_EFFECT3, MAXCHANNEL };

	enum class TEXTURE_TYPE { TYPE_DEFAULT = 0, TYPE_CUBE, TYPE_END };
	enum class MEMORY_TYPE { MEMORY_STATIC = 0, MEMORY_DYNAMIC, MEMORY_END };

	enum class RIGID_BODY { ACCEL=0, SPEED};

	enum class KEY_STATE {
		TAP, // �� ���� ����
		HOLD,// �� ������ ����
		AWAY,// �� �� ����
		NONE,// �� �ȴ��� ����
	};
	enum class KEY
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0,
		F1, F2, F3, F4,
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		ALT,
		LSHIFT,
		SPACE,
		CTRL,
		ENTER,
		ESC,
		TAB,
		LBUTTON,
		RBUTTON,
		BACKSPACE,
		DELETEKEY,
		LAST,
	};

	enum class MOUSEBUTTON { MBS_LBUTTON = 0, MBS_RBUTTON, MBS_WHEEL, MBS_X, MBS_END };
	enum class MOUSEMOVE { MMS_X = 0, MMS_Y, MMS_WHEEL, MMS_END };

	enum class CONTROLLER { PLAYER = 0, AI, LOCK, CONTROLLER_END };
	enum class TARGETMODE { TARGET_SINGLE, TARGET_MULTIRAY, TARGET_MULTIWIDE, TARGET_END};

	enum class MATRIX_STATE { RIGHT, UP, LOOK, POSITION, STATE_END };

	enum class COLLISION_TYPE
	{
		DEFAULT = 0,
		PLAYER,
		PLAYER_ATTACK,
		MONSTER,
		MONSTER_ATTACK,
		EFFECTS,
		SIGHT,
		RANGE,
		CAMERA,
		MOUSE,
		OBJECT,
		ITEM,
		TYPE_END
	};

	enum class COLLIDER_SHAPE
	{
		SPHERE = 0,
		OBB,
		MESH,
		RAY,
		SHAPE_END
	};


	// �� �ൿ ���� �з��� 100������. ��, �ൿ �������� �ִ� 100������ ������ �� �ִ�.
	// �ִ� �ൿ ������ 900������� �� �� �ִ�. (��Ʈ�ѷ����� �ø� �� ����)
	enum class STATE
	{
		STATE_NONE = 0,
		MOVE_UPPER_LEFT,
		MOVE_DOWN_FRONT,
		MOVE_LIFT_FRONT,
		MOVE_LIFT_BACK,
		MOVE_JUMP_FRONT,
		MOVE_UPPER_RIGHT,
		MOVE_FORWARD,
		MOVETARGET_CHASE = 100,
		MOVETAGET_CHASE_PLAYER,
		MOVETARGET_RSPIN,
		MOVETARGET_LSPIN,
		MOVETARGET_BACK,
		MOVEROLLER_RSPIN,
		MOVEROLLER_LSPIN,
		ATTACK_TAP = 200, //Fire�� �� ���� ȣ���ϰ�, ������ �ð����� ���
		ATTACK_HOLD, //������ �ð����� ��� Fire�� ȣ��
		STATE_END
	};
	enum class MOVE_UI_DIR
	{
		MOVE_UI_RIGHT = 0,
		MOVE_UI_LEFT,
		MOVE_UI_UP,
		MOVE_UI_DOWN,
		MOVE_UI_END
	};

	enum class GPS_TYPE
	{
		GPS_FRIENDLY = 0,
		GPS_ENEMY,
		GPS_END
	};
}



	













