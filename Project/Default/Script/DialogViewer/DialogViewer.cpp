#include "Stdafx/stdafx.h"

#include "Script/DialogViewer/DialogViewer.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedText/RenderedText.h"

DialogViewer::DialogViewer()
	: Component((const Component_ID)typeid(DialogViewer).name())
{
	upper = lower = NULL;
}

DialogViewer::~DialogViewer() { }

void DialogViewer::Operation() { }

void DialogViewer::Init()
{
	if (cycle.cycle.size() > 0)
	{
		DialogInfo dialog = cycle.cycle[0];

		if (dialog.upper)
		{
			upper->GetGameObjectByName(SKIG_DIALOG_VIEWER_PORTRAIT)->GetComponent<RenderedImage>()
				->SetImage(IMG->FindImage(dialog.spriteKey));
			upper->GetGameObjectByName(SKIG_DIALOG_VIEWER_TEXT)->GetComponent<RenderedText>()
				->SetStr(dialog.text);
		}
		else
		{
			lower->GetGameObjectByName(SKIG_DIALOG_VIEWER_PORTRAIT)->GetComponent<RenderedImage>()
				->SetImage(IMG->FindImage(dialog.spriteKey));
			lower->GetGameObjectByName(SKIG_DIALOG_VIEWER_TEXT)->GetComponent<RenderedText>()
				->SetStr(dialog.text);
		}
	}
}

void DialogViewer::FixedUpdate() { }

void DialogViewer::Update()
{
	if (!enabled) return;

	if (GAMEMANAGER->GetPhase() == PHASE::PHASE_DIALOG && MOUSE_CLICKED)
	{
		Notify(EVENT::DIALOG_CLICK);
		MOUSE_CLICKED = false;
	}
}

void DialogViewer::LateUpdate() { }

void DialogViewer::OnCollision(Collision _col) { }

void DialogViewer::Next()
{
	if (cycle.cycleIdx < (int)cycle.cycle.size() - 1)
	{
		++cycle.cycleIdx;

		if (cycle.cycle[cycle.cycleIdx].upper)
		{
			upper->GetGameObjectByName(SKIG_DIALOG_VIEWER_PORTRAIT)->GetComponent<RenderedImage>()
				->SetImage(IMG->FindImage(cycle.cycle[cycle.cycleIdx].spriteKey));
			upper->GetGameObjectByName(SKIG_DIALOG_VIEWER_TEXT)->GetComponent<RenderedText>()
				->SetStr(cycle.cycle[cycle.cycleIdx].text);
		}
		else
		{
			lower->GetGameObjectByName(SKIG_DIALOG_VIEWER_PORTRAIT)->GetComponent<RenderedImage>()
				->SetImage(IMG->FindImage(cycle.cycle[cycle.cycleIdx].spriteKey));
			lower->GetGameObjectByName(SKIG_DIALOG_VIEWER_TEXT)->GetComponent<RenderedText>()
				->SetStr(cycle.cycle[cycle.cycleIdx].text);
		}
	}
}

bool DialogViewer::IsEnd()
{
	return cycle.cycleIdx == (int)cycle.cycle.size() - 1;
}
