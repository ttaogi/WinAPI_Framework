#include "Stdafx/stdafx.h"

#include "Factory.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "DesignPattern/ComponentBase/Component/Bar/Bar.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/Collider/Collider.h"
#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Rigidbody/Rigidbody.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "Image/Image.h"
#include "Player/Player.h"

#pragma region FactoryButton
GameObject* ButtonFactory::GetObject(
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

	go->GetComponent<Transform>()->SetPosition(_pos);

	go->AddComponent(btn);
	go->AddComponent(rcT);
	go->AddComponent(rImg);

	return go;
}
#pragma endregion FactoryButton

#pragma region FactoryBar
GameObject* BarFactory::GetObject(
	std::function<void()> _callBack_v_CB_v, D_POINT _pos,
	int _rectWidth, int _rectHeight, int _margin, double _rate)
{
	GameObject* go = new GameObject();
	GameObject* background = new GameObject();
	GameObject* guage = new GameObject();

	RectTransform* backRcT = new RectTransform();
	backRcT->SetRect(_rectWidth - 2 * _margin, _rectHeight - 2 * _margin);
	RenderedImage* backRImg = new RenderedImage();
	backRImg->SetImage(IMG->FindImage(KEY_UI_BAR_BACKGROUND_STRIPE));
	background->AddComponent(backRcT);
	background->AddComponent(backRImg);
	background->GetComponent<Transform>()->SetPosition(_pos);
	background->SetName(SKIG_BAR_BACKGROUND);

	RectTransform* guageRcT = new RectTransform();
	guageRcT->SetRect(_rectWidth - 2 * _margin, _rectHeight - 2 * _margin);
	RenderedImage* guageRImg = new RenderedImage();
	guageRImg->SetImage(IMG->FindImage(KEY_UI_BAR_GUAGE_STRIPE));
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
#pragma endregion FactoryBar

#pragma region FactoryPlayer
GameObject* PlayerFactory::GetObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe)
{
	GameObject* go = new GameObject();

	Player* player = new Player();
	player->Init();

	RectTransform* rcT = new RectTransform();
	rcT->SetRect(_rectWidth, _rectHeight);

	RenderedImage* rImg = new RenderedImage();
	rImg->SetImage(_stripe);

	Rigidbody* rb = new Rigidbody();

	Collider* col = new Collider();

	go->GetComponent<Transform>()->SetPosition(_pos);

	go->AddComponent(player);
	go->AddComponent(rcT);
	go->AddComponent(rImg);
	go->AddComponent(rb);
	go->AddComponent(col);

	return go;
}
#pragma endregion FactoryPlayer

#pragma region FactoryPlatform
GameObject* PlatformFactory::GetObject(D_POINT _pos, int _rectWidth, int _rectHeight, Image* _stripe)
{
	GameObject* go = new GameObject();

	RectTransform* rcT = new RectTransform();
	rcT->SetRect(_rectWidth, _rectHeight);

	RenderedImage* rImg = new RenderedImage();
	rImg->SetRenderingType(RENDERED_IMAGE_RENDERING_TYPE::LOOP);
	rImg->SetImage(_stripe);

	Collider* col = new Collider();

	go->GetComponent<Transform>()->SetPosition(_pos);

	go->AddComponent(rcT);
	go->AddComponent(rImg);
	go->AddComponent(col);

	return go;
}
#pragma endregion FactoryPlatform
