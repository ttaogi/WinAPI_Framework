#pragma once

#include "DesignPattern/ComponentBase/Component/Behaviour/Behaviour.h"
#include "Utility/Enums/Enums.h"

class Rendered : virtual public Behaviour
{
private:
	SORTING_LAYER sortingLayer;
	int orderInLayer;
protected:
public:
	Rendered();
	virtual ~Rendered();

	virtual void Operation() override;

	virtual void Render(HDC _hdc) = 0;

	SORTING_LAYER	GetSortingLayer() const					{ return sortingLayer; }
	void			SetSortingLayer(SORTING_LAYER _layer)	{ sortingLayer = _layer; }
	int		GetOrderInLayer() const		{ return orderInLayer; }
	void	SetOrderInLayer(int _order)	{ orderInLayer = _order; }
};

struct CmpRenderedPtr
{
	bool operator()(const Rendered* lhs, const Rendered* rhs) const
	{
		if (lhs->GetSortingLayer() == rhs->GetSortingLayer())
			return lhs->GetOrderInLayer() > rhs->GetOrderInLayer();
		else
			return (int)(lhs->GetSortingLayer()) > (int)(rhs->GetSortingLayer());
	}
};
