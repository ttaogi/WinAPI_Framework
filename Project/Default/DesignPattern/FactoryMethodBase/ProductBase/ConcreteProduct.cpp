#include "Stdafx/stdafx.h"

#include "DesignPattern/FactoryMethodBase/ProductBase/ConcreteProduct.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "DesignPattern/ComponentBase/Component/Bar/Bar.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Collider/Collider.h"
#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedText/RenderedText.h"
#include "DesignPattern/ComponentBase/Component/Rigidbody/Rigidbody.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "Image/Animation/Animation.h"
#include "Image/Image.h"
#include "Script/Character/Player/Player.h"
#include "Script/Character/Enemy/Enemy.h"
#include "Script/DialogViewer/DialogViewer.h"
#include "Script/Effect/FlameBurst.h"
#include "Script/EquipChange/EquipChange.h"
#include "Script/HpBar/HpBar.h"
#include "Script/ShopList/ShopList.h"
#include "Script/Tile/Tile.h"

static int uiCount = 0;
static int characterCount = 0;
static int platformCount = 0;
static int tileCount = 0;
static int effectCount = 0;

#pragma region ProductBaseButton
GameObject* FactoryDefaultButton::CreateObject(
	std::function<void()> _callBack_v_CB_v, D_POINT _pos,
	int _rectWidth, int _rectHeight, Image* _image, std::wstring _str)
{
	GameObject* go = new GameObject();
	Button* btn = new Button(_str);
	RectTransform* rcT = new RectTransform();
	RenderedImage* rImg = new RenderedImage();

	btn->SetCallBack_v_CB_v(_callBack_v_CB_v);
	btn->Init();
	rcT->SetRect(_rectWidth, _rectHeight);
	rImg->SetImage(_image);
	rImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	rImg->SetOrderInLayer(uiCount++);

	go->GetComponent<Transform>()->SetPosition(_pos);

	go->AddComponent(btn);
	go->AddComponent(rcT);
	go->AddComponent(rImg);

	return go;
}

GameObject* FactoryButtonMouseOn::CreateObject(
	std::function<void()> _callBack_v_CB_v, D_POINT _pos,
	int _rectWidth, int _rectHeight, Image* _image, std::wstring _str)
{
	GameObject* go = new GameObject();
	Button* btn = new ButtonMouseOn(_str);
	RectTransform* rcT = new RectTransform();
	RenderedImage* rImg = new RenderedImage();

	btn->SetCallBack_v_CB_v(_callBack_v_CB_v);
	btn->Init();
	rcT->SetRect(_rectWidth, _rectHeight);
	rImg->SetImage(_image);
	rImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	rImg->SetOrderInLayer(uiCount++);
	rImg->SetEnabled(false);

	go->GetComponent<Transform>()->SetPosition(_pos);

	go->AddComponent(btn);
	go->AddComponent(rcT);
	go->AddComponent(rImg);

	return go;
}
#pragma endregion ProductBaseButton


#pragma region ProductBasePlayer
/*
AL
-RectTransform
-RenderedAnimator
-Player
*/
GameObject* FactoryPlayerAl::CreateObject(Observer* _observer, D_POINT _pos, POINT _gridPos)
{
	GameObject* go = new GameObject();
	D_POINT pos{ (double)GridPosToPos(_gridPos).x, (double)GridPosToPos(_gridPos).y };
	go->GetComponent<Transform>()->SetPosition(pos);
	//go->GetComponent<Transform>()->SetPosition(_pos);

	RectTransform* rcT = new RectTransform();
	rcT->SetRect(TILE_WIDTH / 2, TILE_HEIGHT_Z0 / 2);

	RenderedAnimator* rAnim = new RenderedAnimator();
	rAnim->SetSortingLayer(SORTING_LAYER::CHARACTER);
	rAnim->SetOrderInLayer(characterCount++);
	rAnim->SetByCamera(true);
	rAnim->Init();

	Animation* idleLeftBottom = new Animation();
	idleLeftBottom->Init(
		KEY_AL_IDLE_LEFT_BOTTOM,
		POINT{ -28, -60 }, CHARACTER_STATE::IDLE_LEFT_BOTTOM,
		true, false, 6
	);
	Animation* idleLeftTop = new Animation();
	idleLeftTop->Init(
		KEY_AL_IDLE_LEFT_TOP,
		POINT{ -28, -60 }, CHARACTER_STATE::IDLE_LEFT_TOP,
		true, false, 6
	);
	Animation* idleRightBottom = new Animation();
	idleRightBottom->Init(
		KEY_AL_IDLE_RIGHT_BOTTOM,
		POINT{ -28, -60 }, CHARACTER_STATE::IDLE_RIGHT_BOTTOM,
		true, false, 6
	);
	Animation* idleRightTop = new Animation();
	idleRightTop->Init(
		KEY_AL_IDLE_RIGHT_TOP,
		POINT{ -28, -60 }, CHARACTER_STATE::IDLE_RIGHT_TOP,
		true, false, 6
	);

	Animation* moveLeftBottom = new Animation();
	moveLeftBottom->Init(
		KEY_AL_MOVE_LEFT_BOTTOM,
		POINT{ -22, -64 }, CHARACTER_STATE::MOVE_LEFT_BOTTOM,
		true, false, 6
	);
	Animation* moveLeftTop = new Animation();
	moveLeftTop->Init(
		KEY_AL_MOVE_LEFT_TOP,
		POINT{ -22, -64 }, CHARACTER_STATE::MOVE_LEFT_TOP,
		true, false, 6
	);
	Animation* moveRightBottom = new Animation();
	moveRightBottom->Init(
		KEY_AL_MOVE_RIGHT_BOTTOM,
		POINT{ -22, -64 }, CHARACTER_STATE::MOVE_RIGHT_BOTTOM,
		true, false, 6
	);
	Animation* moveRightTop = new Animation();
	moveRightTop->Init(
		KEY_AL_MOVE_RIGHT_TOP,
		POINT{ -22, -64 }, CHARACTER_STATE::MOVE_RIGHT_TOP,
		true, false, 6
	);

	Animation* attackLeftBottom = new Animation();
	attackLeftBottom->Init(
		KEY_AL_ATTACK_LEFT_BOTTOM,
		POINT{ -48, -70 }, CHARACTER_STATE::ATTACK_LEFT_BOTTOM,
		false, false, 6
	);
	Animation* attackLeftTop = new Animation();
	attackLeftTop->Init(
		KEY_AL_ATTACK_LEFT_TOP,
		POINT{ -40, -66 }, CHARACTER_STATE::ATTACK_LEFT_TOP,
		false, false, 6
	);
	Animation* attackRightBottom = new Animation();
	attackRightBottom->Init(
		KEY_AL_ATTACK_RIGHT_BOTTOM,
		POINT{ -32, -70 }, CHARACTER_STATE::ATTACK_RIGHT_BOTTOM,
		false, false, 6
	);
	Animation* attackRightTop = new Animation();
	attackRightTop->Init(
		KEY_AL_ATTACK_RIGHT_TOP,
		POINT{ -40, -66 }, CHARACTER_STATE::ATTACK_RIGHT_TOP,
		false, false, 6
	);

	rAnim->AddAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM, idleLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::IDLE_LEFT_TOP, idleLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM, idleRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP, idleRightTop);

	rAnim->AddAnimation(CHARACTER_STATE::MOVE_LEFT_BOTTOM, moveLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_LEFT_TOP, moveLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_RIGHT_BOTTOM, moveRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_RIGHT_TOP, moveRightTop);

	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_LEFT_BOTTOM, attackLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_LEFT_TOP, attackLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_RIGHT_BOTTOM, attackRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_RIGHT_TOP, attackRightTop);

	rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);

	Player* player = new Player();
	CharacterInfo cInfo = GAMEDATA->GetCharacterInfo(CHARACTER_ID::AL);
	EquipInfo weapon = GAMEDATA->GetEquipInfo(cInfo.weapon);
	EquipInfo armor = GAMEDATA->GetEquipInfo(cInfo.armor);
	player->SetAbility(
		cInfo.hp,
		cInfo.hpMax,
		cInfo.str + weapon.str + armor.str,
		cInfo.mgc + weapon.mgc + armor.mgc,
		cInfo.def + weapon.def + armor.def,
		cInfo.mDef + weapon.mDef + armor.mDef,
		cInfo.dex
	);
	player->AddObserver(_observer);
	player->SetGridPos(_gridPos);
	player->SetId(CHARACTER_ID::AL);
	player->Init();

	go->AddComponent(rcT);
	go->AddComponent(rAnim);
	go->AddComponent(player);
	go->SetTag(TAG::PLAYER);

	return go;
}

GameObject* FactoryPlayerKarin::CreateObject(Observer* _observer, D_POINT _pos, POINT _gridPos)
{
	GameObject* go = new GameObject();
	D_POINT pos{ (double)GridPosToPos(_gridPos).x, (double)GridPosToPos(_gridPos).y };
	go->GetComponent<Transform>()->SetPosition(pos);
	//go->GetComponent<Transform>()->SetPosition(_pos);

	RectTransform* rcT = new RectTransform();
	rcT->SetRect(TILE_WIDTH / 2, TILE_HEIGHT_Z0 / 2);

	RenderedAnimator* rAnim = new RenderedAnimator();
	rAnim->SetSortingLayer(SORTING_LAYER::CHARACTER);
	rAnim->SetOrderInLayer(characterCount++);
	rAnim->SetByCamera(true);
	rAnim->Init();

	Animation* idleLeftBottom = new Animation();
	idleLeftBottom->Init(
		KEY_KARIN_IDLE_LEFT_BOTTOM,
		POINT{ -36, -64 }, CHARACTER_STATE::IDLE_LEFT_BOTTOM,
		true, false, 6
	);
	Animation* idleLeftTop = new Animation();
	idleLeftTop->Init(
		KEY_KARIN_IDLE_LEFT_TOP,
		POINT{ -36, -64 }, CHARACTER_STATE::IDLE_LEFT_TOP,
		true, false, 6
	);
	Animation* idleRightBottom = new Animation();
	idleRightBottom->Init(
		KEY_KARIN_IDLE_RIGHT_BOTTOM,
		POINT{ -36, -64 }, CHARACTER_STATE::IDLE_RIGHT_BOTTOM,
		true, false, 6
	);
	Animation* idleRightTop = new Animation();
	idleRightTop->Init(
		KEY_KARIN_IDLE_RIGHT_TOP,
		POINT{ -36, -64 }, CHARACTER_STATE::IDLE_RIGHT_TOP,
		true, false, 6
	);

	Animation* moveLeftBottom = new Animation();
	moveLeftBottom->Init(
		KEY_KARIN_MOVE_LEFT_BOTTOM,
		POINT{ -36, -64 }, CHARACTER_STATE::MOVE_LEFT_BOTTOM,
		true, false, 6
	);
	Animation* moveLeftTop = new Animation();
	moveLeftTop->Init(
		KEY_KARIN_MOVE_LEFT_TOP,
		POINT{ -36, -64 }, CHARACTER_STATE::MOVE_LEFT_TOP,
		true, false, 6
	);
	Animation* moveRightBottom = new Animation();
	moveRightBottom->Init(
		KEY_KARIN_MOVE_RIGHT_BOTTOM,
		POINT{ -36, -64 }, CHARACTER_STATE::MOVE_RIGHT_BOTTOM,
		true, false, 6
	);
	Animation* moveRightTop = new Animation();
	moveRightTop->Init(
		KEY_KARIN_MOVE_RIGHT_TOP,
		POINT{ -36, -64 }, CHARACTER_STATE::MOVE_RIGHT_TOP,
		true, false, 6
	);

	Animation* attackLeftBottom = new Animation();
	attackLeftBottom->Init(
		KEY_KARIN_ATTACK_LEFT_BOTTOM,
		POINT{ -34, -90 }, CHARACTER_STATE::ATTACK_LEFT_BOTTOM,
		false, false, 6
	);
	Animation* attackLeftTop = new Animation();
	attackLeftTop->Init(
		KEY_KARIN_ATTACK_LEFT_TOP,
		POINT{ -34, -90 }, CHARACTER_STATE::ATTACK_LEFT_TOP,
		false, false, 6
	);
	Animation* attackRightBottom = new Animation();
	attackRightBottom->Init(
		KEY_KARIN_ATTACK_RIGHT_BOTTOM,
		POINT{ -34, -90 }, CHARACTER_STATE::ATTACK_RIGHT_BOTTOM,
		false, false, 6
	);
	Animation* attackRightTop = new Animation();
	attackRightTop->Init(
		KEY_KARIN_ATTACK_RIGHT_TOP,
		POINT{ -34, -90 }, CHARACTER_STATE::ATTACK_RIGHT_TOP,
		false, false, 6
	);

	rAnim->AddAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM, idleLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::IDLE_LEFT_TOP, idleLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM, idleRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP, idleRightTop);

	rAnim->AddAnimation(CHARACTER_STATE::MOVE_LEFT_BOTTOM, moveLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_LEFT_TOP, moveLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_RIGHT_BOTTOM, moveRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_RIGHT_TOP, moveRightTop);

	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_LEFT_BOTTOM, attackLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_LEFT_TOP, attackLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_RIGHT_BOTTOM, attackRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_RIGHT_TOP, attackRightTop);

	rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);

	Player* player = new Player();
	CharacterInfo cInfo = GAMEDATA->GetCharacterInfo(CHARACTER_ID::KARIN);
	EquipInfo weapon = GAMEDATA->GetEquipInfo(cInfo.weapon);
	EquipInfo armor = GAMEDATA->GetEquipInfo(cInfo.armor);
	player->SetAbility(
		cInfo.hp,
		cInfo.hpMax,
		cInfo.str + weapon.str + armor.str,
		cInfo.mgc + weapon.mgc + armor.mgc,
		cInfo.def + weapon.def + armor.def,
		cInfo.mDef + weapon.mDef + armor.mDef,
		cInfo.dex
	);
	player->AddObserver(_observer);
	player->SetGridPos(_gridPos);
	player->SetId(CHARACTER_ID::KARIN);
	player->Init();

	go->AddComponent(rcT);
	go->AddComponent(rAnim);
	go->AddComponent(player);
	go->SetTag(TAG::PLAYER);

	return go;
}
#pragma endregion ProductBasePlayer


#pragma region ProductBaseEnemy
/*
Slime
-RectTransform
-RenderedAnimator
-Enemy
*/
GameObject* FactoryEnemySlime::CreateObject(Observer* _observer, D_POINT _pos, POINT _gridPos)
{
	GameObject* go = new GameObject();
	D_POINT pos{ (double)GridPosToPos(_gridPos).x, (double)GridPosToPos(_gridPos).y };
	go->GetComponent<Transform>()->SetPosition(pos);

	RectTransform* rcT = new RectTransform();
	rcT->SetRect(TILE_WIDTH / 2, TILE_HEIGHT_Z0 / 2);

	RenderedAnimator* rAnim = new RenderedAnimator();
	rAnim->SetSortingLayer(SORTING_LAYER::CHARACTER);
	rAnim->SetOrderInLayer(characterCount++);
	rAnim->SetByCamera(true);
	rAnim->Init();

	Animation* idleLeftBottom = new Animation();
	idleLeftBottom->Init(
		KEY_SLIME_IDLE,
		POINT{ -21, -38 }, CHARACTER_STATE::IDLE_LEFT_BOTTOM,
		true, false, 6
	);
	Animation* idleLeftTop = new Animation();
	idleLeftTop->Init(
		KEY_SLIME_IDLE,
		POINT{ -21, -38 }, CHARACTER_STATE::IDLE_LEFT_TOP,
		true, false, 6
	);
	Animation* idleRightBottom = new Animation();
	idleRightBottom->Init(
		KEY_SLIME_IDLE,
		POINT{ -21, -38 }, CHARACTER_STATE::IDLE_RIGHT_BOTTOM,
		true, false, 6
	);
	Animation* idleRightTop = new Animation();
	idleRightTop->Init(
		KEY_SLIME_IDLE,
		POINT{ -21, -38 }, CHARACTER_STATE::IDLE_RIGHT_TOP,
		true, false, 6
	);

	Animation* moveLeftBottom = new Animation();
	moveLeftBottom->Init(
		KEY_SLIME_MOVE,
		POINT{ -21, -38 }, CHARACTER_STATE::MOVE_LEFT_BOTTOM,
		true, false, 6
	);
	Animation* moveLeftTop = new Animation();
	moveLeftTop->Init(
		KEY_SLIME_MOVE,
		POINT{ -21, -38 }, CHARACTER_STATE::MOVE_LEFT_TOP,
		true, false, 6
	);
	Animation* moveRightBottom = new Animation();
	moveRightBottom->Init(
		KEY_SLIME_MOVE,
		POINT{ -21, -38 }, CHARACTER_STATE::MOVE_RIGHT_BOTTOM,
		true, false, 6
	);
	Animation* moveRightTop = new Animation();
	moveRightTop->Init(
		KEY_SLIME_MOVE,
		POINT{ -21, -38 }, CHARACTER_STATE::MOVE_RIGHT_TOP,
		true, false, 6
	);

	Animation* attackLeftBottom = new Animation();
	attackLeftBottom->Init(
		KEY_SLIME_ATTACK_LEFT_BOTTOM,
		POINT{ -80, -56 }, CHARACTER_STATE::ATTACK_LEFT_BOTTOM,
		false, false, 12
	);
	Animation* attackLeftTop = new Animation();
	attackLeftTop->Init(
		KEY_SLIME_ATTACK_LEFT_TOP,
		POINT{ -94, -84 }, CHARACTER_STATE::ATTACK_LEFT_TOP,
		false, false, 12
	);
	Animation* attackRightBottom = new Animation();
	attackRightBottom->Init(
		KEY_SLIME_ATTACK_RIGHT_BOTTOM,
		POINT{ -24, -56 }, CHARACTER_STATE::ATTACK_RIGHT_BOTTOM,
		false, false, 12
	);
	Animation* attackRightTop = new Animation();
	attackRightTop->Init(
		KEY_SLIME_ATTACK_RIGHT_TOP,
		POINT{ -16, -84 }, CHARACTER_STATE::ATTACK_RIGHT_TOP,
		false, false, 12
	);

	Animation* attackedLeftBottom = new Animation();
	attackedLeftBottom->Init(
		KEY_SLIME_ATTACKED_LEFT,
		POINT{ -20, -44 }, CHARACTER_STATE::ATTACKED_LEFT_BOTTOM,
		false, false, 8
	);
	Animation* attackedLeftTop = new Animation();
	attackedLeftTop->Init(
		KEY_SLIME_ATTACKED_LEFT,
		POINT{ -20, -44 }, CHARACTER_STATE::ATTACKED_LEFT_TOP,
		false, false, 8
	);
	Animation* attackedRightBottom = new Animation();
	attackedRightBottom->Init(
		KEY_SLIME_ATTACKED_RIGHT,
		POINT{-20, -44 }, CHARACTER_STATE::ATTACKED_RIGHT_BOTTOM,
		false, false, 8
	);
	Animation* attackedRightTop = new Animation();
	attackedRightTop->Init(
		KEY_SLIME_ATTACKED_RIGHT,
		POINT{ -20, -44 }, CHARACTER_STATE::ATTACKED_RIGHT_TOP,
		false, false, 8
	);

	rAnim->AddAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM, idleLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::IDLE_LEFT_TOP, idleLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::IDLE_RIGHT_BOTTOM, idleRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::IDLE_RIGHT_TOP, idleRightTop);

	rAnim->AddAnimation(CHARACTER_STATE::MOVE_LEFT_BOTTOM, moveLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_LEFT_TOP, moveLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_RIGHT_BOTTOM, moveRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_RIGHT_TOP, moveRightTop);

	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_LEFT_BOTTOM, attackLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_LEFT_TOP, attackLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_RIGHT_BOTTOM, attackRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACK_RIGHT_TOP, attackRightTop);

	rAnim->AddAnimation(CHARACTER_STATE::ATTACKED_LEFT_BOTTOM, attackedLeftBottom);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACKED_LEFT_TOP, attackedLeftTop);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACKED_RIGHT_BOTTOM, attackedRightBottom);
	rAnim->AddAnimation(CHARACTER_STATE::ATTACKED_RIGHT_TOP, attackedRightTop);

	rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);

	Enemy* enemy = new Enemy();
	enemy->SetAbility(
		20, 20,
		7, 0, 0, 0, 0
	);
	enemy->AddObserver(_observer);
	enemy->SetGridPos(_gridPos);
	enemy->Init();

	go->AddComponent(rcT);
	go->AddComponent(rAnim);
	go->AddComponent(enemy);
	go->SetTag(TAG::ENEMY);

	return go;
}
#pragma endregion ProductBaseEnemy


#pragma region ProductBaseDialogViewer
GameObject* FactoryDefaultDialogViewer::CreateObject(Observer* _observer, std::wstring _spot, int _processivity)
{
	GameObject* go = new GameObject();
	
	GameObject* upper = new GameObject();
	upper->GetComponent<Transform>()->SetPosition(D_POINT{320, 80});
	RectTransform* upperRcT = new RectTransform();
	upperRcT->SetRect(640, 160);
	RenderedImage* upperBackground = new RenderedImage();
	upperBackground->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	upperBackground->SetImage(IMG->FindImage(KEY_UI_DIALOG_BACKGROUND_SPRITE));
	upperBackground->SetSortingLayer(SORTING_LAYER::DIALOG_BACKGROUND);
	upperBackground->SetOrderInLayer(uiCount++);
	upper->AddComponent(upperRcT);
	upper->AddComponent(upperBackground);

	GameObject* upperPortrait = new GameObject();
	upperPortrait->GetComponent<Transform>()->SetPosition(D_POINT{ 120, 96 });
	RectTransform* uPortraitRcT = new RectTransform();
	uPortraitRcT->SetRect(240, 192);
	RenderedImage* uPortraitRImg = new RenderedImage();
	uPortraitRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	uPortraitRImg->SetImage(NULL);
	uPortraitRImg->SetSortingLayer(SORTING_LAYER::DIALOG_PORTRAIT);
	uPortraitRImg->SetOrderInLayer(uiCount++);
	upperPortrait->AddComponent(uPortraitRcT);
	upperPortrait->AddComponent(uPortraitRImg);
	upperPortrait->SetName(SKIG_DIALOG_VIEWER_PORTRAIT);

	GameObject* upperText = new GameObject();
	upperText->GetComponent<Transform>()->SetPosition(D_POINT{ 430, 80 });
	RectTransform* uTextRcT = new RectTransform();
	uTextRcT->SetRect(380, 110);
	RenderedText* uRText = new RenderedText();
	uRText->SetSortingLayer(SORTING_LAYER::DIALOG_TEXT);
	uRText->SetOrderInLayer(uiCount++);
	upperText->AddComponent(uTextRcT);
	upperText->AddComponent(uRText);
	upperText->SetName(SKIG_DIALOG_VIEWER_TEXT);

	upper->AddGameObject(upperPortrait);
	upper->AddGameObject(upperText);

	GameObject* lower = new GameObject();
	lower->GetComponent<Transform>()->SetPosition(D_POINT{ 320, 400 });
	RectTransform* lowerRcT = new RectTransform();
	lowerRcT->SetRect(640, 160);
	RenderedImage* lowerBackground = new RenderedImage();
	lowerBackground->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	lowerBackground->SetImage(IMG->FindImage(KEY_UI_DIALOG_BACKGROUND_SPRITE));
	lowerBackground->SetSortingLayer(SORTING_LAYER::DIALOG_BACKGROUND);
	lowerBackground->SetOrderInLayer(uiCount++);
	lower->AddComponent(lowerRcT);
	lower->AddComponent(lowerBackground);

	GameObject* lowerPortrait = new GameObject();
	lowerPortrait->GetComponent<Transform>()->SetPosition(D_POINT{ 520, 384 });
	RectTransform* lPortraitRcT = new RectTransform();
	lPortraitRcT->SetRect(240, 192);
	RenderedImage* lPortraitRImg = new RenderedImage();
	lPortraitRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	lPortraitRImg->SetImage(NULL);
	lPortraitRImg->SetSortingLayer(SORTING_LAYER::DIALOG_PORTRAIT);
	lPortraitRImg->SetOrderInLayer(uiCount++);
	lowerPortrait->AddComponent(lPortraitRcT);
	lowerPortrait->AddComponent(lPortraitRImg);
	lowerPortrait->SetName(SKIG_DIALOG_VIEWER_PORTRAIT);

	GameObject* lowerText = new GameObject();
	lowerText->GetComponent<Transform>()->SetPosition(D_POINT{ 210, 400 });
	RectTransform* lTextRcT = new RectTransform();
	lTextRcT->SetRect(380, 110);
	RenderedText* lRText = new RenderedText();
	lRText->SetSortingLayer(SORTING_LAYER::DIALOG_TEXT);
	lRText->SetOrderInLayer(uiCount++);
	lowerText->AddComponent(lTextRcT);
	lowerText->AddComponent(lRText);
	lowerText->SetName(SKIG_DIALOG_VIEWER_TEXT);

	lower->AddGameObject(lowerPortrait);
	lower->AddGameObject(lowerText);

	go->GetComponent<Transform>()->SetPosition(D_POINT{ 0, 0 });
	DialogViewer* dv = new DialogViewer();
	dv->SetUpper(upper);
	dv->SetLower(lower);
	dv->SetCycle(DIALOG->GetDialogCycle(_spot, _processivity));
	dv->AddObserver(_observer);
	dv->Init();
	go->AddComponent(dv);

	go->AddGameObject(upper);
	go->AddGameObject(lower);
	go->SetName(SKIG_DIALOG_VIEWER);

	return go;
}
#pragma endregion ProductBaseDialogViewer


#pragma region ProductBaseShopList
/*
GO(420, 378)
-ShopList
-RectTransform
-RenderedImage(background)

	Panel*n
	-ShopListPanel
	-RectTransform
	-RenderedImage(416, 25)
		ItemName
		-RectTransform
		-RenderedText
		ItemPrice
		-RectTransform
		-RenderedText

	Description(width : 230, height : 90, from top : 285)
	-RectTransform
	-RenderedText

	Gold(60, 20 // 340, 280)
	-RectTransform
	-RenderedText

	BuyButton
	-*Button
	-RectTransform(112, 21)
	-RenderedImage

	ExitButton
	-*Button
	-RectTransform(112, 21)
	-RenderedImage

	ToEquipChangeButton
	-*Button
	-RectTransform(112, 21)
	-ReneredImage
*/
GameObject* FactoryDefaultShopList::CreateObject(Observer* _observer)
{
	GameObject* go = new GameObject();
	go->GetComponent<Transform>()->SetPosition(D_POINT{(double)(WINSIZE_X / 2), (double)(WINSIZE_Y / 2)});
	RectTransform* goRcT = new RectTransform();
	goRcT->SetRect(420, 378);
	RenderedImage* goRImg = new RenderedImage();
	goRImg->SetImage(IMG->FindImage(KEY_UI_SHOPLIST_BACKGROUND_SPRITE));
	goRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	goRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	goRImg->SetOrderInLayer(uiCount++);
	ShopList* shop = new ShopList();
	shop->AddObserver(_observer);
	shop->SetSelectedItem(GAMEDATA->GetEquipInfo(EQUIP_ID::LONGSWORD)); // LONGSWORD : 1
	shop->Init();
	go->AddComponent(goRcT);
	go->AddComponent(goRImg);
	go->AddComponent(shop);
	go->SetName(SKIG_SHOP_LIST);

	/*
	Panel*n (width : 416, height : 25px)
	-ShopListPanel
	-RectTransform
	-RenderedImage
		ItemName
		-RectTransform
		-RenderedText
		ItemPrice
		-RectTransform
		-RenderedText
	*/
	for (int i = 1; i < (int)EQUIP_ID::EQUIP_ID_NUM; ++i)
	{
		double y = 51 + 47 + 13 + i * 25;
		GameObject* panelGo = new GameObject();
		panelGo->GetComponent<Transform>()->SetPosition(D_POINT{ (double)(WINSIZE_X / 2) + 1, y });
		RectTransform* panelRcT = new RectTransform();
		panelRcT->SetRect(412, 25);
		RenderedImage* panelRImg = new RenderedImage();
		panelRImg->SetImage(IMG->FindImage(KEY_UI_SHOPLIST_PANEL_BACKGROUND_SPRITE));
		panelRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
		panelRImg->SetOrderInLayer(uiCount++);
		panelRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
		if(i != 1) panelRImg->SetEnabled(false);
		ShopListPanel* panel = new ShopListPanel();
		panel->AddObserver(shop);
		panel->SetEquip(GAMEDATA->GetEquipInfo((EQUIP_ID)i));
		panel->Init();
		panelGo->AddComponent(panelRcT);
		panelGo->AddComponent(panelRImg);
		panelGo->AddComponent(panel);
		panelGo->SetTag(TAG::SHOP_PANEL);

		GameObject* nameGo = new GameObject();
		nameGo->GetComponent<Transform>()->SetPosition(D_POINT{ (double)(110 + 25 + 50), y });
		RectTransform* nameRcT = new RectTransform();
		nameRcT->SetRect(100, 25);
		RenderedText* nameRText = new RenderedText();
		nameRText->SetSortingLayer(SORTING_LAYER::UI_TEXT);
		nameRText->SetOrderInLayer(uiCount++);
		nameRText->SetStr(GAMEDATA->GetEquipInfo(EQUIP_ID(i)).name);
		nameGo->AddComponent(nameRcT);
		nameGo->AddComponent(nameRText);

		GameObject* priceGo = new GameObject();
		priceGo->GetComponent<Transform>()->SetPosition(D_POINT{ (double)(110 + 220 + 50), y });
		RectTransform* priceRcT = new RectTransform();
		priceRcT->SetRect(100, 25);
		RenderedText* priceRTect = new RenderedText();
		priceRTect->SetSortingLayer(SORTING_LAYER::UI_TEXT);
		priceRTect->SetOrderInLayer(uiCount++);
		priceRTect->SetStr(to_wstring(GAMEDATA->GetEquipInfo(EQUIP_ID(i)).priceBuy));
		priceGo->AddComponent(priceRcT);
		priceGo->AddComponent(priceRTect);

		panelGo->AddGameObject(nameGo);
		panelGo->AddGameObject(priceGo);

		go->AddGameObject(panelGo);
	}

	// description.(width : 230, height : 90, from top : 285)
	GameObject* descriptionGo = new GameObject();
	descriptionGo->GetComponent<Transform>()->SetPosition(D_POINT{ 110 + 25 + 115, 51 + 285 + 45 });
	RectTransform* descriptionRcT = new RectTransform();
	descriptionRcT->SetRect(230, 90);
	RenderedText* descriptionRText = new RenderedText();
	descriptionRText->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	descriptionRText->SetOrderInLayer(uiCount++);
	descriptionRText->SetStr(L"-");
	descriptionGo->AddComponent(descriptionRcT);
	descriptionGo->AddComponent(descriptionRText);
	descriptionGo->SetName(SKIG_SHOP_LIST_DESCRIPTION);

	/*
	Gold(60, 20 // 340, 280)
		- RectTransform
		- RenderedText
	*/
	GameObject* goldGo = new GameObject();
	goldGo->GetComponent<Transform>()->SetPosition(D_POINT{ 110 + 340 + 30, 51 + 280 + 10 });
	RectTransform* goldRcT = new RectTransform();
	goldRcT->SetRect(60, 20);
	RenderedText* goldRText = new RenderedText();
	goldRText->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	goldRText->SetOrderInLayer(uiCount++);
	goldRText->SetStr(to_wstring(GAMEDATA->GetGold()));
	goldGo->AddComponent(goldRcT);
	goldGo->AddComponent(goldRText);
	goldGo->SetName(SKIG_SHOP_LIST_GOLD);

	/*
	BuyButton
	-Button
	-RectTransform(112, 21) - 355, 315
	-RenderedImage
	*/
	GameObject* buyButtonGo = new GameObject();
	buyButtonGo->GetComponent<Transform>()->SetPosition(D_POINT{ 110 + 355, 51 + 315 - 1 });
	RectTransform* buyButtonRcT = new RectTransform();
	buyButtonRcT->SetRect(112, 21);
	RenderedImage* buyButtonRImg = new RenderedImage();
	buyButtonRImg->SetImage(IMG->FindImage(KEY_UI_SHOPLIST_BUY_BUTTON_SPRITE));
	buyButtonRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	buyButtonRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	buyButtonRImg->SetOrderInLayer(uiCount++);
	BuyButton* buyButton = new BuyButton();
	buyButton->AddObserver(shop);
	buyButton->Init();
	buyButtonGo->AddComponent(buyButtonRcT);
	buyButtonGo->AddComponent(buyButtonRImg);
	buyButtonGo->AddComponent(buyButton);

	/*
	ExitButton
	-Button
	-RectTransform(112, 21) - 355, 365
	-RenderedImage
	*/
	GameObject* exitButtonGo = new GameObject();
	exitButtonGo->GetComponent<Transform>()->SetPosition(D_POINT{ 110 + 355, 51 + 365 - 3 });
	RectTransform* exitButtonRcT = new RectTransform();
	exitButtonRcT->SetRect(112, 21);
	RenderedImage* exitButtonRImg = new RenderedImage();
	exitButtonRImg->SetImage(IMG->FindImage(KEY_UI_SHOPLIST_EXIT_BUTTON_SPRITE));
	exitButtonRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	exitButtonRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	exitButtonRImg->SetOrderInLayer(uiCount++);
	ExitButton* exitButton = new ExitButton();
	exitButton->AddObserver(shop);
	exitButton->Init();
	exitButtonGo->AddComponent(exitButtonRcT);
	exitButtonGo->AddComponent(exitButtonRImg);
	exitButtonGo->AddComponent(exitButton);

	/*
	ToEquipChangeButton
	-*Button
	-RectTransform(112, 21)
	-ReneredImage
	*/
	GameObject* toEquipChangeButtonGo = new GameObject();
	toEquipChangeButtonGo->GetComponent<Transform>()->SetPosition(D_POINT{ 110 + 355, 51 + 340 - 2 });
	RectTransform* toEquipChangeButtonRcT = new RectTransform();
	toEquipChangeButtonRcT->SetRect(112, 21);
	RenderedImage* toEquipChangeButtonRImg = new RenderedImage();
	toEquipChangeButtonRImg->SetImage(IMG->FindImage(KEY_UI_TO_EQUIP_CHANGE_BUTTON_SPRITE));
	toEquipChangeButtonRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	toEquipChangeButtonRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	toEquipChangeButtonRImg->SetOrderInLayer(uiCount++);
	ToEquipChangeButton* toEquipChangeButton = new ToEquipChangeButton();
	toEquipChangeButton->AddObserver(shop);
	toEquipChangeButton->Init();
	toEquipChangeButtonGo->AddComponent(toEquipChangeButtonRcT);
	toEquipChangeButtonGo->AddComponent(toEquipChangeButtonRImg);
	toEquipChangeButtonGo->AddComponent(toEquipChangeButton);

	go->AddGameObject(descriptionGo);
	go->AddGameObject(goldGo);
	go->AddGameObject(buyButtonGo);
	go->AddGameObject(exitButtonGo);
	go->AddGameObject(toEquipChangeButtonGo);

	return go;
}
#pragma endregion ProductBaseShopList


#pragma region ProductBaseEquipChange
/* 17, 21
GO (605, 438)
-RectTransform
-RenderedImage(background)
-EquipChange

	CharacterPanel*n (120, 88)
	-RectTransform
	-RenderedImage
	-ECCharacterPanel

	AbilityTabPanel // 313, 32 - (60, 24)
	-RectTransform
	-ECAbilityTabPanel

	EquipTabPanel (60, 24)
	-RectTransform
	-ECEquipTabPanel

	AbilityPanel
	-ECAbilityPanel
		CharacterPortrait // 330, 59 - (240, 176)
		-RectTransform
		-RenderedImage
		CharacterLevel // 319, 239 - (246, 23)
		-RectTransform
		-RenderedText
		CharacterAbilityType // 319, 265 - (50, 130)
		-RectTransform
		-RenderedText
		CharacterAbility*Figure // 369, * - (60, 18) * n
		-RectTransform
		-RenderedText

	EquipPanel
		WeaponText // 320, 58 - (240, 24)
		-RectTransform
		-RenderedText
		-ECWeaponText
		ArmorText
		-RectTransform
		-RenderedText
		-ECArmorText
		EquipInInvenPanel*n // 319, 265 - (174, 24)
		-RectTransform
		-RenderedText
		-ECEquipInInvenPanel

	ToShopListButton // 471, 405 - (99, 28)
	-RectTransform
	-ToShopListButton

	EquipChangeButton // 345, 405 - (99, 28)
	-RectTransform
	-EquipChangeButton
*/
GameObject* FactoryDefaultEquipChange::CreateObject(Observer* _observer)
{
	GameObject* go = new GameObject();
	go->GetComponent<Transform>()->SetPosition(D_POINT{ (double)(WINSIZE_X / 2), (double)(WINSIZE_Y / 2) });
	RectTransform* goRcT = new RectTransform();
	goRcT->SetRect(605, 438);
	RenderedImage* goRImg = new RenderedImage();
	goRImg->SetImage(IMG->FindImage(KEY_UI_EQUIP_CHANGE_BACKGROUND_SPRITE));
	goRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	goRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	goRImg->SetOrderInLayer(uiCount++);
	EquipChange* goEquipChange = new EquipChange();
	goEquipChange->AddObserver(_observer);
	go->AddComponent(goRcT);
	go->AddComponent(goRImg);
	go->AddComponent(goEquipChange);
	go->SetName(SKIG_EQUIP_CHANGE);


	GameObject* cpAlGo = new GameObject(); // cp = character panel.
	cpAlGo->GetComponent<Transform>()->SetPosition(D_POINT{ 90, 100 });
	RectTransform* cpAlGoRcT = new RectTransform();
	cpAlGoRcT->SetRect(120, 88);
	RenderedImage* cpAlGoRImg = new RenderedImage();
	cpAlGoRImg->SetImage(IMG->FindImage(KEY_UI_EQUIP_CHANGE_PORTRAIT_AL_SPRITE));
	cpAlGoRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	cpAlGoRImg->SetSortingLayer(SORTING_LAYER::UI_IMAGE);
	cpAlGoRImg->SetOrderInLayer(uiCount++);
	ECCharacterPanel* cpAlGoECCP = new ECCharacterPanel();
	cpAlGoECCP->AddObserver(goEquipChange);
	cpAlGoECCP->Init(CHARACTER_ID::AL);
	cpAlGo->AddComponent(cpAlGoRcT);
	cpAlGo->AddComponent(cpAlGoRImg);
	cpAlGo->AddComponent(cpAlGoECCP);

	GameObject* cpKarinGo = new GameObject();
	cpKarinGo->GetComponent<Transform>()->SetPosition(D_POINT{ 90, 200 });
	RectTransform* cpKarinGoRcT = new RectTransform();
	cpKarinGoRcT->SetRect(120, 88);
	RenderedImage* cpKarinGoRImg = new RenderedImage();
	cpKarinGoRImg->SetImage(IMG->FindImage(KEY_UI_EQUIP_CHANGE_PORTRAIT_KARIN_SPRITE));
	cpKarinGoRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	cpKarinGoRImg->SetSortingLayer(SORTING_LAYER::UI_IMAGE);
	cpKarinGoRImg->SetOrderInLayer(uiCount++);
	ECCharacterPanel* cpKarinGoECCP = new ECCharacterPanel();
	cpKarinGoECCP->AddObserver(goEquipChange);
	cpKarinGoECCP->Init(CHARACTER_ID::KARIN);
	cpKarinGo->AddComponent(cpKarinGoRcT);
	cpKarinGo->AddComponent(cpKarinGoRImg);
	cpKarinGo->AddComponent(cpKarinGoECCP);


	GameObject* abilTabPanelGo = new GameObject();
	abilTabPanelGo->GetComponent<Transform>()->SetPosition(D_POINT{ 360, 65 });
	RectTransform* abilTabPanelGoRcT = new RectTransform();
	abilTabPanelGoRcT->SetRect(60, 24);
	ECAbilityTabPanel* abilTabPanelGoECATP = new ECAbilityTabPanel();
	abilTabPanelGoECATP->AddObserver(goEquipChange);
	abilTabPanelGoECATP->Init();
	abilTabPanelGo->AddComponent(abilTabPanelGoRcT);
	abilTabPanelGo->AddComponent(abilTabPanelGoECATP);

	GameObject* equipTabPanelGo = new GameObject();
	equipTabPanelGo->GetComponent<Transform>()->SetPosition(D_POINT{ 423, 65 });
	RectTransform* equipTabPanelGoRcT = new RectTransform();
	equipTabPanelGoRcT->SetRect(60, 24);
	ECEquipTabPanel* equipTabPanelGoECETP = new ECEquipTabPanel();
	equipTabPanelGoECETP->AddObserver(goEquipChange);
	equipTabPanelGoECETP->Init();
	equipTabPanelGo->AddComponent(equipTabPanelGoRcT);
	equipTabPanelGo->AddComponent(equipTabPanelGoECETP);


	GameObject* abilPanelGo = new GameObject();

	GameObject* chPortraitGo = new GameObject();
	chPortraitGo->GetComponent<Transform>()->SetPosition(D_POINT{ 458, 167 });
	RectTransform* chPortraitGoRcT = new RectTransform();
	chPortraitGoRcT->SetRect(240, 176);
	RenderedImage* chPortraitGoRImg = new RenderedImage();
	chPortraitGoRImg->SetImage(IMG->FindImage(KEY_UI_PORTRAIT_KARIN_DEFAULT_SPRITE));
	chPortraitGoRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	chPortraitGoRImg->SetSortingLayer(SORTING_LAYER::UI_IMAGE);
	chPortraitGoRImg->SetOrderInLayer(uiCount++);
	chPortraitGo->AddComponent(chPortraitGoRcT);
	chPortraitGo->AddComponent(chPortraitGoRImg);

	GameObject* chLevelGo = new GameObject();
	chLevelGo->GetComponent<Transform>()->SetPosition(D_POINT{ 459, 271 });
	RectTransform* chLevelGoRcT = new RectTransform();
	chLevelGoRcT->SetRect(246, 23);
	RenderedText* chLevelGoRT = new RenderedText();
	chLevelGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	chLevelGoRT->SetOrderInLayer(uiCount++);
	chLevelGo->AddComponent(chLevelGoRcT);
	chLevelGo->AddComponent(chLevelGoRT);

	GameObject* chAbilTypeGo = new GameObject();
	chAbilTypeGo->GetComponent<Transform>()->SetPosition(D_POINT{ 361, 351 });
	RectTransform* chAbilTypeGoRcT = new RectTransform();
	chAbilTypeGoRcT->SetRect(50, 130);
	RenderedText* chAbilTypeGoRT = new RenderedText();
	chAbilTypeGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	chAbilTypeGoRT->SetOrderInLayer(uiCount++);
	chAbilTypeGoRT->SetFontSize(18);
	chAbilTypeGoRT->SetStr(L"체력(MP)\n마력(MP)\n공격력\n방어력\n지력\n마항력\n민첩성");
	chAbilTypeGo->AddComponent(chAbilTypeGoRcT);
	chAbilTypeGo->AddComponent(chAbilTypeGoRT);

	GameObject* chAbilHpFigureGo = new GameObject();
	chAbilHpFigureGo->GetComponent<Transform>()->SetPosition(D_POINT{ 436, 295 });
	RectTransform* chAbilHpFigureGoRcT = new RectTransform();
	chAbilHpFigureGoRcT->SetRect(60, 18);
	RenderedText* chAbilHpFigureGoRT = new RenderedText();
	chAbilHpFigureGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	chAbilHpFigureGoRT->SetOrderInLayer(uiCount++);
	chAbilHpFigureGoRT->SetFontSize(18);
	chAbilHpFigureGo->AddComponent(chAbilHpFigureGoRcT);
	chAbilHpFigureGo->AddComponent(chAbilHpFigureGoRT);

	GameObject* chAbilMpFigureGo = new GameObject();
	chAbilMpFigureGo->GetComponent<Transform>()->SetPosition(D_POINT{ 436, 313 });
	RectTransform* chAbilMpFigureGoRcT = new RectTransform();
	chAbilMpFigureGoRcT->SetRect(60, 18);
	RenderedText* chAbilMpFigureGoRT = new RenderedText();
	chAbilMpFigureGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	chAbilMpFigureGoRT->SetOrderInLayer(uiCount++);
	chAbilMpFigureGoRT->SetFontSize(18);
	chAbilMpFigureGo->AddComponent(chAbilMpFigureGoRcT);
	chAbilMpFigureGo->AddComponent(chAbilMpFigureGoRT);

	GameObject* chAbilStrFigureGo = new GameObject();
	chAbilStrFigureGo->GetComponent<Transform>()->SetPosition(D_POINT{ 436, 331 });
	RectTransform* chAbilStrFigureGoRcT = new RectTransform();
	chAbilStrFigureGoRcT->SetRect(60, 18);
	RenderedText* chAbilStrFigureGoRT = new RenderedText();
	chAbilStrFigureGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	chAbilStrFigureGoRT->SetOrderInLayer(uiCount++);
	chAbilStrFigureGoRT->SetFontSize(18);
	chAbilStrFigureGo->AddComponent(chAbilStrFigureGoRcT);
	chAbilStrFigureGo->AddComponent(chAbilStrFigureGoRT);

	GameObject* chAbilDefFigureGo = new GameObject();
	chAbilDefFigureGo->GetComponent<Transform>()->SetPosition(D_POINT{ 436, 349 });
	RectTransform* chAbilDefFigureGoRcT = new RectTransform();
	chAbilDefFigureGoRcT->SetRect(60, 18);
	RenderedText* chAbilDefFigureGoRT = new RenderedText();
	chAbilDefFigureGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	chAbilDefFigureGoRT->SetOrderInLayer(uiCount++);
	chAbilDefFigureGoRT->SetFontSize(18);
	chAbilDefFigureGo->AddComponent(chAbilDefFigureGoRcT);
	chAbilDefFigureGo->AddComponent(chAbilDefFigureGoRT);

	GameObject* chAbilMgcFigureGo = new GameObject();
	chAbilMgcFigureGo->GetComponent<Transform>()->SetPosition(D_POINT{ 436, 367 });
	RectTransform* chAbilMgcFigureGoRcT = new RectTransform();
	chAbilMgcFigureGoRcT->SetRect(60, 18);
	RenderedText* chAbilMgcFigureGoRT = new RenderedText();
	chAbilMgcFigureGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	chAbilMgcFigureGoRT->SetOrderInLayer(uiCount++);
	chAbilMgcFigureGoRT->SetFontSize(18);
	chAbilMgcFigureGo->AddComponent(chAbilMgcFigureGoRcT);
	chAbilMgcFigureGo->AddComponent(chAbilMgcFigureGoRT);

	GameObject* chAbilMDefFigureGo = new GameObject();
	chAbilMDefFigureGo->GetComponent<Transform>()->SetPosition(D_POINT{ 436, 385 });
	RectTransform* chAbilMDefFigureGoRcT = new RectTransform();
	chAbilMDefFigureGoRcT->SetRect(60, 18);
	RenderedText* chAbilMDefFigureGoRT = new RenderedText();
	chAbilMDefFigureGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	chAbilMDefFigureGoRT->SetOrderInLayer(uiCount++);
	chAbilMDefFigureGoRT->SetFontSize(18);
	chAbilMDefFigureGo->AddComponent(chAbilMDefFigureGoRcT);
	chAbilMDefFigureGo->AddComponent(chAbilMDefFigureGoRT);

	GameObject* chAbilDexFigureGo = new GameObject();
	chAbilDexFigureGo->GetComponent<Transform>()->SetPosition(D_POINT{ 436, 403 });
	RectTransform* chAbilDexFigureGoRcT = new RectTransform();
	chAbilDexFigureGoRcT->SetRect(60, 18);
	RenderedText* chAbilDexFigureGoRT = new RenderedText();
	chAbilDexFigureGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	chAbilDexFigureGoRT->SetOrderInLayer(uiCount++);
	chAbilDexFigureGoRT->SetFontSize(18);
	chAbilDexFigureGo->AddComponent(chAbilDexFigureGoRcT);
	chAbilDexFigureGo->AddComponent(chAbilDexFigureGoRT);

	abilPanelGo->AddGameObject(chPortraitGo);
	abilPanelGo->AddGameObject(chLevelGo);
	abilPanelGo->AddGameObject(chAbilTypeGo);

	abilPanelGo->AddGameObject(chAbilHpFigureGo);
	abilPanelGo->AddGameObject(chAbilMpFigureGo);
	abilPanelGo->AddGameObject(chAbilStrFigureGo);
	abilPanelGo->AddGameObject(chAbilDefFigureGo);
	abilPanelGo->AddGameObject(chAbilMgcFigureGo);
	abilPanelGo->AddGameObject(chAbilMDefFigureGo);
	abilPanelGo->AddGameObject(chAbilDexFigureGo);


	GameObject* equipPanelGo = new GameObject();

	GameObject* weaponTextGo = new GameObject();
	weaponTextGo->GetComponent<Transform>()->SetPosition(D_POINT{ 457, 91 });
	RectTransform* weaponTextGoRcT = new RectTransform();
	weaponTextGoRcT->SetRect(240, 24);
	RenderedText* weaponTextGoRT = new RenderedText();
	weaponTextGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	weaponTextGoRT->SetOrderInLayer(uiCount++);
	ECWeaponText* weaponTextGoECWT = new ECWeaponText();
	weaponTextGoECWT->AddObserver(goEquipChange);
	weaponTextGoECWT->Init();
	weaponTextGo->AddComponent(weaponTextGoRcT);
	weaponTextGo->AddComponent(weaponTextGoRT);
	weaponTextGo->AddComponent(weaponTextGoECWT);

	GameObject* armorTextGo = new GameObject();
	armorTextGo->GetComponent<Transform>()->SetPosition(D_POINT{ 457, 115 });
	RectTransform* armorTextGoRcT = new RectTransform();
	armorTextGoRcT->SetRect(240, 24);
	RenderedText* armorTextGoRT = new RenderedText();
	armorTextGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
	armorTextGoRT->SetOrderInLayer(uiCount++);
	ECArmorText* armorTextGoECAT = new ECArmorText();
	armorTextGoECAT->AddObserver(goEquipChange);
	armorTextGoECAT->Init();
	armorTextGo->AddComponent(armorTextGoRcT);
	armorTextGo->AddComponent(armorTextGoRT);
	armorTextGo->AddComponent(armorTextGoECAT);

	//for
	for(int i = 0; i < 3; ++i)
	{
		GameObject* equipInInvenPanelGo = new GameObject(); // 319, 265 - (174, 24) * n
		equipInInvenPanelGo->GetComponent<Transform>()->SetPosition(D_POINT{ (double)423, (double)(298 + 24 * i) });
		RectTransform* equipInInvenPanelGoRcT = new RectTransform();
		equipInInvenPanelGoRcT->SetRect(174, 24);
		RenderedText* equipInInvenPanelGoRT = new RenderedText();
		equipInInvenPanelGoRT->SetSortingLayer(SORTING_LAYER::UI_TEXT);
		equipInInvenPanelGoRT->SetOrderInLayer(uiCount++);
		ECEquipInInvenPanel* equipInInvenPanelGoECEIIP = new ECEquipInInvenPanel();
		equipInInvenPanelGoECEIIP->AddObserver(goEquipChange);
		equipInInvenPanelGoECEIIP->Init();
		equipInInvenPanelGo->AddComponent(equipInInvenPanelGoRcT);
		equipInInvenPanelGo->AddComponent(equipInInvenPanelGoRT);
		equipInInvenPanelGo->AddComponent(equipInInvenPanelGoECEIIP);

		goEquipChange->AddEuipInInvenPanel(equipInInvenPanelGoECEIIP);
		equipPanelGo->AddGameObject(equipInInvenPanelGo);
	}

	equipPanelGo->AddGameObject(weaponTextGo);
	equipPanelGo->AddGameObject(armorTextGo);


	GameObject* toShopListButtonGo = new GameObject(); // 471, 405 - (99, 28)
	toShopListButtonGo->GetComponent<Transform>()->SetPosition(D_POINT{ 537, 440 });
	RectTransform* toShopListButtonGoRcT = new RectTransform();
	toShopListButtonGoRcT->SetRect(99, 28);
	ToShopListButton* toShopListButtonGoTSLB = new ToShopListButton();
	toShopListButtonGoTSLB->AddObserver(goEquipChange);
	toShopListButtonGoTSLB->Init();
	toShopListButtonGo->AddComponent(toShopListButtonGoRcT);
	toShopListButtonGo->AddComponent(toShopListButtonGoTSLB);

	GameObject* equipChangeButtonGo = new GameObject(); // 345, 405 - (99, 28)
	equipChangeButtonGo->GetComponent<Transform>()->SetPosition(D_POINT{ 411, 440 });
	RectTransform* equipChangeButtonGoRcT = new RectTransform();
	equipChangeButtonGoRcT->SetRect(99, 28);
	EquipChangeButton* equipChangeButtonGoECB = new EquipChangeButton();
	equipChangeButtonGoECB->AddObserver(goEquipChange);
	equipChangeButtonGoECB->Init();
	equipChangeButtonGo->AddComponent(equipChangeButtonGoRcT);
	equipChangeButtonGo->AddComponent(equipChangeButtonGoECB);


	go->AddGameObject(cpAlGo);
	go->AddGameObject(cpKarinGo);
	go->AddGameObject(abilTabPanelGo);
	go->AddGameObject(equipTabPanelGo);
	go->AddGameObject(abilPanelGo);
	go->AddGameObject(equipPanelGo);
	go->AddGameObject(toShopListButtonGo);
	go->AddGameObject(equipChangeButtonGo);

	goEquipChange->SetCurCharacter(CHARACTER_ID::AL);
	goEquipChange->SetCurTab(TAB::ABILITY);
	goEquipChange->SetSelectedEquipType(EQUIP_TYPE::WEAPON);
	goEquipChange->SetSelectedEquip(EQUIP_ID::NONE);

	goEquipChange->SetAbilPanel(abilPanelGo);
	goEquipChange->SetChPortrait(chPortraitGoRImg);
	goEquipChange->SetChLevel(chLevelGoRT);
	goEquipChange->SetChAbilHpFigure(chAbilHpFigureGoRT);
	goEquipChange->SetChAbilMpFigure(chAbilMpFigureGoRT);
	goEquipChange->SetChAbilStrFigure(chAbilStrFigureGoRT);
	goEquipChange->SetChAbilDefFigure(chAbilDefFigureGoRT);
	goEquipChange->SetChAbilMgcFigure(chAbilMgcFigureGoRT);
	goEquipChange->SetChAbilMDefFigure(chAbilMDefFigureGoRT);
	goEquipChange->SetChAbilDexFigure(chAbilDexFigureGoRT);
	goEquipChange->SetEquipPanel(equipPanelGo);
	goEquipChange->SetWeaponText(weaponTextGoRT);
	goEquipChange->SetArmorText(armorTextGoRT);
	//
	goEquipChange->Init();

	return go;
}
#pragma endregion ProductBaseEquipChange


#pragma region ProductBaseTile
/*
GameObject
-RectTransform
-RenderedImage
	TilePanel(Subject)
	-RectTransform
	-RenderedImage
	-Tile
	FocusPanel
	-RectTransform
	-RenderedImage
*/
GameObject* FactoryDefaultTile::CreateObject(TILE_TYPE _type, Observer* _observer, POINT _gridPos)
{
	POINT pos = GridPosToPos(_gridPos);
	D_POINT dPos;
	if (_type == TILE_TYPE::DIRT_Z1 || _type == TILE_TYPE::GRASS_Z1)
		pos.y -= (TILE_HEIGHT_Z1 - TILE_HEIGHT_Z0);
	dPos = pos;

	GameObject* go = new GameObject();
	go->GetComponent<Transform>()->SetPosition(dPos);
	RectTransform* goRcT = new RectTransform();
	goRcT->SetRect(TILE_WIDTH, TILE_HEIGHT_Z0);
	RenderedImage* goRImg = new RenderedImage();
	if (_type == TILE_TYPE::DIRT_Z0)
		goRImg->SetImage(IMG->FindImage(KEY_TILE_DIRT_Z0_SPRITE));
	if (_type == TILE_TYPE::DIRT_Z1)
		goRImg->SetImage(IMG->FindImage(KEY_TILE_DIRT_Z1_SPRITE));
	if (_type == TILE_TYPE::GRASS_Z0)
		goRImg->SetImage(IMG->FindImage(KEY_TILE_GRASS_Z0_SPRITE));
	if (_type == TILE_TYPE::GRASS_Z1)
		goRImg->SetImage(IMG->FindImage(KEY_TILE_GRASS_Z1_SPRITE));
	goRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	goRImg->SetSortingLayer(SORTING_LAYER::TILE);
	goRImg->SetOrderInLayer(tileCount++);
	goRImg->SetByCamera(true);
	go->AddComponent(goRcT);
	go->AddComponent(goRImg);

	GameObject* tilePanelGo = new GameObject();
	tilePanelGo->GetComponent<Transform>()->SetPosition(dPos);
	RectTransform* tilePanelRcT = new RectTransform();
	tilePanelRcT->SetRect(TILE_WIDTH, TILE_HEIGHT_Z0);
	RenderedImage* tilePanelRImg = new RenderedImage();
	tilePanelRImg->SetImage(IMG->FindImage(KEY_TILE_PANEL));
	tilePanelRImg->SetAlpha(127);
	tilePanelRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	tilePanelRImg->SetSortingLayer(SORTING_LAYER::TILE_PANEL);
	tilePanelRImg->SetOrderInLayer(uiCount++);
	tilePanelRImg->SetByCamera(true);
	tilePanelRImg->SetEnabled(false);
	Tile* tile = new Tile();
	tile->SetGridPos(_gridPos);
	tile->AddObserver(_observer);
	tile->Init();
	tilePanelGo->AddComponent(tilePanelRcT);
	tilePanelGo->AddComponent(tilePanelRImg);
	tilePanelGo->AddComponent(tile);
	tilePanelGo->SetName(SKIG_TILE_TILE);
	//tilePanelGo->SetActive(false);

	GameObject* tileFocusGo = new GameObject();
	tileFocusGo->GetComponent<Transform>()->SetPosition(dPos);
	RectTransform* tileFocusRcT = new RectTransform();
	tileFocusRcT->SetRect(TILE_WIDTH, TILE_HEIGHT_Z0);
	RenderedImage* tileFocusRImg = new RenderedImage();
	tileFocusRImg->SetImage(IMG->FindImage(KEY_TILE_FOCUS));
	tileFocusRImg->SetAlpha(127);
	tileFocusRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::DEFAULT);
	tileFocusRImg->SetSortingLayer(SORTING_LAYER::TILE_FOCUS);
	tileFocusRImg->SetOrderInLayer(uiCount++);
	tileFocusRImg->SetByCamera(true);
	tileFocusRImg->SetEnabled(false);
	TileFocus* tileFocus = new TileFocus();
	tileFocus->Init();
	tileFocusGo->AddComponent(tileFocusRcT);
	tileFocusGo->AddComponent(tileFocusRImg);
	tileFocusGo->AddComponent(tileFocus);

	go->AddGameObject(tilePanelGo);
	go->AddGameObject(tileFocusGo);

	return go;
}
#pragma endregion ProductBaseTile


#pragma region ProductBaseEffect
/*
GameObject
-RenderedAnimator
*/
GameObject* FactoryEffectFlameBurst::CreateObject(POINT _gridPos)
{
	D_POINT dPos;
	dPos = GridPosToPos(_gridPos);

	GameObject* go = new GameObject();
	go->GetComponent<Transform>()->SetPosition(dPos);
	RenderedAnimator* rAnim = new RenderedAnimator();
	rAnim->SetSortingLayer(SORTING_LAYER::EFFECT);
	rAnim->SetOrderInLayer(effectCount++);
	rAnim->SetByCamera(true);
	rAnim->Init();
	FlameBurst* flameBurst = new FlameBurst();
	flameBurst->SetRAnim(rAnim);

	Animation* anim = new Animation();
	anim->Init(
		KEY_EFFECT_FLAME_BURST,
		POINT{ -70, -200 }, CHARACTER_STATE::IDLE_LEFT_BOTTOM,
		false, false, 15
	);

	rAnim->AddAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM, anim);

	go->AddComponent(rAnim);
	go->AddComponent(flameBurst);
	go->SetTag(TAG::EFFECT);

	return go;
}
#pragma endregion ProductBaseEffect


#pragma region ProductBaseHpBar
/*
GameObject
-HpBar

	Background
	-RectTransform
	-RenderedImage

	Hp
	-RectTransform
	-RenderedImage
*/
GameObject* FactoryHpBar::CreateObject()
{
	GameObject* go = new GameObject();
	go->GetComponent<Transform>()->SetPosition(D_POINT{ 70, 450 });
	HpBar* hpBar = new HpBar();
	hpBar->Init();
	go->AddComponent(hpBar);

	GameObject* background = new GameObject();
	background->GetComponent<Transform>()->SetPosition(D_POINT{ 70, 450 });
	RectTransform* bgRcT = new RectTransform();
	bgRcT->SetRect(HP_BAR_WIDTH, HP_BAR_HEIGHT);
	RenderedImage* bgRImg = new RenderedImage();
	bgRImg->SetImage(IMG->FindImage(KEY_UI_HP_BAR_BACKGROUND_SPRITE));
	bgRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::LOOP);
	bgRImg->SetByCamera(false);
	bgRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	bgRImg->SetOrderInLayer(uiCount++);
	background->AddComponent(bgRcT);
	background->AddComponent(bgRImg);
	background->SetName(SKIG_HP_BAR_BACKGROUND);

	GameObject* hp = new GameObject();
	hp->GetComponent<Transform>()->SetPosition(D_POINT{ 70, 450 });
	RectTransform* hpRcT = new RectTransform();
	hpRcT->SetRect(HP_BAR_WIDTH, HP_BAR_HEIGHT);
	RenderedImage* hpRImg = new RenderedImage();
	hpRImg->SetImage(IMG->FindImage(KEY_UI_HP_BAR_HP_SPRITE));
	hpRImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::LOOP);
	hpRImg->SetByCamera(false);
	hpRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	hpRImg->SetOrderInLayer(uiCount++);
	hp->AddComponent(hpRcT);
	hp->AddComponent(hpRImg);
	hp->SetName(SKIG_HP_BAR_HP);
	
	go->AddGameObject(background);
	go->AddGameObject(hp);

	return go;
}
#pragma endregion ProductBaseHpBar
