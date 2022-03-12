#pragma once

#include "json.h"

class JsonManager : public SingletonBase<JsonManager>
{
private:
public:
	JsonManager();
	~JsonManager();

	HRESULT Init();
	void Release();

	bool LoadFileEx();
	bool SaveFileEx();
};