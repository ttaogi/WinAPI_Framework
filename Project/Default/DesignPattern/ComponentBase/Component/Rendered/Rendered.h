#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/Behaviour.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "Utility/Enums/Enums.h"

class Rendered : virtual public Behaviour
{
private:
	SORTING_LAYER sortingLayer;
	int orderInLayer;
protected:
	bool byCamera;
public:
	Rendered();
	virtual ~Rendered();

	virtual void Operation() override;

	virtual void Render(HDC _hdc) = 0;

	SORTING_LAYER	GetSortingLayer() const					{ return sortingLayer; }
	void			SetSortingLayer(SORTING_LAYER _layer)	{ sortingLayer = _layer; }
	int		GetOrderInLayer() const		{ return orderInLayer; }
	void	SetOrderInLayer(int _order)	{ orderInLayer = _order; }
	bool	GetByCamera() const			{ return byCamera; }
	void	SetByCamera(bool _byCamera) { byCamera = _byCamera; }
};

struct CmpRenderedPtr
{
	bool operator()(const Rendered* lhs, const Rendered* rhs) const
	{
		if (lhs->GetSortingLayer() == rhs->GetSortingLayer())
		{
			POINT lPos = lhs->transform->GetPosition().ToPoint();
			POINT rPos = rhs->transform->GetPosition().ToPoint();
			if (lPos.y == rPos.y)
				return lhs->GetOrderInLayer() > rhs->GetOrderInLayer();
			else
				return lPos.y > rPos.y;
		}
		else
			return (int)(lhs->GetSortingLayer()) > (int)(rhs->GetSortingLayer());
	}
};
