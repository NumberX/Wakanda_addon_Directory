#pragma once
#include"v8.h"
#include"DirectorywrapAsynchro.h"
#include"GroupwrapAsynchro.h"
#include"UserwrapAsynchro.h"
#include"SessionwrapAsynchro.h"
using namespace v8;
using namespace std;
using namespace WaDirectorywrapAsynchro_data_v8;
namespace WaDirectorywrapAsynchro_data_v8{
	union DataCont
	{
	
		
		DirectorywrapAsynchro* PtDirectorywrapAsynchro;

		UserwrapAsynchro* PtUserwrapAsynchro;

		SessionwrapAsynchro* PtSessionwrapAsynchro;

		GroupwrapAsynchro* PtGroupwrapAsynchro;

		char* GroupId;

		char* SessionId;

		char* Password;

		char* UserId;

		char* DataPassage;

		DataCont(){};
	};
class DataControle
{
public:
	DataControle(){};
	~DataControle(){};
	DataCont Output;
};
}
