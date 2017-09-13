#include "StdAfx.h"



namespace Shared {

	void Slider::ModifySRT(D3DXVECTOR3* scale,D3DXVECTOR3* rot,D3DXVECTOR3* trans,Slider::Operation op,const AAUCardData::BoneMod& mod) {
		switch (op) {
		case ADD:
			scale->x += mod.scales[0];
			scale->y += mod.scales[1];
			scale->z += mod.scales[2];
			trans->x += mod.transformations[0];
			trans->y += mod.transformations[1];
			trans->z += mod.transformations[2];
			rot->x += mod.rotations[0];
			rot->y += mod.rotations[1];
			rot->z += mod.rotations[2];
			break;
		case MULTIPLY:
			scale->x *= mod.scales[0];
			scale->y *= mod.scales[1];
			scale->z *= mod.scales[2];
			trans->x *= mod.transformations[0];
			trans->y *= mod.transformations[1];
			trans->z *= mod.transformations[2];
			rot->x += mod.rotations[0];
			rot->y += mod.rotations[1];
			rot->z += mod.rotations[2];
			break;
		case DIVIDE:
			if (mod.scales[0] != 0) scale->x /= mod.scales[0];
			if (mod.scales[1] != 0) scale->y /= mod.scales[1];
			if (mod.scales[2] != 0) scale->z /= mod.scales[2];
			if (mod.transformations[0] != 0) trans->x /= mod.transformations[0];
			if (mod.transformations[1] != 0)trans->y /= mod.transformations[1];
			if (mod.transformations[2] != 0)trans->z /= mod.transformations[2];
			rot->x += mod.rotations[0];
			rot->y += mod.rotations[1];
			rot->z += mod.rotations[2];
			break;
		default:
			break;
		}
	}

	void Slider::ModifyKeyframe(ExtClass::Keyframe* frame,Slider::Operation op,const AAUCardData::BoneMod& elem) {
		switch (op) {
		case ADD: {
			frame->m_scaleX += elem.scales[0];
			frame->m_scaleY += elem.scales[1];
			frame->m_scaleZ += elem.scales[2];
			D3DXQUATERNION rotQuat;
			(*Shared::D3DXQuaternionRotationYawPitchRoll)(&rotQuat,elem.rotations[1],elem.rotations[0],elem.rotations[2]);
			D3DXQUATERNION* origQuat = (D3DXQUATERNION*)&frame->m_quatX;
			(*Shared::D3DXQuaternionMultiply)(origQuat,origQuat,&rotQuat);
			frame->m_transX += elem.transformations[0];
			frame->m_transY += elem.transformations[1];
			frame->m_transZ += elem.transformations[2];
			break; }
		case MULTIPLY: {
			frame->m_scaleX *= elem.scales[0];
			frame->m_scaleY *= elem.scales[1];
			frame->m_scaleZ *= elem.scales[2];
			D3DXQUATERNION rotQuat;
			(*Shared::D3DXQuaternionRotationYawPitchRoll)(&rotQuat,elem.rotations[1],elem.rotations[0],elem.rotations[2]);
			D3DXQUATERNION* origQuat = (D3DXQUATERNION*)&frame->m_quatX;
			(*Shared::D3DXQuaternionMultiply)(origQuat,origQuat,&rotQuat);
			frame->m_transX *= elem.transformations[0];
			frame->m_transY *= elem.transformations[1];
			frame->m_transZ *= elem.transformations[2];
			break; }
		case DIVIDE: {
			if(elem.scales[0] != 0) frame->m_scaleX /= elem.scales[0];
			if (elem.scales[1] != 0) frame->m_scaleY /= elem.scales[1];
			if (elem.scales[2] != 0) frame->m_scaleZ /= elem.scales[2];
			D3DXQUATERNION rotQuat;
			(*Shared::D3DXQuaternionRotationYawPitchRoll)(&rotQuat,elem.rotations[1],elem.rotations[0],elem.rotations[2]);
			D3DXQUATERNION* origQuat = (D3DXQUATERNION*)&frame->m_quatX;
			(*Shared::D3DXQuaternionMultiply)(origQuat,origQuat,&rotQuat);
			if (elem.transformations[0] != 0) frame->m_transX /= elem.transformations[0];
			if (elem.transformations[1] != 0) frame->m_transY /= elem.transformations[1];
			if (elem.transformations[2] != 0) frame->m_transZ /= elem.transformations[2];
			break; }
		default:
			break;
		}
	}

#define EXPR(ex) static_cast<float(*)(float)>([](float x)->float { return (ex); })

	const std::vector<Slider> g_sliders[ExtClass::CharacterStruct::N_MODELS] = {
		{
			//FACE
			{ ExtClass::CharacterStruct::FACE, 0, TEXT("A00_J_kuti"),{ 1,0,0, 0,0,0, 0,0,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //mouth
			{ ExtClass::CharacterStruct::FACE, 1, TEXT("A00_O_mimi"),{ 0,0,0, 0,0,0, 0,1,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //ear height
			{ ExtClass::CharacterStruct::FACE, 2, TEXT("A00_J_kuti"),{ 0,0,0, 0,0,0, 0,1,0.9f }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //mouth height
			{ ExtClass::CharacterStruct::FACE, 3, TEXT("A00_J_mayuLrot"),{ 0,0,0, 0,0,0, 0,1,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //left eyebrow height
			{ ExtClass::CharacterStruct::FACE, 4, TEXT("A00_J_mayuRrot"),{ 0,0,0, 0,0,0, 0,1,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //right eyebrow height
			{ ExtClass::CharacterStruct::FACE, 5, TEXT("A00_J_meC"),{ 0,0,0, 0,0,0, 0,0,1 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //eye depth?
			/* mimi
			x 0.64346
			y 0.38282
			z 0.4461*/
			{ ExtClass::CharacterStruct::FACE, 6, TEXT("A00_O_mimi"),{ 1,0,0, 0,0,0, 0.64346f,0,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //ear stuff; doesnt make sense without split ears
			{ ExtClass::CharacterStruct::FACE, 7, TEXT("A00_O_mimiL"),{ 1,0,0, 0,0,0, -0.64346f,0,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //ear stuff; doesnt make sense without split ears
			{ ExtClass::CharacterStruct::FACE, 8, TEXT("A00_O_mimi"),{ 0,1,0, 0,0,0, 0,0.38282f,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //ear stuff; doesnt make sense without split ears
			{ ExtClass::CharacterStruct::FACE, 9, TEXT("A00_O_mimiL"),{ 0,1,0, 0,0,0, 0,0.38282f,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //ear stuff; doesnt make sense without split ears
			{ ExtClass::CharacterStruct::FACE, 10, TEXT("AS00_N_megane"),{ 0,0,0, 0,0,0, 0,1,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //glasses Y
			{ ExtClass::CharacterStruct::FACE, 11, TEXT("AS00_N_megane"),{ 0,0,0, 0,0,0, 0,0,1 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //glasses Z
			{ ExtClass::CharacterStruct::FACE, 12, TEXT("AS00_N_megane"),{ 0,0,0, 1,0,0, 0,0,0 }, Slider::ADD, AAUCardData::MODIFY_FRAME }, //glasses Z
		},
		{
			//SKELETON
			{ ExtClass::CharacterStruct::SKELETON, 0, TEXT("a01_J_Hip_010"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //body height,
			{ ExtClass::CharacterStruct::SKELETON, 1, TEXT("a01_J_Hip_010"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //body width,
			{ ExtClass::CharacterStruct::SKELETON, 2, TEXT("a01_J_Hip_010"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //body thickness
			{ ExtClass::CharacterStruct::SKELETON, 3, TEXT("a01_J_ArmL_01"),	{ 1,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left arm thickness
			{ ExtClass::CharacterStruct::SKELETON, 4, TEXT("a01_J_ArmR_01"),	{ 1,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right arm thickness
			{ ExtClass::CharacterStruct::SKELETON, 5, TEXT("a01_J_HandL_02"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left hand fingers length
			{ ExtClass::CharacterStruct::SKELETON, 6, TEXT("a01_J_HandR_02"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right hand fingers length
			{ ExtClass::CharacterStruct::SKELETON, 7, TEXT("a01_J_Kosi_010"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //kosi thickness
			{ ExtClass::CharacterStruct::SKELETON, 8, TEXT("a01_J_Kosi_010"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME },
			{ ExtClass::CharacterStruct::SKELETON, 9, TEXT("a01_J_SiriL_010"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME },
			{ ExtClass::CharacterStruct::SKELETON,10, TEXT("a01_J_SiriR_010"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME },
			{ ExtClass::CharacterStruct::SKELETON,11, TEXT("a01_J_SiriL_010"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME },
			{ ExtClass::CharacterStruct::SKELETON,12, TEXT("a01_J_SiriR_010"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME },
			{ ExtClass::CharacterStruct::SKELETON,13, TEXT("a01_J_OyaL_01"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left hand thumb length
			{ ExtClass::CharacterStruct::SKELETON,14, TEXT("a01_J_OyaR_01"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right hand thumb length
			{ ExtClass::CharacterStruct::SKELETON,15, TEXT("a01_J_FootL_03"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left foot length
			{ ExtClass::CharacterStruct::SKELETON,16, TEXT("a01_J_FootR_03"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right foot length
			{ ExtClass::CharacterStruct::SKELETON,17, TEXT("a01_J_FootL_03"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left foot width
			{ ExtClass::CharacterStruct::SKELETON,18, TEXT("a01_J_FootR_03"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right foot width
			{ ExtClass::CharacterStruct::SKELETON,19, TEXT("a01_J_UplegL_020"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left thigh width
			{ ExtClass::CharacterStruct::SKELETON,20, TEXT("a01_J_UplegR_020"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right thigh width
			{ ExtClass::CharacterStruct::SKELETON,21, TEXT("a01_J_KataL_02"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left shoulder height
			{ ExtClass::CharacterStruct::SKELETON,22, TEXT("a01_J_KataR_02"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right shoulder height
			{ ExtClass::CharacterStruct::SKELETON,23, TEXT("a01_J_KataL_01"),	{ 0,0,0, 0,0,0, 0,1,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left shoulder height
			{ ExtClass::CharacterStruct::SKELETON,24, TEXT("a01_J_KataR_01"),	{ 0,0,0, 0,0,0, 0,1,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right shoulder height
			{ ExtClass::CharacterStruct::SKELETON,25, TEXT("a01_J_Kosi_020"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::DIVIDE, AAUCardData::MODIFY_FRAME }, //counterpart to 7
			{ ExtClass::CharacterStruct::SKELETON,26, TEXT("a01_J_Kosi_020"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::DIVIDE, AAUCardData::MODIFY_FRAME }, //counterpart to 8
			{ ExtClass::CharacterStruct::SKELETON,27, TEXT("a01_J_Neck_01"),	{ 1,0,1, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //neck size
			{ ExtClass::CharacterStruct::SKELETON,28, TEXT("a01_J_Neck_02"),	{ 1,0,1, 0,0,0, 0,0,0 },		Slider::DIVIDE, AAUCardData::MODIFY_FRAME }, //neck size counterpart
			{ ExtClass::CharacterStruct::SKELETON,29, TEXT("a_J_dan07"),		{ 1,1,1, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //male only
			{ ExtClass::CharacterStruct::SKELETON,30, TEXT("a_J_dan03"),		{ 0,0,0, 0,0,0, 0,0,1 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //apply to females too
			{ ExtClass::CharacterStruct::SKELETON,31, TEXT("a_J_ana03"),		{ 0,0,0, 0,0,0, 0,0,1 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //not sure why these exist twice
			{ ExtClass::CharacterStruct::SKELETON,32, TEXT("a_J_dan03"),		{ 1,1,0, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //girth
			{ ExtClass::CharacterStruct::SKELETON,33, TEXT("a_J_ana03"),		{ 1,1,0, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //
			{ ExtClass::CharacterStruct::SKELETON,34, TEXT("a_J_dan06"),		{ 1,1,1, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //apply to females too
			{ ExtClass::CharacterStruct::SKELETON,35, TEXT("a_J_ana06"),		{ 1,1,1, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //not sure why these exist twice
			{ ExtClass::CharacterStruct::SKELETON,36, TEXT("a01_J_KataL_02"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left shoulder width
			{ ExtClass::CharacterStruct::SKELETON,37, TEXT("a01_J_KataR_02"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right shoulder width
			{ ExtClass::CharacterStruct::SKELETON,38, TEXT("a01_J_UplegL_020"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left thigh height
			{ ExtClass::CharacterStruct::SKELETON,39, TEXT("a01_J_UplegR_020"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right thigh height
			{ ExtClass::CharacterStruct::SKELETON,40, TEXT("a01_J_UplegL_020"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left thigh thickness
			{ ExtClass::CharacterStruct::SKELETON,41, TEXT("a01_J_UplegR_020"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right thigh thickness
			{ ExtClass::CharacterStruct::SKELETON,42, TEXT("a01_J_LegL_01"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left calve width
			{ ExtClass::CharacterStruct::SKELETON,43, TEXT("a01_J_LegR_01"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right calve width
			{ ExtClass::CharacterStruct::SKELETON,44, TEXT("a01_J_LegL_01"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left calve height
			{ ExtClass::CharacterStruct::SKELETON,45, TEXT("a01_J_LegR_01"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right calve height
			{ ExtClass::CharacterStruct::SKELETON,46, TEXT("a01_J_LegL_01"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left calve thickness
			{ ExtClass::CharacterStruct::SKELETON,47, TEXT("a01_J_LegR_01"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right calve thickness
			{ ExtClass::CharacterStruct::SKELETON,48, TEXT("a01_J_HandL_02"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left hand thickness
			{ ExtClass::CharacterStruct::SKELETON,49, TEXT("a01_J_HandR_02"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right hand thickness
			{ ExtClass::CharacterStruct::SKELETON,50, TEXT("a01_J_OyaL_01"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left hand thumb thickness
			{ ExtClass::CharacterStruct::SKELETON,51, TEXT("a01_J_OyaR_01"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right hand thumb thickness
			{ ExtClass::CharacterStruct::SKELETON,52, TEXT("a01_J_HandL_02"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left hand width
			{ ExtClass::CharacterStruct::SKELETON,53, TEXT("a01_J_HandR_02"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right hand width
			{ ExtClass::CharacterStruct::SKELETON,54, TEXT("a01_J_OyaL_01"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //left hand thumb width
			{ ExtClass::CharacterStruct::SKELETON,55, TEXT("a01_J_OyaR_01"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //right hand thumb width

			{ ExtClass::CharacterStruct::SKELETON,56, TEXT("a01_J_Spin_010"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //waist height
			{ ExtClass::CharacterStruct::SKELETON,57, TEXT("a01_J_Spin_020"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::DIVIDE, AAUCardData::MODIFY_FRAME }, //chest height
			{ ExtClass::CharacterStruct::SKELETON,58, TEXT("a01_J_Spin_020"),	{ 0,0,0, 0,0,0, 0,-0.11f,0 },	Slider::ADD, AAUCardData::MODIFY_FRAME }, //chest height

			{ ExtClass::CharacterStruct::SKELETON,59, TEXT("a01_J_Spin_010"),	{ 0,0,0, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //waist height
			{ ExtClass::CharacterStruct::SKELETON,60, TEXT("a01_J_Kosi_010"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::MULTIPLY, AAUCardData::MODIFY_FRAME }, //hip height
			{ ExtClass::CharacterStruct::SKELETON,61, TEXT("a01_J_Kosi_010"),	{ 0,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //hip height
			{ ExtClass::CharacterStruct::SKELETON,62, TEXT("a01_J_UplegL_010"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::DIVIDE, AAUCardData::MODIFY_FRAME }, //left thigh height
			{ ExtClass::CharacterStruct::SKELETON,63, TEXT("a01_J_UplegR_010"),	{ 0,1,0, 0,0,0, 0,0,0 },		Slider::DIVIDE, AAUCardData::MODIFY_FRAME }, //right thigh height

			{ ExtClass::CharacterStruct::SKELETON,99, TEXT("a01_J_Spin_020"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //chest width
			{ ExtClass::CharacterStruct::SKELETON,99, TEXT("a01_J_Spin_020"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //chest thickness
			{ ExtClass::CharacterStruct::SKELETON,99, TEXT("a01_J_Spin_010"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //waist width
			{ ExtClass::CharacterStruct::SKELETON,99, TEXT("a01_J_Spin_010"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //waist thickness
			{ ExtClass::CharacterStruct::SKELETON,99, TEXT("a01_J_Kosi_010"),	{ 1,0,0, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //hip width
			{ ExtClass::CharacterStruct::SKELETON,99, TEXT("a01_J_Kosi_010"),	{ 0,0,1, 0,0,0, 0,0,0 },		Slider::ADD, AAUCardData::MODIFY_FRAME }, //hip thickness
		},
		{
			//BODY
			{ ExtClass::CharacterStruct::BODY, 0, TEXT("a01_J_Kosi_010"),	{ 1,0,0, 0,0,0, 0,0,0 },					Slider::ADD, AAUCardData::MODIFY_BONE }, //kosi thickness
			{ ExtClass::CharacterStruct::BODY, 1, TEXT("a01_J_Kosi_010"),	{ 0,0,1, 0,0,0, 0,0,0 },					Slider::ADD, AAUCardData::MODIFY_BONE }, //kosi width
			{ ExtClass::CharacterStruct::BODY, 2, TEXT("a01_J_Neck_01"),	{ 1,0,1, 0,0,0, 0,0,0 },					Slider::ADD, AAUCardData::MODIFY_BONE },
			{ ExtClass::CharacterStruct::BODY, 3, TEXT("a01_J_Neck_02"),	{ 1,0,1, 0,0,0, 0,0,0 },					Slider::ADD, AAUCardData::MODIFY_BONE },
			{ ExtClass::CharacterStruct::BODY, 4, TEXT("a01_J_ArmL_01"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.264981031f },	Slider::ADD, AAUCardData::MODIFY_BONE }, //upper arm
			{ ExtClass::CharacterStruct::BODY, 5, TEXT("a01_J_UdeL_01"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.346239984f },	Slider::ADD, AAUCardData::MODIFY_BONE }, //lower arm
			{ ExtClass::CharacterStruct::BODY, 6, TEXT("a01_J_HijiL_01"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.346239984f },	Slider::ADD, AAUCardData::MODIFY_BONE }, //armgelenk
			{ ExtClass::CharacterStruct::BODY, 7, TEXT("a01_J_ArmR_01"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.264981031f },	Slider::ADD, AAUCardData::MODIFY_BONE },
			{ ExtClass::CharacterStruct::BODY, 8, TEXT("a01_J_UdeR_01"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.346239984f },	Slider::ADD, AAUCardData::MODIFY_BONE },
			{ ExtClass::CharacterStruct::BODY, 9, TEXT("a01_J_HijiR_01"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.346239984f },	Slider::ADD, AAUCardData::MODIFY_BONE },
			{ ExtClass::CharacterStruct::BODY,10, TEXT("a01_J_TekubiL_01"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.346239984f },	Slider::ADD, AAUCardData::MODIFY_BONE },
			{ ExtClass::CharacterStruct::BODY,11, TEXT("a01_J_TekubiR_01"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.346239984f },	Slider::ADD, AAUCardData::MODIFY_BONE },
			{ ExtClass::CharacterStruct::BODY,12, TEXT("a01_J_ArmL_02"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.264981031f },	Slider::ADD, AAUCardData::MODIFY_BONE },
			{ ExtClass::CharacterStruct::BODY,13, TEXT("a01_J_ArmR_02"),	{ 0,1,1, 0,0,0, 0,-15.795f,0.264981031f },	Slider::ADD, AAUCardData::MODIFY_BONE },
		},
		{
			//HAIR_FRONT
		},
		{
			//HAIR_SIDE
		},
		{
			//HAIR_BACK
		},
		{
			//HAIR_EXT
		},
		{
			//FACE_SLIDERS
		},
		{
			//SKIRT

		}
	};

#undef EXPR

}