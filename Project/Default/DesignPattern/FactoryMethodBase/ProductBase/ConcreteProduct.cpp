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
#include "Script/DialogViewer/DialogViewer.h"
#include "Script/Character/Player/Player.h"
#include "Script/Character/Enemy/Enemy.h"
#include "Script/ShopList/ShopList.h"
#include "Script/Tile/Tile.h"

static int uiCount = 0;
static int characterCount = 0;
static int platformCount = 0;
static int tileCount = 0;

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


#pragma region ProductBaseBar
GameObject* FactoryDefaultBar::CreateObject(
	std::function<void()> _callBack_v_CB_v, D_POINT _pos,
	int _rectWidth, int _rectHeight, int _margin, double _rate)
{
	GameObject* go = new GameObject();
	GameObject* background = new GameObject();
	GameObject* guage = new GameObject();

	RectTransform* backRcT = new RectTransform();
	backRcT->SetRect(_rectWidth - 2 * _margin, _rectHeight - 2 * _margin);
	RenderedImage* backRImg = new RenderedImage();
	backRImg->SetImage(IMG->FindImage(KEY_UI_BAR_BACKGROUND_SPRITE));
	backRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	backRImg->SetOrderInLayer(uiCount++);
	background->AddComponent(backRcT);
	background->AddComponent(backRImg);
	background->GetComponent<Transform>()->SetPosition(_pos);
	background->SetName(SKIG_BAR_BACKGROUND);

	RectTransform* guageRcT = new RectTransform();
	guageRcT->SetRect(_rectWidth - 2 * _margin, _rectHeight - 2 * _margin);
	RenderedImage* guageRImg = new RenderedImage();
	guageRImg->SetImage(IMG->FindImage(KEY_UI_BAR_GUAGE_SPRITE));
	guageRImg->SetSortingLayer(SORTING_LAYER::UI_BACKGROUND);
	guageRImg->SetOrderInLayer(uiCount++);
	guage->AddComponent(guageRcT);
	guage->AddComponent(guageRImg);
	guage->GetComponent<Transform>()->SetPosition(_pos);
	guage->SetName(SKIG_BAR_GUAGE);

	RectTransform* goRcT = new RectTransform();
	goRcT->SetRect(_rectWidth, _rectHeight);
	Bar* goBar = new Bar();
	goBar->SetCallBack_v_CB_v(_callBack_v_CB_v);
	goBar->Init();

	go->AddComponent(goRcT);
	go->AddComponent(goBar);
	go->GetComponent<Transform>()->SetPosition(_pos);

	go->AddGameObject(background);
	go->AddGameObject(guage);

	goBar->SetRate(_rate);

	return go;
}
#pragma endregion ProductBaseBar


#pragma region ProductBasePlayer
/*
AL
-RenderedAnimator
-Player
*/
GameObject* FactoryPlayerAl::CreateObject(Observer* _observer, D_POINT _pos, POINT _gridPos)
{
	GameObject* go = new GameObject();
	D_POINT pos{ GridPosToPos(_gridPos).x, GridPosToPos(_gridPos).y };
	go->GetComponent<Transform>()->SetPosition(pos);
	//go->GetComponent<Transform>()->SetPosition(_pos);

	RenderedAnimator* rAnim = new RenderedAnimator();
	rAnim->SetSortingLayer(SORTING_LAYER::PLAYER);
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
		POINT{ -40, -68 }, CHARACTER_STATE::ATTACK_LEFT_BOTTOM,
		false, false, 6
	);
	Animation* attackLeftTop = new Animation();
	attackLeftTop->Init(
		KEY_AL_ATTACK_LEFT_TOP,
		POINT{ -40, -68 }, CHARACTER_STATE::ATTACK_LEFT_TOP,
		false, false, 6
	);
	Animation* attackRightBottom = new Animation();
	attackRightBottom->Init(
		KEY_AL_ATTACK_RIGHT_BOTTOM,
		POINT{ -40, -68 }, CHARACTER_STATE::ATTACK_RIGHT_BOTTOM,
		false, false, 6
	);
	Animation* attackRightTop = new Animation();
	attackRightTop->Init(
		KEY_AL_ATTACK_RIGHT_TOP,
		POINT{ -40, -68 }, CHARACTER_STATE::ATTACK_RIGHT_TOP,
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
	player->Init();

	go->AddComponent(rAnim);
	go->AddComponent(player);
	go->SetTag(TAG::PLAYER);

	return go;
}

GameObject* FactoryPlayerKarin::CreateObject(Observer* _observer, D_POINT _pos, POINT _gridPos)
{
	GameObject* go = new GameObject();
	D_POINT pos{ GridPosToPos(_gridPos).x, GridPosToPos(_gridPos).y };
	go->GetComponent<Transform>()->SetPosition(pos);
	//go->GetComponent<Transform>()->SetPosition(_pos);

	RenderedAnimator* rAnim = new RenderedAnimator();
	rAnim->SetSortingLayer(SORTING_LAYER::PLAYER);
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
		POINT{ -34, -72 }, CHARACTER_STATE::ATTACK_LEFT_BOTTOM,
		false, false, 6
	);
	Animation* attackLeftTop = new Animation();
	attackLeftTop->Init(
		KEY_KARIN_ATTACK_LEFT_TOP,
		POINT{ -34, -72 }, CHARACTER_STATE::ATTACK_LEFT_TOP,
		false, false, 6
	);
	Animation* attackRightBottom = new Animation();
	attackRightBottom->Init(
		KEY_KARIN_ATTACK_RIGHT_BOTTOM,
		POINT{ -34, -72 }, CHARACTER_STATE::ATTACK_RIGHT_BOTTOM,
		false, false, 6
	);
	Animation* attackRightTop = new Animation();
	attackRightTop->Init(
		KEY_KARIN_ATTACK_RIGHT_TOP,
		POINT{ -34, -72 }, CHARACTER_STATE::ATTACK_RIGHT_TOP,
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
	player->Init();

	go->AddComponent(rAnim);
	go->AddComponent(player);
	go->SetTag(TAG::PLAYER);

	return go;
}
#pragma endregion ProductBasePlayer


#pragma region ProductBaseEnemy
/*
Slime
-RenderedAnimator
-Enemy
*/
GameObject* FactoryEnemySlime::CreateObject(Observer* _observer, D_POINT _pos, POINT _gridPos)
{
	GameObject* go = new GameObject();
	D_POINT pos{ GridPosToPos(_gridPos).x, GridPosToPos(_gridPos).y };
	go->GetComponent<Transform>()->SetPosition(pos);

	RenderedAnimator* rAnim = new RenderedAnimator();
	rAnim->SetSortingLayer(SORTING_LAYER::ENEMY);
	rAnim->SetOrderInLayer(characterCount++);
	rAnim->SetByCamera(true);
	rAnim->Init();

	Animation* idle = new Animation();
	idle->Init(
		KEY_SLIME_IDLE,
		POINT{ -21, -38 }, CHARACTER_STATE::IDLE_LEFT_BOTTOM,
		true, false, 6
	);
	Animation* move = new Animation();
	move->Init(
		KEY_SLIME_MOVE,
		POINT{ -21, -38 }, CHARACTER_STATE::MOVE_LEFT_BOTTOM,
		true, false, 6
	);

	rAnim->AddAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM, idle);
	rAnim->AddAnimation(CHARACTER_STATE::MOVE_LEFT_BOTTOM, move);

	rAnim->ChangeAnimation(CHARACTER_STATE::IDLE_LEFT_BOTTOM);

	Enemy* enemy = new Enemy();
	enemy->AddObserver(_observer);
	enemy->SetGridPos(_gridPos);
	enemy->Init();

	go->AddComponent(rAnim);
	go->AddComponent(enemy);
	go->SetTag(TAG::ENEMY);

	return go;
}
#pragma endregion ProductBaseEnemy


#pragma region ProductBasePlatform
GameObject* FactoryDefaultPlatform::CreateObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _sprite)
{
	GameObject* go = new GameObject();

	RectTransform* rcT = new RectTransform();
	rcT->SetRect(_rectWidth, _rectHeight);

	RenderedImage* rImg = new RenderedImage();
	rImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::LOOP);
	rImg->SetImage(_sprite);
	rImg->SetSortingLayer(SORTING_LAYER::PLATFORM);
	rImg->SetOrderInLayer(platformCount++);

	Collider* col = new Collider();

	go->GetComponent<Transform>()->SetPosition(_pos);

	go->AddComponent(rcT);
	go->AddComponent(rImg);
	go->AddComponent(col);

	return go;
}
#pragma endregion ProductBasePlatform


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
	-Button
	-RectTransform(112, 21)
	-RenderedImage

	ExitButton
	-Button
	-RectTransform(112, 21)
	-RenderedImage
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

	go->AddGameObject(descriptionGo);
	go->AddGameObject(goldGo);
	go->AddGameObject(buyButtonGo);
	go->AddGameObject(exitButtonGo);

	return go;
}
#pragma endregion ProductBaseShopList


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

