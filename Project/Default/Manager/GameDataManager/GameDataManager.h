#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class CharacterInfo
{
public:
	CHARACTER_ID id;
	bool isMember;
	int level;
	int hp;
	int hpMax;
	int str;
	int mgc;
	int def;
	int mDef;
	int dex;
	int exp;
	int expMax;

	EQUIP_ID weapon;
	EQUIP_ID armor;
public:
	void Print()
	{
		std::wcout << "\t**********" << std::endl
			<< L"\tid : " << (int)id << std::endl
			<< L"\tisMember : " << isMember << std::endl
			<< L"\tlevel : " << level << std::endl
			<< L"\thp : " << hp << L" / " << hpMax << std::endl
			<< L"\tstr : " << str << std::endl
			<< L"\tmgc : " << mgc << std::endl
			<< L"\tdef : " << def << std::endl
			<< L"\tmDef : " << mDef << std::endl
			<< L"\tdex : " << dex << std::endl
			<< L"\texp : " << exp << std::endl
			<< L"\texpMax : " << expMax << std::endl
			<< L"\tweapon : " << (int)weapon << std::endl
			<< L"\tarmor : " << (int)armor << std::endl
			<< "\t**********" << std::endl;
	}
};

class EquipInfo
{
public:
	EQUIP_ID id;
	std::wstring name;
	int priceBuy;
	int priceSell;
	int level;
	int str;
	int mgc;
	int def;
	int mDef;
public:
	void Print()
	{
		std::wcout << "\t**********" << std::endl 
			<< L"\tid : " << (int)id << std::endl
			<< L"\tname : " << name << std::endl
			<< L"\tprice buy : " << priceBuy << std::endl
			<< L"\tprice sell : " << priceSell << std::endl
			<< L"\tlevel : " << level << std::endl
			<< L"\tstr : " << str << std::endl
			<< L"\tmgc : " << mgc << std::endl
			<< L"\tdef : " << def << std::endl
			<< L"\tmdef : " << mDef << std::endl
			<< "\t**********" << std::endl;
	}
};

class GameDataManager : public SingletonBase<GameDataManager>
{
private:
	int processivity;
	float volume;

	std::vector<CharacterInfo> characterInfoVec;
	std::vector<EquipInfo> equipInfoVec;
protected:
public:
	GameDataManager();
	virtual ~GameDataManager();

	HRESULT Init();
	void Release();

	int		GetProcessivity() const		{ return processivity; }
	void	SetProcessivity(int _pro)	{ processivity = _pro; }
	float	GetVolume() const			{ return volume; }
	void	SetVolume(float _volume)	{ volume = _volume; }
	CharacterInfo	GetCharacterInfo(CHARACTER_ID _id) const;
	void			SetCharacterInfo(CHARACTER_ID _id, CharacterInfo _info);
};