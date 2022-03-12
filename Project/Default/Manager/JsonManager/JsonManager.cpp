#include "Stdafx/stdafx.h"

#include "Manager/JsonManager/JsonManager.h"

#include <iostream>
#include <fstream>
#include <istream>

const wstring EX_FILE_DIR = L"ex����.json";

JsonManager::JsonManager() { }

JsonManager::~JsonManager() { }

HRESULT JsonManager::Init()
{
	LoadFileEx();

	return S_OK;
}

void JsonManager::Release()
{
	SaveFileEx();
}

bool JsonManager::LoadFileEx()
{
	string fileDir = WcsToMbsKorean(EX_FILE_DIR);

	ifstream json_dir(fileDir);
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value value;

	JSONCPP_STRING errs;
	bool ok = parseFromStream(builder, json_dir, &value, &errs);

	if (ok)
	{
		cout << "CPU: " << value["CPU"] << endl;
		cout << "Program Python: " << value["Program"]["Python"] << endl;
		cout << "Computer Cable: " << value["Computer"]["Cable"] << endl;
		cout << "Computer Cable[0]: " << value["Computer"]["Cable"][0] << endl;
		cout << endl;

		// "Int" ���� ������ -1 ��ȯ.
		cout << "Computer Number Int(as int): " << value["Computer"]["Number"].get("Int", -1).asInt() << endl;
		// "Int" ���� ������ 0 ��ȯ.
		cout << "Computer Number Int(as int): " << value["Computer"]["Number"]["Int"].asInt() << endl;
		// "Double" ���� ������ -1 ��ȯ.
		cout << "Computer Number Double(as double): " << value["Computer"]["Number"].get("Double", -1).asDouble() << endl;
		// "Double" ���� ������ Empty ��ȯ.
		cout << "Computer Number Double(as string): " << value["Computer"]["Number"].get("Double", "Empty").asString() << endl;
		// "Bool" ���� ������ false ��ȯ.
		cout << "Computer Number Bool(as bool): " << value["Computer"]["Number"].get("Bool", false).asBool() << endl;
		cout << endl;

		cout << "Root size: " << value.size() << endl;
		cout << "Program size: " << value["Program"].size() << endl;
		cout << "Computer Cable size: " << value["Computer"]["Cable"].size() << endl;
		cout << endl;

		// size() ���� for ������ �״�� ���ϸ� warning C4018�� �߻� �Ѵ�.
		int size = value["Computer"]["Cable"].size();
		for (int i = 0; i < size; i++)
			cout << "Computer Cable: " << value["Computer"]["Cable"][i] << endl;
		cout << endl;

		for (auto i : value["Computer"]["Cable"])
			cout << "Computer Cable: " << i << endl;
	}
	else
	{
		wcout << L"JsonManager LoadFileEx() failed." << endl;
		return false;
	}

	return true;
}

bool JsonManager::SaveFileEx()
{
	string fileDir = WcsToMbsKorean(EX_FILE_DIR);

	ofstream json_file;
	json_file.open(fileDir);

	Json::Value Computer;
	Computer["CPU"] = "I7";
	Computer["RAM"] = "16G";

	Json::Value Language;
	Language["C++"] = "Visual Studio";
	Language["Python"] = "IDLE";

	Computer["Program"] = Language;
	Computer["HDD"] = "2TB";

	Json::Value Cable;
	Cable.append("Power");
	Cable.append("Printer");
	Cable.append("Mouse");

	Computer["Computer"]["Cable"] = Cable;

	Json::Value number;
	number["Int"] = 123;
	number["Double"] = 456.012;
	number["Bool"] = true;

	Computer["Computer"]["Number"] = number;

	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = " "; // Tab
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	// ���ĺ� ������ write �ȴ�.
	writer->write(Computer, &cout);
	writer->write(Computer, &json_file);
	cout << endl; // add lf and flush.

	json_file.close();

	return true;
}
