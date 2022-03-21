#pragma once

#include "json.h"

class JsonManager : public SingletonBase<JsonManager>
{
private:
public:
	JsonManager();
	virtual ~JsonManager();

	HRESULT Init();
	void Release();

	bool LoadFileEx();
	bool SaveFileEx();
};