#pragma once
#include"v8.h"
#include"Directorywrap.h"
#include"Groupwrap.h"
#include"Userwrap.h"
#include"Sessionwrap.h"
using namespace v8;
using namespace std;
using namespace WaDirectory_View;
namespace WaDirectory_Controle{
	union DataContsyn
	{
	
		
		Directorywrap* PtDirectorywrap;

		Userwrap* PtUserwrap;

		Sessionwrap* PtSessionwrap;

		Groupwrap* PtGroupwrap;

		char* GroupId;

		char* SessionId;

		char* Password;

		char* UserId;

		char* DataPassage;

		DataContsyn(){};
	};
class DataControlesyn
{
public:
	DataControlesyn(){};
	~DataControlesyn(){};
	DataContsyn Output;
};
}