#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class DialogInfo
{
public:
	bool upper;
	std::wstring stripeKey;
	std::wstring name;
	std::wstring text;
public:
	DialogInfo();
	DialogInfo(bool _upper, std::wstring _stripeKey, std::wstring _name, std::wstring _text);

	void Print() const;
};

class DialogCycle
{
public:
	int cycleIdx;
	std::wstring cycleName;
	std::vector<DialogInfo> cycle;
public:
	DialogCycle();

	void Print() const;
};

class DialogProcessivityMap
{
public:
	std::map<int, DialogCycle> dialogMap;
	DialogCycle defaultDialog;
public:
	DialogProcessivityMap();

	DialogCycle GetDialogCycle(int _processivity);

	void Print() const;
};

class DialogManager : public SingletonBase<DialogManager>
{
private:
	std::map<std::wstring, DialogProcessivityMap> dialogDB;
protected:
public:
	DialogManager();
	virtual ~DialogManager();

	HRESULT Init();
	void Release();

	DialogCycle GetDialogCycle(std::wstring _spot, int _processivity);

	void Print() const;
};