#pragma once
#include"v8.h"
#include"Directorywrap.h"
#include"Groupwrap.h"
#include"Userwrap.h"
#include"Sessionwrap.h"
using namespace v8;
using namespace std;
using namespace WaDirectorywrap_data_v8;
namespace WaDirectorywrap_data_v8{
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